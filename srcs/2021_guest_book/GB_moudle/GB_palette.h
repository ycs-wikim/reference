#pragma once

#include<Windows.h>
#include<vector>
#include<stdlib.h>
#include<ctime>

// 파레트
#define BTNS (sizeof(cols)/sizeof(COLORREF))    // 색상 버튼 갯수
//#define S_BTN_x 650                             // 색상 버튼 시작 x위치
//#define S_BTN_y 30                              // 색상 버튼 시작 y위치
#define BTN_gap 3                               // 버튼 간격
#define BTN_size 35                             // 버튼 크기

// 윈도우 설정 
#define Window_Size_Width 1370                  //윈도우 넓이
#define Window_Size_Height 700                  // 윈도우 높이

#ifndef WINDOW_COLOR
#define WINDOW_COLOR RGB(230,230,230)
#endif

#define Screen_Save_Timer 
static COLORREF cols[] = {
                    RGB(0,0,0),         //검정
                    RGB(255,255,255),   //흰색
                    RGB(192,192,192),   //회색
                    RGB(238,45,54),     //빨간색
                    RGB(255,127,39),    //주황색
                    RGB(255,242,0),     //노란색
                    RGB(113,222,22),    //연두색
                    RGB(14,190,98),     //초록색
                    RGB(23,186,255),    //하늘색
                    RGB(64,125,217),    //파란색
                    RGB(163,73,164),    //보라색
                    RGB(255,174,201),   //연분홍
                    RGB(251,117,190),   //분홍
                    RGB(185,122,87),    //갈색
};

typedef struct btn      //색상 버튼내용을 저장할 구조체
{
    RECT rect;
    COLORREF col;
    HBRUSH brsh;
    HPEN pen;
    //HWND Wnd;
}BTN;

class Palette
{
public:
    BTN btn_ran;
    COLORREF ran;
    HPEN pen;
    int x;
    int y;
    int boundary_x;
    int boundary_y;
    std::vector<BTN> btns;

    Palette(int x, int y);
    ~Palette();
    void paint(HWND hWnd, HDC hdc);
    COLORREF is_press(LPARAM lParam);

    COLORREF ChangeRand();
};

class GB_Pen
{
public:
    int x;
    int y;
    int width;
    int height;
    int size;
    int text_x;
    int text_y;
    int text_size;
    COLORREF col;
    RECT area;
    RECT text_area;

    GB_Pen(int x, int y, int width, int height);
    GB_Pen(int x, int y, int width, int height, int text_x, int text_y, int text_size);
    void set_color(COLORREF col);
    COLORREF get_color();
    void set_size(int size);
    void set_size_up();
    void set_size_down();
    int get_size();
    void paint(HWND hWnd, HDC hdc);
    void paint_text(HWND hWnd, HDC hdc);
};

