#ifndef PENTHICKNESS_H
#define PENTHICKNESS_H

#include <Windows.h>
#include <CommCtrl.h>  
#include <functional>
class PenThickness
{
public:

    PenThickness();
    ~PenThickness();

    void show(HINSTANCE hInst, HWND hWndParent);
    /// 현재 설정된 펜 굵기를 반환
    static int getPenWidth();
    /// 굵기를 직접 설정하도록 메서드 추가
    static void setPenWidth(int width);
    // 두께 변경 시 호출될 콜백 함수 등록
    void setThicknessChangedCallback(std::function<void(int)> callback);


private:
    static INT_PTR CALLBACK dlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

    void initializeCommonControls();

    static int penWidth;

    static std::function<void(int)> thicknessChangedCallback;
};
#endif
