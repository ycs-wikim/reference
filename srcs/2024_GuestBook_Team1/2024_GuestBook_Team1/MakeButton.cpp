#include "MakeButton.h"

void MakeButton::makeMenuButton(int x, int y, int width, int height, int func, LPCWSTR text)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->func = func;
    this->text = text;
    this->hButton = nullptr;
}

void MakeButton::showMenuButton(HWND g_Hwnd, int path, HWND& get_hWnd)
{
    this->hButton = g_Hwnd;

    get_hWnd = CreateWindowW(
        L"BUTTON",                                                          // 버튼 클래스 이름
        text,                                                               // 버튼 텍스트
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_ICON | BS_FLAT,             // 버튼 스타일
        x,                                                                  // 버튼의 x 위치
        y,                                                                  // 버튼의 y 위치
        width,                                                              // 버튼의 폭
        height,                                                             // 버튼의 높이
        this->hButton,                                                             // 부모 윈도우 핸들
        (HMENU)func,                                                        // 버튼의 ID
        (HINSTANCE)GetWindowLongPtr(this->hButton, GWLP_HINSTANCE),                // 인스턴스 핸들
        NULL                                                                // 추가 매개변수
    );
    insertIconImg(text, path, (HINSTANCE)GetWindowLongPtr(this->hButton, GWLP_HINSTANCE));

    /// 점선 테두리 삭제 메세지 전송
    SendMessage(g_Hwnd, WM_UPDATEUISTATE, MAKELONG(UIS_SET, UISF_HIDEFOCUS), 0);

}

void MakeButton::insertIconImg(LPCWSTR text, int path, HINSTANCE hInst)
{
    /// 버튼의 크기에 맞는 아이콘을 불러오기 위해 LoadImage를 사용.
    HICON hIcon = (HICON)LoadImage(
        hInst,                        /// 인스턴스 핸들
        MAKEINTRESOURCE(path),        /// 리소스 경로
        IMAGE_ICON,                   /// 아이콘 유형
        width,                        /// 아이콘의 가로 크기
        height,                       /// 아이콘의 세로 크기
        LR_DEFAULTCOLOR               /// 기본 색상 로드 플래그
    );

    /// 버튼에 아이콘 설정 함수
    SendMessageW(
        FindWindowExW(this->hButton, NULL, L"BUTTON", text),   /// 버튼의 핸들을 찾습니다.
        BM_SETIMAGE,                                    /// 버튼에 이미지를 설정하는 메시지
        IMAGE_ICON,                                     /// 이미지 유형이 아이콘임을 지정
        (LPARAM)hIcon                                   /// 설정할 아이콘
    );

}


MakeButton::MakeButton()
{
    /// 생성자 초기화
    this->rectButton.left = 0;
    this->rectButton.top = 0;
    this->rectButton.right = 0;
    this->rectButton.bottom = 0;
    this->icon = 0;
    this->toggleState = false;
}


MakeButton::MakeButton(int left, int top, int right, int bottom)
{
    /// 생성자 초기화
    this->rectButton.left = left;
    this->rectButton.top = top;
    this->rectButton.right = right;
    this->rectButton.bottom = bottom;
    this->icon = 0;
    this->toggleState = false;
}

void MakeButton::setCoordinate(int left, int top, int right, int bottom)
{
    this->rectButton.left = left;           /// RECT 자료형 left
    this->rectButton.top = top;             /// RECT 자료형 top
    this->rectButton.right = right;         /// RECT 자료형 right
    this->rectButton.bottom = bottom;       /// RECT 자료형 bottom
    this->icon = 0;                         /// icon 0으로 초기화
}

