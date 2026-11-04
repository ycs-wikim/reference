#include "DrawController.h"

namespace {
    inline void DrawPointsLine(HDC hdc, const std::vector<Point>& pts) {
        if (pts.empty()) return;
        if (pts.size() == 1) {
            MoveToEx(hdc, pts[0].x, pts[0].y, nullptr);
            LineTo(hdc, pts[0].x + 1, pts[0].y);
            return;
        }
        MoveToEx(hdc, pts[0].x, pts[0].y, nullptr);
        for (size_t i = 1; i < pts.size(); ++i) {
            LineTo(hdc, pts[i].x, pts[i].y);
        }
    }
}

void DrawController::DrawStrokes(HDC hdc,
    const std::vector<Stroke>& strokes,
    int penWidth,
    COLORREF color
    )
{

    for (const auto& s : strokes) { /// 다시 그릴 때 사용하는 역할
        LOGBRUSH style = {};
        style.lbStyle = BS_SOLID;
        style.lbColor = s.color;
        /// ExtCreatePen 사용
        HPEN pen = ExtCreatePen(PS_GEOMETRIC | s.penStyle, s.penWidth, &style, 0, nullptr);
        HGDIOBJ oldPen = SelectObject(hdc, pen);
        HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
        DrawPointsLine(hdc, s.points);
        SelectObject(hdc, oldBrush);
        SelectObject(hdc, oldPen);
        DeleteObject(pen);
    }
}

void DrawController::DrawLatestStroke(HDC hdc, const Stroke& stroke, int penWidth, COLORREF color) { /// 점과 점을 이어주는 역할

    LOGBRUSH style = {};
    style.lbStyle = BS_SOLID;
    style.lbColor = stroke.color;
    HPEN pen = ExtCreatePen(PS_GEOMETRIC | stroke.penStyle, stroke.penWidth,&style,0,nullptr);
    HGDIOBJ oldPen = SelectObject(hdc, pen);
    HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

    DrawPointsLine(hdc, stroke.points);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
}

// 점(dot)을 그리는 새 함수
void DrawController::DrawCursorDot(HDC hdc, POINT pos, int penWidth, COLORREF color, bool isErasing) {

    if (isErasing) {
        HBRUSH hFillBrush = CreateSolidBrush(RGB(255, 255, 255));
        HGDIOBJ hOldBrush = SelectObject(hdc, hFillBrush);

        HPEN hBorderPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        HGDIOBJ hOldPen = SelectObject(hdc, hBorderPen);

        int radius = penWidth / 2;
        if (radius < 2) radius = 2;

        Ellipse(hdc, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);

        SelectObject(hdc, hOldPen);
        SelectObject(hdc, hOldBrush);
        DeleteObject(hBorderPen);
        DeleteObject(hFillBrush);
    }
    else {
        HBRUSH hBrush = CreateSolidBrush(color);
        HGDIOBJ oldBrush = SelectObject(hdc, hBrush);
        HPEN hPen = (HPEN)GetStockObject(NULL_PEN);
        HGDIOBJ oldPen = SelectObject(hdc, hPen);

        int radius = penWidth / 2;
        if (radius < 2) radius = 2;

        Ellipse(hdc, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(hBrush);
    }
}