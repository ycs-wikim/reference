#include "WndFunc.h"


HWND WndFunc::drowWnd = nullptr;
HWND WndFunc::nameWnd = nullptr;
HWND WndFunc::toolWnd = nullptr;
HWND WndFunc::canvasWnd = nullptr;
//HWND WndFunc::menuWnd = nullptr;
HWND WndFunc::sideWnd = nullptr;
HWND WndFunc::visitListWnd = nullptr;
HWND WndFunc::fileManager = nullptr;
HWND WndFunc::colorWnd = nullptr;

HWND WndFunc::DrowBT = nullptr;
HWND WndFunc::LoadBT = nullptr;
HWND WndFunc::CreditBT = nullptr;

bool WndFunc::buttonOn = true;
bool WndFunc::creditOn = false;
HWND WndFunc::fileNameW = nullptr;

HINSTANCE WndFunc::hInst = nullptr;
RECT WndFunc::wndSize = { 0, 0, 0, 0 };



RECT WndFunc::GetRT(HWND hWnd)
{
    if (!IsWindow(hWnd)) {  // hWnd가 유효한지 확인
        //MessageBox(NULL, L"유효하지 않은 창 핸들입니다.", L"에러", MB_OK);
        return RECT{ 0, 0, 0, 0 };  // 초기화된 RECT 반환
    }

    GetClientRect(hWnd, &this->rect);
    return this->rect;
}

void WndFunc::RegisterNewClass(HINSTANCE hInst, LPCWSTR className)
{
    WNDCLASS wc = {};
    wc.lpfnWndProc = DefWindowProc;  // 기본 메시지 처리기
    wc.hInstance = hInst;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = className;

    RegisterClass(&wc);
}