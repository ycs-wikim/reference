// https://www.acmicpc.net/problem/22876
// 츠바메가에시
// n        n개의 뽑기를 받는다.
// x y v    x, y 좌표 점수순으로 입력이 들어온다
// 
// x score 맵, y score 맵을 만든다.
// 가장 높은 값을 찾아 0으로 만든다.
//      이때 사용한 제비도 0으로 만든다
//      해당 제비가 포함되어있던 score 맵에서 해당 제비의 점수를 뺀다.
// 3회 반복한다.
//

#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct Point
{
	int x;
	int y;
};

struct lot
{
	int other;
	int score;
	Point point;
};

// 제비들의 위치를 저장
vector<lot> lots;

// x좌표를 key로 y좌표를 저장하는 맵
map<int, vector<lot *> * > xmap;
// x좌표에 대한 점수를 저장
map<int, int> xscore;

// y좌표를 key로 x좌표를 저장하는 맵
map<int, vector<lot *> * > ymap;
// y좌표에 대한 점수를 저장
map<int, int> yscore;

map<int, int >temp_xscore;
map<int, int >temp_yscore;

// 해당 점수 배열에서 제비들을 지운다.
// x , y 중 1 이상인 값이 검격의 좌표이다.
void RemoveLot(int x, int y, map<int, int > * temp_xscore, map<int, int > * temp_yscore)
{
	vector<lot*> * lot_map;
	map<int, int >* target_score;		// score map 임시 저장
	int target = -1;
	
	// x 좌표에 대하여 검격을 날림 (세로 검격)
	// y score 에 영향을 줌
	if (x >= 0)
	{
		target = 0;
		lot_map = ymap[target];
		target_score = temp_yscore;
	}
	// y 좌표에 대하여 검격을 날림 (가로 검격)
	// x score 에 영향을 줌
	else if (y >= 0)
	{
		target = 1;
		lot_map = xmap[target];
		target_score = temp_xscore;
	}

	// 아무 값도 들어오지 않으면 종료
	if (target == -1)
		return;

	for (const auto i : *lot_map)
	{
		// target이 0 이라면 x 검격		1이라면 y 검격
		int po = target == 1 ? i->point.y : i->point.x;
		// 값을 바꿈
		(*target_score)[target] -= po;
	}
}


// 가장 큰 값을 값 세개를 차례로 찾는다.
long long int solve1()
{

}

// 4초의 장점을 이용해 전체 탐색을 진행한다.
long long int solve2()
{

}

// 하나의 검격은 다른 검격의 한 값에만 영향을 준다.
// 이를 이용해 검격 관계표를 생성하여 연산한다.

long long int solve3()
{

}

// 한 방향에서 3개	2가지 경우	(해당 경우는 제비의 제거가 영향을 끼지치 않음)
// 한 방향에서 2개 다른방향에서 1개 의 검격을 할 수 있다.	2가지 경우
//			(해당 경우는 제비의 제거가 다른 검격에 영향을 끼친다. 
//							-> 한 방향에서 가장 큰 두개를 선택 하고 관련 제비를 제거 후 가장 큰 검격을 뽑는다.)
// 모든 경우의 수는 4개 이므로 이 경우를 모두 구해서 가장 큰 값을 가져온다.
long long int solve4()
{

}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;
	cin >> n;

	// 초기화
	lots.assign(n, lot{0,0,0,0});

	for (size_t i = 0; i < n; i++)
	{
		lot * tlot = &lots[i];
		// 좌표, 점수 입력
		cin >> tlot->point.x >> tlot->point.y >> tlot->score;
		
		// 해당 키가 존재하지 않으므로 새로 생성
		if (xmap.find(tlot->point.x) == xmap.end())
		{
			// 맵에 새로운 백터를 만듦
			xmap.insert({ tlot->point.x, new vector<lot*> } );

			// xscore 에 새로운 0 값 대입
			xscore.insert({ tlot->point.x , 0 });
		}

		// xmap 에 lot에 대한 포인터값 저장
		xmap[tlot->point.x]->push_back(tlot);
		
		// xscore 값 누산
		xscore[tlot->point.x] += lots[i].score;


		// 해당 키가 존재하지 않으므로 새로 생성
		if (ymap.find(tlot->point.y) == ymap.end())
		{
			// 맵에 새로운 백터를 만듦
			ymap.insert({ tlot->point.y, new vector<lot*> });
		}

		// ymap 에 lot에 대한 포인터값 저장
		xmap[tlot->point.y]->push_back(tlot);

		// yscore 값 누산
		yscore[tlot->point.y] += lots[i].score;
	}

	cout << solve1();
	cout << solve2();
}

