#pragma once
#include "Entity.h"


template <typename T> 
class Timer;

class PlayerBase :
	public Entity
{
public:

    void inv_end(); // 무적 종료
    void inv_start(int time);
    bool IsDead();
    void Reset();
    // 무적 시작
    void revive(); // 라이프 소모 후 부활 시 호출
    void flicker(); // 무적중 깜박임
    PlayerBase();
    static void SetCharacterBit(HINSTANCE hInst);
    void DrawObject(HDC hdc);
    PatternResult Attack();
    bool GetDamages(int x);
    int GetLife();

	
private:
    Timer<PlayerBase> *timer; // Timer 객체 만듦
    bool inv; //invincibility : 무적
    int Life;
    int PowerCount;
    bool inv_Invisible;
    
    bool bDead;
};

