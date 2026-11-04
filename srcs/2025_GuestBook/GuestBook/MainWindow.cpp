#include "MainWindow.h"
#include "DrawWindow.h"
#include "resource.h"
#include "Sidebar.h"
bool MainWindow::Create(HINSTANCE hInst, int nCmdShow) {
    hInstance = hInst;

    WNDCLASS wc = {};
    wc.lpfnWndProc = MainWindow::WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = L"MainWindowClass";
    wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(220,220,220)));
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LOGO));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, wc.lpszClassName, L"2025_졸업작품 방명록", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 
        900, 700,
        NULL, NULL, hInst, this);

    if (!hwnd) return false;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    return true;
}

LRESULT CALLBACK MainWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    MainWindow* pThis = nullptr;
   
    switch (msg) {
    case WM_NCCREATE: {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = static_cast<MainWindow*>(cs->lpCreateParams);
        if (pThis) {

            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
            pThis->hwnd = hwnd;
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    }

    pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    if (pThis) return pThis->HandleMessage(msg, wParam, lParam);

    return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT MainWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg) {
        OutputDebugString(L"Main WM_CREATE called\n");
    case WM_CREATE: {
        sideBar.SetSlider(hwnd, hInstance);
        return 0;

    }
    case WM_SIZE: {
        ResizeChildren();
        return 0;
    }
    case WM_VSCROLL: {
        HWND hSlider = (HWND)lParam; // 메시지를 보낸 컨트롤(슬라이더)의 핸들

        if (hSlider == sideBar.GetSliderHandle()) {

            if (LOWORD(wParam) == TB_THUMBTRACK || LOWORD(wParam) == TB_ENDTRACK) {

                int newPenWidth = (int) SendMessage(hSlider, TBM_GETPOS, 0, 0);

                drawWindow->SetPenWidth(newPenWidth);
            }
        }
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);

}

void MainWindow::Show(int nCmdShow) {
    if (hwnd) ::ShowWindow(hwnd, nCmdShow);
}



void MainWindow::ResizeChildren() {
    RECT rcClient;
    GetClientRect(hwnd, &rcClient);
    int parentWidth = rcClient.right;
    int parentHeight = rcClient.bottom;

    const int TOOLBAR_HEIGHT = 50;
    const int SIDEBAR_WIDTH = 100;
    const int SIDEBAR_Y_OFFSET = 60; // (MoveWindow에서 60을 사용하셨으므로)
    
    if (toolWindow) {
        MoveWindow(toolWindow->GetHwnd(), 0, 0, parentWidth, TOOLBAR_HEIGHT, TRUE);
    }

    // (사이드바 재배치 로직)
    if (sideBar.GetSliderHandle()) {
        int sliderY = TOOLBAR_HEIGHT + 70; // (예: 툴바 아래 70px)
        int sliderHeight = parentHeight - sliderY - 20; // (예: 하단 20px 여백)
        MoveWindow(sideBar.GetSliderHandle(), 25, sliderY, 50, sliderHeight, TRUE);
    }

    if (drawWindow) {
        // (MoveWindow는 DrawWindow에 WM_SIZE를 자동으로 보냅니다)
        MoveWindow(drawWindow->GetHwnd(),
            SIDEBAR_WIDTH, TOOLBAR_HEIGHT,
            parentWidth - SIDEBAR_WIDTH,
            parentHeight - TOOLBAR_HEIGHT,
            TRUE);
    }
}