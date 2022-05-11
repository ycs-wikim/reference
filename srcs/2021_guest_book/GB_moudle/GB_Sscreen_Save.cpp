#include "GB_Sscreen_Save.h"

void ScrnTimer(HWND hWnd)
{
	KillTimer(hWnd, ScrnSave_Timer);
	SetTimer(hWnd, ScrnSave_Timer, ScrnSaveToTime, NULL);
}

void ScrnSavePaint(HWND hWnd)
{
	RECT* window = {};
	HDC hdc;



	hdc = GetDC(0);
	//GetWindowRect(0,window);

	Rectangle(hdc, window->left,window->top,window->right,window->bottom);
	ReleaseDC(0, hdc);
}
