/**
@file ConnExcel.h
@brief 엑셀관련 클래스 멤버 정의 파일
*/

#pragma once

#include <Windows.h>
#include <iostream>
#include <codecvt>
#include <locale>
#include <string>
#include <fstream>
#include <comdef.h>
#include <tchar.h>
#include <thread>
#include <algorithm>

#include "Resource.h"
#include "WndFunc.h"
#include "DrowWindow.h"

class ConnExcel
{
public:

    void insertExcel(const std::wstring);
    std::wstring getVisitList();
    void listScroll(HWND, int, RECT);

    int getTextSize(HWND, std::wstring);
    void listScrollThread(HWND, int, RECT);

    int getTextPosX();
    void setTextPosX(int);

    bool getIsScroll();
    void setIsScroll(bool);

    bool getIsStart();
    void setIsStart(bool);

    void resumeScroll();
    void suspendScroll();

    void stopThread();


    static std::wstring list;

private:
    std::wstring uniVisit;
    std::string multiVisit;

    std::string wcharToChar(const std::wstring);
    std::wstring charToWchar(const std::string);

    std::thread listScrollThreadHandle;

    WCHAR text[10000];
    int textPosX;
    int textWidth = 0;
    /// 방문자 전광판 기본값 false
    bool isScroll = false;
    bool isStart = false;

    HANDLE listHandle;

};
