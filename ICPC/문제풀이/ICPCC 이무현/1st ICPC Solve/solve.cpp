#include <iostream>
#include <vector>

using namespace std;
vector<vector<char>>map;

// 해당 범위가 동일한 숫자로 이루어져 있는지 확인
// 가장 처음 오는 문자를 저장 한 후 다른 문자가 오면 false 반환
bool check(int x, int y, int width)
{
	char t = map[y][x];
	for (size_t i = y; i < y + width; i++)
	{
		for (size_t j = x; j < x + width; j++)
		{
			if (t != map[i][j])
			{
				return false;		// 불일치 하는 문자가 하나라도 오면 false 반환
			}
		}
	}
	return true;		// 범위내의 모든 문자가 동일한 경우 true 반환
}

// 문제 도입부
// 범위지정 및 문제 해결방법 정의
int solve(int x, int y, int width)
{
	// 모든 문자가 같다면 해당 문자 출력
	if (check(x, y, width))
	{
		cout << map[y][x];
	}
	// 다른 문자가 있다면 네부분으로 나눠 풀이
	else
	{
		int half = width / 2;		// 반복적인 수를 줄이기 위한 임시변수
		cout << "(";
		solve(x, y, half);			// 좌상

		solve(x + half, y, half);	// 우상

		solve(x, y + half, half);	// 좌하

		solve(x + half, y + half, half);	// 우하
		cout << ")";
	}
	return 0;
}

int main(void)
{
	int n;			// 2의 제곱수 2 4 8 16 32 64이 들어온다.
	cin >> n;		// n을 입력 받는다.

	map = vector<vector<char>>(n, vector<char>(n,0));	
	
	// 값을 대입
	for (size_t y = 0; y < n; y++)
	{
		for (size_t x = 0; x < n; x++)
		{
			cin >> map[y][x];
		}
	}
	solve(0, 0, n);		// 0,0을 기점으로 전체를 탐색하며 시작
	return 0;
}


