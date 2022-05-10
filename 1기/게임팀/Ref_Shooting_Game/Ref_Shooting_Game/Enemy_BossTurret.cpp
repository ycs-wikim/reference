#include "Enemy_BossTurret.h"
#include "Bullet_Normal.h"
#include "PatternNormal.h"

//움직이는거, 체력, 데미지
Enemy_BossTurret::Enemy_BossTurret()
{
	SetHealth(75);
	SetSize(50, 50);
	SetLocation(POINT{ 700,20 });
	patternNormal = new PatternNormal(500, 7);
	patternNormal->SetHomming(true);
	SetType(2);
}

Enemy_BossTurret::~Enemy_BossTurret()
{
	delete patternNormal;
}
bool Enemy_BossTurret::MoveNext()
{
	Location = POINT{ Location.x , Location.y };

	// 맵밖으로 나가면 false 아닐경우 true 반환
	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
}

PatternResult Enemy_BossTurret::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/
	PatternResult result = patternNormal->Next(Param);
	return result;

	result.Bullet->SetSpeed(5);
}
void Enemy_BossTurret::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

