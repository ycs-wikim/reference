#include "ColorController.h"
#include <windows.h>
ColorController::ColorController()
{	
	ZeroMemory(&ColorControl, sizeof(ColorControl));
	ColorControl.lStructSize = sizeof(ColorControl); 
	ColorControl.hwndOwner = nullptr; 
	ColorControl.hInstance = nullptr; 
	ColorControl.rgbResult = RGB(0,0,0); 
	ColorControl.Flags = CC_FULLOPEN | CC_RGBINIT;
	Colors[0] = RGB(0, 0, 0);
	Colors[1] = RGB(255, 255, 255);
	Colors[2] = RGB(255, 0, 0);
	Colors[3] = RGB(0, 255, 0);
	Colors[4] = RGB(0, 0, 255);
	for (int i = 5; i < 16; i++) {
		Colors[i] = RGB(192, 192, 192);
	}
	ColorControl.lpCustColors = Colors; 
}

bool ColorController::Show() {
	return ChooseColor(&ColorControl);
}

COLORREF ColorController::GetColor() const {
	return ColorControl.rgbResult;
}