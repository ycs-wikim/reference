// 던전지도 (실패)
// https://www.acmicpc.net/problem/19543
// 
// 던전을 돌아 보스방을 찾아가려 한다
// 출발 지점을 선택 할 수 있을 때 보스방으로 향할 수 있는 방의 수를 출력하라.
// 
// N * M 크기 y * x 로 방의 크기가 주어진다.
// 라인의 수가 주어진다.
// 라인의 수 만큼 문자열이 주어진다.
// N 만큼 문자열이 주어지며 이 문자열이 던전의 모양을 의미한다.

// 가장 오른쪽 줄의 위쪽에서 U이 아니라면 전부 false이다.

#include<iostream>
#include<vector>
#include<algorithm>

//#define DEBUG

#define UP		'U'
#define RIGHT	'R'
#define FAIL	'F'
#define SUCCESS	'S'

using namespace std;

struct input {
	int Y_boundary;		// y값의 최댓값
	int X_boundary;		// x값의 최댓값
	int	number_tile;	// 타일의 수
	string tile_list;	// 타일의 순서를 입력받음
} input = {0,0,0};

vector<string> temp_tile;	// 타일을 임시 저장할 벡터

long long int solve()
{
	long long int start, end;
	long long int result = 0;
	string tile;

	// 가장 오른쪽 위 칸에서 시작함
	// 가장 오른쪽의 인덱스 번호를 가진다.
	start = end = input.X_boundary - 1;	

	tile = temp_tile[input.tile_list[input.tile_list.size() - 1] - 'A'];
	// 도착지점은 무조건 U로 하고 시작한다.
	tile[tile.size() - 1] = 'U';

	
	for (long long int i = input.tile_list.size() - 1 ; i >= 0; i--)
	{
		// start를 옮김
		// 현재 위치의 왼쪽에 R이 있다면 왼쪽으로 한칸 옮김
		// 자신의 왼쪽이 U일 때 까지 왼쪽으로 한칸 씩 옮김
		do
		{
			// 왼쪽으로 이동할 수 없으면 그대로 종료
			// 이유는 가장 좌측의 값이 R이든 U이든 범위 내에 존재하기 때문에 무슨 값이 되든 상관 없다.
			if (start - 1 < 0)
				break;

			// 나보다 왼쪽의 값이 U 라면 이동이 불가능
			if (tile[start - 1] != RIGHT)
				break;

			// start 가 범위 내에 있으면서 좌측이 R값이라면 이동
			start--;
		} while (true);

		// end를 옮김
		// 현재 위치가 가 아니라면 왼쪽으로 한칸 옮김
		// U가 나올때 까지 위치를 계속 옮김
		do
		{
			// end를 옮겼는데 start 보다 end가 더 작아진다면 더 이상 진행 할 수 있는 방이 없으므로 종료
			if (end < start)
				break;

			// 나의 값이 U라면 이동할 필요가 없음
			if (tile[end] == UP)
				break;

			end--;
		} while (true);		
/*
#ifdef DEBUG
		cout << start + 1 << " " << end + 1 << " " << end - start + 1 << "\n";
		cout << tile << "\n\n";
#endif // DEBUG
*/
		// end가 start 보다 작아지면 조건에 만족하는 방이 없으므로 종료
		if (end < start)
			break;

		// 결과값을 누산 
		result += end - start + 1;

		if (i - 1 < 0)
			break;
		// tile에 다음에 확인해야하는 위치의 타일 형태를 임시 저장
		tile = temp_tile[input.tile_list[i - 1] - 'A'];
	}

	return result;
}

int main(void)
{
	char temp;

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	// 맵 크기와 타일의 수를 입력받아 저장
	cin >> input.Y_boundary >> input.X_boundary;
	cin >> input.number_tile;

	// 타일 종류를 입력받음
	// A : 0 
	// 타일의 갯수만큼 크기를 할당함
	temp_tile = vector<string>(input.number_tile);
	for (long long int i = 0 ; i < temp_tile.size() ; i++)
		cin >> temp_tile[i];

	// 타일의 배치순서를 입력 받음
	cin >> input.tile_list;

	cout << solve();

/*
#ifdef DEBUG
	srand(time(NULL));
	while (true)
	{
		cin >> temp;
		input.tile_list.clear();
		for (int i = 0; i < input.Y_boundary; i++)
		{
			input.tile_list.push_back(rand() % temp_tile.size() + 'A');
		}

		for (int i = input.tile_list.size() - 1; i >= 0; i--)
		{
			cout << temp_tile[input.tile_list[i] - 'A'] << "\n";
		}

		cout << solve() << "\n";
	}
#endif // DEBUG
*/
	
}
