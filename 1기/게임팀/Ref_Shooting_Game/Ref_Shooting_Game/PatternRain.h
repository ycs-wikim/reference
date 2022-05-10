#pragma once
#include "PatternBase.h"
class PatternRain :
    public PatternBase
{
public:
    PatternRain(int Interval, int size);
    PatternResult Next(PatternParam Param);

private:
};

