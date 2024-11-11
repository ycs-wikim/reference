#pragma once

#include <Windows.h>
#include <memory>
#include "ConnExcel.h"
#include "Resource.h"
#include "WndFunc.h"
#include "Function.h"
#include "PenThickness.h"


class DrowWindow {
public:
    // 인스턴스를 초기화하는 역할
    DrowWindow(int mode, HINSTANCE hInst);

    /**
    * @brief 클래스 등록 후 호출되는 CALLBACK 메서드
    * @param HWND hWnd
    * @param UINT message 
    * @param WPARAM wParam 
    * @param LPARAM lParam 
    */
    static LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 정적 윈도우 프로시저
    
    /**
    * @brief 클래스 등록 후 호출되는 CALLBACK 메서드에서 호출하는 가상 메서드
    * @param HWND hWnd
    * @param UINT message
    * @param WPARAM wParam
    * @param LPARAM lParam
    */
    virtual LRESULT handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 가상 함수로 메시지 처리

    /**
    * @brief 윈도우 생성 메서드
    * @param left 윈도우의 왼쪽 위치
    * @param top 윈도우의 위쪽 위치
    * @param width 윈도우의 너비
    * @param height 윈도우의 높이
    * @param parent 부모 윈도우 핸들
    */
    void createWindowNB(int left, int top, int width, int height, HWND parent);
    void createWindowTB(int left, int top, int width, int height, HWND parent);
    void createWindowCV(int left, int top, int width, int height, HWND parent);
    void createWindowSB(int left, int top, int width, int height, HWND parent);
    void createWindowCP(int left, int top, int width, int height, HWND parent);
    void createWindowVL(int left, int top, int width, int height, HWND parent);
    void createWindowFM(int left, int top, int right, int bottom, HWND parent);
    
    /**
    * @brief 각 윈도우 생성 후 호출되는 CALLBACK 메서드
    * @param hWnd 윈도우 핸들
    * @param message 메시지 코드
    * @param wParam 추가 메시지 정보
    * @param lParam 추가 메시지 정보
    */
    static LRESULT CALLBACK WndProcNB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 정적 윈도우 프로시저
    static LRESULT CALLBACK WndProcTB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WndProcCV(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WndProcSB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    static LRESULT CALLBACK WndProcCP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    /**
    * @brief 각 윈도우 생성 후 CALLBACK 메서드에 의해 호출되는 가상 메서드
    * @param hWnd 윈도우 핸들
    * @param message 메시지 코드
    * @param wParam 추가 메시지 정보
    * @param lParam 추가 메시지 정보
    */
    virtual LRESULT handleMessageNB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 
    virtual LRESULT handleMessageTB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    virtual LRESULT handleMessageCV(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 
    virtual LRESULT handleMessageSB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 
    virtual LRESULT handleMessageCP(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 


    static LRESULT CALLBACK WndProcFM(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 정적 윈도우 프로시저

    virtual LRESULT handleMessageFM(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 가상 함수로 메시지 처리

    PINFO drawPInfo;

    int x, y, px, py;

protected:
    std::unique_ptr<Function> function;
    std::unique_ptr<PenThickness> penThickness;


    /// 전광판 윈도우 정적 윈도우
    static LRESULT CALLBACK WndProcVL(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 정적 윈도우 프로시저
    /// 전광판 처리 메서드
    virtual LRESULT handleMessageVL(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // 가상 함수로 메시지 처리
    

private:
    HWND hwnd;
    HINSTANCE hInst;
    WNDCLASS wc;
    int mode;
    COLORREF bkColor;
    std::unique_ptr<WndFunc> wndFunc;
    bool pCnt = true;

    bool lCnt = true;

    WCHAR text[10000];

   

};