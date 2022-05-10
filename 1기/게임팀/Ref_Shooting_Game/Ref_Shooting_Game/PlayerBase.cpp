#include "PlayerBase.h"
#include "Bullet_Normal.h"
#include "BulletLaser.h"
#include "Timer.h"
#include <iostream>

PlayerBase::PlayerBase()
{
	SetLocation(POINT{ 700,500 });
	SetHealth(5);// 체력 5
	Life = 3;
	PowerCount = 3;
	SetSize(8, 8);
	SetPlayer();
	inv = false;
	inv_Invisible = false;
	bDead = false;
	timer = new Timer<PlayerBase>();
	SetType(0); // 0 == 플레이어
}

void PlayerBase::SetCharacterBit(HINSTANCE hInst)
{
	BIT_Character = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_Player));
}

void PlayerBase::DrawObject(HDC hdc)
{
	if (inv_Invisible == true || bDead == true) return;

	HDC hdc2 = CreateCompatibleDC(hdc);

	
	// 빨간 체력바
	RECT temp = GetRect();

	HBRUSH red_brush = CreateSolidBrush(RGB(255, 0, 0));
	RECT health_rect = { 1030, 180, 1050 + (GetHealth() * 50) , 210 };
	FillRect(hdc, &health_rect, red_brush);
	DeleteObject(red_brush);


	HBITMAP OldBitmap = (HBITMAP)SelectObject(hdc2, BIT_Character); //메모리DC에 비트맵오브젝트를 넣는다.

	//비트맵
//	BitBlt(hdc, Location.x, Location.y, 50, 50, hdc2, 0, 0, SRCCOPY);
	TransparentBlt(hdc, Location.x-12, Location.y-13, 32, 32, hdc2, 0, 0, 32, 32, RGB(255, 255, 255));

	// 충돌판정
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);


	SelectObject(hdc2, OldBitmap);
	DeleteDC(hdc2);
}

/*
void PlayerBase::DrawObject(HDC hdc)
{

	if (inv_Invisible == true || bDead == true) return;
	RECT temp = GetRect();
	Rectangle(hdc, temp.left, temp.top, temp.right, temp.bottom);

	HBRUSH red_brush = CreateSolidBrush(RGB(255, 0, 0));
	RECT health_rect = { 1030, 180, 1050 + (GetHealth() * 50) , 210 };
	FillRect(hdc, &health_rect, red_brush);
	SelectObject(hdc, red_brush);
	DeleteObject(red_brush);
	Ellipse(hdc, temp.left, temp.top, temp.right, temp.bottom);
}
*/

PatternResult PlayerBase::Attack()
{


	POINT location = GetLocation();
	// 중앙에서 Bullet 발사
	location.x += GetSize().x / 2 - 5 / 2;
	location.y += GetSize().y / 2 - 5 / 2;

	BulletBase* Bullet = new Bullet_Normal(location, POINTF{ 0,-5 });		//일반형



	Bullet->SetSize(8, 8);
	Bullet->SetPlayer();		// 플레이어 소유로 변경

	PatternResult result;
	result.Bullet = Bullet;
	result.Interval = 0;

	return result;
}

bool PlayerBase::GetDamages(int x)
{
	if (inv == true || bDead == true)
	{
		return false;
	}
	int ChangedHP;
	ChangedHP = GetHealth() - x;
	if (ChangedHP < 1)
	{
		Life--;
		if (Life < 1)
		{
			return true;
		}

		bDead = true;
		cout << "죽음   남은 목숨 : " << Life << endl;
		timer->TimerStart(*this, 2000, &PlayerBase::revive);
	}
	else
	{
		inv_start(1000);
		SetHealth(ChangedHP);
		cout << "남은 체력 : " << GetHealth() << endl;
	}

	return false;

}

int PlayerBase::GetLife()
{
	return this->Life;
}


void PlayerBase::revive()
{
	inv_start(3000);
	SetHealth(5);
	bDead = false;
	SetLocation(POINT{ 700,500 });
	
}


// 무정동안 깜박이게 함
void PlayerBase::flicker()
{
	if (inv == false)
	{
		inv_Invisible = false;
		return;
	}

	if (inv_Invisible == true)
		inv_Invisible = false;
	else
		inv_Invisible = true;

	timer->TimerStart(*this, 50, &PlayerBase::flicker);
}


void PlayerBase::inv_end()
{
	inv = false;
}

void PlayerBase::inv_start(int time)
{
	inv = true;
	timer->TimerStart(*this, time, &PlayerBase::inv_end);
	flicker();
}

bool PlayerBase::IsDead()
{
	return bDead;
}

void PlayerBase::Reset()
{
	SetLocation(POINT{ 800,400 });
	SetHealth(5);// 체력 5
	Life = 3;
	PowerCount = 3;
	inv = false;
	inv_Invisible = false;
	bDead = false;
}