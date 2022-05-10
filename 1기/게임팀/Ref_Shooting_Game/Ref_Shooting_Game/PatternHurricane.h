#pragma warning(disable:4828)
#pragma once
#include "PatternBase.h"
class PatternHurricane :
    public PatternBase
{
public:
    PatternHurricane(int Interval, int size);
    PatternResult Next(PatternParam Param);
private:
    int degree;          // 각도
    bool flag;
};

