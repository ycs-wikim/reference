#pragma once
#include "EnemyBase.h"
class Enemy_Boss :
    public EnemyBase
{
public:
    Enemy_Boss();
    ~Enemy_Boss();
    PatternResult Attack(PatternParam Param);
    void DrawObject(HDC hdc);
private:
    bool flag;
    class PatternFlower* patternFlower;
};


