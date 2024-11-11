#pragma once
#include <Windows.h>
#include "DrowWindow.h"
#include "MakeButton.h" 
#include "WndFunc.h"
#include "DW_ColorBox.h"

class DW_ToolMenu
{

public:

protected:

    HINSTANCE tInst;
    HWND tWnd;
    RECT toolRT;

    std::unique_ptr<Function> function;
    //std::unique_ptr<ColorPalette> colorPalette;

    HRGN roundRgn;
};

