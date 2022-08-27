// GuestBook_Editor.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#pragma once
#include "framework.h"
#include "GuestBook_Editor.h"
#define MAX_LOADSTRING 100

#pragma warning (disable : 4996)

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND End_Credit;

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
	LoadStringW(hInstance, IDC_GUESTBOOKEDITOR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GUESTBOOKEDITOR));

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

	return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GUESTBOOKEDITOR));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = CreateSolidBrush(WINDOW_COLOR);
	wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GUESTBOOKEDITOR);
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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

//전역 변수 선언
//vector<PINFO> g_Pinfo;  g_SPinfo.pinfo
SPINFO g_SPinfo;
vector<GB_BUTTON *> buttons;
HWND g_hWnd;
HBRUSH win_brush;
HFONT font;
bool is_replay = false;
bool is_scrSave = false;


int RainBow_R = 0;
int RainBow_G = 0;
int RainBow_B = 0;

ULONGLONG scr_check_time;

// Thread
HANDLE replay_thread = nullptr;

//CRITICAL
CRITICAL_SECTION cs;
bool is_terminate = false;
CRITICAL_SECTION scr_cs;
bool is_save = false;
long long scr_save_time;
long long scr_start_time;

UINT rainbow_timer = NULL;

//GB_BUTTON* btn_test = new GB_BUTTON(L"테스트", 50, 30, 150, 50);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int pre_x, pre_y;
	static bool left = false;
	// 팔레트
	static Palette* palette;
	// PEN
	static GB_Pen* pen;
	static INT_PTR dialog= 0;
	//HDC hdc;
	COLORREF ret;
	//PINFO temp_pinfo;
	//HPEN npen, open;
	//int x, y;
	

	switch (message)
	{
	case WM_GETMINMAXINFO: // 윈도우 창 크기 고정
	{

		//((MINMAXINFO*)lParam)->ptMaxTrackSize.x = Window_Size_Width;
		//((MINMAXINFO*)lParam)->ptMaxTrackSize.y = Window_Size_Height;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = Window_Size_Width;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = Window_Size_Height;
		break;
	}
	case WM_CREATE:
	{
		// 스크린 중앙 배치
		Center_Screen(hWnd, WS_OVERLAPPEDWINDOW, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);
		
		srand(time(NULL));

		g_hWnd = hWnd;
		palette = new Palette(Palette_x, Palette_y);
		pen = new GB_Pen(Pen_x, Pen_y, Pen_width, Pen_height, Pen_text_x, Pen_text_y, Pen_size);

		font = CreateFont(35, 0, 0, 0, 0, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));
		win_brush = CreateSolidBrush(WINDOW_COLOR);

		//버튼 생성 및 할당
		//buttons.push_back(new GB_BUTTON(L"테스트", 100, 50, 200, 150, 50));
		buttons.push_back(new GB_BUTTON(L"┼", PLUS, PLUS_x, PLUS_y, PLUS_size));
		buttons.push_back(new GB_BUTTON(MINUS_text, MINUS, MINUS_x, MINUS_y, MINUS_size));
		buttons.push_back(new GB_BUTTON(CLEAR_text, CLEAR, CLEAR_x, CLEAR_y, CLEAR_width, CLEAR_height));
		buttons.push_back(new GB_BUTTON(REPLAY_text, REPLAY, REPLAY_x, REPLAY_y, REPLAY_width, REPLAY_height));
		buttons.push_back(new GB_BUTTON(RANDOM_text, RANDOM, RANDOM_x, RANDOM_y, RANDOM_width, RANDOM_height));
		buttons.push_back(new GB_BUTTON(CREDIT_text, CREDIT, CREDIT_x, CREDIT_y, CREDIT_width, CREDIT_height));
		buttons.push_back(new GB_BUTTON(SAVE_text, SAVE, SAVE_x, SAVE_y, SAVE_width, SAVE_height));
		buttons.push_back(new GB_BUTTON(LOAD_text, LOAD, LOAD_x, LOAD_y, LOAD_width, LOAD_height));
		buttons.push_back(new GB_BUTTON(RAINBOW_text, RAINBOW_b, RAINBOW_x, RAINBOW_y, RAINBOW_width, RAINBOW_height));

		g_SPinfo.x = BOUNDARY_LEFT;
		g_SPinfo.y = BOUNDARY_TOP;
		g_SPinfo.height = BOUNDARY_RIGHT - BOUNDARY_LEFT;
		g_SPinfo.width = BOUNDARY_BOTTOM - BOUNDARY_TOP;

		// 임계 영역 설정
		InitializeCriticalSection(&cs);
		InitializeCriticalSection(&scr_cs);

		scr_check_time = GetTickCount64();
		CreateThread(NULL, 0, Scr_Save_thread, nullptr, 0, NULL);
		scr_save_time = SRC_TIME;
		break;
	}
	
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_Screen_save:
			Scr_Creitical_flag(true);
			scr_check_time = GetTickCount64() - scr_save_time;
			Sleep(50);
			return 0;
		case IDM_CREDITS:    //크레딧(C) 클릭시
		{
			dialog = DialogBox(hInst, MAKEINTRESOURCE(IDM_CREDITS), hWnd, About);
			break;
		}
		case IDM_RainBow:
		{
			// Rainbow 펜 
			if(rainbow_timer == NULL)
				rainbow_timer = SetTimer(hWnd, RAINBOW, 50, NULL);
			else
			{
				KillTimer(hWnd, RAINBOW);
				rainbow_timer = NULL;
			}
			return 0;
		}
		case IDM_SAVE:
		{
			OPENFILENAME OFN;
			wchar_t str[256] = { 0, };
			wchar_t file_name[256] = L"";
			memset(&OFN, 0, sizeof(OPENFILENAME));

			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
			OFN.lpstrFile = file_name;
			OFN.nMaxFile = 256;
			

			if (GetSaveFileName(&OFN) != 0)
			{
				//wsprintf(str, L"%s파일을 선택했습니다.", OFN.lpstrFile);
				//MessageBox(hWnd, str, L"파일 열기 성공", MB_OK);
				wsprintf(str, L"%s", OFN.lpstrFile);
				if(file_save(g_SPinfo, str))
					MessageBox(hWnd, str, L"파일 저장 성공", MB_OK);
				else
					MessageBox(hWnd, L"실패", L"파일 저장 실패", MB_OK);
			}
			else
			{
				MessageBox(hWnd, L"실패", L"파일 저장 실패", MB_OK);
			}
			break;
		}
		case IDM_LOAD:
		{
			OPENFILENAME OFN;
			wchar_t str[256] = { 0, };
			wchar_t file_name[256] = { 0, };
			memset(&OFN, 0, sizeof(OPENFILENAME));

			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
			OFN.lpstrFile = file_name;
			OFN.nMaxFile = 256;

			if (GetOpenFileName(&OFN) != 0)
			{
				wsprintf(str, L"%s", OFN.lpstrFile);
				if (file_load(g_SPinfo, str))
					MessageBox(hWnd, str, L"파일 열기 성공", MB_OK);
				else
					MessageBox(hWnd, L"실패", L"파일 열기 실패", MB_OK);
			}
			else
			{
				MessageBox(hWnd, L"실패", L"파일 열기 실패", MB_OK);
			}
			InvalidateRect(NULL, NULL, true);
			break;
		}
		case IDM_5s:
			scr_save_time = 5 * 1000;
			break;
		case IDM_10s:
			scr_save_time = 10 * 1000;
			break;
		case IDM_30s:
			scr_save_time = 30 * 1000;
			break;
		case IDM_1min:
			scr_save_time = 60 * 1000;
			break;
		case IDM_5min:
			scr_save_time = 5 * 60 * 1000;
			break;
		case IDM_10min:
			scr_save_time = 10 * 60 * 1000;
			break;
		case IDM_30min:
			scr_save_time = 30 * 60 * 1000;
			break;
		case IDM_save_enable:
			scr_save_time = 99999999;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}

	case WM_TIMER:
	{
		switch (wParam)
		{
		case RAINBOW:
		{
			static int i = 0; // 3 ~ 11
			pen->set_color(cols[i+3]);
			InvalidateRect(hWnd, &palette->btn_ran.rect, true);
			InvalidateRect(hWnd, &pen->area, true);
			i = (i + 1) % 9;
			break;
		}
		default:
			break;
		}
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...


		// 서명 영역 출력
		paint_signed_area(hWnd, hdc);
		// 로고 출력
		Drawlogo(hInst, hdc, Main_Logo_X, Main_Logo_Y, Main_Logo_Width, Main_Logo_Height, Main_logo);
		Drawlogo(hInst, hdc, Serve_Logo_X, Serve_Logo_Y, Serve_Logo_Width, Serve_Logo_Height, Serve_logo);
		// 팔레트 출력
		palette->paint(hWnd, hdc);

		// 펜 형태 출력
		pen->paint(hWnd, hdc);
		pen->paint_text(hWnd, hdc);

		// 버튼 출력
		for (const auto i : buttons)
			i->paint(hWnd, hdc);
		//btn_test->paint(hWnd, hdc);

		//이전의 그림 정보 출력
		if(replay_thread == nullptr)
			mouse_paint(hdc);

		EndPaint(hWnd, &ps);
		break;
	}

	case WM_LBUTTONDOWN:
		// 팔레트가 눌렸는지 확인
		ret = palette->is_press(lParam);
		if (ret != -1)
		{
			pen->set_color(ret);
			InvalidateRect(hWnd, &pen->area, TRUE);
			KillTimer(hWnd, RAINBOW);
			rainbow_timer = NULL;
			break;
		}

		// 버튼이 눌렸는지 확인 및 버튼 처리
		ret = button_check(lParam);
		do {
			if (ret == 0)
				break;
			if (ret == PLUS)
				break;
			if (ret == MINUS)
				break;
			if (ret == RAINBOW_b)
				break;
			KillTimer(hWnd, RAINBOW);
			rainbow_timer = NULL;
			break;
		} while (true);

		switch (ret)
		{
		case 0:
			break;
		case REPLAY:
			if (replay_thread == nullptr)	// 생성되어있지 않다면
			{
				Critical_flag(false);
				replay_thread = CreateThread(NULL, 0, drawing, nullptr, 0, NULL);
			}
			else
				Critical_flag(true);
			InvalidateRect(hWnd, NULL, true);
			break;
		case CLEAR:
			if (replay_thread != nullptr)
				Critical_flag(true);
			g_SPinfo.pinfo.clear();
			InvalidateRect(hWnd, NULL, true);
			break;
		case RANDOM:
			pen->set_color(palette->ChangeRand());
			InvalidateRect(hWnd, &palette->btn_ran.rect, true);
			InvalidateRect(hWnd, &pen->area, true);
			break;
		case PLUS:
			pen->set_size_up();
			InvalidateRect(hWnd, &pen->area, TRUE);
			InvalidateRect(hWnd, &pen->text_area, TRUE);
			break;
		case MINUS:
			pen->set_size_down();
			InvalidateRect(hWnd, &pen->area, TRUE);
			InvalidateRect(hWnd, &pen->text_area, TRUE);
			break;
		case CREDIT :
			dialog = DialogBox(hInst, MAKEINTRESOURCE(IDM_CREDITS), hWnd, About);
			KillTimer(hWnd, RAINBOW);
			rainbow_timer = NULL;
			break;
		case SAVE :
		{
			OPENFILENAME OFN;
			wchar_t str[256] = { 0, };
			wchar_t file_name[256] = L"";
			memset(&OFN, 0, sizeof(OPENFILENAME));

			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
			OFN.lpstrFile = file_name;
			OFN.nMaxFile = 256;


			if (GetSaveFileName(&OFN) != 0)
			{
				//wsprintf(str, L"%s파일을 선택했습니다.", OFN.lpstrFile);
				//MessageBox(hWnd, str, L"파일 열기 성공", MB_OK);
				wsprintf(str, L"%s", OFN.lpstrFile);
				if (file_save(g_SPinfo, str))
					MessageBox(hWnd, str, L"파일 저장 성공", MB_OK);
				else
					MessageBox(hWnd, L"실패", L"파일 저장 실패", MB_OK);
			}
			else
			{
				MessageBox(hWnd, L"실패", L"파일 저장 실패", MB_OK);
			}
			break;
		}
		case LOAD:
		{
			OPENFILENAME OFN;
			wchar_t str[256] = { 0, };
			wchar_t file_name[256] = { 0, };
			memset(&OFN, 0, sizeof(OPENFILENAME));

			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = L"모든 파일(*.*)\0*.*\0";
			OFN.lpstrFile = file_name;
			OFN.nMaxFile = 256;

			if (GetOpenFileName(&OFN) != 0)
			{
				wsprintf(str, L"%s", OFN.lpstrFile);
				if (file_load(g_SPinfo, str))
					MessageBox(hWnd, str, L"파일 열기 성공", MB_OK);
				else
					MessageBox(hWnd, L"실패", L"파일 열기 실패", MB_OK);
			}
			else
			{
				MessageBox(hWnd, L"실패", L"파일 열기 실패", MB_OK);
			}
			InvalidateRect(NULL, NULL, true);
			break;
		}
		case RAINBOW_b:
			if (rainbow_timer == NULL)
				rainbow_timer = SetTimer(hWnd, RAINBOW, 50, NULL);
			else
			{
				KillTimer(hWnd, RAINBOW);
				rainbow_timer = NULL;
			}
			break;
		default:
			break;
		}

	case WM_MOUSEMOVE:
		if (GetTickCount64() - scr_start_time > 300)	// 화면보호기 시작 후 0.5 초 동안 무효화
		{
			Scr_Creitical_flag(false);	// 마우스 관련 이벤트 발생시 false 로 만듦
			scr_check_time = GetTickCount64();
		}
		
	case WM_LBUTTONUP:
		
		mouse_proc(hWnd, message, lParam, pen->size, pen->col);
		break;

	case WM_DESTROY:
		delete(palette);

		DeleteCriticalSection(&cs);
		DeleteCriticalSection(&scr_cs);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	End_Credit = hDlg;

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



