#pragma once

#include "Button.h"

class Control
{
private:
	HWND hWnd;

	int x_;
	int y_;
	int width_;
	int height_;

	std::unique_ptr<Button> button_new_file_;
	std::unique_ptr<Button> button_load_;
	std::unique_ptr<Button> button_save_;
	std::unique_ptr<Button> button_color_;
	std::unique_ptr<Button> button_play_;
public:
	Control(HWND hWnd);
	~Control() = default;

	void MouseDown(POINT mouse_position);
	void Draw(HDC hdc);

	int GetWidth();
	int GetHeight();
};
