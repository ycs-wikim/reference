#include "GB_moudles.h"

// 메인 로고

// // 메인 크기
#define Main_Logo_Width 300
#define Main_Logo_Height 298

// 메인 시작 X Y 좌표
#define Main_Logo_X (1420 / 2)- (Main_Logo_Width / 2)
#define Main_Logo_Y (900 / 2) - (Main_Logo_Height / 2)



// 서브 로고

// 로고 크기
#define Serve_Logo_Width 200
#define Serve_Logo_Height 48


// 로고 시작 X Y 좌표
#define Serve_Logo_X 1420 - Serve_Logo_Width - 100
#define Serve_Logo_Y 900 - Serve_Logo_Height - 10 - 200


// 로그 투명도
#define Logo_Transparency 60





void Drawlogo(HINSTANCE hInst, HDC hdc, int xDest, int yDest, int wDest, int hDest,int i);