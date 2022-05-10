
#include "EnemyBase.h"
class Enemy_turret :
    public EnemyBase
{
public:
    Enemy_turret();
    ~Enemy_turret();
    bool MoveNext();
    PatternResult Attack(PatternParam Param);
    void DrawObject(HDC hdc);
private:
    class PatternNormal* patternNormal;
};
