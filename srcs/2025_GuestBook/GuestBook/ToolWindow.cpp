#include "ToolWindow.h"
#define NEW 100
#define SAVE 101
#define LOAD 102
#define REPLAY 103
#define CLEAR 104
#define ERASE 105
#define BRUSH 106
#define COLOR 107
#define STOP 108
#define END 109
#define BLACK 110
#define RED 111
#define BLUE 112
#define GREEN 113
bool ToolWindow::Create(HWND parentHwnd, HINSTANCE hInst) {
    hInstance = hInst;

    WNDCLASS wc = {};
    wc.lpfnWndProc = ToolWindow::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"ToolWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, wc.lpszClassName, NULL,
        WS_CHILD | WS_VISIBLE,
        0, 0,
        200, 50,  // 너비 200으로 줄임, 필요하면 조정
        parentHwnd, nullptr, hInstance, this);

    if (!hwnd) return false;
    buttonController.Init(hwnd, hInstance);
    CreateButton();
    return true;
}
LRESULT CALLBACK ToolWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
   
    ToolWindow* pThis = nullptr;

    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pcs = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = static_cast<ToolWindow*>(pcs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        pThis->hwnd = hwnd;
    }
    else {
        pThis = reinterpret_cast<ToolWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    switch (msg) {
   
    case WM_COMMAND: {
        pThis->buttonController.HandleCommand(wParam);
        return 0;
    }
    }


    return DefWindowProc(hwnd, msg, wParam, lParam);
}



void ToolWindow::CreateButton() {
    buttonController.Create(hwnd, L"새파일", NEW, 15, 10, 50, 50);
    buttonController.SetImage(156);
    buttonController.Create(hwnd, L"저장", SAVE, 70, 10, 70, 50);
    buttonController.SetImage(140);
    buttonController.Create(hwnd, L"불러오기", LOAD, 130, 10, 50, 30);
    buttonController.SetImage(155);
    buttonController.Create(hwnd, L"리플레이", REPLAY, 190, 10, 50, 30);
    buttonController.SetImage(139);
    replayHwnd = buttonController.GetHwnd();
    buttonController.Create(hwnd, L"중단", STOP, 250, 10, 50, 30);
    buttonController.SetImage(135);
    buttonController.Create(hwnd, L"전체지우기", CLEAR, 310, 10, 50, 30);
    buttonController.SetImage(134);
    buttonController.Create(hwnd, L"지우기", ERASE, 370, 10, 50, 30);
    buttonController.SetImage(136);
    buttonController.Create(hwnd, L"브러쉬", BRUSH, 430, 10, 50, 30);
    buttonController.SetImage(138);
    buttonController.Create(hwnd, L"색상", COLOR, 490, 10, 50, 30);
    buttonController.SetImage(133);
    buttonController.Create(hwnd, L"BLACK", BLACK, 550, 10, 50, 30);
    buttonController.SetImage(142);
    buttonController.Create(hwnd, L"RED", RED, 610, 10, 50, 30);
    buttonController.SetImage(147);
    buttonController.Create(hwnd, L"GREEN", GREEN, 670, 10, 50, 30);
    buttonController.SetImage(144);
    buttonController.Create(hwnd, L"BLUE", BLUE, 730, 10, 50, 30);
    buttonController.SetImage(143);
};


