#pragma once
#include <windows.h>
#include <vector>
#include "Stroke.h"

class DrawController {
public:
    void DrawStrokes(HDC hdc,
        const std::vector<Stroke>& stroke,
        int penWidth = 2,
        COLORREF color = RGB(30, 30, 30));

    void DrawLatestStroke(HDC hdc, const Stroke& stroke, int penWidth, COLORREF color);
    void DrawCursorDot(HDC hdc, POINT pos, int penWidth, COLORREF color, bool isErasing);

};