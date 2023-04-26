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

	RECT canvas_area_;

	bool is_canvas_click_;

	std::vector<std::vector<PointInfo>> lines_;
	std::vector<PointInfo> line_;

	std::vector<std::vector<PointInfo>> history_;

	int mouse_current_x_;
	int mouse_current_y_;
public:
	Canvas(HWND hWnd);
	~Canvas() = default;

	void CanvasReset();

	void MouseUp();
	void MouseDown(POINT mouse_position);
	void MouseMove(POINT mouse_position, int width, double time, COLORREF color);
	void Draw(HDC hdc);
	void DrawLine(HDC hdc, size_t lines_idx, size_t line_idx);
	void OpenSaveFile();
	void OpenLoadFile();
	void LoadFile(fs::path path);

	int GetWidth();
	int GetHeight();

	const std::vector<std::vector<PointInfo>>& GetLines();
};

