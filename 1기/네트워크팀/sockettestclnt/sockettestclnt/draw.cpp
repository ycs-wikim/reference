#include "framework.h"
#include "sockettestclnt.h"

RECT r_username = { 0, 650, 300, 800};
RECT r_roomlist = { 0, 0, 300, 650};
RECT r_userlist = { 980, 0, 1280, 800};
RECT r_chatarea = { 300, 0, 980, 800};

void ScreenSet(HWND hWnd) {
    MoveWindow(hWnd, 300, 100, SC_WIDTH, SC_HEIGHT, true);
}

void ScreenFix(LPARAM lParam) {
    ((MINMAXINFO*)lParam)->ptMaxTrackSize.x = SC_WIDTH;
    ((MINMAXINFO*)lParam)->ptMaxTrackSize.y = SC_HEIGHT;
    ((MINMAXINFO*)lParam)->ptMinTrackSize.x = SC_WIDTH;
    ((MINMAXINFO*)lParam)->ptMinTrackSize.y = SC_HEIGHT;
}

void drawIntoRoom(HDC hdc, HWND hWnd, HINSTANCE hInst) {
    HBRUSH osBrush, newBrush;
    osBrush = (HBRUSH)SelectObject(hdc, newBrush = (HBRUSH)GetStockObject(NULL_BRUSH));
    drawRoomList(hdc);
    drawUserName(hdc, hInst);
    drawChatArea(hdc, hWnd, hInst);
    drawUserList(hdc);
    DeleteObject(SelectObject(hdc, osBrush));
}

void drawRoomList(HDC hdc) {
    HBRUSH osBrush, newBrush;
    osBrush = (HBRUSH)SelectObject(hdc, newBrush = (HBRUSH)GetStockObject(NULL_BRUSH));
    Rectangle(hdc, r_roomlist.left, r_roomlist.top, r_roomlist.right, r_roomlist.bottom);
    DeleteObject(SelectObject(hdc, osBrush));
}

void drawUserName(HDC hdc, HINSTANCE hInst) {
    HBRUSH osBrush, newBrush;
    osBrush = (HBRUSH)SelectObject(hdc, newBrush = (HBRUSH)GetStockObject(NULL_BRUSH));
    Rectangle(hdc, r_username.left, r_username.top, r_username.right, r_username.bottom);
    DeleteObject(SelectObject(hdc, osBrush));
}

void drawChatArea(HDC hdc, HWND hWnd, HINSTANCE hInst) {
    HBRUSH osBrush, newBrush;
    osBrush = (HBRUSH)SelectObject(hdc, newBrush = (HBRUSH)GetStockObject(NULL_BRUSH));
    Rectangle(hdc, r_chatarea.left, r_chatarea.top, r_chatarea.right, r_chatarea.bottom);
    DeleteObject(SelectObject(hdc, osBrush));
}

void drawUserList(HDC hdc) {
    HBRUSH osBrush, newBrush;
    osBrush = (HBRUSH)SelectObject(hdc, newBrush = (HBRUSH)GetStockObject(NULL_BRUSH));
    Rectangle(hdc, r_userlist.left, r_userlist.top, r_userlist.right, r_userlist.bottom);
    DeleteObject(SelectObject(hdc, osBrush));
}