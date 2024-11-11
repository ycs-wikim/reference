#include "Function.h"

int Function::penNum = 0;
LINFO Function::drawLInfo = { };
HWND Function::hWnd = nullptr;
int Function::bShape = BASIC;
int Function::stampID = BASIC;
HICON hIcon;
HICON replayhIcon;

void Function::record(PINFO inputPI)
{
    //if (isReplay) return;

	inputPI.bShape = bShape;
	inputPI.pWidth = currentThickness;
	inputPI.stampValue = stampID;

	drawLInfo.pInfo.push_back(inputPI);

    /*std::wstring message = L"record() 호출됨, drawLInfo.pInfo 크기: " + std::to_wstring(drawLInfo.pInfo.size()) +
       L"\nFunction 객체 주소: " + std::to_wstring((uintptr_t)this);
    MessageBox(nullptr, message.c_str(), L"디버깅: record", MB_OK); */



}

void Function::draw(HWND hWnd, PINFO dInfo, bool isRecord) // 뒤에 브러쉬 추가
{
    hdc = GetDC(hWnd);

    if (isLeftClick)
    {
        px = LOWORD(dInfo.lParam); // 그리기 시작한 좌표
        py = HIWORD(dInfo.lParam);

        currentTime = std::chrono::steady_clock::now(); // 그리기 시간 저장

		setPenStyle(dInfo, dInfo.pColor);

		if (isReplay) {
			if (dInfo.bShape != STAMP)
			{
				MoveToEx(hdc, x, y, NULL);
				LineTo(hdc, px, py);
				DeleteObject(nPen);
			}
			else if (dInfo.bShape == STAMP && dInfo.state == WM_LBUTTONDOWN) {
				replayhIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(dInfo.stampValue), IMAGE_ICON, 124, 124, 0); // 스탬프 아이콘 설정
				DrawIconEx(hdc, x - 60, y - 60, replayhIcon, 120, 120, 0, NULL, DI_NORMAL);
				DestroyIcon(replayhIcon);
			}
		}
		else if (stampOn && dInfo.state == WM_LBUTTONDOWN) {
			DrawIconEx(hdc, x - 60, y - 60, hIcon, 120, 120, 0, NULL, DI_NORMAL);
			DestroyIcon(hIcon);
			DeleteObject(nPen);
		}
		else if (stampOn == false && dInfo.state == WM_MOUSEMOVE) {
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, px, py);
		}

        x = px;
        y = py;

        DrawTime = currentTime; // 마지막 시간 업데이트

        if (isRecord)
            record(dInfo);

    }
    ReleaseDC(hWnd, hdc);

}

void Function::re_draw(HDC phdc, PINFO dInfo, HWND hd) // 뒤에 브러쉬 추가
{
    hdc = phdc;

    if (isLeftClick)
    {
        px = LOWORD(dInfo.lParam); // 그리기 시작한 좌표
        py = HIWORD(dInfo.lParam);

        setPenStyle(dInfo, dInfo.pColor);

		if (dInfo.bShape == STAMP && dInfo.state == WM_LBUTTONDOWN) {
			replayhIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(dInfo.stampValue), IMAGE_ICON, 124, 124, 0); // 스탬프 아이콘 설정
			DrawIconEx(hdc, x - 60, y - 60, replayhIcon, 120, 120, 0, NULL, DI_NORMAL);
			DestroyIcon(replayhIcon);
			DestroyIcon(hIcon);
		}
		else if (stampOn == false && dInfo.state == WM_MOUSEMOVE) {
			if (dInfo.bShape == SPRAY || dInfo.bShape == WATERCOLOR || dInfo.bShape == PENCIL)
			{
				//SetPixel(hdc, px, py, RGB(255, 255, 255));
			}
			else
			{
				MoveToEx(hdc, x, y, NULL);
				if (dInfo.bShape == BASIC || dInfo.bShape == BRUSH) {
					LineTo(hdc, px, py);
				}
				DeleteObject(nPen);
			}
		}

        x = px;
        y = py;


    }

}


void Function::mouseUD(PINFO dInfo, bool isRecord)
{
    if (dInfo.state == WM_LBUTTONDOWN)
    {

        x = LOWORD(dInfo.lParam); //좌클릭 한 좌표
        y = HIWORD(dInfo.lParam);

        DrawTime = std::chrono::steady_clock::now(); // 붓 브러쉬 사용을 위한 그리는 시작 시간 저장.      
        lastThicknessChangeTime = DrawTime; // 두께 변경 시간 초기화
        currentThickness = dInfo.pWidth; // 붓 전용 펜 사이즈.


        isLeftClick = true;
    }
    else
    {
        isLeftClick = false;
    }


    if (isRecord)
        record(dInfo);

}

