// 오목 (성공)
// https://www.acmicpc.net/problem/2615
// 
// 5개의 돌이 연속으로 놓인경우 에만 한 쪽이 이겼다고 판정한다.
// 바둑판의 상태가 입력으로 주어질 때 상태와 가장 왼쪽 위의 위치를 출력하라 (승부가 나지 않은 경우는 위치를 출력하지 않는다.)
// 
// 동시에 이긴경우, 두군데 이상에서 동시에 이긴경우는 들어오지 않는다.
// 검은색이 이긴 경우 1, 흰색이 이긴경우 2, 아직 승부가 나지 않은 경우 0

// 가장 왼쪽에 있는 점의 좌표를 출력한다.
// 만약 상하로 길게 늘어져 있는 경우 가장 위의 좌표를 출력한다.
//

#include <iostream>

#define NONE 0
#define BLACK 1
#define WHITE 2

using namespace std;

int board[19][19];	// 바둑판의 상태를 받을 배열

		// 좌, 우, 상, 하, 우상, 좌하, 좌상, 우하
int dx[] = { -1, 1, 0, 0, 1, -1, -1, 1 };
int dy[] = { 0, 0, -1, 1, -1, 1, -1, 1 };


// 해당 방향으로 몇개가 같은 것 인가?
// 중심을 제외한 개수를 반환
// x,y을 제외하고 특정 방향으로 몇개의 돌이 같은 돌인지 수를 세는 함수
int move_check(int x, int y, int dx, int dy)
{
	int temp_x = x + dx, temp_y = y + dy;
	int count = 0;
	do
	{
		// count 가 5가 넘어 간다면
		if (count >= 5)
			break;

		// 좌표가 범위 밖으로 넘어간다면
		if (temp_x < 0)
			break;
		if (19 <= temp_x)
			break;
		if (temp_y < 0)
			break;
		if (19 <= temp_y)
			break;

		// 돌이 없는 경우 종료
		if (board[temp_y][temp_x] == NONE)
			break;

		// 다른 색상의 돌이 온다면
		if (board[y][x] != board[temp_y][temp_x])
			break;

		//돌의 갯수를 1 증가시키고 다음 좌표로 이동함
		temp_x += dx;
		temp_y += dy;
		count++;

	} while (true);

	// 연속된 돌의 갯수 반환
	return count;
}

// 정확하게 5만 판별해내야 함
// 현재 위치부터 5개가 연달아 존재하는지 확인
bool five_check(int x, int y)
{
	int count;			// 연속된 돌의 갯수를 셀 변수

	// dx dy를 이용하여 방향성을 주며 탐색함
	// count 가 정확하게 5라면 true 반환
	for (int i = 0; i < 8; i += 2)
	{
		count = 1;
		count += move_check(x, y, dx[i], dy[i]);
		count += move_check(x, y, dx[i + 1], dy[i + 1]);

		// 정확하게 5개가 연달아 있다면 true 반환
		if (count == 5)
			return true;
	}

	// 5개가 아니라면 false 반환
	return false;
}

// 둘이 동시에 이기는 경우는 없음
int solve()
{
	// x좌표
	for (int x = 0; x < 19; x++)
	{
		// y좌표
		for (int y = 0; y < 19; y++)
		{
			// 돌이 올려져 있지 않다면 continue
			if (board[y][x] == NONE)
				continue;

			// 5개가 연속이라면
			if (five_check(x, y))
			{
				// 승자가 있다면 승자와 좌표를 출력하고 함수 종료
				cout << board[y][x] << "\n";
				cout << y + 1 << " " << x + 1;
				return board[y][x];
			}
		}
	}
	// 승자가 없다면 0 출력하고 함수 종료
	cout << NONE;
	return NONE;
}

int main()
{
	// 오목판을 입력받음
	for (auto& i : board)
	{
		for (auto& j : i)
		{
			cin >> j;
		}
	}

	// 풀이 코드를 호출 함
	solve();
	return 0;
}