#pragma once
#include "Object.h"
#include "PatternBase.h"
#include "Resource.h"
class Entity :
    public Object
{
private :
    int Health;
    int Type; // 플레이어, 잡몹, 보스 구분
    
protected:
    static HBITMAP BIT_Character;
public:
    int GetHealth();
    void SetHealth(int newHealth);
    virtual bool GetDamages(int x);
    void SetType(int x);
    int GetType();

    static void SetCharacterBit(HINSTANCE hInst);

    static void DeleteCharacterBit();
    
};



