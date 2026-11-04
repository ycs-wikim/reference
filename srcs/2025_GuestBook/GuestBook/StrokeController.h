#pragma once
#include <vector>
#include <windows.h>
#include <mutex>
#include "Stroke.h"

class StrokeController {
public:
    void Begin(int x, int y, COLORREF color,int penStyle, int penWidth);
    void Add(int x, int y);
    void End();
    void Clear();
    void AddPoint(Point p);
    void AddStroke();

    const Stroke* Current() const { return recording ? &current : nullptr; }
    bool IsRecording() const { return recording; }

    void setStrokes(const std::vector<Stroke> strokes) { this->strokes = strokes; }
    const std::vector<Stroke>& Strokes() const { return strokes; }

    void Reset();
private:
    std::mutex mtx;
    DWORD lastTime{};
    std::vector<Stroke> strokes;
    Stroke current;
    bool recording = false;
};
