#include "pch.h"
#include "FileManager.h"
#include "Window.h"

using namespace std;
using namespace Gdiplus;

FileManager::FileManager(HWND hWnd)
{
	this->hWnd = hWnd;
	wsprintf(root_path_, L"%s\\Guests", fs::current_path().c_str());
	wsprintf(current_path_, L"%s", root_path_);

	// 멤버 변수 초기화
	list_item_height_ = 50;

	width_ = 300;
	x_ = Window::GetInstance()->GetWindowArea().right - width_;
	y_ = 0;
	height_ = (Window::GetInstance()->GetWindowArea().bottom - y_);

	is_active_ = true;
}

void FileManager::ScrollBarControl(POINT mouse_position)
{
	scroll_bar_thumb_percent_ = min(max(((mouse_position.y - (scroll_bar_y_ + (scroll_bar_thumb_height_ / 2))) * 1.0f) / (scroll_bar_height_ - scroll_bar_thumb_height_), 0), 1.0f);
	InvalidateRect(hWnd, &file_manager_area_, FALSE);
}

LPCWSTR FileManager::ConvertBytes(uintmax_t bytes)
{
	const int byte = 1024;
	wchar_t result[256] = L"0B";
	string units[] = { "TB", "GB", "MB", "KB", "B" };
	wstring unit_to_wstring = L"";
	uintmax_t max = (uintmax_t)pow(byte, (sizeof(units) / sizeof(units[0])) - 1);

	for (string unit : units)
	{
		if (bytes > max)
		{
			unit_to_wstring.assign(unit.begin(), unit.end());
			wsprintf(result, L"%s%s", to_wstring(bytes / max).c_str(), unit_to_wstring.c_str());
			return result;
		}

		max /= byte;
	}

	return result;
}

void FileManager::MouseUp()
{
	if (is_scroll_bar_click_)
	{
		is_scroll_bar_click_ = false;
	}
}

void FileManager::MouseDown(POINT mouse_position)
{
	if (is_active_)
	{
		if (PtInRect(&list_box_area_, mouse_position))
		{
			for (size_t i = 0; i < items_.size(); i++)
			{
				RECT list_item_area = { list_box_x_, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (i * list_item_height_), list_box_x_ + list_box_width_, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (i * list_item_height_) + list_item_height_ };
				if (PtInRect(&list_item_area, mouse_position))
				{
					list_item_select_ = i;
					InvalidateRect(hWnd, &file_manager_area_, FALSE);
					break;
				}
			}

			// 파일 관리자에서 파일 삭제
			/*for (int i = 0; i < items_.size(); i++)
			{
				WCHAR file_name_word[1024];
				wsprintf(file_name_word, L"%s을(를) 삭제하시겠습니까?", items_[i].file_name.c_str());
				RECT trash_item_area = { list_box_x_ + list_box_width_ - 35, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (i * list_item_height_), list_box_x_ + list_box_width_, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (i * list_item_height_) + list_item_height_ };
				if (PtInRect(&trash_item_area, mouse_position))
				{
					if (MessageBox(hWnd, file_name_word, L"", MB_YESNO) == IDYES)
					{
						if (fs::is_directory(items_[i].file_path))
						{
							fs::remove_all(items_[i].file_path);
						}
						else if (fs::is_regular_file(items_[i].file_path))
						{
							fs::remove(items_[i].file_path);
						}

						list_item_select_ = 0;
						InvalidateRect(hWnd, &file_manager_area_, FALSE);
						break;
					}
				}
			}*/
		}

		if ((items_.size() * list_item_height_) > list_box_height_)
		{
			if (PtInRect(&scroll_bar_area_, mouse_position))
			{
				ScrollBarControl(mouse_position);
				is_scroll_bar_click_ = true;
			}
		}
	}
}

