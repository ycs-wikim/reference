

// 서브 로고
// 로고 시작 X Y 좌표
#define Serve_Logo_X 100
#define Serve_Logo_Y 100

// 로고 크기
#define Serve_Logo_Width 280
#define Serve_Logo_Height 117

// 메인 로고
// 메인 시작 X Y 좌표
#define Serve_Logo_X 300
#define Serve_Logo_Y 300

// 메인 크기
#define Serve_Logo_Width 300
#define Serve_Logo_Height 298



void Drawlogo(HINSTANCE hInst, HDC hdc, int xDest, int yDest, int wDest, int hDest);

//{
//    BLENDFUNCTION _bf;
//    _bf.BlendOp = 0;
//    _bf.BlendFlags = 0;
//    _bf.SourceConstantAlpha = 155;
//    _bf.AlphaFormat = 0;
//
//    HBITMAP MyBitmap, OldBitmap;
//    HDC MemDC = CreateCompatibleDC(hdc);
//
//    MyBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(Main_logo));
//    OldBitmap = (HBITMAP)SelectObject(MemDC, MyBitmap);
//
//    //BitBlt(hdc, 0, 0, 250, 90, MemDC, 0, 0, SRCCOPY);
//    GdiAlphaBlend(hdc, xDest, yDest, wDest, hDest, MemDC, xDest, yDest, wDest, hDest, _bf);
//    GdiTransparentBlt(hdc, xDest, yDest, wDest, hDest, MemDC, xDest, yDest, wDest, hDest, RGB(0, 0, 0));
//
//    SelectObject(MemDC, OldBitmap);
//    DeleteObject(MyBitmap);
//}