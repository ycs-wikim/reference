#include "Function.h"
#include "Struct.h"
#include "PenThickness.h"
#include "DrowWindow.h"
#include "WndFunc.h"
#include "DW_ColorBox.h"
#include "DW_NameBar.h"
#include "Function.h"

class DW_Canvas
{
protected:
    //LRESULT HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

    std::unique_ptr<Function> function;
    //std::unique_ptr<ColorPalette> colorPalette;
    std::unique_ptr<PenThickness> penThickness;

    RECT canvasRT;

    HDC hdc;

public:


};