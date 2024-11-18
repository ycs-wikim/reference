#include "PenThickness.h"
#include "resource.h"
#include <CommCtrl.h>  

int PenThickness::penWidth = 10;

PenThickness::PenThickness() {}

PenThickness::~PenThickness() {}

// 펜 굵기 설정 대화 상자를 표시하는 함수
void PenThickness::show(HINSTANCE hInst, HWND hWndParent) {
    initializeCommonControls();
    DialogBox(hInst, MAKEINTRESOURCE(IDD_PEN_THICKNESS), hWndParent, dlgProc);
}

// 슬라이더와 같은 공용 컨트롤을 사용할 수 있도록 초기화하는 함수
void PenThickness::initializeCommonControls() {
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_BAR_CLASSES;
    InitCommonControlsEx(&icex);
}

// 대화 상자 프로시저, 대화 상자에서 발생하는 메시지를 처리
INT_PTR CALLBACK PenThickness::dlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG:
        SendDlgItemMessage(hDlg, IDC_THICKNESS_SLIDER, TBM_SETRANGE, TRUE, MAKELPARAM(1, 20));  // 펜 굵기 범위 1 ~ 20까지 수정 시 늘리거나 줄일 수 있음
        SendDlgItemMessage(hDlg, IDC_THICKNESS_SLIDER, TBM_SETPOS, TRUE, penWidth);
        SetDlgItemInt(hDlg, IDC_THICKNESS_EDIT, penWidth, FALSE);
        return TRUE;  // 대화 상자가 성공적으로 초기화되었음을 반환

    case WM_HSCROLL:  // 슬라이더를 조작할 때 발생하는 메시지 처리
        if (LOWORD(wParam) == TB_THUMBTRACK || LOWORD(wParam) == TB_ENDTRACK) {
            penWidth = SendDlgItemMessage(hDlg, IDC_THICKNESS_SLIDER, TBM_GETPOS, 0, 0);
            SetDlgItemInt(hDlg, IDC_THICKNESS_EDIT, penWidth, FALSE);
        }
        return TRUE;

    case WM_COMMAND:  // 버튼 클릭 등 명령을 처리
        switch (LOWORD(wParam)) {
        case IDOK:
            penWidth = GetDlgItemInt(hDlg, IDC_THICKNESS_EDIT, NULL, FALSE);
            EndDialog(hDlg, IDOK);
            return TRUE;

        case IDCANCEL:
            EndDialog(hDlg, IDCANCEL);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

// 펜 굵기를 반환하는 함수
int PenThickness::getPenWidth() {
    return penWidth;  // 현재 설정된 펜 굵기 값 반환
}

void PenThickness::setPenWidth(int width) {
    penWidth = width;
}