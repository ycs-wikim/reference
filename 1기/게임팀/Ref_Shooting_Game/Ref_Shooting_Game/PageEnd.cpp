#include "PageEnd.h"
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")

HBITMAP PageEnd::BIT_GameOver = NULL;

PageEnd::PageEnd()
{
	end = 1;
}

void PageEnd::SetGameOverBit(HINSTANCE hInst)
{
	BIT_GameOver = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GAMEOVER));
}

void PageEnd::DeleteGameOverBit()
{
	if (BIT_GameOver != NULL) DeleteObject(BIT_GameOver);
}

void PageEnd::DrawEnd(HDC hdc)
{
	HDC hdc2 = CreateCompatibleDC(hdc);

	HBITMAP OldBitmap = (HBITMAP)SelectObject(hdc2, BIT_GameOver); //메모리DC에 비트맵오브젝트를 넣는다.

	//투명화  /   화이트( 255, 255, 255 ) 색은 무시한다.
	// hdc, 그려질 x, 그려질 y, 가로, 세로, hdc2, 0, 0, 가로, 세로, 무시할 색상 )
	TransparentBlt(hdc, 580, 125, 236, 236, hdc2, 0, 0, 236, 236, RGB(255, 255, 255));


	WCHAR buf[100] = { 0, }; //문자열 버퍼
	int x = 640;
	int y = 400;

	Rectangle(hdc, 645, 405, 755, 500); // width 110 height 95
	if (end == 1)
	{

		Rectangle(hdc, 665, 415, 735, 440); //70 25

	}
	else if (end == 2)
	{
		Rectangle(hdc, 650, 440, 750, 465); // 100 25

	}

	else if (end == 3)
	{
		Rectangle(hdc, 660, 465, 740, 490); // 80 25

	}

	wsprintfW(buf, L"RESTART");
	TextOut(hdc, x + 30, y + 20, buf, lstrlenW(buf));
	wsprintfW(buf, L"GO TO START");
	TextOut(hdc, x + 15, y + 45, buf, lstrlenW(buf));
	wsprintfW(buf, L"EXIT GAME");
	TextOut(hdc, x + 25, y + 70, buf, lstrlenW(buf));

	SelectObject(hdc2, OldBitmap);
	DeleteDC(hdc2);
}

int PageEnd::end_choose(WPARAM wParam)
{
	int x = 0;
	switch (wParam)
	{
	case 0x26:  // 위쪽
		end--;
		if (end == 0)
			end = 3;
		break;
	case 0x28:  // 아래쪽
		end++;
		if (end == 4)
			end = 1;
		break;
	case 0x0D:// Enter
		x = end;
		break;
	}
	return x;
}

