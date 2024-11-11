#ifndef WNDFUNC_H
#define WNDFUNC_H

#include <Windows.h>

class WndFunc
{
public:
    static HWND drowWnd;
    static HWND nameWnd;
    static HWND toolWnd;
    static HWND canvasWnd;
    static HWND menuWnd;
    static HWND sideWnd;
    static HWND visitListWnd;
    static HWND colorWnd;

    static HWND DrowBT;
    static HWND LoadBT;
    static HWND CreditBT;
    static HWND fileNameW;
    static HWND fileManager;

    static bool buttonOn;
    static bool creditOn;

    static HINSTANCE hInst;

    static RECT wndSize;

    RECT GetRT(HWND);
    void RegisterNewClass(HINSTANCE, LPCWSTR);



private:
    RECT rect;
    WNDCLASS wc;
};

#endif WNDFUNC_H
