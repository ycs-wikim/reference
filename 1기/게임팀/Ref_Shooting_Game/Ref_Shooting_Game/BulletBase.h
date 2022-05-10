#pragma once
#include "Object.h"


template<typename T>
class Timer;

class BulletBase :
    public Object
{
private:
    
    static int g_KeyCode;
    int KeyCode;
    bool bMoveStop;
    
protected:
    POINTF Velocity;
    POINTF LocationF;
    float Speed;
    Timer<BulletBase>* timer;
public:
    BulletBase();
    ~BulletBase();
    BulletBase(POINT newLocation, POINTF newVelocity);
    virtual bool MoveNext();                   
    void SetVelocity(POINTF pointf);
    POINTF GetVelocity();
    int GetKeyCode();
    void SetSpeed(int newSpeed);

    void StopMoving(int second);
    void WakeUp();
    

};

