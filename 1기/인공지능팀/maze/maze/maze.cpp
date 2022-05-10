// maze.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
#include <cstring>



#define MAZE_SIZE 41 // 미로 크기   반드시 홀수
#define MIX_COUNT 3  // 랜덤 횟수   적을수록 미로가 비슷해짐
#define CROSS_PERCENT 35 // 갈림길 확률(분모)   적을수록 갈림길이 많아짐
#define MAX_HEALTH 3 // 최대 생명력

using namespace std;

// 생명력 변수, 점수 변수 info()에서 쓰임
int health = 0, score = 0;
//폭탄 개수
int bomb_cnt = 0;
//player 좌표
int player_x = 1;
int player_y = 1;


int enemys[MAZE_SIZE][2];

enum {
	OUTER_WALL = -1,
	WALL = 0,
	ROAD = 1,
	FLAG = 2,
	EXIT = 5,
	PLAYER = 10,
	ENEMY = 15,
	BOMB = 20,
	BOMB_EFFECT = 30,
	ENEMY_EFFECT = 31,
};
enum {
	EAST = 0,
	WEST,
	SOUTH,
	NORTH
};

int maze[MAZE_SIZE][MAZE_SIZE];

void CreateMaze();
void dfs(int, int);
void ShowMaze();
void PlayMaze();
void bomb_use();
void info1(int num);
void info2();
void info3();
void info4();
void gotoyx_obj(int y, int x, int Object);
void gotoyx(int y, int x);
void UpdateInfo();

int main()
{

	srand((unsigned int)time(NULL));

	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo); //커서 숨기기

	char command[100];
	sprintf_s(command, "mode con: lines=%d cols=%d", MAZE_SIZE + 15, MAZE_SIZE * 2 + 50);//콘솔 크기 변경
	system(command);

	system("title Maze");	//콘솔 타이틀 지정
	CreateMaze();
	PlayMaze();

}


void CreateMaze()
{

	health = MAX_HEALTH;
	score = 500 + MAZE_SIZE * 35;
	bomb_cnt = 0;

	player_x = 1;
	player_y = 1;
	memset(maze, WALL, sizeof(maze)); // 미로 전체를 벽으로 초기화

	for (int i = 0; i < MAZE_SIZE; i++)	//외벽을 뚫을수 없는 벽으로 설정
	{
		maze[0][i] = OUTER_WALL;
		maze[MAZE_SIZE - 1][i] = OUTER_WALL;
		maze[i][0] = OUTER_WALL;
		maze[i][MAZE_SIZE - 1] = OUTER_WALL;

	}

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
	for (int i = 0; i < MAZE_SIZE + 5; i++)
	{
		if (i < MAZE_SIZE)
		{
			for (int j = 0; j < MAZE_SIZE; j++)
			{
				switch (maze[i][j])
				{
				case OUTER_WALL:
				case WALL: cout << "■";
					break;
				case ROAD: cout << "  ";
					break;
				case FLAG: cout << "＠";
					break;
				case PLAYER: cout << "☆";
					break;
				case ENEMY: cout << "△";
					break;
				case BOMB: cout << "δ";
					break;
				default: cout << "  ";
				}
			}
		}
		info1(i);
		cout << endl;
	}
}


// 인게임 도움말 출력
void info1(int num) {

	int printStartNum;
	if (MAZE_SIZE >= 12)
		printStartNum = MAZE_SIZE / 2 - 12 / 2;  // 미로 가운데에 출력
	else
		printStartNum = 0;	//미로가 작으면 바로 출력

	if (num >= MAZE_SIZE)	//	info1 박스 보다 미로가 작을경우 여백 생성
		for (int i = 0; i < MAZE_SIZE; i++) cout << "  ";

	switch (num - printStartNum)
	{
	case 0:
		printf("┌---------------┐  ┌-------------------┐");
		break;
	case 1:
		printf("│ 생명력 :");
		for (int i = 0; i < health; i++) {
			printf("♥");
		}
		for (int i = 0; i < MAX_HEALTH - health; i++) {
			printf("♡");
		}
		printf("│  ");

		printf("│  폭탄 개수 : % d   │", bomb_cnt);
		break;
	case 2:
		printf("│ 점  수 : %4d │  │  1. e키 누르기    │", score);
		break;
	case 3:
		printf("└---------------┘  │  2. w,s,a,d       │");
		break;
	case 4:
		printf("                   └-------------------┘");
		break;
	case 5:
		printf("┌---------------┐");
		break;
	case 6:
		printf("│ 상 :    w     │");
		break;
	case 7:
		printf("│ 하 :    s     │");
		break;
	case 8:
		printf("│ 좌 :    a     │");
		break;
	case 9:
		printf("│ 우 :    d     │");
		break;
	case 10:
		printf("│ R  :  재시작  │");
		break;
	case 11:
		printf("└---------------┘");
		break;
	default:
		break;
	}

}