void MakeButton::drawRectButton(HDC tHdc, int icon)
{
    this->icon = icon;  /// 멤버 변수에 icon 값 저장
    
    
    /// 사각형 그릴 때 외곽선 없게 처리 (NULL_BRUSH)
    /// 만약 버튼 추가 후 클릭 영역 확인 필요시 이부분 주석 처리
    HBRUSH hOldBrush = (HBRUSH)SelectObject(tHdc, GetStockObject(NULL_BRUSH));
    HPEN hOldPen = (HPEN)SelectObject(tHdc, GetStockObject(NULL_PEN));
    
    /// Rectangle 그리기 
    Rectangle(tHdc,
        this->rectButton.left,
        this->rectButton.top,
        this->rectButton.right,
        this->rectButton.bottom
    );

    /// 아이콘 그리기
    buttonLoadImage(this->icon, tHdc);

    
    /// 이전 브러시와 펜 복원
    SelectObject(tHdc, hOldBrush);
    SelectObject(tHdc, hOldPen);

    /// 리소스 해제
    DeleteObject(hOldBrush);
    DeleteObject(hOldPen);
}

/// 타원 그리기 메서드
void MakeButton::drawEllipseButton(HDC tHdc, COLORREF test)
{
    this->icon = icon;  /// 멤버 변수에 icon 값 저장

    /// 현재 ColorBox에 정의된 색상으로 색 선택
    HBRUSH tb1 = CreateSolidBrush(test);
    HBRUSH tb2 = (HBRUSH)SelectObject(tHdc, tb1);

    /// 원형 버튼 그리기
    Ellipse(tHdc,
        rectButton.left,
        rectButton.top,
        rectButton.right,
        rectButton.bottom
    );

    /// 원래 펜 선택 후 리소스 해제
    SelectObject(tHdc, tb2);
    DeleteObject(tb1);


    buttonLoadImage(this->icon, tHdc);
}

void MakeButton::doubleImgButton(HDC tHdc, int icon1, int icon2)
{
    /// 현재 토글 상태에 따라 그릴 아이콘 선택
    /// toggleState 기본값 false 이므로 icon2 먼저 출력
    int iconToDraw = toggleState ? icon1 : icon2;

    /// 배경을 투명하게 설정 (NULL_BRUSH 사용)
    HBRUSH hOldBrush = (HBRUSH)SelectObject(tHdc, GetStockObject(NULL_BRUSH));
    HPEN hOldPen = (HPEN)SelectObject(tHdc, GetStockObject(NULL_PEN));

    /// Rectangle 그리기 
    Rectangle(tHdc,
        this->rectButton.left,
        this->rectButton.top,
        this->rectButton.right,
        this->rectButton.bottom
    );

    /// 아이콘 삽입
    buttonLoadImage(iconToDraw, tHdc);

    /// 이전 브러시와 펜 복원
    SelectObject(tHdc, hOldBrush);
    SelectObject(tHdc, hOldPen);
}


void MakeButton::buttonLoadImage(int icon, HDC tHdc)
{
    /// 아이콘 로드
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
        MAKEINTRESOURCE(icon),
        IMAGE_ICON,
        30,
        30,
        0
    );

    /// 아이콘 그리기
    DrawIconEx(tHdc,
        this->rectButton.left,
        this->rectButton.top,
        hIcon, 30, 30, 0, NULL, DI_NORMAL);

    /// 아이콘 자원 해제
    DestroyIcon(hIcon);
}


void MakeButton::clickEffectPen(int icon, int clickIcon, HDC tHdc)
{
    /// 아이콘 로드
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
        MAKEINTRESOURCE(icon),
        IMAGE_ICON,
        30,
        30,
        0
    );

    DrawIconEx(tHdc,
        this->rectButton.left - 5,
        this->rectButton.top - 5,
        hIcon, 40, 40, 0, NULL, DI_NORMAL);

    // 아이콘 자원 해제
    DestroyIcon(hIcon);

    /// 이펙트 그린 후 기존 아이콘(clickIcon) 덮어씌우기
    buttonLoadImage(clickIcon, tHdc);
}

void MakeButton::clickEffectPen(int icon, HDC tHdc)
{
    /// 이펙트 아이콘
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL),
        MAKEINTRESOURCE(icon),
        IMAGE_ICON,
        38,
        38,
        0
    );

    /// 이펙트 그리기
    DrawIconEx(tHdc,
        this->rectButton.left - 4,
        this->rectButton.top - 4,
        hIcon, 38, 38, 0, NULL, DI_NORMAL);

    // 아이콘 자원 해제
    DestroyIcon(hIcon);
}


