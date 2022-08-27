// 가주아 (해결)
// https://www.acmicpc.net/problem/16464
// 
// 1 ~ K-1 까지의 수가 적혀있는 카드에서 N개를 연속으로 가져왔을 때 합이 K가 나올 수 있는지 확인하라. 
// 연속된 숫자의 합으로 K를 만들 수 있는지 확인
// 
// N : 게임 횟수
// K : 만들어야하는 수
// 

#include<iostream>
#include<vector>

using namespace std;


bool is_possible(int n)
{

	while (n != 1)
	{
		if (n % 2 == 1)
			return 1;
		n /= 2;
	}
	
	return false;
}


void solve()
{
	int n;
	cin >> n;

	if (is_possible(n))
		cout << "Gazua" << "\n";
	else
		cout << "GoHanGang" << "\n";
}


int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int n;

	cin >> n;

	// n번 반복함
	for (size_t i = 0; i < n; i++)
	{
		solve();
	}
	return 0;
}
