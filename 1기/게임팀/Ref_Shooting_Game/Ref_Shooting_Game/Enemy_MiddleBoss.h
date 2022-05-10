#pragma once
#include "EnemyBase.h"
class Enemy_MiddleBoss :
    public EnemyBase
{
public:
    Enemy_MiddleBoss();
    ~Enemy_MiddleBoss();
    bool MoveNext();
    PatternResult Attack(PatternParam Param);
    void DrawObject(HDC hdc);
private:
    bool flag;
    class PatternHurricane* patternHurricane;
};

