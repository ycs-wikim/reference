#include "DW_ToolMenu.h"
#include "DW_NameBar.h"
#include "PenThickness.h"

std::unique_ptr<ConnExcel> connExcel = std::make_unique<ConnExcel>();

/// 네임 바 정적 메서드
LRESULT CALLBACK DrowWindow::WndProcTB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
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
        return pThis->handleMessageTB(hWnd, message, wParam, lParam); // 인스턴스의 가상 함수 호출
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

const int xOffset = 400; // 컬러창 x 좌표
const int yOffset = 100; // 컬러창 y 좌표

/// 펜 종류 버튼 생성 (창 크기 변경이나 리플레이시에도 위치 변경 없어 생성자로 좌표 초기화)
MakeButton basicPenButton(10, 10, 40, 40);
MakeButton pencilButton(50, 10, 80, 40);
MakeButton brushButton(90, 10, 120, 40);
MakeButton sprayButton(130, 10, 160, 40);
//MakeButton rectpenButton(170, 10, 200, 40);
MakeButton waterpenButton(170, 10, 200, 40);
MakeButton visitListButton(1200, 10, 1230, 40);

/// 스탬프 종류 버튼 생성
MakeButton heartButton(250, 10, 280, 40);
MakeButton uhButton(290, 10, 320, 40);
MakeButton yuhanButton(330, 10, 360, 40);
MakeButton pfButton(370, 10, 400, 40);
MakeButton guButton(410, 10, 440, 40);

/// 색상 종류 버튼 생성 (그리기는 WM_PAINT로 처리)
MakeButton colorButton1;
MakeButton colorButton2;
MakeButton colorButton3;

/// 아래 3개의 버튼은 리플레이시 or 창 크기 변경 시 위치 이동이 있어 
/// DW_ToolMenu::Create에서 초기 좌표 생성
/// DW_ToolMenu::HandleMessage의 WM_SIZE나 WM_LBUTTONDOWN의 정지, 리플레이 버튼시 좌표 이동

MakeButton eraseButton;      /// 지우개 버튼 생성 
MakeButton playButton;      /// 플레이 버튼 생성
MakeButton stopButton;      /// 중지 버튼 생성
//MakeButton saveButton;      /// 세이브 버튼 생성

//ColorPalette colorGet;      /// 색상 받아오기용 인스턴스 

PAINTSTRUCT t_ps = { 0 };
HBRUSH ToolBrush = nullptr;
HPEN ToolPen = nullptr;
HDC tHdc = nullptr;

RECT a;         /// IntersectRect 반환용 RECT
RECT mouse;      /// 마우스 좌표 기준 RECT 생성

/// LBUTTONDOWN시 마다 selectedBrushButton과 selectedIcon이 업데이트
/// 이펙트 처리는 WM_PAINT에서 처리
/// 클릭시 selectedBrushButton 변수에 해당 RECT 데이터 저장
/// buttonLoadImage 메서드로 해당 Rect에 이펙트 생성
MakeButton* selectedBrushButton = nullptr;  /// 현재 선택된 버튼
int selectedIcon = 0;                  /// 현재 선택된 아이콘 ID

/// 클릭한 색상 추적용 변수
MakeButton* selectedColorButton = nullptr;  // 현재 선택된 색상 버튼

bool replayStay = false;   /// 리플레이 중지 시 화면 무효화 발생해도 현재 좌표 유지 위해 선언

