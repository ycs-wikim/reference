#include "BulletLaser.h"


BulletLaser::BulletLaser(POINT newLocation, POINTF newVelocity) : BulletBase(newLocation, newVelocity)
{
	start_y = newLocation.y;
}


void BulletLaser::DrawObject(HDC hdc)
{

	RECT temp;
	temp = GetRect();
	Rectangle(hdc, temp.left, temp.top, temp.right, temp.bottom);

}

bool BulletLaser::MoveNext()
{
	if (LocationF.y + Velocity.y * Speed < 8) return true;
	LocationF = { LocationF.x + Velocity.x * Speed, LocationF.y + Velocity.y * Speed };
	Location = { (LONG)LocationF.x , (LONG)LocationF.y };
	height = start_y - Location.y;


	return true;
}
