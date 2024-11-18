#pragma once
#include "DrowWindow.h"
#include "FileManager.h"
#include "DW_SideMenu.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <shlobj.h>  // SHGetKnownFolderPath
#include <knownfolders.h>  // FOLDERID_Desktop

class DW_FileManager
{
public:
    static HWND hListBox;
    static void saveFileList(const std::vector<std::wstring>& fileList);
    static std::vector<std::wstring> loadFileList();
    static std::wstring filePath;
    static std::wstring getFilePath();

protected:

    HWND NewFile; 
    HWND SaveFile;
    HWND LoadFile;
    HWND FileManager;
   
};

