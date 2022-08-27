// 실패
// 2343 [실버 5] 기타 레슨
// https://www.acmicpc.net/problem/2343

// 참조
// https://movefast.tistory.com/311

// n개의 영상 m개의 블루레이
// dvd의 최소요구 크기 구하기 

#include<iostream>
#include<vector>
using namespace std;

#define LEFT -1
#define NONE 0
#define RIGHT 1

struct start_end
{
	int start;
	int end;
};

vector<int> videos;		// video의 길이를 입력받을 벡터
vector<int> sum_cd;		// cd의 크기를 누적 저장해놓을 벡터
vector<start_end> cd_point;		// cd의 시작점과 끝을 저장할 벡터

// 경계값을 옮기는 것이 더 낮은 값을 갖는지 확인하는 메소드
// a < b 를 항상 만족해야한다.
int move_is_lower(int a, int b)
{
	int left, right;	// 경계의 왼쪽에 있는 값, 오른쪽에 있는 값

	left = videos[cd_point[a].end];		// 경계의 왼쪽에 있는 값 중 가장 오른쪽에 있는 값
	right = videos[cd_point[b].start];	// 경계의 오른쪽에 있는 값 중 가장 왼쪽에 있는 값

	// 두 부분합이 같은경우 옮기지 않는 것이 좋다.
	if (sum_cd[a] == sum_cd[b])
		return NONE;
	
	// 경계를 이동한 경우
	// 기존의 최대값보다 옮겼을 때의 최대값 보다 내려가면 옮기는 것이 좋다.

	// 경계를 왼쪽으로 이동한 경우
	// a의 합계는 낮아지고 b의 합계는 높아진다.
	if (max(sum_cd[a], sum_cd[b]) > max(sum_cd[a] - left, sum_cd[b] + left))
	{
		// 참인 경우 왼쪽으로 옮기는 것이 좋다
		return LEFT;
	}

	// 경계를 오른쪽으로 이동한 경우
	// a의 합계는 높아지고 b의 합계는 낮아진다.
	if (max(sum_cd[a], sum_cd[b]) > max(sum_cd[a] + right, sum_cd[b] - right))
	{
		// 참인 경우 왼쪽으로 옮기는 것이 좋다
		return RIGHT;
	}

	return NONE;
}

// 두 비디오의 경계선을 좌 우로 옮긴다.
bool boundary_move(int a, int b, int direction)
{
	int temp;
	// 경계의 이동이 왼쪽 방향이라면
	if (LEFT == direction)
	{
		temp = videos[cd_point[a].end];		// 왼쪽의 값중 가장 오른쪽에 있는 값

		sum_cd[a] -= temp;		// 합계의 값이 감소한다.
		sum_cd[b] += temp;		// 합계의 값이 증가한다.

		cd_point[a].end -= 1;	// 왼쪽 값의 오른쪽 한계가 왼쪽으로 한칸 이동한다.
		cd_point[b].start -= 1;	// 오른쪽 값의 왼쪽 한계가 왼쪽으로 한칸 이동한다.
		return true;
	}
	// 경계의 이동이 오른쪽 방향이라면
	else if (RIGHT == direction)
	{
		temp = videos[cd_point[b].start];		// 오른쪽의 값중 가장 왼쪽에 있는 값

		sum_cd[a] += temp;		// 합계의 값이 증가한다.
		sum_cd[b] -= temp;		// 합계의 값이 감소한다.

		cd_point[a].end += 1;	// 왼쪽 값의 오른쪽 한계가 오른쪽으로 한칸 이동한다.
		cd_point[b].start += 1;	// 오른쪽 값의 왼쪽 한계가 오른쪽으로 한칸 이동한다.
		return true;
	}
	return false;		// 왼쪽도 오른쪽도 아니라면 false 반환

}

int main()
{
	int temp;			// 임시변수
	int n, cd;			// 강의의 수, cd의 수 
	int result = 0;

	cin >> n >> cd;		// 강의의 수와 cd의 수를 입력받는다.

	videos = vector<int>(n, 0);		// video의 갯수만큼 벡터 할당
	sum_cd = vector<int>(cd, 0);	// cd의 갯수만큼 벡터 할당
	cd_point = vector<start_end>(cd, { 0,0 });		// cd의 갯수만큼 벡터 할당

	// 비디오를 입력받는다.
	for (auto& i : videos)	
	{
		cin >> i;
	}

	// cd의 갯수로 분할하여 임시 저장
	temp = n / cd;
	for (int i = 0; i < cd; i++)
	{
		cd_point[i].start = i * temp;			
		cd_point[i].end = (i + 1) * temp - 1;
		//cout << cd_point[i].start << " " << cd_point[i].end << "\n";
	}

	cd_point[cd - 1].end = n - 1;	// 마지막 범위는 배열의 끝까지 가르키도록 함

	// 각 구간의 부분합을 계산
	temp = 0;
	for (auto const& i : cd_point)
	{
		for (int j = i.start; j <= i.end; j++)
		{
			sum_cd[temp] += videos[j];
		}
		temp++;
	}

	bool is_change = false; // 변경 사항이 발생한 적 있는지 확인하는 플래그 변수 
	do
	{
		is_change = false;	// 한바퀴 돌 때마다 초기화 해준다.
		
		// cd의 갯수 -1 만큼씩 반복문을 실행한다.
		for (int i = 0; i < cd - 1; i++)
		{
			// 옮기는 것이 나은지 확인 후 옮긴다.
			// 또한 반환값이 true 라면 옮김이 발생한 것 이므로 is_change에 업데이트 한다.
			is_change = boundary_move(i, i + 1, move_is_lower(i, i + 1)) ? true: is_change;	
		}

	} while (is_change);	// 변경 사항이 발생한 적 없다면 종료한다.

	// 가장 큰 값을 찾는다.
	for (auto& i : sum_cd)
		result = max(result, i);

	for (auto const& i : cd_point)
	{
		temp = 0;
		cout << i.start << " " << i.end << "\n";
		for (int j = i.start; j <= i.end; j++)
		{
			cout << videos[j] << " ";
			temp += videos[j];
		}
		cout << "\nsum : " << temp << "\n\n";
	}

	cout << result;

	return 0;
}