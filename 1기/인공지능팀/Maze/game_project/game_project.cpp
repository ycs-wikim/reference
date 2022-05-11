#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <queue>
#include <time.h>

#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 
#define MAGIC_KEY 224

#define Player "♣"
#define Enemy "●"
#define Goal "★"
#define Wall "■"
#define Road "□"

using namespace std;

//함수
void text_color(int foreground, int backgrond);
void pos_random(string random);
void create_maze();
void maze_dfs(int curr_x, int curr_y);
void maze_set();
void print_maze();
void playing_maze();
void moving_palyer();
int check_block(int dir);
void moving_enemy();
int enemy_bfs();
void gotoxy(int x, int y);
void SetConsoleView();
void DrawRules();
void DrawReadyGame();
void Rules();
void DrawUserCursor(int& y);
void GameStart();
void Initial_set();

int dx[4] = { 2,0,-2,0 };
int dy[4] = { 0,2,0,-2 };

int crush_dx[4] = { 1,0,-1,0 };
int crush_dy[4] = { 0,1,0,-1 };

int length, width; // 세로,가로
bool end_flag = false;

int bfs_p, bfs_e; // 플레이어와 적의 골인지점 최소 길이

enum MENU {
	GAMESTART = 0,
	RULES,
	QUIT
};

MENU ReadyGame();

typedef struct Player_pos { // 플레이어 위치
	int curr_x = 1, curr_y = 1; // 플레이어 현재 마우스 위치
	int maze_x = 1, maze_y = 1; // 플레이어 현재 미로 위에서 위치
}PP;
PP P;

typedef struct Enemy_pos { // 적 위치
	int curr_x = 0, curr_y = 0; // 적 현재 마우스 위치
	int maze_x = 0, maze_y = 0; // 적 현재 미로 위에서 위치
}EP;
EP E;

vector<vector<string>> maze; //미로
vector<vector<int>> visted; //방문 체크
queue < pair<int, int>> enemy_q;

enum KEYBOARD { UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80, ESC = 27, ENTER = 13 }; // 키 입력


int main() {

	SetConsoleView();
	while (true)
	{
		Initial_set();

		switch (ReadyGame())
		{
		case GAMESTART:
			system("cls");
			GameStart();
			break;

		case RULES:
			system("cls");
			Rules();
			break;

		case QUIT:
			return 0;
		}
	}
	return 0;
}

//초기 세팅
void Initial_set() {
	end_flag = false;
	P.curr_x = 1;
	P.curr_y = 1;
	P.maze_x = 1;
	P.maze_y = 1;
	bfs_e = 0;
	bfs_p = 0;
}

// 마우스 좌표 이동
void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 콘솔 크기, 콘솔 제목
void SetConsoleView() {

	system("mode con:cols=65 lines=31");
	system("title 미로찾기 게임");
}

// 규칙
void DrawRules() {

	system("cls");
	gotoxy(4, 3);
	cout << "적을 피하여 목표(";
	text_color(YELLOW, BLACK);
	cout << Goal;
	text_color(WHITE, BLACK);
	cout << ")까지 도착하세요.";
	gotoxy(4, 4);
	cout << "단,내(";

	text_color(LIGHTGREEN, BLACK);
	cout << "♣";

	text_color(WHITE, BLACK);
	cout << ")가 움직일시 적(";

	text_color(LIGHTRED, BLACK);
	cout << "●";

	text_color(WHITE, BLACK);
	cout << ")도 따라옵니다.";
	gotoxy(4, 5);
	cout << "조작키는 ";
	text_color(YELLOW, BLACK);
	cout << "→ ← ↑↓ ";

	text_color(WHITE, BLACK);
	cout << "이며, ";
	gotoxy(4, 6);
	text_color(YELLOW, BLACK);
	cout << "ESC ";

	text_color(WHITE, BLACK);
	cout << "를 누르면 메인 화면으로 돌아옵니다.";
	gotoxy(14, 10);
	text_color(YELLOW, BLACK);
	cout << "Press any key\n";
}

