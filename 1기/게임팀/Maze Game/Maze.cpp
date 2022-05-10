#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>



#define MAZE_SIZE 41 // 미로 크기   반드시 홀수
#define MIX_COUNT 3  // 랜덤 횟수   적을수록 미로가 비슷해짐
#define CROSS_PERCENT 35 // 갈림길 확률(분모)   적을수록 갈림길이 많아짐

using namespace std;

enum {
	OUTER_WALL = -1,
	WALL = 0,
	ROAD = 1,
	FLAG = 2,
	EXIT = 5,
	PLAYER = 10
};
enum {
	EAST = 0,
	WEST,
	SOUTH,
	NORTH
};

int maze[MAZE_SIZE][MAZE_SIZE] = { WALL, };


void CreateMaze();
void dfs(int, int);
void ShowMaze();
void PlayMaze();

int main()
{
	srand((unsigned int)time(NULL));

	CreateMaze();
	PlayMaze();
}


void CreateMaze()
{
	maze[MAZE_SIZE - 2][MAZE_SIZE - 1] = EXIT;
	for (int i = 1; i < MAZE_SIZE; i += 2) // 거쳐야 하는 포인트 생성  길생성시 포인트 전부를 지나야됨
	{
		for (int j = 1; j < MAZE_SIZE; j += 2)
		{
			maze[i][j] = FLAG;
		}
	}

	dfs(1, 1);
}


void dfs(int y, int x) // 길뚫는 함수
{
	int d1[4][2] = { {0,1},{0,-1},{1,0},{-1,0} }; //오른쪽, 왼쪽, 아래, 위
	int d2[4][2] = { {0,2},{0,-2},{2,0},{-2,0} };


	int dir[4] = { EAST, WEST, SOUTH, NORTH };  // 가야할 방향 순서
	int i = MIX_COUNT;
	while (i--)  // 길 뚫는 방향을 랜덤으로 하기 위해 무작위로 섞음
	{
		swap(dir[rand() % 4], dir[rand() % 4]);
	}


	for (int j = 0; j < 4; j++)
	{
		int dy1 = d1[dir[j]][1], dx1 = d1[dir[j]][0]; // 움직여야 되는 거리
		int dy2 = d2[dir[j]][1], dx2 = d2[dir[j]][0];



		if (x + dx2 >= MAZE_SIZE || x + dx2 < 0 || y + dy2 >= MAZE_SIZE || y + dy2 < 0)   // 배열 범위 초과시 스킵
			continue;

		if (maze[y + dy2][x + dx2] == FLAG) // 만약 해당 방향에 지나지 않은 포인트가 있을경우
		{

			maze[y + dy1][x + dx1] = ROAD; // 사이에 있는 벽을 뚫음
			maze[y + dy2][x + dx2] = ROAD;	// 포인트를 길로 바꿈 
			dfs(y + dy2, x + dx2);
		}
		else if (maze[y + dy2][x + dx2] == ROAD)
		{
			if (rand() % CROSS_PERCENT == 0) // 확률적으로 원래 있던 길과 연결됨 (갈림길 생성)
			{
				maze[y + dy1][x + dx1] = ROAD;
			}
		}


	}
	return;
}


void ShowMaze()
{
	for (int i = 0; i < MAZE_SIZE; i++)
	{
		for (int j = 0; j < MAZE_SIZE; j++)
		{
			switch (maze[i][j])
			{
			case WALL: cout << "■";
				break;
			case ROAD: cout << "  ";
				break;
			case FLAG: cout << "＠";
				break;
			case PLAYER: cout << "☆";
				break;
			default: cout << "  ";
			}
		}
		cout << endl;
	}
}


void PlayMaze()
{
	int player_x = 1;
	int player_y = 1;
	maze[player_y][player_x] = PLAYER;

	ShowMaze();
	while (1)
	{
		int key = _getch();
		maze[player_y][player_x] = ROAD;
		switch (key)
		{
		case 'a':
		case 75:
			if (maze[player_y][player_x - 1] == ROAD) player_x--;
			break;
		case 'd':
		case 77:
			if (maze[player_y][player_x + 1] == ROAD) player_x++;
			break;
		case 'w':
		case 72:
			if (maze[player_y - 1][player_x] == ROAD) player_y--;
			break;
		case 's':
		case 80:
			if (maze[player_y + 1][player_x] == ROAD) player_y++;
			break;
		default:
			break;
		}
		maze[player_y][player_x] = PLAYER;
		system("cls");
		ShowMaze();
	}
}