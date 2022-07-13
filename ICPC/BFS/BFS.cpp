#include <iostream>
#include <queue>

using namespace std;

vector<int> visted(7);
vector<int> nodes[7];

void init()
{
	// visted -1로 초기화
	for (int i = 0; i < 7; i++)
	{
		visted[i] = -1;
	}

	// 인접한 그래드 초기화
	// A:0 B:1 C:2 D:3 E:4 F:5 G:6
	nodes[0].push_back(1);
	nodes[0].push_back(2);

	nodes[1].push_back(0);
	nodes[1].push_back(3);

	nodes[2].push_back(0);
	nodes[2].push_back(4);

	nodes[3].push_back(1);
	nodes[3].push_back(4);
	nodes[3].push_back(5);

	nodes[4].push_back(2);
	nodes[4].push_back(3);
	nodes[4].push_back(6);

	nodes[5].push_back(3);
	nodes[5].push_back(6);

	nodes[6].push_back(4);
	nodes[6].push_back(5);
}

void bfs(int start, int end)
{
	queue<int> QUEUE;

	// 시작 위치 
	QUEUE.push(start);
	visted[start] = 0;

	while (QUEUE.empty() == false)
	{
		// 현재 노드
		int currentNode = QUEUE.front();
		QUEUE.pop();

		// 현재 노드가 목적지면..
		if (currentNode == end)
		{
			cout << visted[end];
		}

		for (int index = 0; index < nodes[currentNode].size(); index++)
		{
			// 인접한 노드
			int nextNode = nodes[currentNode][index];

			// 방문한적이 있다면 넘어감
			if (visted[nextNode] != -1)	continue;

			// 방문한적이 없다면 QUEUE에 인접한 노드 PUSH
			QUEUE.push(nextNode);

			// 방문체크 인접한노드 = 현재노드 + 1
			visted[nextNode] = visted[currentNode] + 1;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	// 초기 세팅
	init();

	// bfs 탐색
	bfs(0, 6);

	return 0;
}