/// 네임 바 메세지 처리 핸들 메서드
LRESULT DrowWindow::handleMessageTB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_COMMAND:
    {
        switch (wParam)
        {
        case TL_PLAY_BT:
            if (function->getDrawLInfoEmpty())
            {
                break;
            }

            replayStay = true;   /// replay시 true로 설정하여 WM_SIZE 조절을 멈춘다
            playButton.toggleState = !playButton.toggleState;   /// 버튼 누를때마다 이미지 교체 위해 값 반점


            if (pCnt)
            {
                if (!function->getIsReplay())
                {
                    int midPoint = WndFunc::wndSize.right / 2; //중심 좌표 계산

                    SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_PLAY_BT, 0);

                    /// 리플레이 시 브러시 버튼 제외한 다른 버튼들 안보이게 설정
                    //saveButton.setCoordinate(-50, -50, -50, -50);
                    eraseButton.setCoordinate(-50, -50, -50, -50);
                    colorButton1.setCoordinate(-50, -50, -50, -50);
                    colorButton2.setCoordinate(-50, -50, -50, -50);
                    colorButton3.setCoordinate(-50, -50, -50, -50);

                    /// 재생, 중지 버튼 위치 조정
                    playButton.setCoordinate(midPoint - 50, 10, midPoint - 20, 40);
                    stopButton.setCoordinate(midPoint + 20, 10, midPoint + 50, 40);

                    function->setIsReplay(true);
                    pCnt = false;
                    InvalidateRect(WndFunc::toolWnd, NULL, true);
                }
                else
                {
                    SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_PLAY_BT, 0);
                    pCnt = false;
                }
            }
            else
            {
                SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_PLAY_BT, 1);
                pCnt = true;
            }

            InvalidateRect(WndFunc::toolWnd, NULL, true);
            UpdateWindow(WndFunc::toolWnd);
        }
        break;
    }
    case WM_CREATE:
    {
        function = std::make_unique<Function>();

        //colorPalette = make_unique<ColorPalette>();

        int midPoint = WndFunc::wndSize.right / 2;

        /// 프로그램 실행 시 이펙트 적용할 아이콘 설정
        selectedBrushButton = &basicPenButton;   /// 기본 펜 버튼 설정
        selectedIcon = IDI_PEN_ICON;         /// 기본 펜 아이콘 설정
        selectedColorButton = &colorButton1;   /// 프로그램 실행 시 컬러 버튼1 기본값

        eraseButton.setCoordinate(midPoint + 50, 10, midPoint + 80, 40);
        playButton.setCoordinate(midPoint + 115, 10, midPoint + 145, 40);
        stopButton.setCoordinate(midPoint + 160, 10, midPoint + 190, 40);

        break;
    }
    case WM_LBUTTONDOWN:
    {
        /// 캔버스에서 그릴 때 색상 창 열려있으면 닫음
        if (IsWindowVisible(WndFunc::colorWnd))
        {
            //function->setisLeftClick(false);
            ShowWindow(WndFunc::colorWnd, SW_HIDE);
            break;
        }
        HDC hdc = GetDC(hWnd);

        /// 현재 마우스 좌표로 사각형 생성
        mouse.left = LOWORD(lParam);
        mouse.top = HIWORD(lParam);
        mouse.right = mouse.left + 1;
        mouse.bottom = mouse.top + 1;

        /// 방문자 스레드 on/off
        if (IntersectRect(&a, &mouse, &visitListButton.rectButton)) 
        {
            visitListButton.toggleState = !visitListButton.toggleState;   /// 버튼 누를때마다 이미지 교체 위해 값 반전

            if (lCnt)
            {
                if (!connExcel->getIsStart())
                {
                    SendMessage(WndFunc::visitListWnd, WM_COMMAND, TL_PLAY_BT, 0);

                    connExcel->setIsStart(true);
                    lCnt = false;
                }
                else
                {
                    SendMessage(WndFunc::visitListWnd, WM_COMMAND, TL_PLAY_BT, 0);
                    lCnt = false;
                }
            }
            else {
                SendMessage(WndFunc::visitListWnd, WM_COMMAND, TL_PLAY_BT, 1);
                lCnt = true;
            }
        }


        // 예: 기본 펜 선택 코드 수정
        if (IntersectRect(&a, &mouse, &basicPenButton.rectButton)) {
            function->setBShape(BASIC);
            selectedBrushButton = &basicPenButton;
            selectedIcon = IDI_PEN_ICON;

            // 캔버스에 현재 선택된 펜 모양 반영
            SendMessage(WndFunc::canvasWnd, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
        }
        else if (IntersectRect(&a, &mouse, &pencilButton.rectButton)) {
            function->setBShape(PENCIL);
            selectedBrushButton = &pencilButton;
            selectedIcon = IDI_PENCIL_ICON;

            // 캔버스에 현재 선택된 펜 모양 반영
            SendMessage(WndFunc::canvasWnd, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
        }
        /// 브러시
        else if (IntersectRect(&a, &mouse, &brushButton.rectButton)) {
            function->setBShape(BRUSH);

            selectedBrushButton = &brushButton;
            selectedIcon = IDI_BRUSH_ICON;
            // 캔버스에 현재 선택된 펜 모양 반영
            SendMessage(WndFunc::canvasWnd, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
        }
        /// 스프레이
        else if (IntersectRect(&a, &mouse, &sprayButton.rectButton)) {
            function->setBShape(SPRAY);


            selectedBrushButton = &sprayButton;
            selectedIcon = IDI_SPRAY_ICON;
            // 캔버스에 현재 선택된 펜 모양 반영
            SendMessage(WndFunc::canvasWnd, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
        }
        /// 물펜
        else if (IntersectRect(&a, &mouse, &waterpenButton.rectButton)) {
            function->setBShape(WATERCOLOR);

            selectedBrushButton = &waterpenButton;
            selectedIcon = IDI_WATERPEN_ICON;
            // 캔버스에 현재 선택된 펜 모양 반영
            SendMessage(WndFunc::canvasWnd, WM_LBUTTONUP, 0, MAKELPARAM(0, 0));
        }

        /// 하트 스탬프
        else if (IntersectRect(&a, &mouse, &heartButton.rectButton)) {
            function->setBShape(STAMP);
            function->stampIcon(IDI_HEART_ICON);

            selectedBrushButton = &heartButton;
            selectedIcon = IDI_HEART_ICON;
        }
        /// 어? 스탬프
        else if (IntersectRect(&a, &mouse, &uhButton.rectButton)) {
            function->setBShape(STAMP);
            function->stampIcon(IDI_UH_ICON);

            selectedBrushButton = &uhButton;
            selectedIcon = IDI_UH_ICON;
        }
        /// 유한대 마크 스탬프
        else if (IntersectRect(&a, &mouse, &yuhanButton.rectButton)) {
            function->setBShape(STAMP);
            function->stampIcon(IDI_YUHAN_ICON);

            selectedBrushButton = &yuhanButton;
            selectedIcon = IDI_YUHAN_ICON;
        }
        /// 교수절교 스탬프
        else if (IntersectRect(&a, &mouse, &pfButton.rectButton)) {
            function->setBShape(STAMP);
            function->stampIcon(IDI_PF_ICON);

            selectedBrushButton = &pfButton;
            selectedIcon = IDI_PF_ICON;
        }
        /// 비둘기 스탬프
        else if (IntersectRect(&a, &mouse, &guButton.rectButton)) {
            function->setBShape(STAMP);
            function->stampIcon(IDI_GU_ICON);

            selectedBrushButton = &guButton;
            selectedIcon = IDI_GU_ICON;
        }

        // colorButton1에 대한 처리
        else if (IntersectRect(&a, &mouse, &colorButton1.rectButton))
        {
            if (function->getIsReplay()) {
                // 리플레이 중일 때는 색상 선택 박스를 열지 않음
                break;
            }

            // 색상 선택 박스의 고정 위치 설정
            int fixedX = 320; // 고정 x 좌표
            int fixedY = 10;  // 고정 y 좌표

            // 색상 선택 박스의 위치를 화면 좌표 기준으로 설정
            RECT screenRect = colorButton1.rectButton;
            ClientToScreen(hWnd, reinterpret_cast<POINT*>(&screenRect.left));
            ClientToScreen(hWnd, reinterpret_cast<POINT*>(&screenRect.right));

            // 이전 버튼의 선택 박스 숨기기
            if (selectedColorButton != &colorButton1) {
                ShowWindow(WndFunc::colorWnd, SW_HIDE);
            }

            // 색상 선택 박스의 위치를 고정된 위치로 설정
            SetWindowPos(WndFunc::colorWnd, HWND_TOP, fixedX, fixedY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            InvalidateRect(WndFunc::colorWnd, NULL, TRUE);

            // 색상 선택 박스 표시
            if (DW_ColorBox::colorSelect == 0) {
                ShowWindow(WndFunc::colorWnd, SW_SHOW);
            }
            else {
                DW_ColorBox::colorSelect = 0;
            }

            selectedColorButton = &colorButton1; // 선택한 버튼 저장
        }

        // colorButton2에 대한 처리
        else if (IntersectRect(&a, &mouse, &colorButton2.rectButton))
        {
            if (function->getIsReplay()) {
                break;
            }

            // 색상 선택 박스의 고정 위치 설정
            int fixedX = 370; // 고정 x 좌표
            int fixedY = 10;  // 고정 y 좌표

            // 색상 선택 박스의 위치를 화면 좌표 기준으로 설정
            RECT screenRect = colorButton2.rectButton;
            ClientToScreen(hWnd, reinterpret_cast<POINT*>(&screenRect.left));
            ClientToScreen(hWnd, reinterpret_cast<POINT*>(&screenRect.right));

            // 이전 버튼의 선택 박스 숨기기
            if (selectedColorButton != &colorButton2) {
                ShowWindow(WndFunc::colorWnd, SW_HIDE);
            }

            // 색상 선택 박스의 위치를 고정된 위치로 설정
            SetWindowPos(WndFunc::colorWnd, HWND_TOP, fixedX, fixedY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            InvalidateRect(WndFunc::colorWnd, NULL, TRUE);
            if (DW_ColorBox::colorSelect == 1) {
                ShowWindow(WndFunc::colorWnd, SW_SHOW);
            }
            else {
                DW_ColorBox::colorSelect = 1;
            }
            selectedColorButton = &colorButton2; // 선택한 버튼 저장
        }

        // colorButton3에 대한 처리
        else if (IntersectRect(&a, &mouse, &colorButton3.rectButton))
        {
            if (function->getIsReplay()) {
                break;
            }

            // 색상 선택 박스의 고정 위치 설정
            int fixedX = 420; // 고정 x 좌표
            int fixedY = 10;  // 고정 y 좌표

            // 색상 선택 박스의 위치를 화면 좌표 기준으로 설정
            RECT screenRect = colorButton3.rectButton;
            ClientToScreen(hWnd, reinterpret_cast<POINT*>(&screenRect.left));
            ClientToScreen(hWnd, reinterpret_cast<POINT*>(&screenRect.right));

            // 이전 버튼의 선택 박스 숨기기
            if (selectedColorButton != &colorButton3) {
                ShowWindow(WndFunc::colorWnd, SW_HIDE);
            }

            // 색상 선택 박스의 위치를 고정된 위치로 설정
            SetWindowPos(WndFunc::colorWnd, HWND_TOP, fixedX, fixedY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
            InvalidateRect(WndFunc::colorWnd, NULL, TRUE);

            if (DW_ColorBox::colorSelect == 2) {
                ShowWindow(WndFunc::colorWnd, SW_SHOW);
            }
            else {
                DW_ColorBox::colorSelect = 2;
            }
            selectedColorButton = &colorButton3; // 선택한 버튼 저장
        }
        
       


        /// 지우개 버튼 
        else if (IntersectRect(&a, &mouse, &eraseButton.rectButton)) {

            if (function->getDrawLInfoEmpty()) { break; }
            if (!function->getIsReplay()) {
                SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_CLEAR_BT, 0);
                SendMessage(WndFunc::nameWnd, WM_SETTEXT, 0, (LPARAM)L"이름 없음");
            }

        }

        /// 리플레이 버튼
        else if (IntersectRect(&a, &mouse, &playButton.rectButton)) {

            if (function->getDrawLInfoEmpty()) { break; }

            replayStay = true;   /// replay시 true로 설정하여 WM_SIZE 조절을 멈춘다
            playButton.toggleState = !playButton.toggleState;   /// 버튼 누를때마다 이미지 교체 위해 값 반점

            if (pCnt)
            {
                if (!function->getIsReplay())
                {
                    int midPoint = WndFunc::wndSize.right / 2; //중심 좌표 계산

                    SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_PLAY_BT, 0);

                    /// 리플레이 시 브러시 버튼 제외한 다른 버튼들 안보이게 설정
                    //saveButton.setCoordinate(-50, -50, -50, -50);
                    eraseButton.setCoordinate(-50, -50, -50, -50);
                    colorButton1.setCoordinate(-50, -50, -50, -50);
                    colorButton2.setCoordinate(-50, -50, -50, -50);
                    colorButton3.setCoordinate(-50, -50, -50, -50);

                    /// 재생, 중지 버튼 위치 조정
                    playButton.setCoordinate(midPoint - 50, 10, midPoint - 20, 40);
                    stopButton.setCoordinate(midPoint + 20, 10, midPoint + 50, 40);

                    function->setIsReplay(true);
                    pCnt = false;
                    InvalidateRect(WndFunc::toolWnd, NULL, true);
                }
                else
                {
                    SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_PLAY_BT, 0);
                    pCnt = false;
                }
            }
            else {
                SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_PLAY_BT, 1);
                pCnt = true;
            }
            

            InvalidateRect(WndFunc::toolWnd, NULL, true);
            UpdateWindow(WndFunc::toolWnd);

        }

        /// 중지 버튼
        else if (IntersectRect(&a, &mouse, &stopButton.rectButton)) {

            InvalidateRect(WndFunc::toolWnd, nullptr, true);

            if (!function->getIsReplay()) {
                SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_RESET_BT, 0);
            }
            else
            {
                SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_RESET_BT, 0);
                SendMessage(WndFunc::canvasWnd, WM_PAINT, TL_RESET_BT, 0);
                int midPoint = WndFunc::wndSize.right / 2;   /// 윈도우 중심 좌표 계산

                /// 정지버튼 클릭 즉, 리플레이 중지시 지우개, 저장 버튼 원래 자리로 복귀
                eraseButton.setCoordinate(midPoint + 50, 10, midPoint + 80, 40);
                playButton.setCoordinate(midPoint + 115, 10, midPoint + 145, 40);
                stopButton.setCoordinate(midPoint + 160, 10, midPoint + 190, 40);

                //saveButton.setCoordinate((WndFunc::wndSize.right - 50, 10, toolRT.right - 20, 40);
                playButton.toggleState = false;      /// 재생 중 정지해도 초기 아이콘으로 설정

            }
            replayStay = false;      /// 리플레이 상태 종료
            pCnt = true;
            function->setisLeftClick(false);
            InvalidateRect(WndFunc::toolWnd, NULL, true);
        }
        ///// 저장 버튼

        InvalidateRect(WndFunc::toolWnd, NULL, true); //화면 갱신
        ReleaseDC(hWnd, hdc);

        break;
    }

    /// 문제 생기면 이 WM_PAINT 쓰셈
/*
 case WM_PAINT:
 {
     PAINTSTRUCT ps;
     HDC hdc = BeginPaint(hWnd, &ps);
     int midPoint = WndFunc::wndSize.right / 2;

     playButton.setCoordinate(midPoint + 115, 10, midPoint + 145, 40);
     stopButton.setCoordinate(midPoint + 160, 10, midPoint + 190, 40);

     playButton.doubleImgButton(hdc, IDI_PAUSE_ICON, IDI_PLAY_ICON);
     stopButton.drawRectButton(hdc, IDI_STOP_ICON);
     visitListButton.doubleImgButton(hdc, IDI_PAUSE_ICON, IDI_PLAY_ICON);

     if (WndFunc::buttonOn)
     {

         eraseButton.setCoordinate(midPoint + 50, 10, midPoint + 80, 40);
         /// 버튼과 이미지 그리기
         basicPenButton.drawRectButton(hdc, IDI_PEN_ICON);
         pencilButton.drawRectButton(hdc, IDI_PENCIL_ICON);
         brushButton.drawRectButton(hdc, IDI_BRUSH_ICON);
         sprayButton.drawRectButton(hdc, IDI_SPRAY_ICON);
         rectpenButton.drawRectButton(hdc, IDI_RECTPEN_ICON);
         waterpenButton.drawRectButton(hdc, IDI_WATERPEN_ICON);
         eraseButton.drawRectButton(hdc, IDI_ERASE_ICON);



         //saveButton.drawRectButton(memDC, IDI_SAVE_ICON);

         /// 선택된 브러시 버튼에 이펙트 적용
         if (selectedBrushButton != nullptr) {
             selectedBrushButton->clickEffectPen(IDI_PENEFFECT_ICON, selectedIcon, hdc);
         }

         /// 컬러 버튼 그리기 (Ellipse로 색상과 구현 위해 WM_PAINT에서 그리기 + 좌표처리)
         colorButton1.setCoordinate(midPoint - 140, 10, midPoint - 110, 40);
         colorButton2.setCoordinate(midPoint - 90, 10, midPoint - 60, 40);
         colorButton3.setCoordinate(midPoint - 40, 10, midPoint - 10, 40);

         /// 선택된 컬러 버튼에 이펙트 적용
         /// 이펙트 먼저 그린 후 색상 버튼을 그림(drawEllipseButton)
         if (selectedColorButton != nullptr) {
             selectedColorButton->clickEffectPen(IDI_COLOREFFECT_ICON, hdc);
         }

         colorButton1.drawEllipseButton(hdc, DW_ColorBox::getColorNum(0));   /// 색상 버튼 1 미리보기
         colorButton2.drawEllipseButton(hdc, DW_ColorBox::getColorNum(1));   /// 색상 버튼 2 미리보기
         colorButton3.drawEllipseButton(hdc, DW_ColorBox::getColorNum(2));   /// 색상 버튼 3 미리보기
     }
     EndPaint(hWnd, &ps);
     break;
 }
 */
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 더블 버퍼링을 위한 메모리 DC 생성
        HDC memDC = CreateCompatibleDC(hdc);
        HBITMAP hBitmap = CreateCompatibleBitmap(hdc, WndFunc::wndSize.right, WndFunc::wndSize.bottom);
        HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, hBitmap);

        // 배경을 흰색으로 채우기
        HBRUSH hWhiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
        RECT rect;
        GetClientRect(hWnd, &rect);
        FillRect(memDC, &rect, hWhiteBrush);

        int midPoint = WndFunc::wndSize.right / 2;

        

        playButton.setCoordinate(midPoint + 115, 10, midPoint + 145, 40);
        stopButton.setCoordinate(midPoint + 160, 10, midPoint + 190, 40);

        // 메모리 DC에 버튼을 그리기
        playButton.doubleImgButton(memDC, IDI_PAUSE_ICON, IDI_PLAY_ICON);
        stopButton.drawRectButton(memDC, IDI_STOP_ICON);
        visitListButton.doubleImgButton(memDC, IDI_PAUSE_ICON, IDI_PLAY_ICON);

        if (WndFunc::buttonOn)
        {
            MoveToEx(memDC, 225, 10, NULL);
            LineTo(memDC, 225, 40);

            eraseButton.setCoordinate(midPoint + 50, 10, midPoint + 80, 40);

            // 버튼과 이미지 그리기
            basicPenButton.drawRectButton(memDC, IDI_PEN_ICON);
            pencilButton.drawRectButton(memDC, IDI_PENCIL_ICON);
            brushButton.drawRectButton(memDC, IDI_BRUSH_ICON);
            sprayButton.drawRectButton(memDC, IDI_SPRAY_ICON);
            //rectpenButton.drawRectButton(memDC, IDI_RECTPEN_ICON);
            waterpenButton.drawRectButton(memDC, IDI_WATERPEN_ICON);
            eraseButton.drawRectButton(memDC, IDI_ERASE_ICON);

            // 스탬프 버튼 추가
            heartButton.drawRectButton(memDC, IDI_HEART_ICON);
            uhButton.drawRectButton(memDC, IDI_UH_ICON);
            yuhanButton.drawRectButton(memDC, IDI_YUHAN_ICON);
            pfButton.drawRectButton(memDC, IDI_PF_ICON);
            guButton.drawRectButton(memDC, IDI_GU_ICON);


            // 선택된 브러시 버튼에 이펙트 적용
            if (selectedBrushButton != nullptr) {
                selectedBrushButton->clickEffectPen(IDI_PENEFFECT_ICON, selectedIcon, memDC);
            }

            // 컬러 버튼 좌표 설정 및 이펙트 적용
            colorButton1.setCoordinate(midPoint - 140, 10, midPoint - 110, 40);
            colorButton2.setCoordinate(midPoint - 90, 10, midPoint - 60, 40);
            colorButton3.setCoordinate(midPoint - 40, 10, midPoint - 10, 40);

            if (selectedColorButton != nullptr) {
                selectedColorButton->clickEffectPen(IDI_COLOREFFECT_ICON, memDC);
            }

            // 색상 버튼 그리기
            colorButton1.drawEllipseButton(memDC, DW_ColorBox::getColorNum(0));
            colorButton2.drawEllipseButton(memDC, DW_ColorBox::getColorNum(1));
            colorButton3.drawEllipseButton(memDC, DW_ColorBox::getColorNum(2));
        }

        // 메모리 DC의 내용을 화면 DC로 복사하여 출력
        BitBlt(hdc, 0, 0, WndFunc::wndSize.right, WndFunc::wndSize.bottom, memDC, 0, 0, SRCCOPY);

        // 리소스 정리
        SelectObject(memDC, oldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(memDC);

        EndPaint(hWnd, &ps);
        break;
    }

    case WM_ERASEBKGND:
    return 1; // 기본 배경 지우기 방지
     default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



