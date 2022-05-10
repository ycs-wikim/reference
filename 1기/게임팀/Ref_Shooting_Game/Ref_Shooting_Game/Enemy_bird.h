#pragma once
#include "EnemyBase.h"
#include <iostream>

class Enemy_bird
	: public EnemyBase
{
public:
	Enemy_bird();
	~Enemy_bird();
	bool MoveNext();
	PatternResult Attack(PatternParam Param);
	void DrawObject(HDC hdc);
	
private:
	class PatternNormal* patternNormal;
};

