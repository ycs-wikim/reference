#include <iostream>
#include <queue>
#include<stack>
#include<vector>
#include<algorithm>

using namespace std;

// 정점에 대한 정보와 비용이 담긴 그래프
vector<int> tree[100001];

// 정점 방문체크용 배열
vector<int> visted(10001);

void DFS(int current_node)
{
    // 초기 위치 세팅
    visted[current_node] = true;

    // 현재 정점의 인접한 정점 push
    for (int idx = 0; idx < tree[current_node].size(); idx++)
    {
        int next = tree[current_node][idx];

        if (visted[next] == true) continue;

        DFS(next);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // 정점 개수와 간선 개수 
    int V, E;
    cin >> V >> E;

    // 초기 세팅
    for (int idx = 1; idx <= E; idx++)
    {
        char start, end;   
        cin >> start >> end;

        start -= 64;
        end -= 64;
        tree[start].push_back(end);
        tree[end].push_back(start);
    }

    // DFS(Depth First Search)
    DFS(1);

    cout << "탐색 종료";

    return 0;
}