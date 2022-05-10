#include "Enemy_mage.h"
#include "Bullet_Normal.h"
#include "PatternNormal.h"

//움직이는거, 체력, 데미지
Enemy_mage::Enemy_mage()
{
	SetHealth(30);
	SetSize(20, 20);
	SetLocation(POINT{ 700,20 });
	patternNormal = new PatternNormal(500, 7);
	patternNormal->SetHomming(true);
	SetType(1);
	Count = 0;
}

Enemy_mage::~Enemy_mage()
{
	delete patternNormal;
}
bool Enemy_mage::MoveNext()
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

PatternResult Enemy_mage::Attack(PatternParam Param)
{
	PatternResult result;

	if (Count >= 2) {
		
		SetLocation(POINT{ 0,0 });
		result.Bullet = nullptr;
		result.Interval = 0;
	}

	result = patternNormal->Next(Param);
	
	Count++;

	result.Bullet->SetSpeed(3);

	return result;
}
void Enemy_mage::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