// 메인 화면
void DrawReadyGame() {
	system("cls");
	text_color(WHITE, WHITE);
	gotoxy(9, 6);
	cout << "■■■■■■■■■■■■■■■■";

	gotoxy(9, 7);
	cout << "■";
	text_color(WHITE, BLACK);
	cout << "       미로찾기 게임        ";
	text_color(WHITE, WHITE);
	cout << "■";
	gotoxy(9, 8);
	cout << "■■■■■■■■■■■■■■■■";
	text_color(WHITE, BLACK);
	gotoxy(14, 10);
	text_color(YELLOW, BLACK);
	cout << "Press ";
	cout<<"Enter\n";
	text_color(WHITE, BLACK);
	gotoxy(14, 12);
	cout << "GameStart";
	gotoxy(14, 13);
	cout << "Rules";
	gotoxy(14, 14);
	cout << "Quit" << endl;
}

// 규칙
void Rules() {
	DrawRules();
	system("pause>null");
}

// 커서 움직이는것 출력
void DrawUserCursor(int& y) {
	if (y <= 0) {
		y = 0;
	}
	else if (y >= 2) {
		y = 2;
	}

	gotoxy(12, 12 + y);
	cout << ">";
}

// 메인 화면 처리
MENU ReadyGame() {
	int y = 0;
	int input = 0;
	while (true)
	{
		DrawReadyGame();
		DrawUserCursor(y);
		input = _getch();
		//→←↑↓
		if (input == MAGIC_KEY)
		{
			switch (_getch())
			{
			case UP:
				--y;
				break;
			case DOWN:
				++y;
				break;
			}
		}
		else if (input == ENTER)
		{
			switch (y)
			{
			case 0:
				return GAMESTART;
			case 1:
				return RULES;

			case 2:
				return QUIT;
			}
		}
	}
}

// 게임 시작
void GameStart() {

	srand((unsigned int)time(NULL)); // 랜덤 함수
	
	//미로 크기 설정
	length = 14;
	width = 15;

	system("cls");

	length = 2 * length + 1;
	width = 2 * width + 1;
	maze.assign(length, vector<string>(width));
	visted.assign(length, vector<int>(width));

	create_maze(); //미로 만들기

	maze_set(); //미로 설정

	print_maze(); //미로 출력하기

	gotoxy(1, 1);

	playing_maze(); //미로 플레이하기
}

