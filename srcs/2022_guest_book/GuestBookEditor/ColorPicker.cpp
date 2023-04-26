#include "pch.h"
#include "ColorPicker.h"
#include "Window.h"

using namespace std;
using namespace Gdiplus;

ColorPicker::ColorPicker(HWND hWnd)
{
    this->hWnd = hWnd;

    width_ = 420;
    height_ = 300;
    x_ = (Window::GetInstance()->GetWindowArea().right - width_) / 2;
    y_ = (Window::GetInstance()->GetWindowArea().bottom - height_) / 2;
    s_ = 0;
    v_ = 1.0f;
    palette_width_ = 200;
    palette_height_ = 200;
    hue_slider_width_ = 30;
    hue_slider_height_ = 200;
    pen_size_slider_width_ = 200;
    pen_size_slider_height_ = 30;
    color_preview_width_ = 30;
    color_preview_height_ = 30;
    current_color_ = HSVToRGB(360.0f - h_, s_, 1.0f - v_);
    pen_size_ = 10;

    button_close_ = make_unique<Button>([=]
        {
            is_color_picker_open_ = false;
            InvalidateRect(hWnd, &color_picker_area_, FALSE);
        });
}

bool ColorPicker::OnOpen()
{
    return is_color_picker_open_;
}


void ColorPicker::MouseUp()
{
    if (is_color_picker_open_)
    {
        if (is_palette_click_ || is_hue_slider_click_ || is_pen_size_slider_click_)
        {
            is_palette_click_ = false;
            is_hue_slider_click_ = false;
            is_pen_size_slider_click_ = false;
        }
    }
}

void ColorPicker::MouseDown(POINT mouse_position)
{
    if (is_color_picker_open_)
    {
        if (PtInRect(&palette_area_, mouse_position))
        {
            PaletteControl(mouse_position);
            is_palette_click_ = true;
        }
        else if (PtInRect(&hue_slider_area_, mouse_position))
        {
            HueSliderControl(mouse_position);
            is_hue_slider_click_ = true;
        }
        else if (PtInRect(&pen_size_slider_area_, mouse_position))
        {
            PenSizeSliderControl(mouse_position);
            is_pen_size_slider_click_ = true;
        }

        button_close_->MouseDown(mouse_position);
    }
}

void ColorPicker::MouseMove(POINT mouse_position)
{
    if (is_color_picker_open_)
    {
        if (is_palette_click_)
        {
            if (!PtInRect(&palette_area_, mouse_position))
            {
                MouseUp();
                return;
            }

            PaletteControl(mouse_position);
        }
        
        if (is_hue_slider_click_)
        {
            if (!PtInRect(&hue_slider_area_, mouse_position))
            {
                MouseUp();
                return;
            }

            HueSliderControl(mouse_position);
        }
        
        if (is_pen_size_slider_click_)
        {
            if (!PtInRect(&pen_size_slider_area_, mouse_position))
            {
                MouseUp();
                return;
            }

            PenSizeSliderControl(mouse_position);
        }
    }
}

void ColorPicker::PaletteControl(POINT mouse_position)
{
    s_ = min(max(((mouse_position.x - palette_x_) * 1.0f) / palette_width_, 0), 1.0f);
    v_ = min(max(((mouse_position.y - palette_y_) * 1.0f) / palette_height_, 0), 1.0f);
    InvalidateRect(hWnd, NULL, FALSE);
}

void ColorPicker::HueSliderControl(POINT mouse_position)
{
    h_ = min(max(((mouse_position.y - hue_slider_y_) * 360.0f) / hue_slider_height_, 0), 360.0f);
    InvalidateRect(hWnd, NULL, FALSE);
}

void ColorPicker::PenSizeSliderControl(POINT mouse_position)
{
    pen_size_ = min(max(((mouse_position.x - pen_size_slider_x_) * 30.0f) / pen_size_slider_width_, 0), 30.0f);
    InvalidateRect(hWnd, NULL, FALSE);
}

