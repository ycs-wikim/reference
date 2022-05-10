#include "Enemy_Boss.h"
#include "Bullet_Normal.h"
#include "PatternFlower.h"
Enemy_Boss::Enemy_Boss()
{
	SetHealth(300);
	SetSize(200, 200);
	SetLocation(POINT{ 475,15 });
	SetType(3);
	flag = true;
	patternFlower = new PatternFlower(70, 15);
	
}

Enemy_Boss::~Enemy_Boss()
{
	delete patternFlower;
}



PatternResult Enemy_Boss::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/

	PatternResult result = patternFlower->Next(Param);

	return result;
}

void Enemy_Boss::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}