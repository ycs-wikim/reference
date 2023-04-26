#pragma once

#include "resource.h"
#include "framework.h"
#include "FileManager.h"
#include "Canvas.h"

#define MAX_LOADSTRING 100

class Window
{
private:
	HINSTANCE hInst; // 현재 인스턴스
	HWND hWnd;

	RECT client_area_;
	RECT window_area_;

	static LRESULT CALLBACK StaticWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

	void OnPaint(HDC hdc);

	// 싱글톤
	static std::unique_ptr<Window> instance_;
	static std::once_flag flag_;

	std::unique_ptr<Canvas> canvas_;
	std::unique_ptr<FileManager> file_manager_;

	UINT play_timer_;

	double time_;
	double max_time_;

	void UpdateWindowArea();
public:
	Window() = default;
	~Window() = default;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	WCHAR szTitle[MAX_LOADSTRING]; // 제목 표시줄 텍스트입니다.
	WCHAR szWindowClass[MAX_LOADSTRING]; // 기본 창 클래스 이름입니다.

	ATOM MyRegisterClass(HINSTANCE hinstance);
	BOOL InitInstance(HINSTANCE, int);

	static Window* GetInstance();

	static void CALLBACK TimerProc(UINT m_nTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);

	RECT GetWindowArea();
	Canvas* GetCanvas();
	FileManager* GetFileManager();

	void SetMaxTime(double time);
	void Play();

	double GetTime();
};