void Function::replayThread(HWND hWnd)
{
    setIsReplay(true);
    setIsReset(false);

    // std::thread를 사용하여 스레드 시작
    replayThreadHandle = std::thread(&Function::replay, this, hWnd);

    threadHandle = replayThreadHandle.native_handle();
}


//기본 리플레이 동작 함수
void Function::replay(HWND hWnd)
{

    GetClientRect(hWnd, &clientRect);  // 클라이언트 영역 크기 얻기

    while (isReplay)
    {
        // 화면 초기화
        InvalidateRect(hWnd, NULL, TRUE);
        UpdateWindow(hWnd);

        // 화면 DC 가져오기
        hdc = GetDC(hWnd);

        for (size_t i = 0; i < drawLInfo.pInfo.size(); i++)
        {
            if (!isReplay)
            {
                isLeftClick = false;
                break;
            }
            else
                isLeftClick = true;

            PINFO replayInfo = drawLInfo.pInfo[i];

            setBShape(replayInfo.bShape);

			switch (replayInfo.state)
			{
			case WM_LBUTTONDOWN:
				mouseUD(replayInfo, false);
				if (replayInfo.bShape == STAMP) {
					draw(hWnd, replayInfo, false);
				}
				break;

            case WM_MOUSEMOVE:
                draw(hWnd, replayInfo, false);
                break;

            case WM_LBUTTONUP:
                mouseUD(replayInfo, false);
                break;

            default:
                break;
            }

            // 재생 속도 조절
            if (i + 1 < drawLInfo.pInfo.size() && drawLInfo.pInfo[i + 1].state == WM_MOUSEMOVE)
            {
                Sleep((int)((drawLInfo.pInfo[i + 1].pTime - drawLInfo.pInfo[i].pTime) / 10));
            }

            DeleteObject(nPen);
        }
        ReleaseDC(hWnd, hdc);
        // 반복 간격 조절
        Sleep(500);
    }

}


// RESET 버튼 클릭 시 작동되는 함수 (원래 형태로 복원)
void Function::reDrawing(HWND hWnd)
{
    if (replayThreadHandle.joinable())
    {
        isReplay = false;
        ResumeThread(threadHandle);
        stopReplay(WndFunc::canvasWnd);
    }

    InvalidateRect(WndFunc::canvasWnd, NULL, TRUE);
    UpdateWindow(WndFunc::canvasWnd);

    //MessageBox(hWnd, L"reDrawing", L"dd", MB_OK);
}

void Function::clearDrawing(HWND hWnd)
{
    if (replayThreadHandle.joinable())
    {
        isReplay = false;
        ResumeThread(threadHandle);
        stopReplay(WndFunc::canvasWnd);
    }

    // 기록 삭제
    drawLInfo.pInfo.clear();

    // 화면 초기화
    InvalidateRect(hWnd, NULL, TRUE);
    UpdateWindow(hWnd);
}

