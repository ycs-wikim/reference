#pragma once

/** 전처리기(아래에선 CREATEDLL_EXPORTS)가 정의 되어 있다면 함수를 export로
* 정의 되어 있지 않다면 import로 만듦
*/
#ifdef CREATEDLL_EXPORTS
#define Dll_Test_DLL_DECLSPEC __declspec(dllexport)
#else
#define Dll_Test_DLL_DECLSPEC __declspec(dllimport)
#endif

#include <windows.h>
/**
* extern "C" --> c++에서 함수를 작성시 발생하는 네임 맹글링(함수의 이름을 실제와 다르게 저장하는 작업)이 
* 발생시 명시적 링킹이 불가능하므로 발생하지 않도록 C로 컴파일 되도록 하는 부분
*/
extern "C"  Dll_Test_DLL_DECLSPEC  void draw_rac(HWND hWnd, LPARAM lParam);