void FileManager::MouseDoubleDown(POINT mouse_position)
{
	if (is_active_)
	{
		if (PtInRect(&list_box_area_, mouse_position))
		{
			for (size_t i = 0; i < items_.size(); i++)
			{
				RECT list_item_area = { list_box_x_, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (i * list_item_height_), list_box_x_ + list_box_width_ - 35, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (i * list_item_height_) + list_item_height_ };
				if (PtInRect(&list_item_area, mouse_position))
				{
					if (fs::is_directory(items_[i].file_path))
					{
						wsprintf(current_path_, L"%s", items_[i].file_path.c_str());
						list_item_select_ = 0;
						scroll_bar_thumb_percent_ = 0;
						InvalidateRect(hWnd, &file_manager_area_, FALSE);
					}
					else if (fs::is_regular_file(items_[i].file_path))
					{
						// 해당 파일의 확장자가 .gb인지 확인
						if (fs::path(items_[i].file_path).extension() == ".gb")
						{
							Window::GetInstance()->GetCanvas()->LoadFile(items_[i].file_path);
							Window::GetInstance()->Play();
						}
						else
						{
							ShellExecute(NULL, L"open", items_[i].file_path.c_str(), NULL, NULL, SW_SHOW);
						}
					}
					break;
				}
			}
		}
	}
}

void FileManager::MouseMove(POINT mouse_position)
{
	if (is_scroll_bar_click_)
	{
		if (!PtInRect(&scroll_bar_area_, mouse_position))
		{
			MouseUp();
			return;
		}

		ScrollBarControl(mouse_position);
	}
}

void FileManager::MouseWheel(POINT mouse_position, float direction)
{
	if (is_active_)
	{
		if (PtInRect(&list_box_area_, mouse_position))
		{
			if ((items_.size() * list_item_height_) > list_box_height_)
			{
				scroll_bar_thumb_percent_ = min(max(scroll_bar_thumb_percent_ - (direction / 10), 0), 1.0f);
				InvalidateRect(hWnd, &file_manager_area_, FALSE);
			}
		}
	}
}