void Function::setPenStyle(PINFO dinfo, COLORREF col)
{
	// 브러쉬 선택하면 거기에 맞는 펜 제공
	switch (bShape)
	{
	case BASIC: // 기본 그리기
		nPen = CreatePen(PS_SOLID, dinfo.pWidth, col);
		oPen = (HPEN)SelectObject(hdc, nPen);
		stampOn = false; // 스탬프 모드 비활성화
		break;

    case BRUSH: // 붓 브러쉬
    {
        if (!isReplay || isReset)
        {
            int pwidth = dinfo.pWidth;
            if (dinfo.pWidth < 8) { pwidth = 7; }
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - DrawTime).count(); //눌렀을 떄 시간부터 그렸을 때 시간 그 사이의 시간(밀리초)
            duration = max(duration, 1); // 최소 duration 값을 설정하여 0으로 나누는 문제 방지

            double distance = sqrt(pow(px - x, 2) + pow(py - y, 2)); // 선 거리
            double speed = (distance / duration) * 1000; // 속도 계산

            int targetThickness = pwidth; // 속도가 변경될 때 같이 변경 되는 두께 변수

            // 속도가 빠를 때 두께 줄이기
            if (speed > Threshold_Speed) {
                targetThickness = pwidth - (int)((speed - Threshold_Speed) / (Threshold_Speed / (pwidth - Min_Thickness + 1)));
                targetThickness = max(targetThickness, Min_Thickness);
            }
            // 속도가 느릴 때 두께 늘리기
            else {
                targetThickness = Min_Thickness + (int)((Threshold_Speed - speed) / (Threshold_Speed / (pwidth - Min_Thickness + 1)));
                targetThickness = min(targetThickness, pwidth);
            }

            // 두께 변화 간격이 지났는지 확인      
            if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastThicknessChangeTime).count() >= Update_Interval)
            {
                // 붓 전용 사이즈 조절
                if (currentThickness < targetThickness)
                    currentThickness += Smoothing_Factor;
                else if (currentThickness > targetThickness)
                    currentThickness -= Smoothing_Factor;

				// 두께 변경 시간 업데이트
				lastThicknessChangeTime = currentTime;
			}
			// 두께가 변경된 펜 생성
			nPen = CreatePen(PS_SOLID, currentThickness, col);
		}
		else  // 리플레이 중에는 두께를 고정
		{
			nPen = CreatePen(PS_SOLID, dinfo.pWidth, col);  // 그릴 때 저장된 두께 사용
		}
		oPen = (HPEN)SelectObject(hdc, nPen);
		stampOn = false; // 스탬프 모드 비활성화
		break;
	}

	case PENCIL:
	{
		Gdiplus::Graphics graphics(hdc);
		int alpha = 35; // 기본 투명도 설정    		
		Gdiplus::PointF points[60]; // 도형 꼭짓점 갯수
		for (int i = 0; i < 60; ++i)
		{
			INT angle = rand() % 6 * 3.14159f * i / 80; // 꼭짓점 좌표 
			points[i] = Gdiplus::PointF(x + dinfo.pWidth * cos(angle) / 1.2, y + dinfo.pWidth * sin(angle) / 1.2); // 꼭짓점 설정
		}
		Gdiplus::SolidBrush brush(Gdiplus::Color(alpha, GetRValue(col), GetGValue(col), GetBValue(col)));	// 색상 설정
		graphics.FillPolygon(&brush, points, 60); // 정형화 되지 않는 도형 그리기	
		ReleaseDC(hWnd, hdc);
		stampOn = false; // 스탬프 모드 비활성화
		break;
	}

	case SPRAY: // 스프레이 (점을 흩뿌림)
		int spray_pixel;
		if (dinfo.pWidth <= 3) { spray_pixel = 70; } // 팬 굵기에 따른 점 뿌리는 밀도
		else if (dinfo.pWidth >= 4 && dinfo.pWidth <= 6) { spray_pixel = 180; }
		else if (dinfo.pWidth >= 7 && dinfo.pWidth <= 10) { spray_pixel = 290; }
		else if (dinfo.pWidth >= 11 && dinfo.pWidth <= 14) { spray_pixel = 400; }
		else if (dinfo.pWidth >= 15 && dinfo.pWidth <= 20) { spray_pixel = 510; }
		else if (dinfo.pWidth >= 21 && dinfo.pWidth <= 25) { spray_pixel = 620; }
		for (int i = 0; i < spray_pixel; ++i)
		{
			int offsetX = (rand() % (dinfo.pWidth * 8)) - (dinfo.pWidth * 4);
			int offsetY = (rand() % (dinfo.pWidth * 8)) - (dinfo.pWidth * 4);
			if (sqrt(offsetX * offsetX + offsetY * offsetY) <= dinfo.pWidth * 4)
			{
				SetPixel(hdc, x + offsetX, y + offsetY, col);
			}
		}
		ReleaseDC(hWnd, hdc);
		stampOn = false; // 스탬프 모드 비활성화
		break;

	case MARKER: //삭제 
	{
		Gdiplus::Graphics graphics(hdc);
		Gdiplus::SolidBrush marker(Gdiplus::Color(40, GetRValue(col), GetGValue(col), GetBValue(col)));
		graphics.FillRectangle(&marker, x - dinfo.pWidth, y - dinfo.pWidth, dinfo.pWidth * 2, dinfo.pWidth * 2);
		ReleaseDC(hWnd, hdc);
		stampOn = false; // 스탬프 모드 비활성화
		break;
	}

    case WATERCOLOR:
    {
        Gdiplus::Graphics graphics(hdc);
        int alpha = 10; // 기본 투명도 설정
        const int numPoints = 20; // 꼭짓점 갯수
        Gdiplus::PointF points[numPoints];

        // 무작위 각도를 사용하여 비정형적인 모양을 만들기
        for (int i = 0; i < numPoints; ++i) {
            float angle = 2 * 3.14159f * i / numPoints; // 원형 좌표
            float radius = dinfo.pWidth + (rand() % 10); // 무작위 반경 변화
            points[i] = Gdiplus::PointF(x + radius * cos(angle), y + radius * sin(angle)); // 꼭짓점 설정
        }

        Gdiplus::SolidBrush brush(Gdiplus::Color(alpha, GetRValue(col), GetGValue(col), GetBValue(col))); // 색상 설정
        graphics.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias); // 부드럽게 그리기
        graphics.FillPolygon(&brush, points, numPoints); // 비정형 도형 그리기

		ReleaseDC(hWnd, hdc);
		stampOn = false; // 스탬프 모드 비활성화
		break;
	}
	case STAMP:
	{
		hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(stampID), IMAGE_ICON, 124, 124, 0); // 스탬프 아이콘 설정
		stampOn = true; // 스탬프 모드 활성화
		break;
	}
	default:
		break;
	}
}


