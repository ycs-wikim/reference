#include "implicit_link_test.h"

//함수 작성
 void draw_rac(HWND hWnd, LPARAM lParam)
{
	 HDC hdc = GetDC(hWnd);
	 int x = LOWORD(lParam);
	 int y = HIWORD(lParam);

	 MoveToEx(hdc, x, y, NULL);
	 LineTo(hdc, x + 200, y);
	 LineTo(hdc, x + 200, y + 200);

	 MoveToEx(hdc, x + 200, y + 200, NULL);
	 LineTo(hdc, x, y+200);
	 LineTo(hdc, x, y);
};