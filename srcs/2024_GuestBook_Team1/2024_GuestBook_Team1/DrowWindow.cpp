#include "DrowWindow.h"


DrowWindow::DrowWindow(int mode, HINSTANCE hInst)
    : mode(mode), hInst(hInst), hwnd(nullptr), bkColor(RGB(249, 243, 240)) {
    wndFunc = std::make_unique<WndFunc>();
    this->wc = {};
}

/// 네임바 생성 메서드
void DrowWindow::createWindowNB(int left, int top, int right, int bottom, HWND parent)
{
    /// 윈도우 등록
    WNDCLASS wc10 = {};
    wc10.lpfnWndProc = WndProcNB;  // 네임바 메세지 처리하는 정적 메서드
    wc10.lpszClassName = L"CustomNameWindowClass";
    wc10.hInstance = hInst;
    wc10.hbrBackground = CreateSolidBrush(RGB(243, 243, 243));


    if (!RegisterClass(&wc10)) {
        MessageBox(NULL, L"네임 바 등록 실패", L"Error", MB_OK);
        return;
    }

    /// 생성되는 해당 윈도우 핸들값 저장
    WndFunc::nameWnd = CreateWindow(
        L"CustomNameWindowClass",
        L"Name Window",
        WS_CHILD | WS_VISIBLE,
        left, top,
        right,
        bottom,
        parent,
        nullptr,
        hInst,
        reinterpret_cast<LPVOID>(this)  // this 포인터 전달
    );

    if (!WndFunc::nameWnd) {
        DWORD error = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"네임 바 생성 실패: 오류 코드 %d", error);
        MessageBox(NULL, buf, L"Error", MB_OK);
        return;
    }

    ShowWindow(WndFunc::nameWnd, SW_SHOW);
}

/// 툴바 생성 메서드
void DrowWindow::createWindowTB(int left, int top, int right, int bottom, HWND parent)
{
    WNDCLASS wc3 = {};
    wc3.lpfnWndProc = WndProcTB;  // 네임바 메세지 처리하는 정적 메서드
    wc3.lpszClassName = L"Tool";
    wc3.hInstance = hInst;
    wc3.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));


    if (!RegisterClass(&wc3)) {
        MessageBox(NULL, L"툴바 등록 실패", L"Error", MB_OK);
        return;
    }
    /// 생성되는 해당 윈도우 핸들값 저장
    WndFunc::toolWnd = CreateWindow(
        L"Tool",
        L"Tool1",
        WS_CHILD | WS_VISIBLE,
        left, top,
        right,
        bottom,
        parent,
        nullptr,
        hInst,
        reinterpret_cast<LPVOID>(this)  // this 포인터 전달
    );
    if (!WndFunc::toolWnd) {
        DWORD error = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"툴바 생성 실패: 오류 코드 %d", error);
        MessageBox(NULL, buf, L"Error", MB_OK);
        return;
    }
    ShowWindow(WndFunc::toolWnd, SW_SHOW);
}

/// 캔버스 생성 메서드
void DrowWindow::createWindowCV(int left, int top, int right, int bottom, HWND parent)
{
    WNDCLASS wc2 = {};
    wc2.lpfnWndProc = WndProcCV;  // 네임바 메세지 처리하는 정적 메서드
    wc2.lpszClassName = L"CustomNameWindowClass1";
    wc2.hInstance = hInst;
    wc2.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));


    if (!RegisterClass(&wc2)) {
        MessageBox(NULL, L"cavas 등록 실패", L"Error", MB_OK);
        return;
    }
    /// 생성되는 해당 윈도우 핸들값 저장
    WndFunc::canvasWnd = CreateWindow(
        L"CustomNameWindowClass1",
        L"Name Window",
        WS_CHILD | WS_VISIBLE,
        left, top,
        right,
        bottom,
        parent,
        nullptr,
        hInst,
        reinterpret_cast<LPVOID>(this)  // this 포인터 전달
    );
    if (!WndFunc::canvasWnd) {
        DWORD error = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"네임 바 생성 실패: 오류 코드 %d", error);
        MessageBox(NULL, buf, L"Error", MB_OK);
        return;
    }
    ShowWindow(WndFunc::canvasWnd, SW_SHOW);
}