// 텍스트 칼러 설정하기
void text_color(int foreground, int backgrond) {
	int color = foreground + backgrond * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 랜덤으로 위치 배치하기
void pos_random(string random) {

	int rand_length, rand_width;

	//랜덤으로 한칸 길 생성
	while(1) {
		rand_length = rand() % (length - 1);
		rand_width = rand() % (width - 1);

		if (rand_length == 0 || rand_width == 0) continue;
		if (maze[rand_length][rand_width] == Wall) {
			
			if (maze[rand_length + 1][rand_width] == Wall && maze[rand_length - 1][rand_width] == Wall) {
				if (maze[rand_length][rand_width - 1] != Wall && maze[rand_length][rand_width - 1] != Wall) break;
			}
			else if (maze[rand_length][rand_width - 1] == Wall && maze[rand_length][rand_width - 1] == Wall) {
				if (maze[rand_length + 1][rand_width] != Wall && maze[rand_length - 1][rand_width] != Wall) break;
			}
		}
	}
	maze[rand_length][rand_width] = Road;

	if (random == Goal) {
		while (bfs_p < 10) {
			//랜덤으로 random 위치 선정
			do {
				rand_length = rand() % length;
				rand_width = rand() % width;
			} while (rand_length % 2 == 0 || rand_width % 2 == 0);

			queue<pair<int, int>> q;
			vector<vector<int>> check;
			check.assign(length, vector<int>(width));
			check[rand_length][rand_width] = 1;
			q.push({ rand_length,rand_width });

			while (!q.empty()) {
				pair<int, int> curr = q.front();
				q.pop();

				for (int dir = 0; dir < 4; dir++) {
					int nx = curr.first + crush_dx[dir];
					int ny = curr.second + crush_dy[dir];

					if (nx < 0 || nx >= length || ny < 0 || ny >= width) continue;
					if (maze[nx][ny] == Wall || check[nx][ny]) continue;

					check[nx][ny] = check[curr.first][curr.second] + 1;
					q.push({ nx,ny });

					if (nx == 1 && ny == 1) {
						bfs_p = check[nx][ny];
						while (!q.empty()) q.pop();
						break;
					}

				}
			}
		}
		maze[rand_length][rand_width] = random;
	}

	if (random == Enemy) {
		bfs_e = 0;
		while (bfs_e <= bfs_p) {
			//랜덤으로 random 위치 선정
			do {
				rand_length = rand() % length;
				rand_width = rand() % width;
			} while (rand_length % 2 == 0 || rand_width % 2 == 0);

			E.curr_x = rand_width;
			E.curr_y = rand_length;
			E.maze_x = rand_length;
			E.maze_y = rand_width;

			queue<pair<int, int>> q;
			vector<vector<int>> check;
			check.assign(length, vector<int>(width));
			check[rand_length][rand_width] = 1;
			q.push({ rand_length,rand_width });

			while (!q.empty()) {
				pair<int, int> curr = q.front();
				q.pop();

				for (int dir = 0; dir < 4; dir++) {
					int nx = curr.first + crush_dx[dir];
					int ny = curr.second + crush_dy[dir];

					if (nx < 0 || nx >= length || ny < 0 || ny >= width) continue;
					if (maze[nx][ny] == Wall || check[nx][ny]) continue;

					check[nx][ny] = check[curr.first][curr.second] + 1;
					q.push({ nx,ny });

					if (nx == 1 && ny == 1) {
						bfs_e = check[nx][ny];
						while (!q.empty()) q.pop();
						break;
					}

				}
			}
		}
		maze[rand_length][rand_width] = random;
	}

}

// 미로 만들기
void create_maze() {

	//초기 미로 생성
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (i % 2 == 0 && j % 2 == 0) {
				maze[i][j] = Wall;
			}
			else if (i % 2 == 0 && j % 2 == 1) {
				maze[i][j] = Wall;
			}
			else if (i % 2 == 1 && j % 2 == 0) {
				maze[i][j] = Wall;
			}
			else {
				maze[i][j] = Road;
			}
		}
	}

	// 벽 뚫기 위해 랜덤으로 위치 선정
	int rand_length, rand_width;
	do {
		rand_length = rand() % length;
		rand_width = rand() % width;
	} while (rand_length % 2 == 0 || rand_width % 2 == 0);

	maze_dfs(rand_length, rand_width);
}

void maze_dfs(int curr_x, int curr_y) {

	visted[curr_x][curr_y] = true;

	vector<int> random(4, -1); // { 0, 1 , 2, 3} 랜덤 배치

	for (int i = 0; i < 4; i++) {
		while (1) {

			int num = rand() % 4;
			auto it = find(random.begin(), random.end(), num);

			if (it == random.end()) {
				random[i] = num;
				break;
			}
		}
	}

	for (int dir : random) {
		int nx = curr_x + dx[dir];
		int ny = curr_y + dy[dir];

		if (nx < 0 || nx >= length || ny < 0 || ny >= width)	continue;
		if (visted[nx][ny])										continue;

		visted[nx][ny] = true;
		maze[curr_x + crush_dx[dir]][curr_y + crush_dy[dir]] = Road;

		maze_dfs(nx, ny);
	}
}

