#include "Enemy_bird2.h"
#include "Bullet_Normal.h"
#include "PatternNormal.h"

Enemy_bird2::Enemy_bird2()
{
	SetHealth(3);
	SetSize(50, 50);
	SetLocation(POINT{ 400, 10 });
	test_sin = 45;
	patternNormal = new PatternNormal(500, 10);
	SetType(1);
}

Enemy_bird2::~Enemy_bird2()
{
	delete patternNormal;
}

void Enemy_bird2::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

bool Enemy_bird2::MoveNext()
{
	//Rectangle(hdc, 400, 10, 1000, 690) 화면 사이즈
	Location = POINT{ Location.x , Location.y };


	Location.x = 925 - 0.03 * test_sin * test_sin;
	Location.y += 10;
	test_sin -= 4;


	//std::cout << 400 + 0.03 * test_sin * test_sin << "  " << test_sin << "\n"<< std::endl;
	//std::cout << Location.x << "  " << Location.y << std::endl;
	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
}





PatternResult Enemy_bird2::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/
	PatternResult result = patternNormal->Next(Param);
	return result;
}