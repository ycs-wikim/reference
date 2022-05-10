#pragma once

#include "framework.h"
#include <iostream>

class PageEnd
{
public: 
	PageEnd();
	static void SetGameOverBit(HINSTANCE hInst);
	static void DeleteGameOverBit();
	void DrawEnd(HDC hdc);
	int end_choose(WPARAM wparam);

private:
	int end;
	static HBITMAP BIT_GameOver;
};