// 미로 세팅하기
void maze_set() {
	maze[1][1] = Player;
	pos_random(Goal); //골인 지점
	pos_random(Enemy); //적
}

// 미로 출력하기
void print_maze() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (maze[i][j] == Player)		 text_color(LIGHTGREEN, DARKGRAY);
			else if (maze[i][j] == Goal) text_color(YELLOW, DARKGRAY);
			else if (maze[i][j] == Enemy) text_color(LIGHTRED, DARKGRAY);
			else if (maze[i][j] == Road) text_color(DARKGRAY, DARKGRAY);
			else text_color(CYAN, CYAN);
			cout << maze[i][j];
		}
		cout << "\n";
	}
	text_color(WHITE, 0);
}

// 플레이어 움직이기
void moving_palyer() {

	text_color(DARKGRAY, DARKGRAY);
	cout << Road;
	gotoxy(P.curr_x, P.curr_y);
	text_color(LIGHTGREEN, DARKGRAY);
	cout << Player;
	gotoxy(P.curr_x, P.curr_y);
}

// 블럭 체크
int check_block(int dir) {
	while (1) {
		int nx = P.maze_x + crush_dx[dir];
		int ny = P.maze_y + crush_dy[dir];

		if (maze[nx][ny] == Road || maze[nx][ny] == Player) {
			maze[P.maze_x][P.maze_y] = Road;
			maze[nx][ny] = Player;

			P.maze_x = nx;
			P.maze_y = ny;
			return 1;
		}
		else if (maze[nx][ny] == Enemy) {
			text_color(BLACK, BLACK);
			system("cls");
			text_color(WHITE, WHITE);

			gotoxy(9, 6);
			cout << "■■■■■■■■■■■■■■■■";

			gotoxy(9, 7);
			cout << "■";
			text_color(WHITE, BLACK);
			cout << "           LOSE             ";
			text_color(WHITE, WHITE);
			cout << "■";
			gotoxy(9, 8);
			cout << "■■■■■■■■■■■■■■■■";
			gotoxy(14, 10);
			text_color(YELLOW, BLACK);
			cout << "Press Enter\n";
			int input = 0;
			while (1) {
				input = _getch();
				if (input == ENTER) {
					end_flag = true;
					return 0;
				}
			}
		}
		else if (maze[nx][ny] == Goal) {
			text_color(BLACK, BLACK);
			system("cls");
			text_color(WHITE, WHITE);

			gotoxy(9, 6);
			cout << "■■■■■■■■■■■■■■■■";

			gotoxy(9, 7);
			cout << "■";
			text_color(WHITE, BLACK);
			cout << "             WIN            ";
			text_color(WHITE, WHITE);
			cout << "■";
			gotoxy(9, 8);
			cout << "■■■■■■■■■■■■■■■■";
			gotoxy(14, 10);
			text_color(YELLOW, BLACK);
			cout << "Press Enter\n";
			int input = 0;
			while (1) {
				input = _getch();
				if (input == ENTER) {
					end_flag = true;
					return 0;
				}
			}
		}
		else return 0;
	}
}

int enemy_bfs() {

	while (!enemy_q.empty()) {
		pair<int, int> curr = enemy_q.front();
		enemy_q.pop();

		for (int dir = 0; dir < 4; dir++) {
			int nx = curr.first + crush_dx[dir];
			int ny = curr.second + crush_dy[dir];

			if (nx < 0 || nx >= length || ny < 0 || ny >= width)	continue;
			if (maze[nx][ny] == Wall || visted[nx][ny])				continue;

			if (maze[nx][ny] == Player) {
				while (!enemy_q.empty()) enemy_q.pop();
				return visted[curr.first][curr.second];
			}

			visted[nx][ny] = visted[curr.first][curr.second] + 1;
			enemy_q.push({ nx,ny });
		}
	}
	return 0;
}

