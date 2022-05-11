#include"GB_File_io.h"

bool file_save(const SPINFO& info_vector, const wchar_t* path)
{
	//wchar_t path[256];
	fstream fs;


	//MessageBox(0, path, L"저장 경로", MB_OK);

	if (info_vector.pinfo.size() < 100)
		return false;

	fs.open(path, ios::out | ios::trunc);
	if (fs.fail())	// 파일 열기에 실패한 경우
		return false;
	fs << info_vector.x << " ";
	fs << info_vector.y << " ";
	fs << info_vector.width << " ";
	fs << info_vector.height << endl;
	for (const auto& i : info_vector.pinfo)
	{
		fs << i.lparm << " ";
		fs << i.cWidth << " ";
		fs << i.color << " ";
		fs << i.ctime << " ";
		fs << i.state << endl;
	}
	fs.close();
	return true;
}


bool file_load(SPINFO& info_vector, const wchar_t* path)
{
	wchar_t dir[100];
	fstream fs;

	//wsprintf(dir, L"%s/%s", FILE_PATH, path);

	//MessageBox(0, dir, L"불러오기 경로", MB_OK);

	fs.open(path, ios::in);
	if (fs.fail())	// 파일열기에 실패한 경우
		return false;
	info_vector.pinfo.clear();
	fs >> info_vector.x;
	fs >> info_vector.y;
	fs >> info_vector.width;
	fs >> info_vector.height;
	while (!fs.eof())
	{
		PINFO temp;
		fs >> temp.lparm;
		fs >> temp.cWidth;
		fs >> temp.color;
		fs >> temp.ctime;
		fs >> temp.state;
		info_vector.pinfo.push_back(temp);
	}
	return true;
}
