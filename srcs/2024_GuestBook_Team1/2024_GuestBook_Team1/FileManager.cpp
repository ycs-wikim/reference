#include "FileManager.h"

FileManager FileManager::fileManager; //인스턴스 

std::wstring FileManager::baseName = L"";
// 파일 이름을 담아요 

// 스마트 포인터로 ConnExcel 객체 선언
std::unique_ptr<ConnExcel> connExcelFM = std::make_unique<ConnExcel>();


//파일리스트에 파일을 추가하는 함수 
void FileManager::AddFileToList(const std::wstring& fileName)
{
    ///1. baseName이라는 변수에 fileName의 문자열을 넣어줌.
    std::wstring baseName = fileName;
    ///2. fileName의 문자열에서 마지막 \ 또는 /을 찾음 
    size_t pos = fileName.find_last_of(L"\\/");
    ///3. 2번의 경우가 아닐때, pos + 1부터 문자열 끝까지 잘라서 baseName에 저장
    if (pos != std::wstring::npos)
    {
        baseName = fileName.substr(pos + 1);
    }

    /// 파일 이름이 이미 저장된 리스트에 있는지 확인
    if (std::find(savedFileList.begin(), savedFileList.end(), baseName) == savedFileList.end())
    {
        /// 리스트에 존재하지 않으면 리스트에 추가
        savedFileList.push_back(baseName);
        //그 후 파일리스트 UI를 업데이트 
        UpdateFileListUI();
    }
}
void FileManager::SaveFileList()
{
    // 바탕화면 경로를 가져옴
    wchar_t desktopPath[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
        // 만약 경로를 얻지 못했다면 그냥 종료
        MessageBox(nullptr, L"경로 설정에 실패했습니다.", L"오류", MB_OK);
        return;
    }

    // 바탕화면 경로에 저장할 파일 경로를 추가
    std::wstring filePath = L"..\\file\\";

    // 파일 열기 (경로에 파일이 없으면 새로 생성됨)
    std::wofstream ofs(filePath, std::ios::out | std::ios::trunc);
    if (!ofs.is_open())
    {
        MessageBox(nullptr, L"파일 리스트 저장에 실패했습니다.", L"오류", MB_OK);
        return;
    }

    // 중복된 파일을 방지하기 위해 savedFileList를 처리하여 저장
    std::unordered_set<std::wstring> uniqueFiles(savedFileList.begin(), savedFileList.end());
    for (const auto& file : uniqueFiles)
    {
        ofs << file << std::endl;
    }

    ofs.close();
}

void FileManager::LoadFileList()
{
    // 바탕화면 경로를 가져옴
    wchar_t desktopPath[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
        // 만약 경로를 얻지 못했다면 그냥 종료
        return;
    }

    // 바탕화면 경로에 파일 경로를 추가
    std::wstring filePath = L"..\\file\\";

    // 파일 열기
    std::wifstream ifs(filePath);
    if (!ifs.is_open())
    {
        return;
    }

    std::wstring line;
    while (std::getline(ifs, line))
    {
        if (!line.empty())
        {
            savedFileList.push_back(line);
        }
    }

    ifs.close();

    UpdateFileListUI();
}



//파일리스트 UI를 업데이트 함
void FileManager::UpdateFileListUI()
{
    if (DW_FileManager::hListBox == nullptr)
    {
        return;
    }

    /// 파일 리스트에 파일명 추가
    for (const auto& file : savedFileList)
    {
        if (SendMessage(DW_FileManager::hListBox, LB_FINDSTRINGEXACT, -1, (LPARAM)file.c_str()) == LB_ERR) {
            // LB_ADDSTRING API로 추가 
            SendMessage(DW_FileManager::hListBox, LB_ADDSTRING, 0, (LPARAM)file.c_str());
        }
    }
}



