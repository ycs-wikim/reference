#pragma once
#include "framework.h"
static int num;
class PageStart
{
public:
	PageStart();
	void DrawStart(HDC hdc);
	int start_choose(WPARAM wParam);
};

