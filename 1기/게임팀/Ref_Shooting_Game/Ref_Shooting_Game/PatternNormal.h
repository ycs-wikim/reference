#pragma once
#include "PatternBase.h"
class PatternNormal :
    public PatternBase
{
    
public:
    PatternNormal(int Interval, int size);
    PatternResult Next(PatternParam Param);

    void SetHomming(bool bHomming);
private:
    bool bHomming;
};

