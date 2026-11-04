#include "DrawWindow.h"
#include "ColorController.h"
#include "BackBuffer.h"
#include "MainWindow.h"
#include "Application.h"

		bool DrawWindow::Create(HWND parentHwnd, HINSTANCE hInst) {
		hInstance = hInst;
		WNDCLASS wc = {};
		wc.lpfnWndProc = DrawWindow::WndProc;
		wc.hInstance = hInst;
		wc.lpszClassName = L"DrawWindowClass";
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);

		RegisterClass(&wc);

		hwnd = CreateWindowEx(
			0, wc.lpszClassName, L"Guest Book",
			WS_CHILD | WS_VISIBLE,
			0, 50, 700, 600,
			parentHwnd, NULL, hInst, this);
		g_pSaverManager = new ScreensaverManager(hwnd, hInst);
		OutputDebugString(L"create drawWindow\n");
		return hwnd != nullptr;
	}

	LRESULT CALLBACK DrawWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		DrawWindow* self = nullptr;

		if (msg == WM_NCCREATE) {
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			self = reinterpret_cast<DrawWindow*>(cs->lpCreateParams);
			if (self) {
				self->hwnd = hwnd;
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)self);
			}
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		
		self = reinterpret_cast<DrawWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		if (self) return self->HandleMessage(msg, wParam, lParam);

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	LRESULT DrawWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam) {

		switch (msg) {		
		case WM_CREATE: {
			TRACKMOUSEEVENT tme = { 0 };
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hwnd;
			TrackMouseEvent(&tme);
			//화면보호기 추가 코드
			SetTimer(hwnd, IDT_SAVER_TIMER, 1000, NULL);

			m_hPenCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_PENCIL));
			m_hEraserCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ERASER));
			return 0;
		}

		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			RECT rc;
			GetClientRect(hwnd, &rc);
			OnPaint(hdc, rc);
			EndPaint(hwnd, &ps);
			return 0;
		}

		case WM_TIMER:
		{
			if (wParam == IDT_SAVER_TIMER && g_pSaverManager) {
			// 스크린세이버 매니저에게 무활동 검사 지시
			if (isReplaying) {
				g_pSaverManager->ResetActivityTimer();
				return 0;
			}
				g_pSaverManager->CheckInactivity();
		}
			return 0;
		}

		case WM_LBUTTONDOWN:
			OnLButtonDown((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), wParam);
			return 0;

		case WM_MOUSEMOVE:
			OnMouseMove((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), wParam);
			return 0;

		case WM_LBUTTONUP:
			OnLButtonUp((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), wParam);
			return 0;

		case WM_USER_REPLAY_UPDATE:
			InvalidateRect(hwnd, NULL, false);
			UpdateWindow(hwnd);
			return 0;

		case WM_SIZE: {
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);
			OnSize(width, height);
			return 0;
		}
		case WM_SETCURSOR: {
			TRACKMOUSEEVENT tme = { 0 };
			tme.cbSize = sizeof(tme);
			tme.dwFlags = TME_LEAVE;
			tme.hwndTrack = hwnd;
			TrackMouseEvent(&tme);
			if (LOWORD(lParam) == HTCLIENT) {

				HCURSOR hCurrent = erasing ? m_hEraserCursor : m_hPenCursor;

				SetCursor(hCurrent);

				return TRUE;
			}
			break;
		}

		case WM_MOUSELEAVE: {
			m_currentMousePos = { -100, -100 };

			if (!backBuffer || !cacheBuffer || isReplaying) return 0;
			RECT rc; GetClientRect(hwnd, &rc);
			BitBlt(backBuffer->dc(), 0, 0, rc.right - rc.left, rc.bottom - rc.top,
				cacheBuffer->dc(), 0, 0, SRCCOPY);

			HDC hdc = GetDC(hwnd);
			backBuffer->DrawBufferToScreen(hdc);
			ReleaseDC(hwnd, hdc);
			return 0;
		}
		case WM_DESTROY: {
			if (backBuffer) delete backBuffer;
			if (cacheBuffer) delete cacheBuffer;

			//화면보호기 추가 코드
			// 타이머 해제 및 매니저 삭제
			KillTimer(hwnd, IDT_SAVER_TIMER);
			if (g_pSaverManager) {
				delete g_pSaverManager;
				g_pSaverManager = nullptr;
			}

			backBuffer = nullptr;
			cacheBuffer = nullptr;
			return 0;
		}

		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}


	void DrawWindow::OnPaint(HDC hdc, const RECT& rcClient) {
		if (!backBuffer || !cacheBuffer) return;

		cacheBuffer->ClearBuffer(rcClient);
		const auto& strokes = strokeCtrl.Strokes();
		drawCtrl.DrawStrokes(cacheBuffer->dc(), strokes, penWidth, selectedColor);

		BitBlt(backBuffer->dc(), 0, 0, rcClient.right, rcClient.bottom,
			cacheBuffer->dc(), 0, 0, SRCCOPY);

		drawCtrl.DrawCursorDot(backBuffer->dc(), m_currentMousePos,
			currentPenWidth,
			selectedColor,
			erasing);
		backBuffer->DrawBufferToScreen(hdc);

		if (strokeCtrl.IsRecording()) {
			const Stroke* cur = strokeCtrl.Current();
			if (cur) {
				drawCtrl.DrawLatestStroke(backBuffer->dc(), *cur,
					cur->penWidth,
					cur->color);
			}
		}


	}

	void DrawWindow::OnLButtonDown(int x, int y, WPARAM) {
		if (isReplaying) return;
		SetCapture(hwnd);
		COLORREF color = selectedColor;

		strokeCtrl.Begin(x, y, color, currentPenStyle, currentPenWidth);


	}

	void DrawWindow::OnMouseMove(int x, int y, WPARAM flags) {
		if (!backBuffer || !cacheBuffer || isReplaying) return;

		m_currentMousePos.x = x;
		m_currentMousePos.y = y;

		RECT rc;
		GetClientRect(hwnd, &rc);
		BitBlt(backBuffer->dc(), 0, 0, rc.right - rc.left, rc.bottom - rc.top,
			cacheBuffer->dc(), 0, 0, SRCCOPY);

		drawCtrl.DrawCursorDot(backBuffer->dc(), m_currentMousePos,
			currentPenWidth,
			selectedColor,
			erasing);

		if (flags & MK_LBUTTON) {
			strokeCtrl.Add(x, y);

			const Stroke* cur = strokeCtrl.Current();
			if (cur) {

				drawCtrl.DrawLatestStroke(backBuffer->dc(), *cur, currentPenWidth, selectedColor);

			}
		}

				HDC hdc = GetDC(hwnd);
				backBuffer->DrawBufferToScreen(hdc);
				ReleaseDC(hwnd, hdc);
	}

	void DrawWindow::OnLButtonUp(int x, int y, WPARAM) {
		if (!backBuffer || !cacheBuffer || isReplaying) return;

		if (strokeCtrl.IsRecording()) {
			strokeCtrl.Add(x, y);
			const Stroke* finishedStroke = strokeCtrl.Current();

			if (finishedStroke) {
				drawCtrl.DrawLatestStroke(cacheBuffer->dc(), *finishedStroke,
					finishedStroke->penWidth,
					finishedStroke->color);
			}

			strokeCtrl.End();
			ReleaseCapture();

			RECT rc;
			GetClientRect(hwnd, &rc);
			BitBlt(backBuffer->dc(), 0, 0, rc.right - rc.left, rc.bottom - rc.top,
				cacheBuffer->dc(), 0, 0, SRCCOPY);

			drawCtrl.DrawCursorDot(backBuffer->dc(), m_currentMousePos,
				currentPenWidth,
				selectedColor,
				erasing);

			HDC hdc = GetDC(hwnd);
			backBuffer->DrawBufferToScreen(hdc);
			ReleaseDC(hwnd, hdc);
		}
	}

	void DrawWindow::ClearAll() {
		if(!isReplaying)strokeCtrl.Clear();

		RECT rc;
		GetClientRect(hwnd, &rc);
		if (backBuffer) {
			backBuffer->ClearBuffer(rc);
		}
		if (cacheBuffer) {
			cacheBuffer->ClearBuffer(rc);
		}
		InvalidateRect(hwnd, nullptr, TRUE);
	}

	void DrawWindow::ClearScreenOnly() {
		RECT rc;
		GetClientRect(hwnd, &rc);
		if (backBuffer) {
			backBuffer->ClearBuffer(rc);
		}

		InvalidateRect(hwnd, nullptr, TRUE);
	}

	HDC DrawWindow::GetMemDc() const { return backBuffer ? backBuffer->dc() : nullptr; }

	void DrawWindow::SetPenStyle(int PenNum) {
   		switch (PenNum) {
		case 0: currentPenStyle = PS_SOLID; break;
		case 1: currentPenStyle = PS_DASH;  break;
		case 2: currentPenStyle = PS_DOT;   break;
		default: currentPenStyle = PS_SOLID; break;
		}


	}
	void DrawWindow::SetPenWidth(int PenWidth) {
		currentPenWidth = PenWidth;
	}

	void DrawWindow::HideSystemCursor() {
		if (!m_isCursorHidden) {
			ShowCursor(FALSE);
			m_isCursorHidden = true;
		}
	}

	void DrawWindow::ShowSystemCursor() {
		if (m_isCursorHidden) {
			ShowCursor(TRUE);
			m_isCursorHidden = false;
		}
	}
	void DrawWindow::OnSize(int width, int height) {
		if (backBuffer) {
			delete backBuffer;
			backBuffer = nullptr;
		}
		if (cacheBuffer) {
			delete cacheBuffer;
			cacheBuffer = nullptr;
		}

		if (width == 0 || height == 0) return;

		HDC hdc = GetDC(hwnd);

		backBuffer = new BackBuffer();
		backBuffer->CreateBuffer(hdc, width, height);

		cacheBuffer = new BackBuffer();
		cacheBuffer->CreateBuffer(hdc, width, height);

		ReleaseDC(hwnd, hdc);

		InvalidateRect(hwnd, NULL, TRUE);
	}
	    
	void DrawWindow::Reset() {
		strokeCtrl.Reset();
		currentPenWidth = 5;
		selectedColor = RGB(0, 0, 0); 
		currentPenStyle = PS_SOLID;
		erasing = false;
		isReplaying = false;
		InvalidateRect(hwnd, NULL, TRUE);
	}