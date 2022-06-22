#include <iostream>
//#include "dll_2.h"

#define ex1     0 // all blined 상태

#define ex2     1 // 암시적 (사전작업 : dll의 헤더파일, dll의 lib파일, dll의 위치)
#if ex2
//#pragma comment(lib, "dll_2.lib") // #pragma comment(lib, “DLL명.lib”) 
/*
만약 헤더파일에 __declspec(dllimport)가 정의되어 있지 않다면 직접 함수 정의를 하고 사용해야됨
 ex) int sum(int x, int y); 이런식으로

3줄 요약
    속성 -> c/c++ -> 일반 -> 추가 포함 디렉터리  = dll 헤더파일이 있는 폴더 경로
    속성 -> 링커 -> 일반 -> 추가 라이브러리 디렉터리 = dll의 lib 경로

    난 #pragma comment(lib, "DLL명.lib") 이것도 쓰기 싫다?
    속성 -> 링커 -> 입력 -> 추가 종속성 = .lib 파일 지정(dll_1.lib) 경로 아님 특정 파일 지정임

    실행파일과 dll이 같은 위치에 있어야됨
*/
#endif // ex2

#define ex3     1 // 명시적 (사전작업 : #include <windows.h>, dll의 위치)
#if ex3
#include <Windows.h>
typedef int (*LPDLLFUNC)(int, int);
/*
실행중일때 dll을 링크하여 사용함 사용하기에 복잡하고 <windows.h> 선언 필요
dll의 헤더파일에 extern "C" KK1DLL int Add(int a, int b); 이런 식으로 함수마다 선언해야됨
*/
#endif // ex3

int main()
{

#if ex2     // 암시적
    std::cout << Add(10, 20) << std::endl;
#endif


#if ex3     // 명시적

    HINSTANCE hDLL = LoadLibrary(L"dll_2");
    //LoadLibrary(L"dll 이름")으로 dll을 로드하고

    if (NULL == hDLL) {
        printf("dll 로드 실패\n");
        return -1;
    }
    // 로드가 됐는지 확인 

    LPDLLFUNC pDllFunc = (LPDLLFUNC)GetProcAddress(hDLL, "Sub");
    // dll의 이름과 선언한 함수의 주소를 받아와서 호출함
    // GetProcAddress( dll 담은 변수, "호출할 함수명");

    if (NULL == pDllFunc)
    {
        printf("함수 호출 실패\n");
        return -1;
    }
    // 원하는 함수 주소 잘 받아왔는지 확인

    std::cout << pDllFunc(10, 40) << std::endl;
    // 함수 주소를 받아왔으니 주소에 인자로 값을 넘겨줌
    FreeLibrary(hDLL);
    // dll 해제
    return 0;

#endif
}