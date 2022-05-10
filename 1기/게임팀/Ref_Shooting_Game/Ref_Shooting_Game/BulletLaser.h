#pragma once
#include "BulletBase.h"

class BulletLaser : public BulletBase
{
public:
	BulletLaser(POINT newLocation, POINTF newVelocity);
	void DrawObject(HDC hdc);
	bool MoveNext();
private:
	int start_y;		// 처음 y좌표
};

