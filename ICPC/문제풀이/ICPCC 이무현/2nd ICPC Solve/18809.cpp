// 18809 Gaaaaaaaaaarden
// https://www.acmicpc.net/problem/18809
// 배양액을 뿌릴 수 있는 위치는 10군데 이하이다.
// 피우는 꽃의 최대 개수를 반환
// 시간제한 2초

#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>

#define NONE 0
#define LIVER -1
#define UNABLEPLACE -2
#define ABLEPLACE -3
#define GREEN 1
#define RED 2
#define FLOWER 3

using namespace std;

// 위치를 저장할 수 있는 구조체 생성
struct point {
	int x;
	int y;
};

// 
//			 좌, 상, 우, 하
int dx[4] = { -1, 0 ,1 , 0 };
int dy[4] = { 0 ,-1 ,0 , 1 };

// 자료형 선언 
vector<vector<int>> state_map;	// 현재 상황을 저장할 수 있는 맵 선언 (원본 저장)
vector<vector<int>> temp_map;	// 현재 상황을 저장할 수 있는 맵 선언 (변형본 저장)
queue <point> red;				// red 용액의 위치를 저장하는 queue
queue <point> green;			// green 용액의 위치를 저장하는 queue
vector<point> ablePlace;	// 용액을 놓을 수 있는 땅의 좌표와 용액이 퍼지는 형태를 저장

queue <pair<int, point>> bfs_queue;

// 퍼질 수 있는지 확인
bool is_spread(point spot)
{
	int temp;
	do
	{
		if (spot.x < 0)
			break;
		if (spot.x >= temp_map[0].size())
			break;
		if (spot.y < 0)
			break;
		if (spot.y >= temp_map.size())
			break;

		temp = temp_map[spot.y][spot.x];

		if (temp == LIVER)
			break;
		if (temp == FLOWER)
			break;
		// 이미 RED나 GREEN이 있다면 전 회차에서 뿌려진 것 이기 때문에 놓지 못함
		if (temp == RED)
			break;
		if (temp == GREEN)
			break;

		return true;
	} while (true);
	return false;
}

// bfs_queue의 내용을 불러와 모두 처리 후, bfs_queue의 내용이 없으면 종료

int bfs()
{
	queue <pair<int, point>> temp_queue;	
	pair<int, point> temp_point;
	int flower = 0;

	// 액체를 배치한다.
	// flower 가 생성됐는지 확인한다.
	while (!bfs_queue.empty())
	{
		temp_point = bfs_queue.front();
		bfs_queue.pop();
		int& temp = temp_map[temp_point.second.y][temp_point.second.x];

		// 용액이 퍼졌는데 합이 3이면 꽃이 된다.
		if (temp + temp_point.first == FLOWER)
		{
			temp = FLOWER;
			flower++;
			continue;
		}
		// ABLEPLACE 또는 UNABLEPLACE 가 아니라면 이미 다른용액이 있는 것
		else if(temp != ABLEPLACE && temp != UNABLEPLACE)
			continue;

		// 꽃이 되지 않고, 이미 다른 용액이 자리를 잡은 것이 아니라면
		// 자신의 용액을 땅에 배치한다.
		temp = temp_point.first;

		temp_queue.push(temp_point);
	}

	// 배치가 끝난 후 액체의 퍼짐을 확인한다.
	while (!temp_queue.empty())
	{
		temp_point = temp_queue.front();
		temp_queue.pop();
		int x = temp_point.second.x;
		int y = temp_point.second.y;

		// 해당 공간에 꽃이 있다면 더이상 퍼질 수 없다.
		if (temp_map[y][x] == FLOWER)
			continue;

		for (int i = 0; i < 4; i++)
		{
			// 퍼질 수 있다면 
			if (is_spread({ x + dx[i] , y + dy[i] }))
			{
				bfs_queue.push({ temp_point.first, {x + dx[i] , y + dy[i]} });
			}
		}
	}

	// 액체의 퍼짐이 더이상 일어나지 않는 경우
	if (bfs_queue.empty())
		return flower;

	// 액체의 퍼짐이 더 일어나는 경우
	return flower + bfs();
}


int solve(int r, int g)
{
	int empty = ablePlace.size() - (r + g);		// 빈공간의 수를 저장
	int result = 0;
	vector<int> v;

	// 중복조합 코드
	// next_permutation 다음 순열을 구하는 메소드
	// 오름차순 정렬이 되어있어야 한다.
	for (size_t i = 0; i < empty; i++)
		v.push_back(NONE);
	for (size_t i = 0; i < g; i++)
		v.push_back(GREEN);
	for (size_t i = 0; i < r; i++)
		v.push_back(RED);
	sort(v.begin(),v.end());

	do
	{
		int temp = 0;
		while (!bfs_queue.empty()) bfs_queue.pop();

		temp_map = state_map;
		
		for(int i = 0 ; i < v.size() ; i++)
		{
			if (v[i] == RED)
				bfs_queue.push({ RED,ablePlace[i] });
			if (v[i] == GREEN)
				bfs_queue.push({ GREEN,ablePlace[i] });
		}
		result = max(bfs(), result); // 둘중 더 큰값을 저장
	} while (next_permutation(v.begin(), v.end())); 
	
	return result;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);

	int n, m;
	int r, g;
	int result = 0;

	// n * m 크기
	// 행, 열    y, x
	cin >> n >> m;
	state_map = vector<vector<int>>(n, vector<int>(m, 0));

	// 초록색, 빨간색 배양액 개수
	cin >> r >> g;

	// 땅의 상태 입력
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			cin >> state_map[y][x];
			state_map[y][x] = (state_map[y][x] + 1) * -1;
			
			// 배양액을 뿌릴 수 있는 땅인지 확인
			if (state_map[y][x] == ABLEPLACE)	
				ablePlace.push_back(point{ x ,y });
		}
	}

	cout << solve(r, g) << endl;
}

