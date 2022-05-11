#pragma once
#include<fstream>

#include"GB_moudles.h"

#define FILE_PATH L"../../page"
using namespace std;

bool file_save(const SPINFO& info_vector, const wchar_t* name);
bool file_load(SPINFO& info_vector, const wchar_t* name);