void FileManager::Draw(HDC hdc)
{
	if (is_active_)
	{
		Graphics graphics(hdc);

		Image file_icon(L"Resources/FileIcon.png");
		Image gb_file_icon(L"Resources/ImageFileIcon.png");
		Image folder_icon(L"Resources/FolderIcon.png");
		Image opened_folder_icon(L"Resources/OpenedFolderIcon.png");
		Image trash_icon(L"Resources/TrashIcon.png");

		SolidBrush white_brush(Color(255, 255, 255, 255));
		SolidBrush black_brush(Color(255, 0, 0, 0));
		SolidBrush background_brush(Color(255, 219, 219, 219));
		SolidBrush background_brush2(Color(255, 238, 238, 238));
		SolidBrush scroll_bar_brush(Color(255, 230, 230, 230));
		SolidBrush scroll_bar_thumb_brush(Color(255, 192, 192, 192));

		Pen black_pen(Color(255, 0, 0, 0));
		Pen contour_pen(Color(255, 185, 185, 185));

		StringFormat string_format_line_center;
		string_format_line_center.SetLineAlignment(StringAlignmentCenter);

		FontFamily arial_font(L"Arial");
		Font font_style(&arial_font, 12, FontStyleBold, UnitPixel);

		// 파일 매니저
		x_ = Window::GetInstance()->GetWindowArea().right - width_;
		y_ = 0;
		height_ = (Window::GetInstance()->GetWindowArea().bottom - y_);

		file_manager_area_ = { x_, y_, x_ + width_, y_ + height_ };

		graphics.FillRectangle(&background_brush, x_, y_, width_, height_);

		// 상단바
		Point background_points[] = {
			Point(x_, y_),
			Point(x_, y_ + 60),
			Point(x_ + width_, y_ + 60),
			Point(x_ + width_, y_ + 30),
			Point(x_ + 120, y_ + 30),
			Point(x_ + 120, y_) };

		Point contour_points[] = {
			Point(x_, y_),
			Point(x_, y_ + 59),
			Point(x_ + width_ - 1, y_ + 59),
			Point(x_ + width_ - 1, y_ + 30),
			Point(x_ + 120, y_ + 30),
			Point(x_ + 120, y_) };

		graphics.FillPolygon(&background_brush2, background_points, 6);
		graphics.DrawPolygon(&contour_pen, contour_points, 6);

		graphics.DrawImage(&folder_icon, x_ + 10, y_ + 5, 20, 20);

		PointF header_font_position(x_ + 35, y_ + 15);
		graphics.DrawString(L"File Manager", -1, &font_style, header_font_position, &string_format_line_center, &black_brush);

		graphics.FillRectangle(&background_brush2, x_, y_ + 60, width_, height_ - 90);

		// 리스트 박스
		list_box_x_ = x_;
		list_box_y_ = y_ + 60;
		list_box_width_ = width_ - 20;
		list_box_height_ = height_ - 90;

		list_box_area_ = { list_box_x_, list_box_y_, list_box_x_ + list_box_width_, list_box_y_ + list_box_height_ };

		WCHAR path_word[1024] = L"";

		if ((items_.size() * list_item_height_) < list_box_height_ && scroll_bar_thumb_percent_ != 0)
		{
			list_item_select_ = 0;
			scroll_bar_thumb_percent_ = 0;
		}

		Region region(Rect(list_box_x_, list_box_y_, list_box_width_, list_box_height_));

		// 클리핑 마스크 시작
		graphics.SetClip(&region, CombineModeReplace);

		FileRefresh(current_path_);

		if (!items_.empty())
		{
			graphics.FillRectangle(&background_brush, list_box_x_, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (list_item_select_ * list_item_height_), list_box_width_, list_item_height_);

			wsprintf(path_word, L"%s/%s", fs::path(items_[list_item_select_].file_path).parent_path().filename().c_str(), items_[list_item_select_].file_name.c_str());
		}

		WCHAR file_name_word[1024];
		WCHAR file_size_word[1024];

		StringFormat string_format_right_line_center;
		string_format_right_line_center.SetAlignment(StringAlignmentFar);
		string_format_right_line_center.SetLineAlignment(StringAlignmentCenter);

		for (size_t i = 0; i < items_.size(); i++)
		{
			PointF file_name_font_position(list_box_x_ + 35, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (list_item_height_ / 2) + (i * list_item_height_));
			PointF file_size_font_position(list_box_x_ + list_box_width_ - 5, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + (list_item_height_ / 2) + (i * list_item_height_));
			wsprintf(file_name_word, L"%s", items_[i].file_name.c_str());
			wsprintf(file_size_word, L"%s", ConvertBytes(items_[i].file_size));


			if (fs::is_directory(items_[i].file_path))
			{
				if (fs::is_empty(items_[i].file_path))
				{
					graphics.DrawImage(&opened_folder_icon, list_box_x_ + 2.5, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + 10 + (i * list_item_height_), 30, 30);
				}
				else
				{
					graphics.DrawImage(&folder_icon, list_box_x_ + 2.5, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + 10 + (i * list_item_height_), 30, 30);
				}
			}
			else if (fs::is_regular_file(items_[i].file_path))
			{
				if (fs::path(items_[i].file_path).extension() == ".gb" || fs::path(items_[i].file_path).extension() == ".GB")
				{
					graphics.DrawImage(&gb_file_icon, list_box_x_, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + 10 + (i * list_item_height_), 30, 30);
				}
				else if (fs::path(items_[i].file_path).extension() == ".bmp" || fs::path(items_[i].file_path).extension() == ".BMP" ||
					fs::path(items_[i].file_path).extension() == ".jpg" || fs::path(items_[i].file_path).extension() == ".JPG" ||
					fs::path(items_[i].file_path).extension() == ".jpeg" || fs::path(items_[i].file_path).extension() == ".JPEG" ||
					fs::path(items_[i].file_path).extension() == ".png" || fs::path(items_[i].file_path).extension() == ".PNG" ||
					fs::path(items_[i].file_path).extension() == ".gif" || fs::path(items_[i].file_path).extension() == ".GIF")
				{
					Image image_file_icon(items_[i].file_path.c_str());
					graphics.DrawImage(&image_file_icon, list_box_x_, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + 10 + (i * list_item_height_), 30, 30);
				}
				else
				{
					graphics.DrawImage(&file_icon, list_box_x_, list_box_y_ - (((items_.size() * list_item_height_) - list_box_height_) * scroll_bar_thumb_percent_) + 10 + (i * list_item_height_), 30, 30);
				}

				graphics.DrawString(file_size_word, -1, &font_style, file_size_font_position, &string_format_right_line_center, &black_brush);
			}

			graphics.DrawString(file_name_word, -1, &font_style, file_name_font_position, &string_format_line_center, &black_brush);
		}

		// 클리핑 마스크 종료
		graphics.ResetClip();

		// 스크롤바
		scroll_bar_width_ = 20;
		scroll_bar_height_ = list_box_height_;
		scroll_bar_x_ = list_box_x_ + list_box_width_;
		scroll_bar_y_ = list_box_y_;

		scroll_bar_thumb_ratio_ = (double)scroll_bar_height_ / (items_.size() * list_item_height_);

		scroll_bar_area_ = { scroll_bar_x_, scroll_bar_y_, scroll_bar_x_ + scroll_bar_width_, scroll_bar_y_ + scroll_bar_height_ };

		graphics.FillRectangle(&scroll_bar_brush, scroll_bar_x_, scroll_bar_y_, scroll_bar_width_, scroll_bar_height_);

		// Scroll Bar Thumb
		if ((items_.size() * list_item_height_) > list_box_height_)
		{
			scroll_bar_thumb_height_ = scroll_bar_height_ * scroll_bar_thumb_ratio_;
			graphics.FillRectangle(&scroll_bar_thumb_brush, scroll_bar_x_ + 5, scroll_bar_y_ + 5 + (scroll_bar_thumb_percent_ / 1.0f) * (scroll_bar_height_ - scroll_bar_thumb_height_), scroll_bar_width_ - 10, round(scroll_bar_thumb_height_) - 10);
		}

		graphics.DrawRectangle(&contour_pen, x_, y_, width_ - 1, height_ - 1);

		// 하단바
		graphics.FillRectangle(&background_brush2, x_, y_ + height_ - 30, width_, 30);
		graphics.DrawRectangle(&contour_pen, x_, y_ + height_ - 30, width_ - 1, 29);

		Region bottom_region(Rect(x_ + 1, y_ + height_ - 31, width_ - 1, 28));

		// 클리핑 마스크 시작
		graphics.SetClip(&bottom_region, CombineModeReplace);

		PointF path_font_position(x_ + 5, y_ + height_ - 15);
		graphics.DrawString(path_word, -1, &font_style, path_font_position, &string_format_line_center, &black_brush);

		// 클리핑 마스크 종료
		graphics.ResetClip();
	}
}