void ColorPicker::Open()
{
    is_color_picker_open_ = !is_color_picker_open_;

    InvalidateRect(hWnd, &color_picker_area_, FALSE);
}

void ColorPicker::Draw(HDC hdc)
{
    x_ = (Window::GetInstance()->GetWindowArea().right - width_) / 2;
    y_ = (Window::GetInstance()->GetWindowArea().bottom - height_) / 2;

    color_picker_area_ = { x_, y_, x_ + width_, y_ + height_ };

    if (is_color_picker_open_)
    {
        Graphics graphics(hdc);

        Pen black_pen(Color(255, 0, 0, 0));
        Pen white_pen(Color(255, 255, 255, 255));
        Pen contour_pen(Color(255, 185, 185, 185));
        Pen thumb_contour_pen(Color(255, 149, 149, 149));

        SolidBrush white_brush(Color(255, 255, 255, 255));
        SolidBrush black_brush(Color(255, 0, 0, 0));
        SolidBrush white_alpha_brush(Color(50, 255, 255, 255));
        SolidBrush background_brush(Color(255, 238, 238, 238));

        graphics.FillRectangle(&background_brush, x_, y_, width_, height_);

        graphics.FillRectangle(&white_brush, x_, y_, width_, 30);

        StringFormat string_format;
        string_format.SetLineAlignment(StringAlignmentCenter);

        FontFamily arial_font(L"Arial");
        Font font_style(&arial_font, 12, FontStyleBold  , UnitPixel);

        PointF header_font_position(x_ + 20, y_ + 15);
        graphics.DrawString(L"Color Picker", -1, &font_style, header_font_position, &string_format, &black_brush);

        // 팔레트
        palette_x_ = x_ + 20;
        palette_y_ = y_ + 40;

        SolidBrush palette_background(Color(255, 255, 255, 255));
        graphics.FillRectangle(&palette_background, palette_x_, palette_y_, palette_width_, palette_height_);

        LinearGradientBrush palette_horizontal(
            Point(palette_x_, palette_y_),
            Point(palette_x_ + palette_width_, palette_y_),
            Color(0, 255, 255, 255),
            HSVToRGB(360.0f - h_, 1, 1));

        graphics.FillRectangle(&palette_horizontal, palette_x_, palette_y_, palette_width_, palette_height_);

        LinearGradientBrush palette_vertical(
            Point(palette_x_, palette_y_ + palette_height_),
            Point(palette_x_, palette_y_),
            Color(255, 0, 0, 0),
            Color(0, 255, 255, 255));

        graphics.FillRectangle(&palette_vertical, palette_x_, palette_y_, palette_width_, palette_height_);

        Region region(Rect(palette_x_, palette_y_, palette_width_, palette_height_));

        // 클리핑 마스크 시작
        graphics.SetClip(&region, CombineModeReplace);

        graphics.FillEllipse(&white_alpha_brush, palette_x_ + (s_ / 1.0f) * palette_width_ - 10, palette_y_ + (v_ / 1.0f) * palette_height_ - 10, 20, 20);
        graphics.DrawEllipse(&white_pen, palette_x_ + (s_ / 1.0f) * palette_width_ - 10, palette_y_ + (v_ / 1.0f) * palette_height_ - 10, 20, 20);

        // 클리핑 마스크 종료
        graphics.ResetClip();

        // 색상 슬라이더
        hue_slider_x_ = palette_x_ + palette_width_ + 10;
        hue_slider_y_ = palette_y_;

        graphics.FillRectangle(&white_brush, hue_slider_x_, hue_slider_y_, hue_slider_width_, hue_slider_height_);

        Image hue_slider_image(L"Resources/Hue.png");
        graphics.DrawImage(&hue_slider_image, hue_slider_x_, hue_slider_y_, hue_slider_width_, hue_slider_height_);

        Point left_points[] = {
            Point(hue_slider_x_, hue_slider_y_ + (h_ / 360.0f) * hue_slider_height_),
            Point(hue_slider_x_ - 5, hue_slider_y_ + (h_ / 360.0f) * hue_slider_height_ + 5),
            Point(hue_slider_x_ - 5, hue_slider_y_ + (h_ / 360.0f) * hue_slider_height_ - 5) };

        graphics.FillPolygon(&white_brush, left_points, 3);
        graphics.DrawPolygon(&thumb_contour_pen, left_points, 3);

        Point right_points[] = {
            Point(hue_slider_x_ + hue_slider_width_, hue_slider_y_ + (h_ / 360.0f) * hue_slider_height_),
            Point(hue_slider_x_ + hue_slider_width_ + 5, hue_slider_y_ + (h_ / 360.0f) * hue_slider_height_ + 5),
            Point(hue_slider_x_ + hue_slider_width_ + 5, hue_slider_y_ + (h_ / 360.0f) * hue_slider_height_ - 5) };

        graphics.FillPolygon(&white_brush, right_points, 3);
        graphics.DrawPolygon(&thumb_contour_pen, right_points, 3);

        // 팬 크기 슬라이더
        pen_size_slider_x_ = palette_x_;
        pen_size_slider_y_ = palette_y_ + palette_height_ + 10;

        LinearGradientBrush pen_size_slider_horizontal(
            Point(pen_size_slider_x_, pen_size_slider_y_),
            Point(pen_size_slider_x_ + pen_size_slider_width_, pen_size_slider_y_),
            Color(255, 255, 255, 255),
            Color(255, 200, 200, 200));

        graphics.FillRectangle(&pen_size_slider_horizontal, pen_size_slider_x_, pen_size_slider_y_, pen_size_slider_width_, pen_size_slider_height_);

        Point top_points[] = {
            Point(pen_size_slider_x_ + (pen_size_ / 30.0f) * pen_size_slider_width_, pen_size_slider_y_),
            Point(pen_size_slider_x_ + (pen_size_ / 30.0f) * pen_size_slider_width_ - 5, pen_size_slider_y_ - 5),
            Point(pen_size_slider_x_ + (pen_size_ / 30.0f) * pen_size_slider_width_ + 5, pen_size_slider_y_ - 5) };

        graphics.FillPolygon(&white_brush, top_points, 3);
        graphics.DrawPolygon(&thumb_contour_pen, top_points, 3);

        graphics.DrawLine(&white_pen, pen_size_slider_x_, pen_size_slider_y_ + 5, pen_size_slider_x_ + 10, pen_size_slider_y_ + 5);

        Point bottom_points[] = {
            Point(pen_size_slider_x_ + (pen_size_ / 30.0f) * pen_size_slider_width_, pen_size_slider_y_ + pen_size_slider_height_),
            Point(pen_size_slider_x_ + (pen_size_ / 30.0f) * pen_size_slider_width_ - 5, pen_size_slider_y_ + pen_size_slider_height_ + 5),
            Point(pen_size_slider_x_ + (pen_size_ / 30.0f) * pen_size_slider_width_ + 5, pen_size_slider_y_ + pen_size_slider_height_ + 5) };

        graphics.FillPolygon(&white_brush, bottom_points, 3);
        graphics.DrawPolygon(&thumb_contour_pen, bottom_points, 3);

        WCHAR pen_size_word[1024];
        wsprintf(pen_size_word, L"%dpx", (int)trunc(pen_size_));

        PointF pen_size_font_position(pen_size_slider_x_ + 5, pen_size_slider_y_ + 15);
        graphics.DrawString(pen_size_word, -1, &font_style, pen_size_font_position, &string_format, &black_brush);

        current_color_ = HSVToRGB(360.0f - h_, s_, 1.0f - v_);

        // 색상 미리보기
        color_preview_x_ = pen_size_slider_x_ + pen_size_slider_width_ + 10;
        color_preview_y_ = pen_size_slider_y_;

        SolidBrush color_preview_brush(current_color_);
        graphics.FillRectangle(&color_preview_brush, color_preview_x_, color_preview_y_, color_preview_width_, color_preview_height_);

        palette_area_ = { palette_x_ - 10, palette_y_ - 10, palette_x_ + palette_width_ + 10, palette_y_ + palette_height_ + 10 };
        hue_slider_area_ = { hue_slider_x_, hue_slider_y_ - 10, hue_slider_x_ + hue_slider_width_, hue_slider_y_ + hue_slider_height_ + 10 };
        pen_size_slider_area_ = { pen_size_slider_x_ - 10, pen_size_slider_y_, pen_size_slider_x_ + pen_size_slider_width_ + 10, pen_size_slider_y_ + pen_size_slider_height_ };

        WCHAR rgb_word[1024];
        wsprintf(rgb_word, L"RGB: %d, %d, %d", GetR(), GetG(), GetB());

        PointF rgb_font_position(hue_slider_x_ + hue_slider_width_ + 10, hue_slider_y_);
        graphics.DrawString(rgb_word, -1, &font_style, rgb_font_position, &black_brush);

        WCHAR hex_word[1024];
        wsprintf(hex_word, L"HEX: #%02x%02x%02x", GetR(), GetG(), GetB());

        PointF hex_font_position(hue_slider_x_ + hue_slider_width_ + 10, hue_slider_y_ + 13);
        graphics.DrawString(hex_word, -1, &font_style, hex_font_position, &black_brush);

        PointF preview_font_position(hue_slider_x_ + hue_slider_width_ + 10, hue_slider_y_ + 90);
        graphics.DrawString(L"Preview", -1, &font_style, preview_font_position, &black_brush);

        graphics.FillRectangle(&white_brush, hue_slider_x_ + hue_slider_width_ + 10, hue_slider_y_ + 110, 130, 130);

        Pen preivew_pen(current_color_, pen_size_);

        Point preview_points[] = {
            Point(hue_slider_x_ + hue_slider_width_ + 30, hue_slider_y_ + 175),
            Point(hue_slider_x_ + hue_slider_width_ + 52.5f, hue_slider_y_ + 170),
            Point(hue_slider_x_ + hue_slider_width_ + 97.5f, hue_slider_y_ + 180),
            Point(hue_slider_x_ + hue_slider_width_ + 120, hue_slider_y_ + 175) };

        graphics.DrawCurve(&preivew_pen, preview_points, 4);

        graphics.DrawRectangle(&contour_pen, x_, y_, width_ - 1, height_ - 1);

        button_close_->Draw(hdc, L"✕", x_ + width_ - 30, y_, 30, 30);
    }
}

