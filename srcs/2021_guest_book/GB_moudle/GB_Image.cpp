#include "GB_Image.h"

void Drawlogo(HINSTANCE hInst, HDC hdc, int xDest, int yDest, int wDest, int hDest,int i)
{
    BLENDFUNCTION _bf;
    _bf.BlendOp = 0;
    _bf.BlendFlags = 0;
    _bf.SourceConstantAlpha = Logo_Transparency;
    _bf.AlphaFormat = 0;

    HBITMAP MyBitmap, OldBitmap;
    HDC MemDC = CreateCompatibleDC(hdc);

    MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(i));
    OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);

    //BitBlt(hdc, 0, 0, 1000, 1000, MemDC, 0, 0, SRCCOPY);
    GdiAlphaBlend(hdc, xDest, yDest, wDest, hDest, MemDC, 0, 0, wDest, hDest, _bf);
    //GdiTransparentBlt(hdc, xDest, yDest, wDest, hDest, MemDC, 0, 0, wDest, hDest, RGB(255, 255, 255));

    SelectObject(MemDC, OldBitmap);
    DeleteObject(MyBitmap);
}