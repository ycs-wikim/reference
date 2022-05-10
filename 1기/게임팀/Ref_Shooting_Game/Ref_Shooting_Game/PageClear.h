#pragma once

#include"framework.h"

class PageClear
{
public:
	PageClear();
	void DrawClear(HDC hdc);
	int end_choose(WPARAM Wparam);

private:
	int end;
};

