#pragma once
#include <windows.h>

class BackBuffer {
public:
	BackBuffer() = default;
	~BackBuffer();

	int width = 0;
	int height = 0;

	void CreateBuffer(HDC refDC, int w, int h);
	void ClearBuffer(const RECT& rc) const;
	void DrawBufferToScreen(HDC dst, int x = 0, int y = 0) const;
	void ReleaseBuffer();

	HDC dc() const { return memdc; }
	int Width() const { return width; }
	int Height() const { return height; }

private:
	HDC memdc = nullptr; // 메모리 DC
	HBITMAP bmp = nullptr; // 백버퍼 비트맵
	HGDIOBJ old = nullptr; // Select 이전 객체
};