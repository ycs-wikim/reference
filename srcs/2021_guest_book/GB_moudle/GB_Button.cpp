#include"GB_Button.h"

GB_BUTTON::GB_BUTTON(const wchar_t* name, DWORD handle, int x, int y, int size = 10)
{
	init(name, handle, x, y, size, size);
}
GB_BUTTON::GB_BUTTON(const wchar_t* name, DWORD handle, int x, int y, int width, int height)
{
	init(name, handle, x, y, width, height);
}

DWORD GB_BUTTON::is_press(LPARAM lParam)
{
	RECT rect_temp;
	rect_temp.left = LOWORD(lParam);
	rect_temp.right = rect_temp.left + 1;
	rect_temp.top = HIWORD(lParam);
	rect_temp.bottom = rect_temp.top + 1;
	if (IntersectRect(&rect_temp, &this->area, &rect_temp))
	{
		return this->handle;
	}
	return 0;
}
void GB_BUTTON::paint(HWND hWnd, HDC hdc)
{
	HPEN open, npen;
	HBRUSH obrush, nbrush;
	HFONT ofont, nfont;
	int x, y;
	
	npen = CreatePen(PS_SOLID, 3, RGB(200, 200, 200));
	nbrush = CreateSolidBrush(RGB(240, 240, 240));
	nfont = CreateFont((this->height/2), 0, 0, 0, FW_BOLD, 0, 0, 0,HANGEUL_CHARSET,
		0, 0, 0,VARIABLE_PITCH | FF_ROMAN, TEXT("±¼¸²"));

	x = this->x + (this->width - ((this->height / 2) / 3 * 2 * lstrlen(this->name))) / 2;
	//x = this->x + (this->width / 2) - (this->height / 3) * (lstrlen(this->name)) ;
	//y = this->y + (this->height - (this->height / 3) * 2) / 2;
	y = this->y + this->height / 5;
	
	open = (HPEN)SelectObject(hdc,npen);
	obrush = (HBRUSH)SelectObject(hdc, nbrush);
	ofont = (HFONT)SelectObject(hdc, nfont);
	SetBkMode(hdc, TRANSPARENT);

	Rectangle(hdc, this->area.left, this->area.top, this->area.right, this->area.bottom);
	TextOut(hdc, x-4, y, this->name, lstrlen(this->name));

	SelectObject(hdc, open);
	SelectObject(hdc, obrush);
	SelectObject(hdc, ofont);

	DeleteObject(npen);
	DeleteObject(nbrush);
	DeleteObject(nfont);
}

void GB_BUTTON::init(const wchar_t* name, DWORD handle, int x, int y, int width, int height)
{
	RECT rect_temp;

	wcscpy(this->name, name);

	this->handle = handle;

	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	rect_temp.left = x;
	rect_temp.top = y;
	rect_temp.right = x + width;
	rect_temp.bottom = y + height;
	this->area = rect_temp;

	col = RGB(200,200,200);
	line_col = RGB(20, 20, 20);
}