void Function::paint(HDC hdc, RECT canvasRT, PAINTSTRUCT ps)
{
    cHdc = hdc;
    CanvasPen = (HPEN)SelectObject(cHdc, CreatePen(PS_SOLID, 1, RGB(234, 234, 234)));
    Rectangle(cHdc, canvasRT.left, canvasRT.top, canvasRT.right, canvasRT.bottom);
    SelectObject(cHdc, CanvasPen);
    DeleteObject(CanvasPen);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1)); // 배경 색칠


    if (!getIsReplay())
    {
        for (const auto& record : getDrawLInfo().pInfo)
        {
            if (record.bShape != BRUSH)
                setBShape(record.bShape);
            else
                setBShape(BASIC);

			switch (record.state)
			{
			case WM_LBUTTONDOWN:
				mouseUD(record, false);
				if (record.bShape == STAMP) {
					re_draw(cHdc, record, WndFunc::canvasWnd);
				}
				break;

			case WM_LBUTTONUP:
				if (record.bShape == BRUSH) {
					mouseUD(record, FALSE);
					bShape = BRUSH;
				}
				break;

            case WM_MOUSEMOVE:
                re_draw(cHdc, record, WndFunc::canvasWnd);
                break;



            default:
                break;
            }
        }

        DeleteObject(nPen);
    }
}

void Function::stampIcon(int stampID)
{
	this->stampID = stampID;
}

void Function::setBShape(int bShape)
{
    this->bShape = bShape;
}

LINFO Function::getDrawLInfo()
{
    /*std::wstring message = L"getDrawLInfo() 호출, drawLInfo.pInfo 크기: " + std::to_wstring(drawLInfo.pInfo.size()) +
       L"\nFunction 객체 주소: " + std::to_wstring((uintptr_t)this);
    MessageBox(nullptr, message.c_str(), L"디버깅: getDrawLInfo", MB_OK); */
    return drawLInfo;
}

void Function::setIsReplay(bool isReplay)
{
    this->isReplay = isReplay;
}

bool Function::getIsReplay()
{
    return isReplay;
}

void Function::setIsReset(bool isReset)
{
    this->isReset = isReset;
}

bool Function::getIsReset()
{
    return isReset;
}

void Function::suspendReplay()

{
    setIsReplay(true);
    setIsReset(true);
    isLeftClick = false;
    SuspendThread(threadHandle);
    px2 = px;
    py2 = py;
    //MessageBox(hWnd, L"suspend", L"dd", MB_OK);
}

void Function::resumeReplay()
{
    setIsReset(false);
    setIsReplay(true);
    ResumeThread(threadHandle);
    isLeftClick = true;
    x = px2;
    y = py2;
    //MessageBox(hWnd, L"resume", L"dd", MB_OK);
}

void Function::stopReplay(HWND hWnd)
{
    setIsReplay(false);
    setIsReset(true);

    if (replayThreadHandle.joinable())
    {
        replayThreadHandle.join();
    }
    //MessageBox(hWnd, L"stop", L"dd", MB_OK);
}

void Function::setisLeftClick(bool click) {
    this->isLeftClick = click;
}

bool Function::getisLeftClick() {
    return isLeftClick;
}

// 벡터가 비어있는지 검사
bool Function::getDrawLInfoEmpty()
{
    return drawLInfo.pInfo.empty();
}
void Function::GDIPlusStart()
{
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}
void Function::GDIPlusEnd() { //gdi 종료
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

//마우스로 할때 L버튼 누른채 캔버스 윈도우 외부로 나가서 떼면 계속 그려지지만 터치로 할 시 정상작동
void Function::setisCanvas(bool cnt, LPARAM lParam)
{
    {
        if (!isReplay)
            if (cnt)
            {

                if (!isCanvas)
                {
                    SendMessage(WndFunc::canvasWnd, WM_LBUTTONDOWN, NULL, lParam);
                }

                isCanvas = cnt;
            }
            else
            {
                if (isCanvas)
                {
                    SendMessage(WndFunc::canvasWnd, WM_LBUTTONUP, NULL, lParam);
                }

                POINT pt = { LOWORD(lParam), HIWORD(lParam) };
                MapWindowPoints(WndFunc::drowWnd, WndFunc::canvasWnd, &pt, 1);

                x = pt.x;
                y = pt.y;

                isCanvas = cnt;
            }
    }
}