#include "PatternBase.h"
#include "BulletBase.h"
#include "Bullet_Normal.h"

PatternBase::PatternBase()
{
	BulletInterval = 1000;
	BulletSize = 5;
}

PatternBase::PatternBase(int Interval, int size)
{
	BulletInterval = Interval;
	BulletSize = size;
}


void PatternBase::SetBulletinterval(int newInterval)
{
	BulletInterval = newInterval;
}

void PatternBase::SetBulletSize(int newSize)
{
	BulletSize = newSize;
}
