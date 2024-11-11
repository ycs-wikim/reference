#include "DW_SideMenu.h"

/// 네임 바 정적 메서드
LRESULT CALLBACK DrowWindow::WndProcSB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

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
        return pThis->handleMessageSB(hWnd, message, wParam, lParam); // 인스턴스의 가상 함수 호출
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/// 사이드 메뉴의 이미지 버튼 생성
/// 현재 사이드 버튼 RECT크기 대비 이미지 작은 건 수정 예정
MakeButton sideNew(5, 5, 55, 55);
MakeButton sideSave(5, 65, 55, 115);
MakeButton sideLoad(5, 125, 55, 175);
MakeButton sideFM(5, 185, 55, 235);
MakeButton sideCredit(5, 245, 55, 295);

std::vector<PINFO>* DW_SideMenu::penMemory = new std::vector<PINFO>; /// 추가

RECT mouseSide;     /// InterSect를 위한 마우스 좌표 받을 RECT
RECT aSide;         /// InterSect로 반환되는 RECT

bool isListBoxVisible = true; // 초기값: 리스트박스가 보이도록 설정

/// 네임 바 메세지 처리 핸들 메서드
LRESULT DrowWindow::handleMessageSB(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_CREATE:
    {
        // 바탕화면의 "file" 폴더 경로 가져오기
        std::wstring fileFolderPath = DW_FileManager::getFilePath();

        // "file" 폴더 존재 여부 확인 및 생성
        DWORD ftyp = GetFileAttributesW(fileFolderPath.c_str());
        if (ftyp == INVALID_FILE_ATTRIBUTES) {
            // 폴더가 존재하지 않는 경우, 생성
            if (!CreateDirectoryW(fileFolderPath.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
                // 폴더 생성 실패 처리
                MessageBox(hWnd, L"파일 폴더를 생성할 수 없습니다.", L"오류", MB_OK);
                return -1; // 생성 실패 시 윈도우 생성 중단
            }
        }

        break;
    }
    case WM_COMMAND:
    {

        break;
    }
    case WM_LBUTTONDOWN:
    {
        if (function->getIsReplay()) {
            break;
        }
        /// 좌클릭시 현재 마우스 좌표(lParam)을 받아 마우스 RECT 생성
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);

        mouseSide.left = x;
        mouseSide.top = y;
        mouseSide.right = mouseSide.left + 1;
        mouseSide.bottom = mouseSide.top + 1;

        /// 파일 뉴파일
        if (IntersectRect(&aSide, &mouseSide, &sideNew.rectButton)) {
            function->setisLeftClick(false);

            /// 메세지 박스 없애고 if문(InTerSect)내부에 실행 코드 추가
            /// 메세지 박스는 이미지 버튼 활성화 여부 알아보기 위해 임시로 추가한 것
            if (function->getDrawLInfoEmpty()) { break; }
            if (!function->getIsReplay()) {
                SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_CLEAR_BT, 0);
                SendMessage(WndFunc::nameWnd, WM_SETTEXT, 0, (LPARAM)L"이름 없음");
            }
        }

        /// 파일 세이브
        else if (IntersectRect(&aSide, &mouseSide, &sideSave.rectButton)) {
            function->setisLeftClick(false);

            /// 메세지 박스 없애고 if문(InTerSect)내부에 실행 코드 추가
            FileManager::fileManager.selectFileMode(SAVE, hWnd, DW_SideMenu::penMemory); /// 추가
        }

        /// 파일 로드
        else if (IntersectRect(&aSide, &mouseSide, &sideLoad.rectButton)) {
            function->setisLeftClick(false);


            DW_SideMenu::penMemory->clear();

            /// 메세지 박스 없애고 if문(InTerSect)내부에 실행 코드 추가
            FileManager::fileManager.selectFileMode(LOAD, hWnd, DW_SideMenu::penMemory); /// 추가
        }

        /// 파일 매니저
        else if (IntersectRect(&aSide, &mouseSide, &sideFM.rectButton)) {
            function->setisLeftClick(false);

            // 리스트박스 보이기/숨기기 처리

            RECT rect;
            GetClientRect(WndFunc::drowWnd, &rect);
            int Width = rect.right;
            int Height = rect.top;
            int Fm_x = Width - 250;
            int Fm_y = Height + 110;
            int x_2 = 190;
            int y_2 = 302;
            //오른쪽 넓이를 줄이려면 createWindowFM에 3번째(x_2) 좌표값을 줄이기 
            //왼쪽 넓이를 줄이려면 Fm_x 값을 더 줄이면 됩니다.  결과적으로 넓이(폭) 그 자체를 줄이고 싶으면 위에 내용과 여기 내용을 둘 다 사용해야 함.

            createWindowFM(Fm_x, Fm_y, x_2, y_2, WndFunc::drowWnd); //파일매니저 윈도우 생성 

            isListBoxVisible = !isListBoxVisible; // 현재 상태 반전

            ShowWindow(DW_FileManager::hListBox, isListBoxVisible ? SW_HIDE : SW_SHOW); // 리스트박스 보이기/숨기기
            ShowWindow(WndFunc::fileManager, isListBoxVisible ? SW_HIDE : SW_SHOW); // 리스트박스 보이기/숨기기   
        }

        /// 크레딧
        else if (IntersectRect(&aSide, &mouseSide, &sideCredit.rectButton)) {
            SendMessage(GetParent(WndFunc::drowWnd), WM_COMMAND, DEF_CREDIT_BT, 0);
        }
        break;
    }
    case WM_SIZE: // 창 사이즈 변할 때 사이드메뉴 따라가도록 설정.
    {
        RECT rect;
        GetClientRect(WndFunc::drowWnd, &rect);

        int Width = rect.right;
        int Height = rect.top;

        int Fm_x = Width - 250;
        int Fm_y = Height + 110;
        int n_Width = 190;
        int n_Height = 302;

        // 파일매니저 창의 크기와 위치 업데이트
        MoveWindow(WndFunc::fileManager, Fm_x, Fm_y, n_Width, n_Height, TRUE);
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        /// 이미지 버튼 이미지 등록 및 그리기 실행 (필요시 MakeButton.h(.cpp) 참고)
        sideNew.drawRectButton(hdc, IDI_NEW_FILE_ICON);
        sideSave.drawRectButton(hdc, IDI_SAVE_ICON);
        sideLoad.drawRectButton(hdc, IDI_LOAD_ICON);
        sideFM.drawRectButton(hdc, IDI_FILEMANAGER_ICON);
        sideCredit.drawRectButton(hdc, IDI_CREDIT_ICON);


        EndPaint(hWnd, &ps);
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