/// 네임 바 메세지 처리 핸들 메서드
LRESULT DrowWindow::handleMessageVL(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_COMMAND:
    {
        if (wParam == TL_PLAY_BT && lParam == 0)
        {
            if (!connExcel->getIsStart())
            {
                connExcel->listScrollThread(hWnd, WndFunc::wndSize.right, WndFunc::wndSize);

                ConnExcel::list = connExcel->getVisitList().c_str();

                connExcel->setTextPosX(WndFunc::wndSize.right);
            }
            else
            {
                connExcel->resumeScroll();
            }
        }


        if (wParam == TL_PLAY_BT && lParam == 1)
        {
            connExcel->suspendScroll();
        }
        break;
    }
    case WM_CREATE:
    {


        break;
    }
    case WM_DESTROY:
    {
        connExcel->stopThread();
        break;
    }
    case WM_PAINT:
    {

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(WndFunc::visitListWnd, &ps);

        SIZE textSize = { 0 };
        wsprintf(text, ConnExcel::list.c_str());
        SetBkColor(hdc, RGB(249, 243, 240));

        HFONT hFont = CreateFont(17, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            DEFAULT_PITCH | FF_SWISS, TEXT("나눔고딕"));
        HFONT holdFont = (HFONT)SelectObject(hdc, hFont);
        TextOut(hdc, connExcel->getTextPosX(), 5, text, lstrlen(text));
        SelectObject(hdc, holdFont);
        DeleteObject(hFont);


        EndPaint(hWnd, &ps);

        // EndPaint(WndFunc::visitListWnd, &ps);
        break;
    }


    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}