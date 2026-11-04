#include "StrokeController.h"

void StrokeController::Begin(int x, int y, COLORREF color,int penStyle, int penWidth) {
	current.points.clear();
	lastTime = (DWORD)GetTickCount64();
	current.points.push_back(Point{ x, y});
	current.color = color;
	current.penStyle = penStyle;
	current.penWidth = penWidth;
	recording = true;
}

void StrokeController::Add(int x, int y) {
	if (!recording) return;
	DWORD now = (DWORD)GetTickCount64();

	if (!current.points.empty()) {
		const Point& last = current.points.back();
		if (last.x == x && last.y == y) {
			return;
		}
	}
	current.points.push_back(Point{ x, y, now - lastTime });
	lastTime = now;
}

void StrokeController::End() {
	if (!recording) return;
	strokes.push_back(current);
	current.points.clear();
	recording = false;
}

void StrokeController::Clear() {
	std::lock_guard<std::mutex> lock(mtx);
	strokes.clear();
	current.points.clear();
	recording = false;
}

void StrokeController::AddPoint(Point p) {
	current.points.push_back(p);
}

void StrokeController::AddStroke() {
	strokes.push_back(current);
	current.points.clear();
}

void StrokeController::Reset() {
	strokes.clear();
	current.points.clear();
	current.penStyle = PS_SOLID;
	current.penWidth = 5;
	current.color = RGB(0, 0, 0);
	recording = false;
	lastTime = 0; 
}