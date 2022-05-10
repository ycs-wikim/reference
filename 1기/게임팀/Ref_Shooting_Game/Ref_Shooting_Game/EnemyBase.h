#pragma once
#include "Entity.h"
#include <iostream>
class EnemyBase :
    public Entity
{
private:
    static int g_KeyCode;
    int KeyCode;
    int EnemyScore;
    

public:
    EnemyBase();
    ~EnemyBase();

    virtual PatternResult Attack(PatternParam Param);
    EnemyBase(int type, POINT location);
    virtual void DrawObject(HDC hdc);
    virtual bool MoveNext();
    bool GetDamages(int x);
    int GetKeyCode();
 
    float test_sin;
};
