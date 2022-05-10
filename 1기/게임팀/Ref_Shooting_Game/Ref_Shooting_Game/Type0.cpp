#pragma warning(disable:4828)
#include "Type0.h"
#include "EnemyBase.h"
#include "PatternNormal.h"
#pragma comment(lib, "Msimg32.lib")

Type0::Type0()
{
	SetHealth(1);
	SetSize(15, 15);
	SetLocation(POINT{700,50});
	test_sin = 0;
	patternNormal = new PatternNormal(500, 7); // (빈도, 총알사이즈)
	// 탄막 속도는 setspeed로 설정
	SetType(1);
}


Type0::~Type0()
{
	delete patternNormal;
}


void Type0::SetCharacterBit(HINSTANCE hInst)
{
	BIT_Character = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Light));
}

void Type0::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
//	HDC hdc2 = CreateCompatibleDC(hdc);

//	HBITMAP OldBitmap = (HBITMAP)SelectObject(hdc2, BIT_Character); //메모리DC에 비트맵오브젝트를 넣는다.

//	BitBlt(hdc, Location.x,Location.y, 50, 50, hdc2, 0, 0, SRCCOPY);
//	TransparentBlt(hdc, Location.x, Location.y, 20, 20, hdc2, 0, 0, 20,20, RGB(255, 0, 255));

//	SelectObject(hdc2, OldBitmap);
//	DeleteDC(hdc2);
}

bool Type0::MoveNext()
{
	//Rectangle(hdc, 400, 10, 1000, 690) 화면 사이즈
	Location = POINT{ Location.x , Location.y };


	Location.x = Location.x + sin(test_sin) * 45;
	Location.y += 5;
	test_sin += 1;


	// 화면 범위 나가면 false 아니면 true
	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
}

PatternResult Type0::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/
	PatternResult result = patternNormal->Next(Param);
	return result;
}