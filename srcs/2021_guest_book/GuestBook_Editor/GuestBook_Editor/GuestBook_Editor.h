#pragma once

#include "resource.h"

#include "../../GB_moudle/GB_moudles.h"
#include "../../GB_moudle/GB_palette.h"
#include "../../GB_moudle/GB_Button.h"
#include "../../GB_moudle/GB_Sscreen_Save.h"
#include "../../GB_moudle/GB_Image.h"
#include "../../GB_moudle/GB_FIle_io.h"

using namespace std;


DWORD WINAPI drawing(LPVOID points);    // 리플레이 스레드
DWORD WINAPI Scr_Save_thread(LPVOID points);
bool is_area(LPARAM lParam);            // 색칠 가능 영역인지 반환해주는 함수
void paint_signed_area(HWND hWnd, HDC hdc);
void mouse_proc(HWND hWnd, UINT message, LPARAM lParam, int size, COLORREF col);
void mouse_paint(HDC hdc);
DWORD button_check(LPARAM lParam);
void Center_Screen(HWND window, DWORD style, DWORD exStyle); // Window 화면 가운데 위치로 옮기는 함수
void Critical_flag(bool flag);
void Scr_Creitical_flag(bool flag);

#pragma once

// 새로 프로그램에서 사용할 상수값
#ifndef WINDOW_COLOR
#define WINDOW_COLOR RGB(230,230,230)
#endif
#define Window_Size_Width 1420                  // 윈도우 넓이
#define Window_Size_Height 900                  // 윈도우 높이

#define SRC_TIME 30000							// 30초

#define RAINBOW 1

#define FILE_PATH L"../../page"

// 서명 영역
#define BOUNDARY_LEFT 70
#define BOUNDARY_RIGHT 1350
#define BOUNDARY_TOP 140
#define BOUNDARY_BOTTOM 800

// 팔레트
#define Palette_x 71
#define Palette_y 77

// 펜
#define Pen_x 820		// 펜 상태 출력창 위치
#define Pen_y 65
#define Pen_width 200
#define Pen_height 50

#define Pen_text_x 702	// 폰트 사이즈 출력 위치
#define Pen_text_y 75
#define Pen_size 30		// 폰트사이즈


// +버튼
#define PLUS 1001
#define PLUS_text L"+"	// ┼로 출력시 오류
#define PLUS_x 750
#define PLUS_y 75
#define PLUS_size 40

// - 버튼
#define MINUS 1002
#define MINUS_text L"─"
#define MINUS_x 650
#define MINUS_y 75
#define MINUS_size 40 

// CLEAR 버튼
#define CLEAR 1003
#define CLEAR_text L"CLEAR"
#define CLEAR_x 1220
#define CLEAR_y 75
#define CLEAR_width 130
#define CLEAR_height 40

// REPLAY 버튼
#define REPLAY 1004
#define REPLAY_text L"REPLAY"
#define REPLAY_x 1070
#define REPLAY_y 75
#define REPLAY_width 130
#define REPLAY_height 40

// RANDOM 버튼
#define RANDOM 1005
#define RANDOM_text L"RANDOM"
#define RANDOM_x 210
#define RANDOM_y 30
#define RANDOM_width 130
#define RANDOM_height 40

// CREDIT 버튼
#define CREDIT 1006
#define CREDIT_text L"CREDIT"
#define CREDIT_x 70
#define CREDIT_y 30
#define CREDIT_width 130
#define CREDIT_height 40

// SAVE 버튼
#define SAVE 1007
#define SAVE_text L"SAVE"
#define SAVE_x 1070
#define SAVE_y 30
#define SAVE_width 130
#define SAVE_height 40

// LOAD 버튼
#define LOAD 1008
#define LOAD_text L"LOAD"
#define LOAD_x 1220
#define LOAD_y 30
#define LOAD_width 130
#define LOAD_height 40

// RAINBOW 버튼
#define RAINBOW_b 1009
#define RAINBOW_text L"RAINBOW"
#define RAINBOW_x 350
#define RAINBOW_y 30
#define RAINBOW_width 130
#define RAINBOW_height 40


/*
#define
#define _text L""
#define _x
#define _y
#define _size
#define _width
#define _height
*/
