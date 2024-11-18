#pragma once

#include <thread>
#include "Struct.h"
#include "WndFunc.h"
#include "Resource.h"
#include <gdiplus.h> //gdi+ 기능을 사용하기 위한 헤더파일.
#pragma comment (lib, "gdiplus.lib") // GDI+ 라이브러리 링크
#include <cmath> // sqrt(제곱 근) 사용을 위한 추가
#include <chrono> // 붓 브러쉬 사용을 위한 시간 관련 라이브 러리

class Function
{

private:

	HDC hdc;
	HPEN nPen, oPen;
	HBRUSH hPen;
	RECT clientRect;
	

	int px, py;
	int px2, py2;
	int x, y, x2, y2;
	int px3, py3;

	bool stampOn = false;	// 스탬프 모드 활성화 여부
	static int stampID;

	// 붓 브러쉬 변수 
	std::chrono::steady_clock::time_point DrawTime; // 좌클릭 한 시간
	std::chrono::steady_clock::time_point currentTime; // 그리기 시작한 시간
	std::chrono::steady_clock::time_point lastThicknessChangeTime; // 두께 변하는 시간
	const int Min_Thickness = 2;  // 최소 두께
	const int Threshold_Speed = 450; // 속도 임계값 (값 낮을 수록 느리게 그려도 짦아짐)
	const int Smoothing_Factor = 1; // 두께 전환 시 부드러움 정도 (값 클수록 확 줄어듬)
	const int Update_Interval = 30; // 두께 업데이트 간격 (밀리초) (값 클수록 크기 변하는 주기가 줄어듬)
	int currentThickness = 0; // 붓 브러쉬 크기가 바뀌는 변수 (초기화 할려고 0 집어넣음)
	//여기까지 브러쉬 변수 추가


	bool isLeftClick = false;
	bool isReplay = false;
	bool isReset = true;
	bool isCanvas = true;

	ULONG_PTR gdiplusToken;

	void replay(HWND);
	void record(PINFO);

	HDC cHdc = nullptr;
	HPEN CanvasPen = nullptr;
	PAINTSTRUCT cPS = { 0 };

	std::thread replayThreadHandle;
	HANDLE threadHandle;
public:
	static int bShape; // 브러쉬 종류 버튼 없어서 해당 코드에다 변수 넣어서 사용.
	void setisLeftClick(bool);
	bool getisLeftClick();

	void setisCanvas(bool, LPARAM);

	void draw(HWND, PINFO, bool);		//뒤에 브러쉬 추가
	void mouseUD(PINFO, bool);
	void replayThread(HWND);

	void clearDrawing(HWND);
	void reDrawing(HWND);

	void setIsReplay(bool);
	bool getIsReplay();
	void setIsReset(bool);
	bool getIsReset();

	void suspendReplay();
	void resumeReplay();

	void stopReplay(HWND);

	bool getDrawLInfoEmpty();

	void setBShape(int);

	void setPenStyle(PINFO, COLORREF); // LPARAM 인수 에서 PINFO 로 바꿈
	void GDIPlusStart(); // gdi+ 시작 함수 
	void GDIPlusEnd(); // gdi+ 종료 함수

	void paint(HDC, RECT, PAINTSTRUCT);

	void stampIcon(int);

	void re_draw(HDC phdc, PINFO pino, HWND hd);

	LINFO getDrawLInfo();

	static HWND hWnd;
	static LINFO drawLInfo;

	static int penNum;


};