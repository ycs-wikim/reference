#include "BackBuffer.h"

BackBuffer::~BackBuffer() {
	ReleaseBuffer();
}

void BackBuffer::CreateBuffer(HDC refDC, int w, int h) {
	if (memdc && bmp && width == w && height == h && w > 0 && h > 0 ) return; // 맞으면 그대로

	ReleaseBuffer();

	memdc = CreateCompatibleDC(refDC);
	if (!memdc) { return; }

	bmp = CreateCompatibleBitmap(refDC, w, h);
	if (!bmp) {
		DeleteDC(memdc);
		memdc = nullptr;
		return;
	}

	old = SelectObject(memdc, bmp);

	width = w;
	height = h;
}

void BackBuffer::ClearBuffer(const RECT& rc) const {
	if (!memdc) return;
	FillRect(memdc, &rc, (HBRUSH)(COLOR_WINDOW + 1)); // 윈도우 기본 배경
}

/// 리플레이 시 전체 복사
void BackBuffer::DrawBufferToScreen(HDC dst, int x, int y) const {
	if (!memdc || !dst || (width <= 0) || (height <= 0)) return;
	BitBlt(dst, x, y, width, height, memdc, 0, 0, SRCCOPY);
}

void BackBuffer::ReleaseBuffer() {
	if (memdc) {
		if (old) {
			SelectObject(memdc, old);
			old = nullptr;
		}
		if (bmp) {
			DeleteObject(bmp);
			bmp = nullptr;
		}
		DeleteDC(memdc);
		memdc = nullptr;
	}
	width = height = 0;
}