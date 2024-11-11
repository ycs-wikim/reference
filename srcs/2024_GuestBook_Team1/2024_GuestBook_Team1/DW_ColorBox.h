#pragma once
#include <Windows.h>
#include "DrowWindow.h"
#include <Windowsx.h>
#include <cmath>
#include <string>
#include "DW_ToolMenu.h"
#include "PenThickness.h"

struct RoundRECT {
    int left;
    int top;
    int right;
    int bottom;
    int radiusX;
    int radiusY;
};

class DW_ColorBox
{
public:
    static int colorSelect;

    static COLORREF colorP[3];

    static int thicknessP[3];

    static COLORREF getColorNum(int);

    static void setColorNum(int num, COLORREF color);

    static int getThicknessNum(int colorSelect);  // 굵기 값을 가져오는 메서드

    static void setThicknessNum(int num, int thickness); // 굵기 값을 설정하는 메서드

    void DrawColorWheel(HDC hdc, int centerX, int centerY, int radius);
    void DrawColorBar(HDC hdc, RECT rect);
    void DrawSelectedColor(HDC hdc);
    void handleColorSelection(HWND hWnd, int x, int y);
    void DrawSlider(HDC hdc, RECT rect, int value, int max);
    void DrawThicknessSlider(HDC hdc, RECT rect, RoundRECT roundrect,int thicknessValue, int maxThickness);
    COLORREF HSVtoRGB(double h, double s, double v);
    void RGBtoHSV(COLORREF rgb, double& h, double& s, double& v);

};

