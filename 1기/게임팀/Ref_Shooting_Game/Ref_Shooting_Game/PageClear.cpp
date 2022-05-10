#include "PageClear.h"


PageClear::PageClear()
{
	end = 1;
}

void PageClear::DrawClear(HDC hdc)
{
	//HDC hdc2 = CreateCompatibleDC(hdc);

	//HBITMAP MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_GAMEOVER));//비트맵 리소스를 받아온다.
	//HBITMAP OldBitmap = (HBITMAP)SelectObject(hdc2, MyBitmap); //메모리DC에 비트맵오브젝트를 넣는다.
//	BitBlt(hdc, 590, 100, 700, 200, hdc2, 0, 0, SRCCOPY); // DC로 복사(SRCCOPY)한다.
	//TransparentBlt(hdc, 580, 125, 236, 236, hdc2, 0, 0, 236, 236, RGB(255, 255, 255));

	WCHAR buf[100] = { 0, }; //문자열 버퍼
	int x = 640;
	int y = 400;

	Rectangle(hdc, 645, 405, 755, 500);
	if (end == 1)
	{

		Rectangle(hdc, 650, 415, 750, 440);

	}
	else if (end == 2)
	{
		Rectangle(hdc, 660, 440, 740, 465);

	}

	//wsprintfW(buf, L"RESTART");
	//TextOut(hdc, x + 30, y + 20, buf, lstrlenW(buf));
	wsprintfW(buf, L"GO TO START");
	TextOut(hdc, x + 15, y + 20, buf, lstrlenW(buf));
	wsprintfW(buf, L"EXIT GAME");
	TextOut(hdc, x + 25, y + 45, buf, lstrlenW(buf));
}

int PageClear::end_choose(WPARAM wParam)
{
	int x = 0;
	switch (wParam)
	{
	case 0x26:  // 위쪽
		end--;
		if (end == 0)
			end = 2;
		break;
	case 0x28:  // 아래쪽
		end++;
		if (end == 3)
			end = 1;
		break;
	case 0x0D:// Enter
		x = end;
		break;
	}
	return x;
}

