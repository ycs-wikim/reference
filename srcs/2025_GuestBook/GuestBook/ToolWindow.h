#pragma once
#include <windows.h>
#include "ButtonController.h"

class DrawWindow;

class ToolWindow
{
public:
    ToolWindow() = default;
    bool Create(HWND parentHwnd, HINSTANCE hInstance);
    HWND GetHwnd() const { return hwnd; }
    HWND GetReplayHwnd() const { return replayHwnd; }
    void SetDrawWindow(DrawWindow* draw) { drawWindow = draw; }

    ButtonController& GetButtonController() { return buttonController; }

private:
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    void CreateButton();
   
    HWND hwnd = nullptr;
    HWND replayHwnd = nullptr;
    HINSTANCE hInstance = nullptr;
   
    DrawWindow* drawWindow = nullptr;
    
    ButtonController buttonController;
};

