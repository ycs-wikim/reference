#pragma once
#include <windows.h>
#include <vector>
#include <condition_variable>
#include "resource.h"
#include "Stroke.h"
#include "DrawController.h"
#include "StrokeController.h"
#include "BackBuffer.h"
#include "Sidebar.h"
#include "ScreensaverManager.h"
#define WM_USER_REPLAY_UPDATE (WM_USER + 1)
#define IDT_SAVER_TIMER 1


class ToolWindow;
class MainWindow;
class BackBuffer;
class Application;

class DrawWindow
{
public:
    bool Create(HWND parentHwnd, HINSTANCE hInstance);
    HWND GetHwnd() const { return hwnd; }
    HDC GetMemDc() const; 
    BOOL GetErasing() const { return erasing;  }
    COLORREF GetSelectedColor() const { return selectedColor; }
    int GetCurrentPenWidth() const { return currentPenWidth; }
    const std::vector<Stroke>& GetDrawnStrokes() const { return strokeCtrl.Strokes(); }
    void SetStrokes(std::vector<Stroke> strokes) { strokeCtrl.setStrokes(strokes); }
    void SetPenStyle(int PenNum); /// 브러쉬 컨트롤러 다이얼로그에서 받은 넘버
    void SetPenWidth(int PenWidth); /// 브러쉬 컨트롤러 다이얼로그에서 받은 두께

/// const std::vector<Stroke>& GetDrawnStrokes() const { return strokeCtrl.Strokes(); }
    //화면보호기 추가 코드
    ScreensaverManager* g_pSaverManager = nullptr;

    void SetToolWindow(ToolWindow* tool) { toolWindow = tool; }
    void setSelectedColor(COLORREF color) { this->selectedColor = color; }
    void setBuffer(BackBuffer& bBuffer, BackBuffer& cBuffer) { backBuffer = &bBuffer; backBuffer = &cBuffer; }
    void setErasing() { erasing = !erasing; }
    void setReplaying(bool isReplaying) { this->isReplaying = isReplaying; }
    void ClearAll();
    void ClearScreenOnly();

    COLORREF lastSelectedColor = RGB(0, 0, 0);

    void Reset();   /// 초기값 세팅

private:
    LRESULT HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
    void OnPaint(HDC hdc, const RECT& rc);
    void OnLButtonDown(int x, int y, WPARAM flags);
    void OnMouseMove(int x, int y, WPARAM flags);
    void OnLButtonUp(int x, int y, WPARAM flags);

    void OnSize(int width, int height);

    void HideSystemCursor(); // 커서 숨김 함수
    void ShowSystemCursor(); // 커서 표시 함수

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    HWND hwnd = nullptr;
    HINSTANCE hInstance = nullptr;

    ToolWindow* toolWindow = nullptr;
    MainWindow* mainWindow = nullptr;

    BackBuffer* backBuffer = nullptr; 
    BackBuffer* cacheBuffer = nullptr;

    DrawController drawCtrl;
    StrokeController strokeCtrl;
    COLORREF selectedColor = RGB(0, 0, 0);

    POINT m_currentMousePos = { 0,0 }; // ★ 마우스의 현재 위치
    bool m_isCursorHidden = false; // ★ 커서가 숨겨졌는지 여부
    
    HCURSOR m_hPenCursor = 0;    // ★ 펜 모드 커서 (IDC_CROSS)
    HCURSOR m_hEraserCursor = 0; // ★ 지우개 모드 커서


    int penWidth = 5;
    bool erasing = false;
    bool isReplaying = false;
    int currentPenStyle = PS_SOLID;
    int currentPenWidth = 5;
};