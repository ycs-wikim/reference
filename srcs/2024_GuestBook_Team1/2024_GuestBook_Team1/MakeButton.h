#pragma once


#include "framework.h"
#include "Resource.h"

class MakeButton
{
private:
    int icon;      /// 아이콘 지정 멤버 변수

    int x;                /// 버튼의 x 위치
    int y;                /// 버튼의 y 위치
    int width;            /// 버튼의 폭
    int height;           /// 버튼의 높이
    int func;             /// 버튼의 ID
    LPCWSTR text;         /// 버튼 텍스트
    COLORREF buttonColor; /// 버튼 색지정
    HWND hButton;


public:
    RECT rectButton;
    bool toggleState;   /// doubleImgButton 전환 멤버 변수

    void insertIconImg(LPCWSTR text, int path, HINSTANCE hInst);

    void makeMenuButton(int x, int y, int width, int height, int func, LPCWSTR text);
    void showMenuButton(HWND g_Hwnd, int path, HWND& get_hWnd);

    /**
    * @brief MakeButton 클래스의 생성자 위치 좌표를 나중에 지정할 때 사용
    */
    MakeButton();

    /**
    * @brief MakeButton 클래스의 생성자 위치 좌표 초기화
    * @param int left RECT 자료형의 left
    * @param int top RECT 자료형의 top
    * @param int right RECT 자료형의 right
    * @param int bottom RECT 자료형의 bottom
    */
    MakeButton(int left, int top, int right, int bottom);

    /**
    * @brief 일반 이미지 버튼 그리기 WM_PAINT에서 사용
    * @param HDC tHdc WM_PAINT의 hdc
    * @param int icon 버튼에 삽입할 이미지 (.rc, Resource에 정의)
    */
    void drawRectButton(HDC tHdc, int icon);

    /**
    * @brief 색상 버튼 그리기  WM_PAINT에서 사용
    * @param HDC tHdc WM_PAINT의 hdc
    * @param COLORREF test 삽입할 색상 ColorBox의 static 변수 인자로 사용
    */
    void drawEllipseButton(HDC tHdc, COLORREF test);

    /**
    * @brief 클릭시 이미지가 바뀌는 버튼 사용 후 버튼 판정 코드에 토글값 변경 필수
    * @param int icon1 클릭 후 변경될 이미지
    * @param int icon2 먼저 출력되는 이미지
    */
    void doubleImgButton(HDC tHdc, int icon1, int icon2);

    /**
    * @brief RECT 자료형 버튼들의 좌표 지정 메서드
    * @param int left RECT 자료형의 left
    * @param int top RECT 자료형의 top
    * @param int right RECT 자료형의 right
    * @param int bottom RECT 자료형의 bottom
    */
    void setCoordinate(int left, int top, int right, int bottom);

    /**
    * @brief 클릭시 일반 RECT 버튼에 이펙트 적용하는 메서드
    * @param int icon 이펙트 이미지
    * @param int clickIcon 클릭하는 버튼의 아이콘 이미지 
    * @param HDC tHdc 
    */
    void clickEffectPen(int icon, int clickIcon, HDC tHdc);

    /**
    * @brief 클릭시 컬러 버튼에 이펙트 적용하는 메서드
    * @param int icon 이펙트 이미지
    * @param HDC tHdc 
    */
    void clickEffectPen(int icon, HDC tHdc);

protected:
    /**
    * @brief 이미지를 로드하는 메서드
    * @param int icon 아이콘 이미지
    * @param HDC tHdc
    */
    void buttonLoadImage(int icon, HDC tHdc);
};