bool FileManager::save(const wchar_t* path, std::vector<PINFO>* penMemory, HWND hWnd) {

    if (!openForWrite(path)) {
        MessageBox(nullptr, L"파일 저장에 실패 하였습니다.", L"Error", MB_OK);
        return false;
    }
    MessageBox(nullptr, L"파일 저장에 성공 하였습니다.", L"Error", MB_OK);

    /// penMemory의 데이터를 파일에 기록
    for (const auto& i : *penMemory) {

        this->fs << i.lParam << ' '
            << i.pWidth << ' '
            << i.pColor << ' '
            << i.pTime << ' '
            << i.state << ' '
            << i.stampValue << ' '
            << i.bShape << std::endl;

        if (this->fs.fail()) {
            MessageBox(nullptr, L"파일 쓰기 중 오류 발생", L"Error", MB_OK);
            break;
        }
    }

    /// 파일 이름만 추출
    baseName = path;
    size_t pos = baseName.find_last_of(L"\\/");
    if (pos != std::wstring::npos) {
        baseName = baseName.substr(pos + 1);

        std::wstring visitorName = baseName; // 방문자 이름을 wstring 형식으로 저장
        connExcelFM->insertExcel(visitorName);
    }

    this->fs.close();
    AddFileToList(path);

    InvalidateRect(hWnd, NULL, TRUE); /// 화면 갱신
    UpdateWindow(hWnd); /// 화면 업데이트

    return true;
}

/**
 * @fn FileManager::load
 * @brief 파일을 로드하는 함수.
 */
bool FileManager::load(const wchar_t* path, std::vector<PINFO>* penMemory, HWND hWnd) {
    if (!openForRead(path)) {
        MessageBox(nullptr, L"파일 열기에 실패했습니다.", L"Error", MB_OK);
        return false;
    }
    MessageBox(nullptr, L"파일이 성공적으로 열렸습니다.", L"Info", MB_OK);

    penMemory->clear();
    PINFO pen_info;

    /// 파일에서 데이터를 읽어와 penMemory에 추가
    while (this->fs >> pen_info.lParam
        >> pen_info.pWidth
        >> pen_info.pColor
        >> pen_info.pTime
        >> pen_info.state
        >> pen_info.stampValue
        >> pen_info.bShape) {
        penMemory->push_back(pen_info);
    }

    this->fs.close(); /// 파일을 닫음
    AddFileToList(path);  /// 파일 리스트에 추가
    UpdateFileListUI();

    // Function::drawLInfo.pInfo = *penMemory;

     /// 파일 이름만 추출
    baseName = path;
    size_t pos = baseName.find_last_of(L"\\/");
    if (pos != std::wstring::npos) {
        baseName = baseName.substr(pos + 1);
    }

    /// FileNameW에 파일 이름 표시
    SendMessage(WndFunc::nameWnd, WM_SETTEXT, 0, (LPARAM)baseName.c_str());

    InvalidateRect(hWnd, NULL, TRUE); /// 화면 갱신
    UpdateWindow(hWnd); /// 화면 업데이트


    return true;
}
/**
 * @fn FileManager::openForWrite
 * @brief 파일을 쓰기 모드로 여는 함수.
 */
bool FileManager::openForWrite(const wchar_t* path) {
    fs.open(path, std::ios::out | std::ios::trunc);
    return !fs.fail();
}

/**
 * @fn FileManager::openForRead
 * @brief 파일을 읽기 모드로 여는 함수.
 */
bool FileManager::openForRead(const wchar_t* path) {
    fs.open(path, std::ios::in);
    return !fs.fail();
}

// 파일 대화상자를 여는 함수 
bool FileManager::ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize) {
    // 바탕화면 경로 가져오기
    wchar_t desktopPath[MAX_PATH];
    if (FAILED(SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
        MessageBox(nullptr, L"경로 설정에 실패했습니다.", L"오류", MB_OK);
        return false;
    }

    // "file" 폴더 경로 생성
    std::wstring initialDir = L"..\\file\\";

    OFN.lStructSize = sizeof(OPENFILENAME);
    OFN.hwndOwner = hWnd;
    OFN.lpstrFile = fileBuffer;
    OFN.nMaxFile = bufferSize;
    OFN.lpstrInitialDir = initialDir.c_str(); // 초기 디렉토리 설정
    OFN.Flags = flags;

    return (flags & OFN_OVERWRITEPROMPT) ? GetSaveFileName(&OFN) : GetOpenFileName(&OFN);
}

/// 파일을 열거나 저장하는 작업을 하는 창을 뜨게 함 (EX: 다른 이름으로 저장) 
/// OFN_PATHMUSTEXIST: 경로가 유효해야 함.
/// OFN_OVERWRITEPROMPT: 같은 파일명이 존재할 경우 덮어쓰기를 확인.
/// OFN_FILEMUSTEXIST : 파일이 실제로 존재해야 함(파일 열기 시 사용).
bool FileManager::HandleFileOperation(HWND hWnd, std::vector<PINFO>* penMemory, bool isSave) {


    DWORD flags = isSave ? (OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT) : (OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST);
    WCHAR* filePath = isSave ? fileName : fileOpenName;

    /// 대화상자가 취소되면 false를 반환하도록 수정
    if (!ConfigureDialog(hWnd, flags, filePath, sizeof(fileName))) {
        //DW_SideMenu::penMemory->clear();
        SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_CLEAR_BT, 0);
        SendMessage(WndFunc::nameWnd, WM_SETTEXT, 0, (LPARAM)L"이름 없음");
        return false;  // 대화상자가 취소되면 바로 종료
    }

    // ConfigureDialog가 성공적으로 완료된 경우에만 저장 또는 로드 실행
    return isSave ? save(filePath, penMemory, hWnd) : load(filePath, penMemory, hWnd);
}


