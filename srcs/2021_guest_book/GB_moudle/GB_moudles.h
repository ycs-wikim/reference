// 모듈 전체에서 쓰이는 코드
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<Windows.h>

typedef struct point_info
{
    LPARAM          lparm;      //좌표  
    int             cWidth;     //굵기
    COLORREF        color;      //색상
    ULONGLONG           ctime;      //시간
    UINT            state;      //상태{WM_LBUTTONDOWN }
}PINFO;

typedef struct scale_point_info
{
    std::vector<PINFO> pinfo;
    int x;
    int y;
    int width;
    int height;
}SPINFO;