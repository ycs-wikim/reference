#pragma once
#include <windows.h>
#include <commdlg.h>
class ColorController
{
public:

	ColorController(); 
	bool Show(); 
	COLORREF GetColor() const; 

private:
	CHOOSECOLOR ColorControl; 
	COLORREF Colors[16]; 
};
