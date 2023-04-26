#include "pch.h"
#include "GuestBookEditor.h"

using namespace Gdiplus;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    GdiplusStartupInput gdiplus_startup_input;
    ULONG_PTR gdiplus_token;

    GdiplusStartup(&gdiplus_token, &gdiplus_startup_input, NULL);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, Window::GetInstance()->szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GUESTBOOKEDITOR, Window::GetInstance()->szWindowClass, MAX_LOADSTRING);
    Window::GetInstance()->MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!Window::GetInstance()->InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUESTBOOKEDITOR));

    MSG msg;

    // 메모리 누수 확인
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(219);

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    GdiplusShutdown(gdiplus_token);
    return (int)msg.wParam;
}