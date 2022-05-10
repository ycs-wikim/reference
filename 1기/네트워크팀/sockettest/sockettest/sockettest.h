#pragma once

#include "resource.h"

#define MAX 512								// 최대 접속 클라이언트 수 및 최대 패킷 데이터
#define MAX_LOADSTRING 100				
#define IDM_BTN_ServSTART 101				// 서버 시작 메세지에 대한 코드값
#define IDM_BTN_ServCLOSE 102				// 서버 종료 메세지에 대한 코드값

#define SC_WIDTH 1424						// 윈도우 창의 넓이를 나타냅니다.
#define SC_HEIGHT 750						// 윈도우 창의 높이를 나타냅니다.

/*!
* @breif		서버 동작 시 실행되는 스레드
* @detail		해당 스레드가 서버의 역할을 하며 수신을 담당한다.
* @param		LPVOID	param	hWnd값 즉 윈도우 핸들값을 갖고 실행된다.
* @return		리턴값은 아무 의미를 갖지 않는다.
* @retval		1 정상종료
* @bug			
* @warning		
*/
DWORD WINAPI runServ(LPVOID Param);

void drawClntList(HWND hWnd, HDC hdc, POINT* pos);