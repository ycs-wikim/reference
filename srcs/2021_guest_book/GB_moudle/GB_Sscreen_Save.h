#include "GB_moudles.h"

#define ScrnSave_Timer 7000			// 화면보호기 타이머
#define ScrnSaveToTime 30 * 1000	// 화면보호기까지 시간 30초

void ScrnTimer(HWND hWnd);			// 화면보호기 타이머 재설정
void ScrnSavePaint(HWND hWnd);		// 화면보호기 그리기