/// 방문자 리스트 생성 메서드
void DrowWindow::createWindowVL(int left, int top, int right, int bottom, HWND parent)
{
    WNDCLASS wc11 = {};
    wc11.lpfnWndProc = WndProcVL;  // 네임바 메세지 처리하는 정적 메서드
    wc11.lpszClassName = L"CustomNameWindowClass3";
    wc11.hInstance = hInst;
    wc11.hbrBackground = CreateSolidBrush(RGB(249, 243, 240));


    if (!RegisterClass(&wc11)) {
        MessageBox(NULL, L"방문자 리스트 등록 실패", L"Error", MB_OK);
        return;
    }
    /// 생성되는 해당 윈도우 핸들값 저장
    WndFunc::visitListWnd = CreateWindow(
        L"CustomNameWindowClass3",
        L"Name Window",
        WS_CHILD | WS_VISIBLE,
        left, top,
        right,
        bottom,
        parent,
        nullptr,
        hInst,
        reinterpret_cast<LPVOID>(this)  // this 포인터 전달
    );
    if (!WndFunc::visitListWnd) {
        DWORD error = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"방문자리스트 윈도우 생성 실패: 오류 코드 %d", error);
        MessageBox(NULL, buf, L"Error", MB_OK);
        return;
    }
    HFONT hFont = CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
        DEFAULT_PITCH | FF_SWISS, TEXT("나눔고딕"));

    // STATIC 컨트롤에 폰트 설정
    SendMessage(WndFunc::visitListWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

    ShowWindow(WndFunc::visitListWnd, SW_SHOW);
}
    /// 컬러 팔레트 생성 메서드
void DrowWindow::createWindowCP(int left, int top, int right, int bottom, HWND parent)
{

    WNDCLASS wc31 = {};
    wc31.lpfnWndProc = WndProcCP;  
    wc31.lpszClassName = L"Tototo";
    wc31.hInstance = hInst;
    wc31.hbrBackground = CreateSolidBrush(RGB(224, 232, 234));


    if (!RegisterClass(&wc31)) {
        MessageBox(NULL, L"컬러박스 등록 실패", L"Error", MB_OK);
        return;
    }
    /// 생성되는 해당 윈도우 핸들값 저장
    WndFunc::colorWnd = CreateWindow(
        L"Tototo",
        L"Tototo",
        WS_CHILD | WS_VISIBLE,
        left, top,
        right,
        bottom,
        parent,
        nullptr,
        hInst,
        reinterpret_cast<LPVOID>(this)  // this 포인터 전달
    );
    if (!WndFunc::colorWnd) {
        DWORD error = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"컬러박스 생성 실패: 오류 코드 %d", error);
        MessageBox(NULL, buf, L"Error", MB_OK);
        return;
    }
    ShowWindow(WndFunc::colorWnd, SW_HIDE);
}

/// 사이드바 생성 메서드
void DrowWindow::createWindowSB(int left, int top, int right, int bottom, HWND parent)
{
    /// 윈도우 등록은 한번만 해야하기 때문에 윈도우 등록 코드는 한번만 실행
    WNDCLASS wc5 = {};
    wc5.lpfnWndProc = WndProcSB;  /// 네임바 메세지 처리하는 정적 메서드
    wc5.lpszClassName = L"CustomNameWindowClass2";
    wc5.hInstance = hInst;
    wc5.hbrBackground = CreateSolidBrush(RGB(230, 230, 230));
    if (!RegisterClass(&wc5)) {
        MessageBox(NULL, L"side 바 등록 실패", L"Error", MB_OK);
        return;
    }
    WndFunc::sideWnd = CreateWindow(
        L"CustomNameWindowClass2",
        L"Name Window",
        WS_CHILD | WS_VISIBLE,
        left, top,
        right,
        bottom,
        parent,
        nullptr,
        hInst,
        reinterpret_cast<LPVOID>(this)  // this 포인터 전달
    );
    if (!WndFunc::sideWnd) {
        DWORD error = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"사이드 바 생성 실패: 오류 코드 %d", error);
        MessageBox(NULL, buf, L"Error", MB_OK);
        return;
    }
    ShowWindow(WndFunc::sideWnd, SW_HIDE);
}
/// 파일 매니저 생성 메서드
void DrowWindow::createWindowFM(int left, int top, int right, int bottom, HWND parent)
{
    WNDCLASS wc111 = {};
    wc111.lpfnWndProc = WndProcFM;  // 네임바 메세지 처리하는 정적 메서드
    wc111.lpszClassName = L"CustomNameWindowClass111";
    wc111.hInstance = hInst;
    wc111.hbrBackground = CreateSolidBrush(RGB(230, 230, 230));
    wc111.style = CS_DBLCLKS; // CS_DBLCLKS 스타일 추가

    if (!RegisterClass(&wc111)) {

        return;
    }
    WndFunc::fileManager = CreateWindow(
        L"CustomNameWindowClass111",
        L"Name Window",
        WS_CHILD | WS_VISIBLE | CS_DBLCLKS, 
        left, top,
        right,
        bottom,
        parent,
        nullptr,
        hInst,
        reinterpret_cast<LPVOID>(this)  // this 포인터 전달
    );
    if (!WndFunc::fileManager) {
        DWORD error = GetLastError();
        wchar_t buf[256];
        wsprintf(buf, L"파일 매니저 윈도우 생성 실패: 오류 코드 %d", error);
        MessageBox(NULL, buf, L"Error", MB_OK);
        return;
    }

    ShowWindow(WndFunc::fileManager, SW_SHOW);
}

