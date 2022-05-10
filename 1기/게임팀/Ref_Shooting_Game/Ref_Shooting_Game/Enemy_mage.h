#pragma once
#include "EnemyBase.h"
#include <iostream>
class Enemy_mage :
    public EnemyBase
{
public:
    Enemy_mage();
    ~Enemy_mage();
    bool MoveNext();
    PatternResult Attack(PatternParam Param);
    void DrawObject(HDC hdc);
private:
    class PatternNormal* patternNormal;
    int Count;
};

