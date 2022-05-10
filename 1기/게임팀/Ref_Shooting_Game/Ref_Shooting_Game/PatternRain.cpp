
#pragma warning(disable:4828)
#include <random>
#include "PatternRain.h"
#include "Bullet_Normal.h"
#include <iostream>

using namespace std;

PatternRain::PatternRain(int Interval, int size) : PatternBase(Interval, size)
{
}

PatternResult PatternRain::Next(PatternParam Param)
{
	PatternResult result;

	// 정중앙 위치 계산
	POINT location;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(410, 990);

	location.x = dis(gen);
	location.y = 50;


	BulletBase* Bullet = new Bullet_Normal(location, POINTF{0,3});

	Bullet->SetSize(BulletSize, BulletSize);

	result.Bullet = Bullet;
	result.Interval = BulletInterval;


	return result;
}

