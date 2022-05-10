#include "EnemyBase.h"
#include "Bullet_Normal.h"
int EnemyBase::g_KeyCode = 0;

EnemyBase::EnemyBase()
{
	SetLocation(POINT{ 500, 100 });
	SetHealth(5);
	EnemyScore = 500;
	KeyCode = g_KeyCode++;
	
}

EnemyBase::~EnemyBase()
{
}


void EnemyBase::DrawObject(HDC hdc)
{
	RECT temp = GetRect();
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}

PatternResult EnemyBase::Attack(PatternParam Param)
{
	/*
	PatternResult result = Pattern->Next(Param);
	*/
	PatternResult result = { new Bullet_Normal({0,0},{0,0 })};
	return result;
}

bool EnemyBase::MoveNext()
{
	//Rectangle(hdc, 400, 10, 1000, 690) 화면 사이즈
	//Location = POINT{ Location.x , Location.y + 5 };
	

	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
	
}

// 피격 시 체력 감소
bool EnemyBase::GetDamages(int x) 
{
	std::cout << GetHealth();
	int GetLife;
	GetLife = GetHealth() - x;
	if (GetLife <= 0)
		return true;
	else
	{
		SetHealth(GetLife);
		return false;
	}
}

int EnemyBase::GetKeyCode()
{
	return KeyCode;
}