// 적 움직이기
void moving_enemy() {

	int min_num = 987654321, direct = -1;

	for (int dir = 0; dir < 4; dir++) {
		visted.assign(length, vector<int>(width));

		visted[E.maze_x][E.maze_y] = 1;
		int nx = E.maze_x + crush_dx[dir];
		int ny = E.maze_y + crush_dy[dir];

		if (maze[nx][ny] == Wall)	continue;
		if (maze[nx][ny] == Player) {
			text_color(BLACK, BLACK);
			system("cls");
			text_color(WHITE, WHITE);

			gotoxy(9, 6);
			cout << "■■■■■■■■■■■■■■■■";

			gotoxy(9, 7);
			cout << "■";
			text_color(WHITE, BLACK);
			cout << "           LOSE             ";
			text_color(WHITE, WHITE);
			cout << "■";
			gotoxy(9, 8);
			cout << "■■■■■■■■■■■■■■■■";
			gotoxy(14, 10);
			text_color(YELLOW, BLACK);
			cout << "Press Enter\n";
			int input = 0;
			while (1) {
				input = _getch();
				if (input == ENTER) {
					end_flag = true;
					return;
				}
			}
		}

		visted[nx][ny] = 2;
		enemy_q.push({ nx,ny });
		int num = enemy_bfs();
		if (num) {
			if (min_num > num) {
				min_num = num;
				direct = dir;
			}
		}
		visted.clear();
	}

	if (maze[E.maze_x][E.maze_y] == Goal) {
		gotoxy(E.curr_x, E.curr_y);
		text_color(YELLOW, DARKGRAY);
		cout << Goal;
		gotoxy(E.curr_x, E.curr_y);
	}
	else {
		maze[E.maze_x][E.maze_y] = Road;
		gotoxy(E.curr_x, E.curr_y);
		text_color(DARKGRAY, DARKGRAY);
		cout << Road;
		gotoxy(E.curr_x, E.curr_y);
	}

	E.curr_x = E.maze_y + crush_dy[direct];
	E.curr_y = E.maze_x + crush_dx[direct];
	E.maze_x = E.maze_x + crush_dx[direct];
	E.maze_y = E.maze_y + crush_dy[direct];

	if (maze[E.maze_x][E.maze_y] == Goal) {
		gotoxy(E.curr_x, E.curr_y);
		text_color(YELLOW, DARKGRAY);
		cout << Goal;
	}
	else {
		gotoxy(E.curr_x, E.curr_y);
		text_color(LIGHTRED, DARKGRAY);
		cout << Enemy;
		maze[E.maze_x][E.maze_y] = Enemy;
	}
	gotoxy(E.curr_x, E.curr_y);
}

// 미로 실행하기
void playing_maze() {

	gotoxy(P.curr_x, P.curr_y);
	int input;
	while (1) {
		input = _getch();

		switch (input) {
		case DOWN:
			if (check_block(0)) {
				gotoxy(P.curr_x, P.curr_y);
				P.curr_y++;
				moving_palyer();
				moving_enemy();
			}
			if (end_flag) goto ending;
			break;

		case RIGHT:
			if (check_block(1)) {
				gotoxy(P.curr_x, P.curr_y);
				P.curr_x++;
				moving_palyer();
				moving_enemy();
			}
			if (end_flag) goto ending;
			break;

		case UP:
			if (check_block(2)) {
				gotoxy(P.curr_x, P.curr_y);
				P.curr_y--;
				moving_palyer();
				moving_enemy();
			}
			if (end_flag) goto ending;
			break;

		case LEFT:
			if (check_block(3)) {
				gotoxy(P.curr_x, P.curr_y);
				P.curr_x--;
				moving_palyer();
				moving_enemy();
			}
			if (end_flag) goto ending;
			break;

		case ESC:
			text_color(WHITE, BLACK);
			goto ending;
			break;
		default:
			break;
		}
	}
ending:
	return;
}