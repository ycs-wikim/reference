#pragma once

#include "Button.h"

class ColorPicker
{
private:
    HWND hWnd;

    // 생성될 x, y 좌표
    int x_;
    int y_;
    int width_ = 420; // 280
    int height_ = 300;

    double h_; // 색상(Hue)
    double s_ = 1; // 채도(Saturation)
    double v_; // 명도(Value)
    double pen_size_; // 팬 크기

    // 영역
    RECT color_picker_area_;
    RECT palette_area_;
    RECT hue_slider_area_;
    RECT pen_size_slider_area_;

    // 팔레트
    int palette_x_;
    int palette_y_;
    int palette_width_;
    int palette_height_;

    // 색상 슬라이더
    int hue_slider_x_;
    int hue_slider_y_;
    int hue_slider_width_;
    int hue_slider_height_;

    // 팬 크기 슬라이더
    int pen_size_slider_x_;
    int pen_size_slider_y_;
    int pen_size_slider_width_;
    int pen_size_slider_height_;

    // 색상 미리보기
    int color_preview_x_;
    int color_preview_y_;
    int color_preview_width_;
    int color_preview_height_;

    Gdiplus::Color current_color_;

    bool is_color_picker_open_;
    bool is_palette_click_;
    bool is_hue_slider_click_;
    bool is_pen_size_slider_click_;

    std::unique_ptr<Button> button_close_;

    void PaletteControl(POINT mouse_position);
    void HueSliderControl(POINT mouse_position);
    void PenSizeSliderControl(POINT mouse_position);
public:
    ColorPicker(HWND hWnd);
    ~ColorPicker() = default;

    bool OnOpen();

    void MouseUp();
    void MouseDown(POINT mouse_position);
    void MouseMove(POINT mouse_position);
    void Open();
    void Draw(HDC hdc);

    int GetPenSize();

    Gdiplus::Color HSVToRGB(double h, double s, double v);

    BYTE GetR();
    BYTE GetG();
    BYTE GetB();

    COLORREF GetRGB();
};
