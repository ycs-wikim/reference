#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <vector>
#include "Resource.h"

typedef struct pointInfo
{
    LPARAM lParam;      ///좌표
    int pWidth;         ///굵기
    COLORREF pColor;   ///색
    ULONGLONG pTime;   ///그린 시간
    UINT state;         ///마우스 상태
    int bShape;      ///브러쉬 모양

    int stampValue;
}PINFO;


typedef struct lineInfo
{
    std::vector<PINFO> pInfo;
}LINFO;
