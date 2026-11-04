#include "ButtonController.h"

using namespace std;

void ButtonController::Create(HWND parents, LPCWSTR text, int id, int x, int y, int w, int h)
{
	hwnd = CreateWindowW(
		L"STATIC",
		text,
		WS_VISIBLE | WS_CHILD | SS_ICON | SS_NOTIFY,
		x, y,
		w, h,
		parents,
		(HMENU)(UINT_PTR)id,
		(HINSTANCE)GetWindowLongPtr(parents, GWLP_HINSTANCE),
		nullptr
	);
}

void ButtonController::HandleCommand(WPARAM wParam) {
	int id = LOWORD(wParam); /// 버튼 ID식별
	int UserContact = HIWORD(wParam); /// 알림 코드 확인

	/// STATIC 컨트롤의 클릭 알림(STN_CLICKED)일 때만 처리합니다.
	if (UserContact == STN_CLICKED) {
		if (ButtonMessage.count(id)) {
			ButtonMessage[id]();
		}
	}
}

void ButtonController::RegisterHandler(int id, std::function<void()> fn) {
	ButtonMessage[id] = fn;
}

void ButtonController::SetImage(int resourceId)
{
	HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(resourceId));
	if (hIcon) {
		SendMessage(hwnd, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
	}

}