void FileManager::FileRefresh(fs::path path)
{
	fs::path p(path);

	// 해당 경로가 존재하는지 확인
	if (fs::exists(p) && fs::is_directory(p))
	{
		fs::directory_iterator iter(p);

		items_.clear();

		// 현재 폴더가 Geusts가 아닐 경우 상위 폴더와 최상위 폴더 표시
		if (p != root_path_)
		{
			items_.push_back({ ".", root_path_, NULL });
			items_.push_back({ "..", p.parent_path(), NULL });
		}

		while (iter != fs::end(iter))
		{
			const fs::directory_entry& entry = *iter;
			items_.push_back({ entry.path().filename(), entry.path(), entry.file_size() });
			++iter;
		}
	}
	else
	{
		if (!fs::exists(root_path_) && !fs::is_directory(root_path_))
		{
			fs::create_directory(root_path_);
		}

		FileRefresh(root_path_);
	}
}

void FileManager::Active()
{
	is_active_ = !is_active_;
	width_ = is_active_ ? 300 : 0;
	InvalidateRect(hWnd, NULL, FALSE);
}

LPCWSTR FileManager::GetRootPath()
{
	return root_path_;
}

LPCWSTR FileManager::GetCurrentPath()
{
	return current_path_;
}

int FileManager::GetWidth()
{
	return width_;
}

int FileManager::GetHeight()
{
	return height_;
}
