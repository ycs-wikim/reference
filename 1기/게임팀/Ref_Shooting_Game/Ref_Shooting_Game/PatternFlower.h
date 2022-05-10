#pragma once
#include "PatternBase.h"
class PatternFlower :
    public PatternBase
{
public:
    PatternFlower(int Interval, int size);
    PatternResult Next(PatternParam Param);
    void SetAngleOffset(int newOffset);         // ÃÑ¾Ë ½î´Â °£°Ý º¯°æ
private:
    int degree;          // °¢µµ
    int degree2;
    int step;

    int AngleOffset;
};

