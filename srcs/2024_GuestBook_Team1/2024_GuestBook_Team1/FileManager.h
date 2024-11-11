#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "Function.h"
#include "Struct.h"
#include "Resource.h"
#include "Function.h"
#include "DW_SideMenu.h"
#include "DW_NameBar.h"
#include "WndFunc.h"
#include <unordered_set> //파일리스트 중복 방지 헤더  
#include <shlobj.h> //세이브파일 절대 경로 확인 
#include "DW_FileManager.h"


class DW_SideMenu;

class FileManager
{
private:

    bool HandleFileOperation(HWND hWnd, std::vector<PINFO>* penMemory, bool isSave);
    bool ConfigureDialog(HWND hWnd, DWORD flags, WCHAR* fileBuffer, DWORD bufferSize);
    bool save(const wchar_t* path, std::vector<PINFO>* penMemory, HWND hWnd);
    bool load(const wchar_t* path, std::vector<PINFO>* penMemory, HWND hWnd);
    bool openForWrite(const wchar_t* path);
    bool openForRead(const wchar_t* path);

    OPENFILENAME OFN = { 0 };
    WCHAR fileName[260] = { 0 };
    WCHAR fileOpenName[260] = { 0 };
    WCHAR str[260] = { 0 };

    std::fstream fs;
    HWND m_hWnd;
    bool isPanelVisible;

public:
    FileManager() = default;
    ~FileManager() = default;

    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    void selectFileMode(int wmId, HWND cWnd, std::vector<PINFO>* penMemory);
    static FileManager fileManager;

    void AddFileToList(const std::wstring& fileName);
    void UpdateFileListUI();

    std::vector<std::wstring> savedFileList;  // 파일명을 저장하는 리스트
    HWND hFileListBox;  /// 파일 목록을 표시할 리스트 박스
    HWND hRightPanel;   /// 패널 핸들
    HINSTANCE hInst;    /// 인스턴스 핸들

    void SaveFileList(); ///파일리스트 저장
    void LoadFileList(); ///파일리스트 불러오기

    static std::wstring baseName; // 정적 변수 선언

    std::unique_ptr<Function> function;
};