void FileManager::selectFileMode(int wmId, HWND s_hWnd, std::vector<PINFO>* penMemory)
{
    switch (wmId) {
    case SAVE:
    {
        *penMemory = Function::drawLInfo.pInfo;
        // penMemory가 비어있지 않을 경우에만 메시지 전송
        HandleFileOperation(s_hWnd, penMemory, true);
        SendMessage(WndFunc::canvasWnd, WM_COMMAND, TL_CLEAR_BT, 0);
        SendMessage(WndFunc::nameWnd, WM_SETTEXT, 0, (LPARAM)L"이름 없음");
    }
    break;

    case LOAD:
    {
        HandleFileOperation(s_hWnd, penMemory, false);
        Function::drawLInfo.pInfo = *penMemory;

        // penMemory가 비어있지 않을 경우에만 메시지 전송
        if (!penMemory->empty())
        {
            SendMessage(WndFunc::toolWnd, WM_COMMAND, TL_PLAY_BT, 0); // 추가
        }

        if (IsWindowVisible(WndFunc::fileManager) || IsWindowVisible(WndFunc::sideWnd))
        {
            ShowWindow(WndFunc::fileManager, SW_HIDE); // 열려 있으면 닫기
            ShowWindow(WndFunc::sideWnd, SW_HIDE); // 열려 있으면 닫기
            DW_NameBar::sideMenu.toggleState = false;
            InvalidateRect(WndFunc::nameWnd, NULL, TRUE);
        }

        /// 화면 갱신
        InvalidateRect(s_hWnd, NULL, TRUE);
        UpdateWindow(s_hWnd);
    }
    break;

    case SD_FILEMANAGER_BT:
    {
        /// MessageBox(nullptr, DW_FileManager::filePath.c_str(), L"파일 경로", MB_OK); // 경로 출력

        if (IsWindowVisible(WndFunc::fileManager) || IsWindowVisible(WndFunc::sideWnd))
        {
            ShowWindow(WndFunc::fileManager, SW_HIDE); // 열려 있으면 닫기
            ShowWindow(WndFunc::sideWnd, SW_HIDE); // 열려 있으면 닫기
            DW_NameBar::sideMenu.toggleState = false;
            InvalidateRect(WndFunc::nameWnd, NULL, TRUE);

        }
        /// filePath에 저장된 파일을 즉시 로드
        if (load(DW_FileManager::filePath.c_str(), penMemory, s_hWnd)) {
            Function::drawLInfo.pInfo = *penMemory;

            /// 파일 이름만 추출
            baseName = DW_FileManager::filePath;
            size_t pos = baseName.find_last_of(L"\\/");
            if (pos != std::wstring::npos) {
                baseName = baseName.substr(pos + 1);
            }

            /// FileNameW에 파일 이름 표시
            SendMessage(WndFunc::nameWnd, WM_SETTEXT, 0, (LPARAM)baseName.c_str()); /// 2024_GuestBook_Team1로 메시지 전달
            SendMessage(WndFunc::toolWnd, WM_COMMAND, TL_PLAY_BT, 0); /// 추가

            /// 화면 갱신
            InvalidateRect(s_hWnd, NULL, TRUE);
            UpdateWindow(s_hWnd);
        }
    }
    break;
    }
}












