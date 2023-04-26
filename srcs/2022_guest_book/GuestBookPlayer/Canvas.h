#pragma once

namespace fs = std::filesystem;

class Canvas
{
private:
	struct PointInfo
	{
		int start_x;
		int start_y;
		int end_x;
		int end_y;
		int width;

		double time;

		COLORREF color;
	};

	HWND hWnd;

	int x_;
	int y_;
	int width_;
	int height_;

	int canvas_x_;
	int canvas_y_;
	int canvas_width_;
	int canvas_height_;

	std::vector<std::vector<PointInfo>> lines_;
public:
	Canvas(HWND hWnd);
	~Canvas() = default;

	void Draw(HDC hdc);
	void DrawLine(HDC hdc, size_t lines_idx, size_t line_idx);
	void OpenLoadFile();
	void LoadFile(fs::path path);
};