// 리플레이 스레드
DWORD WINAPI drawing(LPVOID points)
{
	HDC hdc;
	HPEN npen;
	int x, y;
	hdc = GetDC(g_hWnd);
	is_replay = true;

	npen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
	while (true)
	{
		if (g_SPinfo.pinfo.size() == 0) break;
		if (is_terminate) break;
		InvalidateRect(g_hWnd, NULL, TRUE);
		for (size_t i = 0; i < (int)(g_SPinfo.pinfo.size() - 1); i++)
		{
			if (is_terminate)
				break;
			
			DeleteObject(npen);
			npen = CreatePen(PS_SOLID, g_SPinfo.pinfo[i].cWidth, g_SPinfo.pinfo[i].color);
			SelectObject(hdc, npen);

			switch (g_SPinfo.pinfo[i].state)
			{
			case WM_LBUTTONDOWN:
				//MessageBox(hWnd, L"실행", L"L버튼", MB_OK);
				x = LOWORD(g_SPinfo.pinfo[i].lparm);
				y = HIWORD(g_SPinfo.pinfo[i].lparm);

				MoveToEx(hdc, x, y, NULL);
				LineTo(hdc, x, y + 1);  //점찍기
				break;

			case WM_MOUSEMOVE:
				LineTo(hdc, LOWORD(g_SPinfo.pinfo[i].lparm), HIWORD(g_SPinfo.pinfo[i].lparm));

				break;
			case WM_LBUTTONUP:
				LineTo(hdc, LOWORD(g_SPinfo.pinfo[i].lparm), HIWORD(g_SPinfo.pinfo[i].lparm));
				break;

			default:
				break;
			}
			if (g_SPinfo.pinfo[i + 1].state == WM_MOUSEMOVE)  // 다음벡터도 WM_MOUSEMOVE일 경우에만 sleep 
			{
				Sleep(g_SPinfo.pinfo[i + 1].ctime - g_SPinfo.pinfo[i].ctime);
			}
		}

		for (size_t i = 0; i < 300; i++)
		{
			Sleep(10);
			if (is_terminate)
				break;
		}
		
	}

	InvalidateRect(g_hWnd, NULL, TRUE);
	DeleteObject(npen);
	ReleaseDC(g_hWnd, hdc);
	Critical_flag(false);
	replay_thread = nullptr;
	return 0;
}