void info2() { // 게임 클리어시 호출 (점수 = 점수 + (생명력 *50)로 계산 )
	printf("\n\n\n\n");
	printf("\t\t\t\t┌------------------------------------------------┐\n");
	printf("\t\t\t\t│   G  A  M  E                 C  L  E  A  R     │\n");
	printf("\t\t\t\t│                                                │\n");
	printf("\t\t\t\t│  점  수 : %4d [%4d + 생명력 보너스 %3d * 50] │\n", score + (health * 50), score, health);
	printf("\t\t\t\t└------------------------------------------------┘\n");
	printf("\n\n\n\n\n");
	info4();
}

void info3() { // 게임 오버시 호출 (여기는 그냥 점수만 출력)
	printf("\n\n\n\n");
	printf("\t\t\t\t┌----------------------------------------------┐\n");
	printf("\t\t\t\t│   G  A  M  E                    O  V  E  R   │\n");
	printf("\t\t\t\t│                                              │\n");
	printf("\t\t\t\t│   점     수 :                     %4d       │\n", score);
	printf("\t\t\t\t└----------------------------------------------┘\n");
	printf("\n\n\n\n\n");
	info4();
}

void info4() { //게임 클리어 및 오버시 재시작 문구 출력

	printf("\t\t\t\t┌----------------------------------------------┐\n");
	printf("\t\t\t\t│          다시 하시겠습니까?	( Y / N )      │\n");
	printf("\t\t\t\t└----------------------------------------------┘\n");
	printf("\n\n\n\n");

	bool check = false;
	while (!check)
	{
		int key = _getch();
		switch (key)
		{
		case 'r':
		case 'y':				// y입력시 다시시작
			system("cls");
			CreateMaze();
			PlayMaze();
			check = true;
			break;
		case 'n':
			return;				// n입력시 리턴
		default:
			break;				// 그 외는 입력을 안받고 반복
		}
	}
}


//폭탄 사용해 벽 뚫기
void bomb_use()
{
	int bomb_x = player_x;
	int bomb_y = player_y;

	int key2 = _getch();
	switch (key2)
	{
	case 'a':	bomb_x--;
		break;
	case 'd':	bomb_x++;
		break;
	case 'w':	bomb_y--;
		break;
	case 's':	bomb_y++;
		break;
	default:
		return;
	}
	bomb_cnt--;
	UpdateInfo();
	int temp = maze[bomb_y][bomb_x];

	gotoyx_obj(bomb_y, bomb_x, BOMB_EFFECT);
	Sleep(300);	//0.3초동안 보여줌

	if (temp == WALL) {// 벽이라면
		gotoyx_obj(bomb_y, bomb_x, ROAD);
	}
	else gotoyx_obj(bomb_y, bomb_x, temp);	//아니면 되돌림

}

