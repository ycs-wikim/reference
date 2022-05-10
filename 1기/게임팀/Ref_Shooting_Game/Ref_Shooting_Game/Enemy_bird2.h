#pragma once
#include "EnemyBase.h"
#include <iostream>

class Enemy_bird2
	: public EnemyBase
{
public:
	Enemy_bird2();
	~Enemy_bird2();
	bool MoveNext();
	PatternResult Attack(PatternParam Param);
	void DrawObject(HDC hdc);

private:
	class PatternNormal* patternNormal;
};