// 화면보호기 
DWORD WINAPI Scr_Save_thread(LPVOID points)
{
	vector<WCHAR*> file_list;
	static SPINFO temp_spinfo;
	static HDC hdc;
	static RECT window = {0};
	HBRUSH nbrush;
	HPEN npen;
	RECT win = {0,};
	WCHAR path[255];
	
	HANDLE hFind;
	WIN32_FIND_DATAW data = { 0, };

	// 화면 영역을 전체 화면 영역으로 전환
	// hWnd 0 에 전체영역으로 칠하기
	//GetWindowRect(0, window);
	// 그대로 그리기 기능 실행
	// 그리기 완성 시 3초 대기
	temp_spinfo = g_SPinfo;
	int x, y;
	SetCurrentDirectory(L"..//..//page");
	GetCurrentDirectory(255, path);
	while (true)
	{
		while (GetTickCount64() - scr_check_time + 50 >= (long long)scr_save_time)
		{
			Scr_Creitical_flag(true);
			scr_start_time = GetTickCount64();
			temp_spinfo.pinfo.clear();

			KillTimer(g_hWnd, RAINBOW);
			rainbow_timer = NULL;

			ShowWindow(g_hWnd, SW_MAXIMIZE);	// 윈도우 최대화
			GetWindowRect(g_hWnd, &win);			// 윈도우 크기 구하기
			Sleep(200);

			// 파일 받아오기
			//GetCurrentDirectory()
			SetCurrentDirectory(path);
			//MessageBox(0, path, L"저장 경로", MB_OK);
			file_list.clear();
			hFind = FindFirstFileW(L"*", &data);
			FindNextFileW(hFind, &data);
			//FindNextFileW(hFind, &data);
			while (FindNextFileW(hFind, &data))
			{
				WCHAR* temp;
				temp = new WCHAR[50];
				wcscpy(temp, data.cFileName);
				file_list.push_back(temp);
				//MessageBox(0, data.cFileName, L"저장 경로", MB_OK);
			}
			FindClose(hFind);

			// 화면보호기 실행
			while(true)
			{
				SetFocus(g_hWnd);// 포커스 이동

				hdc = GetDC(0);
				nbrush = CreateSolidBrush(WINDOW_COLOR);
				npen = CreatePen(PS_SOLID, 1, WINDOW_COLOR);
				SelectObject(hdc, nbrush);
				SelectObject(hdc, npen);
				Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
				ReleaseDC(0, hdc);

				hdc = GetDC(g_hWnd);
				SelectObject(hdc, nbrush);
				SelectObject(hdc, npen);
				Rectangle(hdc, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

				if (temp_spinfo.pinfo.size() == 0 && g_SPinfo.pinfo.size() != 0)// 화면 보호기가 작동하고 처음이라면 
					temp_spinfo = g_SPinfo;
				else if (!file_list.empty())
				{
					int i = rand() % file_list.size();
					WCHAR path_temp[255];
					wcscpy(path_temp, path);
					wcscat(path_temp, L"\\");
					wcscat(path_temp, file_list[i]);
					file_load(temp_spinfo, path_temp);
				}

				if (!is_save) break;	// 화면 보호기 탈출
				
				if (!temp_spinfo.pinfo.empty())	// 두가지를 받아왔을 경우에도 temp_spinfo가 비어 있다면 무한 대기
				{
					for (size_t i = 0; i < temp_spinfo.pinfo.size() - 1; i++)
					{
						if (!is_save) break;

						DeleteObject(npen);
						npen = CreatePen(PS_SOLID, temp_spinfo.pinfo[i].cWidth, temp_spinfo.pinfo[i].color);
						SelectObject(hdc, npen);

						//x = (LOWORD(temp_spinfo.pinfo[i].lparm)-temp_spinfo.x) * (float)GetSystemMetrics(SM_CXSCREEN) / (float)temp_spinfo.width;
						x = (int)((LOWORD(temp_spinfo.pinfo[i].lparm) - temp_spinfo.x) * (float)GetSystemMetrics(SM_CXSCREEN) / (float)temp_spinfo.width / 2L);
						y = (int)((HIWORD(temp_spinfo.pinfo[i].lparm)-temp_spinfo.y) * (float)GetSystemMetrics(SM_CYSCREEN) / (float)temp_spinfo.height * 1.7);
						
						switch (temp_spinfo.pinfo[i].state)
						{
						case WM_LBUTTONDOWN:
							MoveToEx(hdc, x, y, NULL);
							LineTo(hdc, x, y + 1);
							break;

						case WM_MOUSEMOVE:
							LineTo(hdc, x, y);
							break;

						case WM_LBUTTONUP:
							LineTo(hdc, x, y);
							break;

						default:
							break;
						}
						if (temp_spinfo.pinfo[i + 1].state == WM_MOUSEMOVE)  // 다음벡터도 WM_MOUSEMOVE일 경우에만 sleep 
						{
							Sleep((temp_spinfo.pinfo[i + 1].ctime - temp_spinfo.pinfo[i].ctime));
						}
					}
				}
				
				// 랜덤으로 파일 받아오기
				if (!file_list.empty())
				{
					int i = rand() % file_list.size();
					WCHAR path[80];
					wcscpy(path, FILE_PATH);
					wcscat(path, L"/");
					wcscat(path, file_list[i]);
					file_load(temp_spinfo, path);
				}

				// 3초 기다리기
				for (size_t i = 0; i < 30; i++)
				{
					Sleep(100);
					if (!is_save)
						break;
				}
				if (!is_save) break;	// 화면 보호기 탈출
			}
			if (!is_save)// 화면 보호기 탈출
			{
				DeleteObject(nbrush);
				DeleteObject(npen);
				ReleaseDC(g_hWnd, hdc);

				ShowWindow(g_hWnd, SW_RESTORE);
				InvalidateRect(0, NULL, true);
				break;
			}
			
			for (const auto& i : file_list)
			{
				delete i;
			}
		}
	}
	return 0;
}


// 서명영역인지 반환해주는 함수
bool is_area(LPARAM lParam)
{
   do
	{
		if (LOWORD(lParam) < BOUNDARY_LEFT + 3)     // left가 범위 밖이면 break
			break;
		if (BOUNDARY_RIGHT - 3 < LOWORD(lParam))    // right가 범위 밖이면 break
			break;
		if (HIWORD(lParam) < BOUNDARY_TOP + 3)    // top가 범위 밖이면 break
			break;
		if (BOUNDARY_BOTTOM - 3 < HIWORD(lParam))    // bottom가 범위 밖이면 break
			break;
		return true;
	} while (1);
	return false;
}


void paint_signed_area(HWND hWnd, HDC hdc)
{
	HBRUSH nbrush, obrush;
	HFONT nfont, ofont;
	nbrush = CreateSolidBrush(WINDOW_COLOR);
	obrush = (HBRUSH)SelectObject(hdc, nbrush);

	nfont = CreateFont(35, 0, 0, 0, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		VARIABLE_PITCH | FF_ROMAN, TEXT("굴림"));

	ofont = (HFONT)SelectObject(hdc, nfont);

	SetBkColor(hdc, WINDOW_COLOR);  // TextOut의 배경색을 윈도우와 동일하게 변경
	SetBkMode(hdc, OPAQUE);     // TextOut의 배경을 불투명으로 변경
									// TRANSPARENT 투명, OPAQUE 불투명
	Rectangle(hdc, BOUNDARY_LEFT, BOUNDARY_TOP, BOUNDARY_RIGHT, BOUNDARY_BOTTOM);

	SelectObject(hdc, font);

	TextOut(hdc, BOUNDARY_LEFT + 15, BOUNDARY_TOP - 20, L"서명", lstrlenW(L"서명"));
	
	SelectObject(hdc, obrush);
	SelectObject(hdc, ofont);
	DeleteObject(nbrush);
	DeleteObject(nfont);
}


void mouse_proc(HWND hWnd, UINT message, LPARAM lParam, int size, COLORREF col)
{
	static int pre_x, pre_y;
	static bool left = false;

	HDC hdc;
	PINFO temp_pinfo;
	HPEN npen, open;
	int x, y;

	if (!is_area(lParam))
	{
		left = false;
		return;
	}

	hdc = GetDC(hWnd);

	npen = CreatePen(PS_SOLID, size, col);
	open = (HPEN)SelectObject(hdc, npen);

	x = LOWORD(lParam);
	y = HIWORD(lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:

		left = true;
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x, y + 1);
		
		pre_x = x;
		pre_y = y;

		temp_pinfo.lparm = lParam;
		temp_pinfo.state = message;
		temp_pinfo.color = col;
		temp_pinfo.cWidth = size;
		temp_pinfo.ctime = (DWORD)GetTickCount64();
		g_SPinfo.pinfo.push_back(temp_pinfo);
		break;

	case WM_MOUSEMOVE:

		if (left)
		{
			left = true;
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, pre_x, pre_y);

			pre_x = x;
			pre_y = y;

			temp_pinfo.lparm = lParam;
			temp_pinfo.state = message;
			temp_pinfo.color = col;
			temp_pinfo.cWidth = size;
			temp_pinfo.ctime = (DWORD)GetTickCount64();
			g_SPinfo.pinfo.push_back(temp_pinfo);
		}
		break;

	case WM_LBUTTONUP:
		if (left)
		{
			temp_pinfo.lparm = lParam;
			temp_pinfo.state = message;
			temp_pinfo.color = col;
			temp_pinfo.cWidth = size;
			temp_pinfo.ctime = (DWORD)GetTickCount64();
			g_SPinfo.pinfo.push_back(temp_pinfo);
		}

		left = false;
		break;
	}

	DeleteObject(npen);
	ReleaseDC(hWnd, hdc);
	return;
}

