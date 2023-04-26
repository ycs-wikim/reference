#include "pch.h"
#include "Canvas.h"
#include "Window.h"

using namespace std;

Canvas::Canvas(HWND hWnd)
{
	width_ = Window::GetInstance()->GetWindowArea().right - Window::GetInstance()->GetFileManager()->GetWidth();
	height_ = (Window::GetInstance()->GetWindowArea().bottom - y_);
}

void Canvas::Draw(HDC hdc)
{
	width_ = Window::GetInstance()->GetWindowArea().right - Window::GetInstance()->GetFileManager()->GetWidth();
	height_ = (Window::GetInstance()->GetWindowArea().bottom - y_);

	// 윈도우 크기에 따른 위치 보정
	canvas_width_ = 1900;
	canvas_height_ = 760;
	canvas_x_ = ((x_ + width_) - canvas_width_) / 2;
	canvas_y_ = (((y_ + height_) + 90) - canvas_height_) / 2;

	for (size_t i = 0; i < lines_.size(); i++)
	{
		for (size_t j = 0; j < lines_[i].size(); j++)
		{
			if ((int)trunc(lines_[i][j].time * 1000) > Window::GetInstance()->GetTime())
			{
				break;
			}

			DrawLine(hdc, i, j);
		}
	}
}

void Canvas::DrawLine(HDC hdc, size_t lines_idx, size_t line_idx)
{
	HPEN n = CreatePen(PS_SOLID, lines_[lines_idx][line_idx].width, lines_[lines_idx][line_idx].color);
	HPEN o = (HPEN)SelectObject(hdc, n);
	MoveToEx(hdc, lines_[lines_idx][line_idx].start_x + canvas_x_, lines_[lines_idx][line_idx].start_y + canvas_y_, NULL);
	LineTo(hdc, lines_[lines_idx][line_idx].end_x + canvas_x_, lines_[lines_idx][line_idx].end_y + canvas_y_);
	SelectObject(hdc, o);
	DeleteObject(n);
}

void Canvas::OpenLoadFile()
{
	WCHAR file_name[256] = L"";
	WCHAR path[1024] = L"";

	OPENFILENAME OFN;
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = L"Guest Book(*.gb)\0*.gb";
	OFN.lpstrDefExt = L"gb";
	OFN.lpstrFile = file_name;
	OFN.nMaxFile = 256;
	OFN.lpstrInitialDir = Window::GetInstance()->GetFileManager()->GetRootPath();
	OFN.Flags = OFN_NOCHANGEDIR;

	if (GetOpenFileName(&OFN) != 0)
	{
		wsprintf(path, L"%s", OFN.lpstrFile);
		LoadFile(path);
	}
}

void Canvas::LoadFile(fs::path path)
{
	size_t size = 0;
	double drawing_time = 0;

	ifstream load(path, ios::binary);
	if (load.is_open())
	{
		load.read((char*)&size, 4);
		lines_.resize(size);

		for (size_t i = 0; i < lines_.size(); i++)
		{
			size_t line_size = 0;
			load.read((char*)&line_size, 4);

			lines_[i].resize(line_size);
			load.read((char*)&lines_[i][0], line_size * sizeof(PointInfo));
		}

		load.read(reinterpret_cast<char*>(&drawing_time), sizeof(drawing_time));

		load.close();
	}

	Window::GetInstance()->SetMaxTime(drawing_time);

	InvalidateRect(hWnd, NULL, FALSE);
}
