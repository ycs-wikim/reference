#pragma once

#define MAX 512
#define MAX_LOADSTRING 100
#define ID_EDIT 101

#define IDM_BTN_TEST1 204
#define IDM_BTN_TEST2 205
#define IDM_BTN_TEST3 206

#define IDM_BTN_ServConn 1000				// 연결 시작 메세지에 대한 코드값
#define IDM_BTN_ServDC 1001				// 연결 종료 메세지에 대한 코드값
#define IDM_BTN_SendFile 1002

#define SC_WIDTH 1280
#define SC_HEIGHT 800

#define chatX 300

#include "resource.h"
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windowsx.h>

#pragma comment(lib, "ws2_32.lib")

// 서버 통신 스레드 함수
DWORD WINAPI connServ(LPVOID Param);

// 화면 크기 설정과 고정을 위한 함수
void ScreenFix(LPARAM lParam);
void ScreenSet(HWND hWnd);

// 화면 구성을 위한 함수
void drawIntoRoom(HDC hdc, HWND hWnd, HINSTANCE hInst);
void drawRoomList(HDC hdc);
void drawUserName(HDC hdc, HINSTANCE hInst);
void drawChatArea(HDC hdc, HWND hWnd, HINSTANCE hInst);
void drawUserList(HDC hdc);