// 정적 윈도우 프로시저
LRESULT CALLBACK DrowWindow::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    DrowWindow* pThis = nullptr;

    if (message == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<DrowWindow*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else {
        pThis = reinterpret_cast<DrowWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    }
    if (pThis) {
        return pThis->handleMessage(hWnd, message, wParam, lParam); // 인스턴스의 가상 함수 호출
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/// 가상 함수로 메시지 처리
LRESULT DrowWindow::handleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: /// 초기 DrowWnd 생성도 다른 윈도우 생성
    {
        /// 네임바 윈도우 생성
        createWindowNB(0, 0, WndFunc::wndSize.right, 57, hWnd);

        /// 툴바 윈도우 생성
        createWindowTB(-1, 57, WndFunc::wndSize.right, 51, hWnd);

        /// 캔버스 윈도우 생성
        createWindowCV((WndFunc::wndSize.right - 1300) / 2, (WndFunc::wndSize.bottom - 600) / 2, 1300, 700, hWnd);

        /// 전광판 윈도우 생성
        createWindowVL(0, WndFunc::wndSize.bottom - 30, WndFunc::wndSize.right, WndFunc::wndSize.bottom, hWnd);

        /// 사이드바 윈도우 생성
        createWindowSB(WndFunc::wndSize.right - 60, 110, 60, 300, hWnd);

        createWindowCP(WndFunc::wndSize.top + 450, 100, 380, 570, WndFunc::canvasWnd);
        break;
    }
    /*
    case WM_MOUSEMOVE:
    {
        if (function->getisLeftClick()) function->setisCanvas(false, lParam);
        break;
    }
    */
    /// 캔버스에서 그리기 할때 버그 임시 수정
    case WM_MOUSEMOVE:
    {
        function->setisLeftClick(false);
        break;
    }
    case WM_LBUTTONUP:
        function->setisLeftClick(false);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        if (WndFunc::creditOn)
        {
            // 텍스트를 출력할 위치(x, y 좌표)
            int x = WndFunc::wndSize.right / 2 - 175;
            int y = 270 + 25;

            Rectangle(hdc, x - 50, 125, x + 420, 775);

            // 큰 텍스트를 위한 폰트 생성
            HFONT hFontLarge = CreateFont(
                30,                        // 글꼴 높이 (크기를 조정하려면 이 값을 변경)
                0, 0, 0, FW_BOLD,          // 폭, 기울기, 굵기
                FALSE, FALSE, FALSE,       // 이탤릭체, 밑줄, 취소선
                DEFAULT_CHARSET,           // 문자셋
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS,
                L"Arial");                 // 글꼴 이름

            // 기본 텍스트 폰트 생성
            HFONT hFontDefault = CreateFont(
                20,                        // 기본 글꼴 높이
                0, 0, 0, FW_NORMAL,        // 폭, 기울기, 굵기
                FALSE, FALSE, FALSE,
                DEFAULT_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS,
                L"Arial");

            // 큰 텍스트 출력
            SelectObject(hdc, hFontLarge);
            LPCWSTR text = L"유한대학교 컴퓨터 소프트웨어 공학과";
            TextOut(hdc, x, y- 100, text, wcslen(text));

            text = L"Reference 4기";
            TextOut(hdc, x+100, y - 60, text, wcslen(text));

            // 기본 폰트로 전환
            SelectObject(hdc, hFontDefault);

            text = L"프로젝트 팀원";
            TextOut(hdc, x, y + 40, text, wcslen(text));

            text = L"김형균 : PM, 방문자 스레드, 코드 구조 개선";
            TextOut(hdc, x, y + 70, text, wcslen(text));

            text = L"오승호 : CTO, 메인 윈도우, 코드 구조 개선";
            TextOut(hdc, x, y + 100, text, wcslen(text));

            text = L"용지순 : 스탬프 기능";
            TextOut(hdc, x, y + 130, text, wcslen(text));

            text = L"김수길, 김용빈 : 파일 관리자";
            TextOut(hdc, x, y + 160, text, wcslen(text));

            text = L"최가은, 임지섭 : 리플레이 스레드, WM_PAINT 구성";
            TextOut(hdc, x, y + 190, text, wcslen(text));

            text = L"윤찬솔 : 버튼 구성";
            TextOut(hdc, x, y + 220, text, wcslen(text));

            text = L"김주환, 장환희, 전성호 : 펜 스타일";
            TextOut(hdc, x, y + 250, text, wcslen(text));

            text = L"조재현 : 펜 종류 구성";
            TextOut(hdc, x, y + 280, text, wcslen(text));


            text = L"레포지토리 주소";
            TextOut(hdc, x, y + 350, text, wcslen(text));

            text = L"https://github.com/semicolon213/2024_GuestBook_T1";
            TextOut(hdc, x, y + 370, text, wcslen(text));
        }

        EndPaint(hWnd, &ps);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}