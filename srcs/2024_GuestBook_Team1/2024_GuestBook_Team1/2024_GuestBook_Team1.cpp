#include "2024_GuestBook_Team1.h"
#include <commctrl.h>
#include "WndFunc.h"
#include "MakeButton.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

std::unique_ptr<DrowWindow> drowWnd = nullptr;


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.


    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY2024GUESTBOOKTEAM1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2024GUESTBOOKTEAM1));

    MSG msg;



    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//  
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_YUHAN256));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_YUHAN));

    WNDCLASSEXW nbcex = wcex;


    return RegisterClassExW(&wcex);
}

//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//

static RECT DesktopRT;      //사용자 화면 크기 받기용

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    WndFunc::hInst = hInst;

    GetWindowRect(GetDesktopWindow(), &DesktopRT);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        (DesktopRT.right - 1600) / 2, (DesktopRT.bottom - 900) / 2, 1600, 900, nullptr, nullptr, hInstance, nullptr);

    //제목 표시줄 색상 변경
    int aElements[] = { COLOR_ACTIVECAPTION };
    DWORD aOldColors[1];
    DWORD aNewColors[1];
    aOldColors[0] = GetSysColor(aElements[0]);
    aNewColors[0] = RGB(243, 243, 243);
    SetSysColors(1, aElements, aNewColors);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

