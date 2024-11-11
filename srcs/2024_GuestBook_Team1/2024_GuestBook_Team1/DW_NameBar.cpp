#include "DW_NameBar.h"

/// 네임 바 정적 메서드
LRESULT CALLBACK DrowWindow::WndProcNB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

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
        return pThis->handleMessageNB(hWnd, message, wParam, lParam); // 인스턴스의 가상 함수 호출
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

HWND backB = nullptr;
HWND sideB = nullptr;

MakeButton DW_NameBar::sideMenu;
MakeButton exitButton(10, 10, 40, 40);
RECT mousePoint;
RECT a1;

/// 네임 바 메세지 처리 핸들 메서드
LRESULT DrowWindow::handleMessageNB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SETTEXT:
        /// WM_SETTEXT 메시지 처리
        /// save나 로드시 namebar 텍스트 변경

        if (!WndFunc::creditOn) {
            SetWindowText(WndFunc::fileNameW, reinterpret_cast<LPCWSTR>(lParam));
        }
        break;
    case WM_CREATE:
    {
        WndFunc::fileNameW = CreateWindow(L"STATIC", L"이름 없음", WS_CHILD | WS_VISIBLE,
            50, 12, 300, 30, hWnd, (HMENU)NB_FILE_NAME, nullptr, NULL);


        DW_NameBar::sideMenu.setCoordinate(WndFunc::wndSize.right - 40, 10, WndFunc::wndSize.right - 10, 40);

        HFONT hFont = CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
            DEFAULT_PITCH | FF_SWISS, TEXT("나눔고딕"));

        // STATIC 컨트롤에 폰트 설정
        SendMessage(WndFunc::fileNameW, WM_SETFONT, (WPARAM)hFont, TRUE);

        break;
    }
    case WM_SIZE:
    {
        /// 창 크기 변화시 사이드 메뉴 버튼 이동
        DW_NameBar::sideMenu.setCoordinate(WndFunc::wndSize.right - 40, 10, WndFunc::wndSize.right - 10, 40);

        break;
    }
    case WM_LBUTTONDOWN:
    {
        if (function->getIsReplay()) {
            break;
        }

        /// 버튼 클릭 확인용 마우스 좌표 기준 RECT 생성
        mousePoint.left = LOWORD(lParam);
        mousePoint.top = HIWORD(lParam);
        mousePoint.right = mousePoint.left + 1;
        mousePoint.bottom = mousePoint.top + 1;

        /// 사이드 윈도우 존재 시 창 삭제
         /// 사이드 메뉴 버튼을 클릭했는지 확인
        if (IntersectRect(&a1, &mousePoint, &DW_NameBar::sideMenu.rectButton))
        {

            if (!IsWindowVisible(WndFunc::sideWnd))
            {
                DW_NameBar::sideMenu.toggleState = true;
                ShowWindow(WndFunc::sideWnd, SW_SHOW);
            }
            else
            {
                DW_NameBar::sideMenu.toggleState = false;
                ShowWindow(WndFunc::sideWnd, SW_HIDE);
            }
        }

        if (IntersectRect(&a1, &mousePoint, &exitButton.rectButton)) {
            WndFunc::buttonOn = true;
            WndFunc::creditOn = false;

            DW_NameBar::sideMenu.toggleState = false;
            SendMessage(WndFunc::nameWnd, WM_SETTEXT, 0, (LPARAM)L"이름 없음");

            ShowWindow(WndFunc::fileNameW, SW_SHOW);

            ShowWindow(WndFunc::drowWnd, SW_HIDE);
            ShowWindow(WndFunc::nameWnd, SW_HIDE);
            ShowWindow(WndFunc::toolWnd, SW_HIDE);
            ShowWindow(WndFunc::canvasWnd, SW_HIDE);
            ShowWindow(WndFunc::sideWnd, SW_HIDE);
            ShowWindow(WndFunc::visitListWnd, SW_HIDE);

            ShowWindow(WndFunc::DrowBT, SW_SHOW);
            ShowWindow(WndFunc::LoadBT, SW_SHOW);
            ShowWindow(WndFunc::CreditBT, SW_SHOW);

            function->clearDrawing(WndFunc::canvasWnd);
        }
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    }
    case WM_COMMAND:
    {
        int wmId = wParam;

        switch (wmId)
        {

        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        /// 사이드 버튼의 이미지 버튼 두개 
        if (!WndFunc::creditOn) {
            DW_NameBar::sideMenu.doubleImgButton(hdc, IDI_CLOSE_MENU_ICON, IDI_MENU_ICON);
        }
        exitButton.drawRectButton(hdc, IDI_EXIT_ICON);
        EndPaint(hWnd, &ps);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


