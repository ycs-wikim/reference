#pragma once
#include "PatternBase.h"
class PatternRandom :
    public PatternBase
{
public:
    PatternRandom(int Interval, int size);
    PatternResult Next(PatternParam Param);

};