MakeButton bt_Replay;
MakeButton bt_Load;
MakeButton bt_Credit;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        /// 최상위 윈도우 핸들 생성이 윈도우 사이즈 초기화
        GetClientRect(hWnd, &WndFunc::wndSize);

        // DrowWindow 인스턴스 생성
        drowWnd = std::make_unique<DrowWindow>(1, hInst);

        // WNDCLASS 구조체 초기화
        WNDCLASS wc1 = {};
        wc1.lpfnWndProc = DrowWindow::StaticWndProc;  // 정적 함수로 설정
        wc1.hInstance = hInst;
        wc1.hbrBackground = CreateSolidBrush(RGB(249, 243, 240));  // 노란색 브러시 설정
        wc1.lpszClassName = DROW_CLASS;

        // 클래스 등록
        if (!RegisterClass(&wc1)) {
            MessageBox(NULL, L"윈도우 클래스 등록 실패", L"에러", MB_OK);
            return 1;
        }

        // 자식 창 생성
        WndFunc::drowWnd = CreateWindow(
            DROW_CLASS,                     // 클래스 이름
            DROW_NAME,                      // 창 제목
            WS_CHILD | WS_VISIBLE,          // 자식 창 스타일
            0, 0, WndFunc::wndSize.right, WndFunc::wndSize.bottom,  // 위치와 크기 (X, Y, Width, Height)
            hWnd,                           // 부모 창 핸들
            NULL,                           // 메뉴 없음
            hInst,                          // 인스턴스 핸들
            drowWnd.get()                   // DrowWindow 객체 전달
        );

        if (WndFunc::drowWnd == nullptr) {
            MessageBox(NULL, L"창 생성 실패", L"에러", MB_OK);
        }


        bt_Replay.makeMenuButton((WndFunc::wndSize.right / 2) - 450, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, DEF_DROW_BT, L"REPLAY");
        bt_Replay.showMenuButton(hWnd, IDI_MAIN_SIGN_ICON, WndFunc::DrowBT);

        bt_Load.makeMenuButton((WndFunc::wndSize.right / 2) - 120, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, DEF_LOAD_BT, L"불러오기");
        bt_Load.showMenuButton(hWnd, IDI_MAIN_LOAD_ICON, WndFunc::LoadBT);

        bt_Credit.makeMenuButton((WndFunc::wndSize.right / 2) + 210, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, DEF_CREDIT_BT, L"CREDIT");
        bt_Credit.showMenuButton(hWnd, IDI_MAIN_CREDIT_ICON, WndFunc::CreditBT);
        // 버튼 스타일
        DWORD buttonStyle = WS_CHILD | WS_VISIBLE | BS_CENTER | BS_VCENTER | BS_PUSHBUTTON;

        /*
        //WndFunc::DrowBT = CreateWindowW(L"BUTTON", L"서명하기", buttonStyle,
         //   (WndFunc::wndSize.right / 2) - 450, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, hWnd, (HMENU)DEF_DROW_BT, hInst, nullptr);

        //WndFunc::LoadBT = CreateWindowW(L"BUTTON", L"불러오기", buttonStyle,
          //  (WndFunc::wndSize.right / 2) - 120, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, hWnd, (HMENU)DEF_LOAD_BT, hInst, nullptr);

        //WndFunc::CreditBT = CreateWindowW(L"BUTTON", L"CREDIT", buttonStyle,
          //  (WndFunc::wndSize.right / 2) + 210, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, hWnd, (HMENU)DEF_CREDIT_BT, hInst, nullptr);
          */
        ShowWindow(WndFunc::drowWnd, SW_HIDE);
        ShowWindow(WndFunc::nameWnd, SW_HIDE);
        ShowWindow(WndFunc::toolWnd, SW_HIDE);
        ShowWindow(WndFunc::canvasWnd, SW_HIDE);
        ShowWindow(WndFunc::sideWnd, SW_HIDE);
        ShowWindow(WndFunc::visitListWnd, SW_HIDE);
        break;

    }


    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case DEF_DROW_BT:   // 서명하기
        {

            // 새 창 표시
            ShowWindow(WndFunc::drowWnd, SW_SHOW);
            ShowWindow(WndFunc::nameWnd, SW_SHOW);
            ShowWindow(WndFunc::toolWnd, SW_SHOW);
            ShowWindow(WndFunc::canvasWnd, SW_SHOW);
            ShowWindow(WndFunc::visitListWnd, SW_SHOW);

            // 기존 버튼 숨김
            ShowWindow(WndFunc::DrowBT, SW_HIDE);
            ShowWindow(WndFunc::LoadBT, SW_HIDE);
            ShowWindow(WndFunc::CreditBT, SW_HIDE);
            break;
        }
        case DEF_LOAD_BT:   // 불러오기
        {

            /// 현재 버튼을 숨김
            WndFunc::buttonOn = false;

            DW_SideMenu::penMemory->clear();

            FileManager::fileManager.selectFileMode(LOAD, hWnd, DW_SideMenu::penMemory); /// 추가

            ShowWindow(WndFunc::drowWnd, SW_SHOW);
            ShowWindow(WndFunc::nameWnd, SW_SHOW);
            ShowWindow(WndFunc::toolWnd, SW_SHOW);
            ShowWindow(WndFunc::canvasWnd, SW_SHOW);
            ShowWindow(WndFunc::visitListWnd, SW_SHOW);

            ShowWindow(WndFunc::DrowBT, SW_HIDE);
            ShowWindow(WndFunc::LoadBT, SW_HIDE);
            ShowWindow(WndFunc::CreditBT, SW_HIDE);
            break;
        }
        case DEF_CREDIT_BT: // CREDIT
        {

            WndFunc::creditOn = true;

            ShowWindow(WndFunc::drowWnd, SW_SHOW);
            ShowWindow(WndFunc::nameWnd, SW_SHOW);

            ShowWindow(WndFunc::canvasWnd, SW_HIDE);
            ShowWindow(WndFunc::toolWnd, SW_HIDE);
            ShowWindow(WndFunc::fileNameW, SW_HIDE);
            ShowWindow(WndFunc::DrowBT, SW_HIDE);
            ShowWindow(WndFunc::LoadBT, SW_HIDE);
            ShowWindow(WndFunc::CreditBT, SW_HIDE);
            ShowWindow(WndFunc::sideWnd, SW_HIDE);

            SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_CLEAR_BT, 0);

            InvalidateRect(WndFunc::drowWnd, NULL, TRUE);
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    }
    case WM_SIZE:
    {
        /// 창 사이즈 조절시 현재 창 크기를 받아옴
        GetClientRect(hWnd, &WndFunc::wndSize);

        /// 하위 윈도우들 크기 및 위치 조정
        MoveWindow(WndFunc::drowWnd, 0, 0, WndFunc::wndSize.right, WndFunc::wndSize.bottom, true);
        MoveWindow(WndFunc::nameWnd, 0, 0, WndFunc::wndSize.right, 57, true);
        MoveWindow(WndFunc::toolWnd, -1, 57, WndFunc::wndSize.right, 51, true);
        MoveWindow(WndFunc::canvasWnd, (WndFunc::wndSize.right - 1300) / 2 - 100, (WndFunc::wndSize.bottom - 600) / 2 - 40, 1500, 780, true);
        MoveWindow(WndFunc::visitListWnd, 0, WndFunc::wndSize.bottom - 30, WndFunc::wndSize.right, WndFunc::wndSize.bottom, true);
        MoveWindow(WndFunc::sideWnd, WndFunc::wndSize.right - 50, WndFunc::wndSize.top + 107, WndFunc::wndSize.right, 300, true);

        MoveWindow(WndFunc::DrowBT, (WndFunc::wndSize.right / 2) - 450, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, true);
        MoveWindow(WndFunc::LoadBT, (WndFunc::wndSize.right / 2) - 120, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, true);
        MoveWindow(WndFunc::CreditBT, (WndFunc::wndSize.right / 2) + 210, (WndFunc::wndSize.bottom / 2) - 50 + 100, 250, 250, true);
        break;
    }
    case WM_GETMINMAXINFO:
    {
        /// 최소 창 크기 지정
        MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(lParam);

        mmi->ptMinTrackSize.x = 1350;  // 최소 너비 1350px
        mmi->ptMinTrackSize.y = 950;  // 최소 높이 900px

        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // "GUEST BOOK" 텍스트를 화면에 그리기
        const wchar_t* title = L"GUEST BOOK";
        HFONT hFont = CreateFont(
            175,                  // 글꼴 크기
            0, 0, 0,             // 너비와 각도 (0은 자동 설정)
            FW_BOLD,             // 굵게 설정
            FALSE, FALSE, FALSE, // 기울임, 밑줄, 취소선 여부
            DEFAULT_CHARSET,     // 문자 집합
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS,
            L"Arial");           // 글꼴 이름

        HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
        SetBkMode(hdc, TRANSPARENT); // 배경을 투명하게 설정
        SetTextColor(hdc, RGB(0, 0, 0)); // 검은색 텍스트

        // 화면 중앙 상단에 텍스트를 출력
        int x = (WndFunc::wndSize.right - 1000) / 2;  // 텍스트의 가로 위치 조정
        int y = 50;  // 텍스트의 세로 위치 조정
        TextOut(hdc, x, y, title, wcslen(title));

        // 이전 글꼴과 자원 해제
        SelectObject(hdc, hOldFont);
        DeleteObject(hFont);

        // "Ver.2024" 작은 글씨 추가
        const wchar_t* versionText = L"Ver.2024";
        HFONT hFontVersion = CreateFont(
            20,                   // 작은 글씨 크기
            0, 0, 0,             // 너비와 각도 (0은 자동 설정)
            FW_LIGHT,            // 얇게 설정
            FALSE, FALSE, FALSE, // 기울임, 밑줄, 취소선 여부
            DEFAULT_CHARSET,     // 문자 집합
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS,
            L"Arial");           // 글꼴 이름

        hOldFont = (HFONT)SelectObject(hdc, hFontVersion);

        // "GUEST BOOK" 아래에 "Ver.2024" 텍스트 출력
        int versionX = x + 970;  // 큰 글씨 오른쪽 하단에 배치
        int versionY = y + 150;  // 큰 글씨 아래 위치
        TextOut(hdc, versionX, versionY, versionText, wcslen(versionText));

        // 작은 글씨 자원 해제
        SelectObject(hdc, hOldFont);
        DeleteObject(hFontVersion);

        // 기존 펜을 백업하기 위해 선언
        HPEN oldPen;
        // 굵기 3의 펜 생성
        HPEN thickPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

        // HDC에 굵기 3 펜을 선택
        oldPen = (HPEN)SelectObject(hdc, thickPen);


        HFONT hFontText = CreateFont(
            40,                 // "서명하기" 텍스트의 크기
            0, 0, 0,           // 너비와 각도 (0은 자동 설정)
            FW_BOLD,           // 굵게 설정
            FALSE, FALSE, FALSE, // 기울임, 밑줄, 취소선 여부
            DEFAULT_CHARSET,   // 문자 집합
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS,
            L"Malgun Gothic");         // 글꼴 이름
        HFONT hOldFontText = (HFONT)SelectObject(hdc, hFontText);


        // 첫 번째 직사각형 그리기
        Rectangle(hdc, (WndFunc::wndSize.right / 2) - 480, (WndFunc::wndSize.bottom / 2) + 20, (WndFunc::wndSize.right / 2) - 170, (WndFunc::wndSize.bottom / 2) + 330);


        // "서명하기" 텍스트를 큰 글씨로 출력
        LPCWSTR text = L"서명하기";
        TextOut(hdc, (WndFunc::wndSize.right / 2) - 380, (WndFunc::wndSize.bottom / 2) - 40, text, wcslen(text));


        // 두 번째 직사각형 그리기
        Rectangle(hdc, (WndFunc::wndSize.right / 2) - 145, (WndFunc::wndSize.bottom / 2) + 20, (WndFunc::wndSize.right / 2) + 160, (WndFunc::wndSize.bottom / 2) + 330);

        // "서명하기" 텍스트를 큰 글씨로 출력
        text = L"불러오기";
        TextOut(hdc, (WndFunc::wndSize.right / 2) - 50, (WndFunc::wndSize.bottom / 2) - 40, text, wcslen(text));



        // 세 번째 직사각형 그리기
        Rectangle(hdc, (WndFunc::wndSize.right / 2) + 180, (WndFunc::wndSize.bottom / 2) + 20, (WndFunc::wndSize.right / 2) + 490, (WndFunc::wndSize.bottom / 2) + 330);

        // "서명하기" 텍스트를 큰 글씨로 출력
        text = L"CREDIT";
        TextOut(hdc, (WndFunc::wndSize.right / 2) + 285, (WndFunc::wndSize.bottom / 2) - 40, text, wcslen(text));


        // 원래 펜으로 되돌림
        SelectObject(hdc, oldPen);

        // "서명하기" 텍스트의 글꼴 자원 해제
        SelectObject(hdc, hOldFontText);
        DeleteObject(hFontText);

        // 사용한 펜 삭제
        DeleteObject(thickPen);
        EndPaint(hWnd, &ps);
        break;
    }



    case WM_DESTROY:
        SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_RESET_BT, 0);
        PostQuitMessage(0);
        /// function->GDIPlusEnd();
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;

    }
    return (INT_PTR)FALSE;
}

