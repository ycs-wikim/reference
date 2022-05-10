#include "Enemy_MiddleBoss.h"
#include "Bullet_Normal.h"
#include "PatternHurricane.h"
#include <iostream>
//움직이는거, 체력, 데미지
Enemy_MiddleBoss::Enemy_MiddleBoss()
{
	SetHealth(150);
	SetSize(150, 150);
	SetLocation(POINT{ 700,15 });
	flag = true;
	patternHurricane = new PatternHurricane(70, 15);
	SetType(2);
}

Enemy_MiddleBoss::~Enemy_MiddleBoss()
{
	delete patternHurricane;
}
bool Enemy_MiddleBoss::MoveNext()
{
	
	int type = 0;
	Location = POINT{ Location.x , Location.y };
	if(flag==true)
	{
		Location.x += 5;
	if (Location.x > 800)
		flag = false;
	}
	else
	{ 
			Location.x -= 5;
		if (Location.x < 500)
			flag = true;
	}
	// 맵밖으로 나가면 false 아닐경우 true 반환
	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
}

PatternResult Enemy_MiddleBoss::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/
	
	PatternResult result = patternHurricane->Next(Param);
	
	return result;
}

void Enemy_MiddleBoss::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}