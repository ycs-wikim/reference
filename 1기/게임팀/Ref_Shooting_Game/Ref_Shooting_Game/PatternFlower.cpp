#pragma warning(disable:4828)
#include "PatternFlower.h"
#include "Bullet_Normal.h"
#include <iostream>


PatternFlower::PatternFlower(int Interval, int size) : PatternBase(Interval, size)
{
	step = 0;
	degree = 0;
	degree2 = 0;
}

PatternResult PatternFlower::Next(PatternParam Param)
{
	PatternResult result;

	RECT rect = Param.EntityRect;
	int Distance = 50;

	int RealDegree = 0;

	if(step < 5)
		RealDegree = 18 + 72 * step + degree;
	else
		RealDegree = 18 + 72 * (step - 5) + degree2;

	
	// 중앙 위치
	POINT location;
	location.x = rect.left + (rect.right - rect.left) / 2 - BulletSize / 2;
	location.y = rect.top + (rect.bottom - rect.top) / 2 - BulletSize / 2;

	// 총알 위치
	POINT BulletLoc = location;
	BulletLoc.y -= (int)(sin(RealDegree * (3.14 / 180)) * Distance);
	BulletLoc.x -= (int)(cos(RealDegree * (3.14 / 180)) * Distance);


	// 거리벡터
	POINT Dist_vec = { BulletLoc.x - location.x, BulletLoc.y - location.y };

	// 단위벡터 ( 방향 )
	POINTF Unit_vec = { (float)Dist_vec.x / Distance, (float)Dist_vec.y / Distance };

	BulletBase* Bullet = new Bullet_Normal(BulletLoc, Unit_vec);
	Bullet->SetSize(BulletSize, BulletSize);
	result.Bullet = Bullet;



	if (step == 9)
	{
		degree += 5;
		degree2 -= 5;
		step = 0;
		result.Interval = BulletInterval;
	}
	else
	{
		step++;
		result.Interval = 1;
	}

	return result;
}

void PatternFlower::SetAngleOffset(int newOffset)
{
	AngleOffset = newOffset;
}

