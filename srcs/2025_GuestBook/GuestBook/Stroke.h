#pragma once
#include <vector>
#include <windows.h>

struct Point {
    int x, y;   //점의 좌표
    DWORD timestamp;    //기록된 시간
};

struct Stroke {
    std::vector<Point> points;
    COLORREF color = RGB(0, 0, 0);
    int thickness = 2;
    int penStyle=PS_SOLID;
    int penWidth = 2;
};