// 던전지도 (성공)
// https://www.acmicpc.net/problem/19543


// 아이디어1	: 맵을 전부 만들어 아래에서부터 dfs 방식으로 탐색하자
// 철회 이유	: 200000 * 200000 의 데이터를 전부 저장할 수 없다.
// 
// 아이디어 2	: 우측 상단에서부터 일정 범위만 판단하면 도달 할 수 있는지 확인 할 수 있다
//					이를 통해 가능한 방의 수만 계산하자
// 
//

// 실패원인 1	: 오버플로우	자료의 최대크기가 long long int 까지 되는것을 확인하지 못하고 풀이함
// 실패원인 2	: 시간초과		string 자료형의 대입연산에서 값의 복사가 일어나는 것을 인지하지 못하였음
//								이를 포인터 연산으로 변경하여 해결함
// 실패원인 3	: 포인터		포인터 연산시 숙련되지 못한 방식으로 작성하여 혼란이 왔으며, 
//								인덱스 범위를 초과하거나 쓰레기 값이 들어가 런타임 에러를 발생시킴
//

 
// size() 함수 사용 최소화 하기


#include<iostream>
#include<vector>
#include<algorithm>


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
} input = { 0,0,0 };

vector<string> temp_tile;	// 타일을 임시 저장할 벡터

long long int solve()
{
	long long int start, end;
	long long int result = 0;
	string * tile;			// 타일의 주소값을 갖고 연산함 (복사 방지)
	string top;

	// 가장 오른쪽 위 칸에서 시작함
	// 가장 오른쪽의 인덱스 번호를 가진다.
	start = end = input.X_boundary - 1;

	// 가장 위의 타일을 저장하여 도착지점(가장 오른쪽 칸)을 U로 표기함
	top = temp_tile[ input.tile_list[input.tile_list.size()-1] - 'A' ];
	top[top.size() - 1] = 'U';
	
	// 검색할 tile에 가장 위의 타일을 등록함
	tile = &top;

	for (long long int i = input.tile_list.size() - 1; i >= 0; i--)
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
			if ((*tile)[start - 1] != RIGHT)
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
			if ((*tile)[end] == UP)
				break;

			end--;
		} while (true);

		// end가 start 보다 작아지면 조건에 만족하는 방이 없으므로 종료
		if (end < start)
			break;

		// 결과값을 누산 
		result += end - start + 1;

		if (i - 1 < 0)
			break;

		// tile에 다음에 확인해야하는 위치의 타일 형태를 임시 저장
		tile = &temp_tile[(input.tile_list[i - 1] - 'A')];
	}
	return result;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	// 맵 크기와 타일의 수를 입력받아 저장
	cin >> input.Y_boundary >> input.X_boundary;
	cin >> input.number_tile;

	// 타일 종류를 입력받음
	// A : 0 
	// 타일의 갯수만큼 크기를 할당함
	temp_tile = vector<string>(input.number_tile);
	for (long long int i = 0; i < temp_tile.size(); i++)
		cin >> temp_tile[i];

	// 타일의 배치순서를 입력 받음
	cin >> input.tile_list;

	cout << solve();
	return 0;
}
