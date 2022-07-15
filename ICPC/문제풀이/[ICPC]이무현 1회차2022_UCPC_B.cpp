#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define INT_MAX 2147483647
// B번 문제

// Conter Clockwise
// 두 점에대하여 한 점이 시계방향에 있는지 반시계 방향에 있는지 확인하는 코드
int ccw(pair<int, int> p1, pair<int, int> p2, pair<int, int> p3)
{
	int op = p1.first * p2.second + p2.first * p3.second + p3.first * p1.second;
	op -= (p1.second * p2.first + p2.second * p3.first + p3.second * p1.first);
	if (op > 0)
		return 1;
	else if (op == 0)
		return 0;
	else
		return -1;
}

struct point
{
	int x;
	int y;
};

class slicing
{
public:
	int weight;
	int cross_count;
	int cost;
	point p1;
	point p2;

	int ret_cost()
	{
		return (cross_count + 1) * weight;
	}
	void cal_cost()
	{
		cost = (cross_count + 1) * weight;
	}

	// 객체가 target 과 겹치는지 확인하기 위한 알고리즘
	bool is_cross(slicing target)
	{
		int ta;
		int tb;

		ta = ccw({ p1.x, p1.y }, { p2.x, p2.y }, { target.p1.x, target.p1.y });
		ta *= ccw({ p1.x, p1.y }, { p2.x, p2.y }, { target.p2.x, target.p2.y });

		tb = ccw({ target.p1.x, target.p1.y }, { target.p2.x, target.p2.y }, { p1.x, p1.y });
		tb *= ccw({ target.p1.x, target.p1.y }, { target.p2.x, target.p2.y }, { p2.x, p2.y });

		return (ta < 0) && (tb < 0);
	}
	// 객체의 내용을 출력하는 메소드
	void prt(void) {
		cout << p1.x << " ";
		cout << p1.y << " ";
		cout << p2.x << " ";
		cout << p2.y << " ";
		cout << weight << " ";
		if (cross_count)
			cout << cross_count << " ";
		if (cost)
			cout << cost << " ";
		cout << "\n";
	}
};

// 오름차순 정렬
// cross_count 기준으로 정렬
int slicing_sort_by_cross_count(slicing a, slicing b)
{
	return a.cross_count > b.cross_count;
}
// weight 기준으로 정렬
int slicing_sort_by_weight(slicing a, slicing b)
{
	return a.weight < b.weight;
}

// 연산에 필요한 자료들을 선언
vector <slicing> slices;
vector <vector<bool>> cross_map;
map<int, slicing*> slicing_map;	// map이 아닌 vector로 연산해도 됨

int main(void)
{
	// 탐색 순서
	// cross가 가장 작은 순
	// weight가 가장 작은 순
	// 
	// 현 상태에서 cost가 가장 작은 순

	int result = 0;	// 결과를 저장할 변수
	int n;			// 검술 개수를 받을 변수
	cin >> n;

	slices = vector<slicing>(n);	// 검술 횟수 초기화
	cross_map = vector < vector < bool >>(n, vector<bool>(n, false)); // 겹치는 검술정보를 저장할 map

	// 검술의 내용을 입력 받음
	for (size_t i = 0; i < n; i++)
	{
		cin >> slices[i].p1.x >> slices[i].p1.y;
		cin >> slices[i].p2.x >> slices[i].p2.y;
		cin >> slices[i].weight;
		slicing_map.insert({ i,&slices[i] });
		// 다음과 같이 받으므로서 vector를 정렬하더라도
		// map에 인덱스 정보가 남아있어 참조 속도를 높임
		// 포인터를 저장하는 배열을 선언하여도 동일하게 작동됨(그냥 익숙해져보려고 썼다.)
	}

	// 겹치는 검술 정보를 저장
	// 앞에서부터 겹치는 부분만 연산을 진행함
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = i + 1; j < n; j++)
		{
			// 두 검술이 겹친다면
			// 이 때 두 검술이 같은 검술일 가능성은 없음
			if (slices[i].is_cross(slices[j]))
			{
				slices[i].cross_count++;
				slices[j].cross_count++;
				cross_map[i][j] = true;
				cross_map[j][i] = true;
			}
		}
		slices[i].cal_cost();
	}

	// 검술을 cross_count 기준으로 오름차순 정렬
	sort(slices.begin(), slices.end(), slicing_sort_by_cross_count);

	// 검술이 겹치지 않는 검술 우선 실행
	int temp = 0;
	for (temp = 0; temp < n; temp++)
	{
		if (slices[temp].cross_count != 0)
			break;
		result += slices[temp].cost;
		slices[temp].cost = -1;
	}
	// 이 때 temp 는 검술이 겹치기 시작한 최조 인덱스 번호를 가지고 있다.

	// 겹치는게 있는 검술 중 cost가 가장 작은 검술을 실행한다.
	do
	{
		int temp_cost = INT_MAX;
		int temp_i = -1;
		for (size_t i = 0; i < n; i++)
		{
			slicing* temp_slicing = slicing_map[i];
			if (temp_slicing->cost == -1)
				continue;
			if (temp_slicing->cost < temp_cost)
			{
				temp_i = i;
				temp_cost = temp_slicing->cost;
			}
		}

		// 다음 조건문이 충족한다면 더이상 찾을 값이 없다.
		if (temp_i <= -1)
			break;

		// 찾은 검술을 cross_map 에서 제거한다.
		for (size_t i = 0; i < n; i++)
		{
			if (cross_map[temp_i][i])
			{
				// cross_count 를 1 낮추고 재계산함
				slicing_map[i]->cross_count--;
				slicing_map[i]->cal_cost();

				cross_map[temp_i][i] = false;
				cross_map[i][temp_i] = false;
			}
		}

		// -1이 아닌 최소값이 있다면 그 값을 연산한다.
		result += slicing_map[temp_i]->cost;
		slicing_map[temp_i]->cost = -1;

	} while (true);

	cout << result;
}
