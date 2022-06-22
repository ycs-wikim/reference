//암시적
#pragma once

#ifdef DLL_EXPORTS
#define KK1DLL __declspec(dllexport)
#else
#define KK1DLL __declspec(dllimport)
#endif
/* 
만약 DLL_EXPORTS가 정의되어 있다면
KK1DLL은 __declspec(dllexport)로 치환되고
DLL_EXPORTS가 정의되어 있지 않다면
KK1DLL은 __declspec(dllimport)로 치환된다.

__declspec(dllexport)에서 dllexport란?
	외부에서 이 함수를 사용할 수 있도록 dll로 내보내겠다는 의미이고
__declspec(dllimport)에서 dllimport란?
	외부에서 dll 파일을 사용할 때 선언하여 dll로부터 이 함수를 가져와서 사용하겠다는 의미


*/

extern "C" KK1DLL int Add(int a, int b);
extern "C" KK1DLL int Sub(int a, int b);