int ColorPicker::GetPenSize()
{
    return (int)trunc(pen_size_);
}

// HSV 값을 RGB 값으로 변환
Color ColorPicker::HSVToRGB(double h, double s, double v)
{
    double r = 0;
    double g = 0;
    double b = 0;

    if (s == 0)
    {
        r = v;
        g = v;
        b = v;
    }
    else
    {
        int i;
        double f, p, q, t;

        if (h == 360)
        {
            h = 0;
        }
        else
        {
            h = h / 60;
        }

        i = (int)trunc(h);
        f = h - i;

        p = v * (1.0 - s);
        q = v * (1.0 - (s * f));
        t = v * (1.0 - (s * (1.0 - f)));

        switch (i)
        {
        case 0:
            r = v;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = v;
            b = p;
            break;
        case 2:
            r = p;
            g = v;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = v;
            break;
        case 4:
            r = t;
            g = p;
            b = v;
            break;
        default:
            r = v;
            g = p;
            b = q;
            break;
        }
    }

    return Color(255, (BYTE)(r * 255), (BYTE)(g * 255), (BYTE)(b * 255));
}

BYTE ColorPicker::GetR()
{
    return current_color_.GetR();
}

BYTE ColorPicker::GetG()
{
    return current_color_.GetG();
}

BYTE ColorPicker::GetB()
{
    return current_color_.GetB();
}

COLORREF ColorPicker::GetRGB()
{
    return RGB(GetR(), GetG(), GetB());
}
