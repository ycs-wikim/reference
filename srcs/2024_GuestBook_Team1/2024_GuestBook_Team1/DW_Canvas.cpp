#include "DW_Canvas.h"

// 멤버 변수 추가
bool isDrawing = false;    // 드로잉 상태 플래그
POINT lastPoint;           // 이전 점의 좌표

/// 네임 바 정적 메서드
LRESULT CALLBACK DrowWindow::WndProcCV(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    DrowWindow* pThis = nullptr;

    if (message == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<DrowWindow*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else {
        pThis = reinterpret_cast<DrowWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }

    if (pThis) {
        return pThis->handleMessageCV(hWnd, message, wParam, lParam); // 인스턴스의 가상 함수 호출
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}



/// 네임 바 메세지 처리 핸들 메서드
LRESULT DrowWindow::handleMessageCV(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
        static HDC memDC;
        static HBITMAP hBitmap;

    case WM_CREATE:
    {
        HDC hdc = GetDC(WndFunc::canvasWnd);
        memDC = CreateCompatibleDC(hdc);
        hBitmap = CreateCompatibleBitmap(hdc, WndFunc::wndSize.right, WndFunc::wndSize.bottom);
        SelectObject(memDC, hBitmap);
        ReleaseDC(WndFunc::canvasWnd, hdc);
        function = std::make_unique<Function>();
        function->GDIPlusStart(); // 붓 gdi 라이브러리 활성화

    }
    break;
    
    case WM_COMMAND:
    {
        if (wParam == TL_CLEAR_BT)
        {
            if (function->getIsReset())
            {
                function->clearDrawing(WndFunc::canvasWnd);
            }

        }

        if (wParam == TL_PLAY_BT && lParam == 0)
        {
            if (!function->getIsReplay())
            {
                function->replayThread(WndFunc::canvasWnd);
            }
            else
            {
                function->resumeReplay();
            }
        }


        if (wParam == TL_PLAY_BT && lParam == 1)
        {
            function->suspendReplay();
        }

        if (wParam == TL_RESET_BT)
        {
            function->reDrawing(WndFunc::canvasWnd);
        }
    }
    break;
    case WM_MOUSEMOVE:
    {

        if (!function->getIsReset()) break;
        //hdc = GetDC(canWnd);

        if (IsWindowVisible(WndFunc::colorWnd))
        {
            function->setisLeftClick(false);
            //ShowWindow(WndFunc::colorWnd, SW_HIDE); // 열려 있으면 닫기
            break;
        }

        function->setisCanvas(true, lParam);

        ////////////////////////////////////////////////

        drawPInfo.lParam = lParam;
        drawPInfo.pColor = DW_ColorBox::getColorNum(DW_ColorBox::colorSelect);//ColorPalette::colorArr[Function::penNum];
        drawPInfo.pTime = (DWORD)GetTickCount64();
        drawPInfo.pWidth = penThickness->getPenWidth(); /// 펜 굵기 설정
        drawPInfo.state = message;
        function->draw(WndFunc::canvasWnd, drawPInfo, TRUE); // 브러쉬 기능 추가하려면 해당 RECTANGLE 에 알맞는 변수를 넣으면 됨.
    }
    break;

	case WM_LBUTTONDOWN:
        /// 캔버스에서 그릴 때 색상 창 열려있으면 닫음
        if (IsWindowVisible(WndFunc::colorWnd))
        {
            //function->setisLeftClick(false);
            ShowWindow(WndFunc::colorWnd, SW_HIDE);
            break;
        }
		drawPInfo.lParam = lParam;
		drawPInfo.pColor = DW_ColorBox::getColorNum(DW_ColorBox::colorSelect);//ColorPalette::colorArr[Function::penNum];
		drawPInfo.pTime = (DWORD)GetTickCount64();
		drawPInfo.pWidth = penThickness->getPenWidth(); /// 펜 굵기 설정
		drawPInfo.state = message;
		function->mouseUD(drawPInfo, TRUE);
		function->draw(WndFunc::canvasWnd, drawPInfo, TRUE); // 브러쉬 기능 추가하려면 해당 RECTANGLE 에 알맞는 변수를 넣으면 됨.
		break;

	case WM_LBUTTONUP:
		if (!function->getIsReset())
		{
			break;
		}
		drawPInfo.lParam = lParam;
		drawPInfo.pColor = DW_ColorBox::getColorNum(DW_ColorBox::colorSelect);//ColorPalette::colorArr[Function::penNum];
		drawPInfo.pTime = (DWORD)GetTickCount64();
		drawPInfo.pWidth = penThickness->getPenWidth(); /// 펜 굵기 설정
		drawPInfo.state = message;
		function->mouseUD(drawPInfo, TRUE);
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(WndFunc::canvasWnd, &ps);

        function->paint(memDC, WndFunc::wndSize, ps);

        //memDC 를 hdc로 고속 복사
        BitBlt(hdc, 0, 0, WndFunc::wndSize.right, WndFunc::wndSize.bottom, memDC, 0, 0, SRCCOPY);

        ReleaseDC(hWnd, hdc);
        EndPaint(WndFunc::canvasWnd, &ps);
        break;
    }

    case WM_DESTROY:
    {
        DeleteObject(memDC);
        DeleteObject(hBitmap);
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
    return 0;
}
