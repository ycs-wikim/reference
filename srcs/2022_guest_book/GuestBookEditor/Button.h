#pragma once

#include<functional>

class Button
{
private:
	int x_;
	int y_;
	int width_;
	int height_;

	int image_width_;
	int image_height_;

	RECT button_area_;

	std::function<void()> callback_;

	Gdiplus::Color background_color_;
	Gdiplus::Color contour_color_;
	Gdiplus::Color shadow_color_;
	Gdiplus::Color text_color_;

	bool is_interactable_;
	bool is_shadow_;
	bool is_background_;
	bool is_contour_;

	Gdiplus::Image* image_;
public:
	Button(std::function<void()> callback);
	~Button() = default;

	void MouseDown(POINT mouse_position);
	void Draw(HDC hdc, LPCWSTR text, int x, int y, int width, int height);

	void SetInteractable(bool value);
	void SetShadow(bool value);
	void SetBackground(bool value);
	void SetContour(bool value);
	void SetBackgroundColor(Gdiplus::Color color);
	void SetContourColor(Gdiplus::Color color);
	void SetShadowColor(Gdiplus::Color color);
	void SetTextColor(Gdiplus::Color color);
	void SetImage(Gdiplus::Image* image, int width, int height);
};