// 게임 주 연산
void PlayMaze()
{

	maze[player_y][player_x] = PLAYER;

	// 적 초기 생성
	int enemy1_x;
	int	enemy1_y;

	int ecnt = 0;
	while (ecnt < MAZE_SIZE / 3)
	{
		while (1) {
			enemy1_x = rand() % (MAZE_SIZE - 2);
			enemy1_y = rand() % (MAZE_SIZE - 2);
			if (maze[enemy1_y][enemy1_x] == ROAD) {
				maze[enemy1_y][enemy1_x] = ENEMY;
				enemys[ecnt][0] = enemy1_x;
				enemys[ecnt][1] = enemy1_y;
				ecnt++;
				break;
			}
		}
	}

	//폭탄 생성
	int bomb_x;
	int bomb_y;
	int cnt = 0;
	while (cnt < 5) {

		bomb_x = rand() % MAZE_SIZE - 2;
		bomb_y = rand() % MAZE_SIZE - 2;

		if (maze[bomb_y][bomb_x] == ROAD) {
			maze[bomb_y][bomb_x] = BOMB;
			cnt++;
		}
	}


	ShowMaze();


	// 플레이어 키 입력
	while (1)
	{
		score -= 5;
		int key = _getch();
		int goto_x = player_x;
		int goto_y = player_y;
		switch (key)
		{
		case 'a':
		case VK_LEFT:
			goto_x--;
			break;
		case 'd':
		case VK_RIGHT:
			goto_x++;
			break;
		case 'w':
		case VK_UP:
			goto_y--;
			break;
		case 's':
		case VK_DOWN:
			goto_y++;
			break;
		case 'r': //리셋
			system("cls");
			CreateMaze();
			PlayMaze();
			break;

		case 'e'://폭탄 사용
			if (bomb_cnt > 0)  bomb_use();
			break;
		default:
			continue;
		}

		//플레이어 이동
		if (maze[goto_y][goto_x] > WALL)
		{
			// 움직일곳이 폭탄이면 폭탄개수++
			if (maze[goto_y][goto_x] == BOMB) bomb_cnt++;

			gotoyx_obj(player_y, player_x, ROAD);

			player_x = goto_x;
			player_y = goto_y;
			gotoyx_obj(player_y, player_x, PLAYER);

		}

		// 적 이동
		for (int i = 0; i < (MAZE_SIZE / 3); i++)
		{
			int x = enemys[i][0];
			int y = enemys[i][1];
			int enemy_move = rand() % 4;

			// 플레이어와 적이 겹쳐있지 않을때만 적이 있던곳을 비움
			if (!(y == player_y && x == player_x))
				gotoyx_obj(y, x, ROAD);

			// 랜덤으로 뽑힌 적의 방향을 표현
			switch (enemy_move)
			{
			case 0: // 왼쪽
				if (maze[y][x - 1] > WALL \
					&& maze[y][x - 1] != ENEMY)
					x--;
				break;
			case 1: // 오른쪽
				if (maze[y][x + 1] > WALL \
					&& maze[y][x + 1] != EXIT  \
					&& maze[y][x + 1] != ENEMY)
					x++;
				break;
			case 2:// 위
				if (maze[y - 1][x] > WALL \
					&& maze[y - 1][x] != ENEMY)
					y--;
				break;
			case 3:// 아래
				if (maze[y + 1][x] > WALL \
					&& maze[y + 1][x] != ENEMY)
					y++;
				break;
			default:
				break;

			}
			gotoyx_obj(y, x, ENEMY);

			enemys[i][0] = x;
			enemys[i][1] = y;

		}


		// 적과 플레이어가 겹쳐졌을 때
		for (int i = 0; i < (MAZE_SIZE / 3); i++)
		{
			if (enemys[i][1] == player_y && enemys[i][0] == player_x)
			{
				health--;
				score -= 50;
				gotoyx_obj(player_y, player_x, ENEMY_EFFECT);
				UpdateInfo();
				// 생명력이 0이하가 돼서 죽었을 때
				if (health <= 0) {
					system("cls");
					info3();
					// 게임 종료하려고 리턴넣음
					return (void)0;
				}
			}
		}
		// 골인지점 도착시
		if (player_y == MAZE_SIZE - 2 && player_x == MAZE_SIZE - 1)
		{
			system("cls");
			info2();
			// 게임 종료하려고 리턴넣음
			return (void)0;
		}
		UpdateInfo();
	}
}

// 커서 움직이는 함수			전체를 다시 출력하지 않고, 변경이 있는곳만 바꾸기 위함
void gotoyx_obj(int y, int x, int Object)
{

	COORD pos = { short(x * 2) , short(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	switch (Object)
	{
	case OUTER_WALL:
	case WALL: cout << "■";
		break;
	case ROAD: cout << "  ";
		break;
	case FLAG: cout << "＠";
		break;
	case PLAYER: cout << "☆";
		break;
	case ENEMY: cout << "△";
		break;
	case BOMB: cout << "δ";
		break;
	case BOMB_EFFECT:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "◈";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	case ENEMY_EFFECT:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		cout << "★";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		break;
	default: cout << "  ";
	}
	maze[y][x] = Object;
}

void gotoyx(int y, int x)
{
	COORD pos = { short(x * 2) ,short(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void UpdateInfo()
{

	int Info_y;	// 위젯 위치
	if (MAZE_SIZE >= 12)
		Info_y = MAZE_SIZE / 2 - 12 / 2;
	else
		Info_y = 0;

	gotoyx(Info_y + 1, MAZE_SIZE);
	printf("│ 생명력 :");
	for (int i = 0; i < health; i++) {
		printf("♥");
	}
	for (int i = 0; i < MAX_HEALTH - health; i++) {
		printf("♡");
	}
	printf("│  ");
	printf("│  폭탄 개수 : % d   │", bomb_cnt);

	gotoyx(Info_y + 2, MAZE_SIZE);
	printf("│ 점  수 : %4d │  │  1. e키 누르기    │", score);

}

