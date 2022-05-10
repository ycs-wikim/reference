#pragma once
#include "BulletBase.h"
class Bullet_Normal :
    public BulletBase
{
public:
    void DrawObject(HDC hdc);
    Bullet_Normal(POINT newLocation, POINTF newVelocity);

};

