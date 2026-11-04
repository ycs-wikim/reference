#pragma once
#include <windows.h>
#include "ToolWindow.h"
#include "BackBuffer.h"
#include "Sidebar.h"
class DrawWindow;
class MainWindow
{
public:
	MainWindow() = default;
	bool Create(HINSTANCE hInstance, int nCmdShow);
	HWND GetHwnd() const { return hwnd; }

	void SetDrawWindow(DrawWindow* draw) { drawWindow = draw; }
	void SetToolWindow(ToolWindow* tool) { toolWindow = tool; }
	void ResetSideBar() { sideBar.Reset(); }
	void Show(int nCmdShow = SW_SHOW);
	void ResizeChildren();

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	HWND hwnd = nullptr;
	HINSTANCE hInstance = nullptr;

	DrawWindow* drawWindow = nullptr;
	ToolWindow* toolWindow = nullptr;
	Sidebar sideBar;
	BackBuffer backBuffer;
	BackBuffer cacheBuffer;

};

