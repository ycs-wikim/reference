#include "Application.h"
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, int nCmdShow) {
    Application app;

    if (!app.Init(hInstance, nCmdShow)) {
        MessageBox(NULL, L"Application 초기화 실패", L"오류", MB_OK | MB_ICONERROR);
        return -1;
    }

    return app.Run();
}
