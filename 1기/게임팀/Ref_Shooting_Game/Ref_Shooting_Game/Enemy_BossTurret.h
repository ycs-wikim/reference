#pragma once
#include "EnemyBase.h"
class Enemy_BossTurret :
    public EnemyBase
{
public:
    Enemy_BossTurret();
    ~Enemy_BossTurret();
    bool MoveNext();
    PatternResult Attack(PatternParam Param);
    void DrawObject(HDC hdc);
private:
    class PatternNormal* patternNormal;
};
