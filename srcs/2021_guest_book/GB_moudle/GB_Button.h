
#include "GB_moudles.h"


class GB_BUTTON {
public:
	RECT area;
	wchar_t name[20];
	COLORREF col;
	COLORREF line_col;
	DWORD handle;

	int x;
	int	y;
	int width;
	int height;
	

	GB_BUTTON(const wchar_t* name, DWORD handle, int x, int y, int size );
	GB_BUTTON(const wchar_t* name, DWORD handle, int x, int y, int width, int height);
	DWORD is_press(LPARAM lParam);
	void paint(HWND hwnd, HDC hdc);
private:
	void init(const wchar_t* name, DWORD handle, int x, int y, int width, int height);
};