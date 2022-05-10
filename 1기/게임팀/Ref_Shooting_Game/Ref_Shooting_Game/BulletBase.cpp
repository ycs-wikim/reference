#include "BulletBase.h"
#include <iostream>
#include "Timer.h"

int BulletBase::g_KeyCode = 0;

BulletBase::BulletBase()
{
	Velocity = POINTF{0.0f, 0.0f};
	Location = POINT{ 0,0 };
	LocationF = POINTF{ 0,0 };
	KeyCode = g_KeyCode++;
	Speed = 1;
	bMoveStop = false;
	timer = nullptr;

}

BulletBase::~BulletBase()
{
	if (timer != nullptr) delete timer;
}

BulletBase::BulletBase(POINT newLocation, POINTF newVelocity)
{
	Location = newLocation;
	LocationF = { (float)newLocation.x,(float)newLocation.y };
	Velocity = newVelocity;
	KeyCode = g_KeyCode++;
	Speed = 1;
	bMoveStop = false;
	timer = nullptr;
	Sleep(1);
}

bool BulletBase::MoveNext()
{
	if (bMoveStop) return true;
	LocationF = { LocationF.x + Velocity.x * Speed, LocationF.y + Velocity.y * Speed };
	Location = {(LONG)LocationF.x , (LONG)LocationF.y };


	RECT rect = GetRect();

	if (rect.top < 11) return false;
	else if (rect.bottom > 688) return false;
	else if (rect.right > 998) return false;
	else if (rect.left < 400) return false;
	else return true;
}


void BulletBase::SetVelocity(POINTF pointf)
{
	Velocity = pointf;
}

POINTF BulletBase::GetVelocity()
{
	return Velocity;
}

int BulletBase::GetKeyCode()
{
	return KeyCode;
}

void BulletBase::SetSpeed(int newSpeed)
{
	Speed = newSpeed;
}

void BulletBase::StopMoving(int second)
{
	bMoveStop = true;
	if (timer == nullptr) timer = new Timer<BulletBase>();
	timer->TimerStart(*this, second, &BulletBase::WakeUp);
}

void BulletBase::WakeUp()
{
	bMoveStop = false;
	
}