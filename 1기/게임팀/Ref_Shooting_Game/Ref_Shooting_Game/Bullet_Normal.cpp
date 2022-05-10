#include "Bullet_Normal.h"

void Bullet_Normal::DrawObject(HDC hdc)
{
	/*
	RECT temp;
	temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
	*/
	HPEN OldPen = (HPEN)SelectObject(hdc, GetStockObject(DC_PEN));
	HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(DC_BRUSH));
	
	
	RECT rect = GetRect();

	int OffsetX = GetSize().x / 5;
	int OffsetY = GetSize().y / 5;


	COLORREF Color_ = RGB(255, 100, 100);
	if (IsPlayer())
	{
		Color_ = RGB(0, 0, 255);
		OffsetX = GetSize().x / 4;
		OffsetY = GetSize().y / 4;
	}

	// 바깥색
	SetDCBrushColor(hdc, Color_);
	SetDCPenColor(hdc, Color_);

	Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);


	// 흰색
	SetDCBrushColor(hdc, RGB(255, 255, 255));
	SetDCPenColor(hdc, RGB(255, 255, 255));

	Ellipse(hdc, rect.left + OffsetX, rect.top + OffsetY, rect.right - OffsetX, rect.bottom - OffsetY);


	SelectObject(hdc, OldPen);
	SelectObject(hdc, OldBrush);

}

Bullet_Normal::Bullet_Normal(POINT newLocation, POINTF newVelocity) : BulletBase(newLocation, newVelocity)
{

}


