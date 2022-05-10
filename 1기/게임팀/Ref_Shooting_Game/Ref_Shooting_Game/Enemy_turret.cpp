#include "Enemy_turret.h"
#include "Bullet_Normal.h"
#include "PatternNormal.h"

//움직이는거, 체력, 데미지
Enemy_turret::Enemy_turret()
{
	SetHealth(30);
	SetSize(40, 40);
	SetLocation(POINT{ 700,20 });
	patternNormal = new PatternNormal(500, 10);
	patternNormal->SetHomming(true);
	SetType(1);
}

Enemy_turret::~Enemy_turret()
{
	delete patternNormal;
}
bool Enemy_turret::MoveNext()
{
	Location = POINT{ Location.x , Location.y };
	Location.y += 2;
	// 맵밖으로 나가면 false 아닐경우 true 반환
	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
}

PatternResult Enemy_turret::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/
	PatternResult result = patternNormal->Next(Param);
	return result;

	result.Bullet->SetSpeed(2);
}
void Enemy_turret::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