void mouse_paint(HDC hdc)
{
	HPEN open, npen;
	bool left = false;
	int x, y;
	npen = CreatePen(PS_SOLID,5,RGB(255, 255, 255));
	open = (HPEN)SelectObject(hdc, npen);
	for (const auto& i : g_SPinfo.pinfo)
	{
		x = LOWORD(i.lparm);
		y = HIWORD(i.lparm);

		DeleteObject(npen);
		npen = CreatePen(PS_SOLID, i.cWidth, i.color);
		SelectObject(hdc, npen);

		switch (i.state)
		{
		case WM_LBUTTONDOWN:
			
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x, y + 1);
			left = true;
			break;
		case WM_MOUSEMOVE:
			LineTo(hdc, x, y);
			break;
		case WM_LBUTTONUP:
			left = false;
			break;
		default:
			break;
		}
	}
	SelectObject(hdc, open);

}

// 버튼체크
DWORD button_check(LPARAM lParam)
{
	DWORD msg;
	for (const auto i : buttons)
	{
		msg = i->is_press(lParam);
		if (msg)
			return msg;
	}
	return 0;
}

void Center_Screen(HWND window, DWORD style, DWORD exStyle)
{
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT clientRect; GetClientRect(window, &clientRect);
	int clientWidth = clientRect.right - clientRect.left;
	int clientHeight = clientRect.bottom - clientRect.top;
	SetWindowPos(window, NULL, screenWidth / 2 - clientWidth / 2, screenHeight / 2 - clientHeight / 2 - 40, clientWidth, clientHeight, 0);
}


// is_terminate 값 변경 임계영역
void Critical_flag(bool flag)
{
	if (is_terminate == flag)
		return;
	EnterCriticalSection(&cs);
	is_terminate = flag;
	LeaveCriticalSection(&cs);
}

void Scr_Creitical_flag(bool flag)
{
	
	if (flag == true)
	{
		EndDialog(End_Credit, LOWORD(1));
	}

	if (is_save == flag)
	{
		return;
	}

	EnterCriticalSection(&scr_cs);
	is_save = flag;

	if (flag == true)
	{
		Critical_flag(true);
	}

	LeaveCriticalSection(&scr_cs);
}