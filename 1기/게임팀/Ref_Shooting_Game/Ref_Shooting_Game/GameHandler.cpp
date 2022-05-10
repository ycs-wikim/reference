#include "GameHandler.h"
#include "PlayerBase.h"
#include "enemyBase.h"
#include "Bullet_Normal.h"
#include "PageStart.h"
#include "PageEnd.h"
#include "PageClear.h"
#include "Stage.h"
#include "Resource.h"
#include "Type0.h"
#include <iostream>

GameHandler* GameHandler::Instance = nullptr;

GameHandler::GameHandler()
{
	Bullet_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
	Enemy_SemaHnd = CreateSemaphore(NULL, 1, 1, NULL);
	//player = nullptr;

	start_num = 0;
	StageKey = 0;
	bGameover = false;
	bGameclear = false;
	bGameend = false;		//게임 클리어, 종료 공용 변수

	start = new PageStart();
	end = new PageEnd();
	clear = new PageClear();
	player = new  PlayerBase();

	BIT_Frame = NULL;
	BIT_Heart = NULL;
	BIT_NullHeart = NULL;
}

void GameHandler::GameStart()
{
	StageKey++;
	if (start_num != 1)
		return;

	CreateThread(NULL, 0, GameHandler::StageTR, (LPVOID)(__int64)StageKey, 0, NULL);

	CreateThread(NULL, 0, GameHandler::test, (LPVOID)NULL, 0, NULL);            // 플레이어 이동 스레드
	CreateThread(NULL, 0, GameHandler::attack, (LPVOID)NULL, 0, NULL);			// 플레이어 공격 스레드

}

void GameHandler::GameOver()
{
	bGameover = true;
	bGameend = true;
}

void GameHandler::GameClear()
{
	bGameclear = true;
	bGameend = true;
}

void GameHandler::ResetGame()
{
	start_num = 0;
	bGameend = false;
	bGameover = false;
	bGameclear = false;
	player->Reset();
}
void GameHandler::RestartGame()
{
	bGameend = false;
	bGameover = false;
	bGameclear = false;
	player->Reset();
	GameStart();
}
GameHandler::~GameHandler()
{
	delete player;
	delete start;
	delete end;
	delete player;

	DeleteObject(BIT_NullHeart);
	DeleteObject(BIT_Heart);
	DeleteObject(BIT_Frame);
	
	CloseHandle(Bullet_SemaHnd);
	CloseHandle(Enemy_SemaHnd);

	PageEnd::DeleteGameOverBit();
	PlayerBase::DeleteCharacterBit();
	Type0::DeleteCharacterBit();
}

void GameHandler::OnPaint(HDC hdc)
{
	HDC hdc2 = CreateCompatibleDC(hdc);

	HBITMAP OldBitmap;

	// 게임의 전체적인 틀
	OldBitmap = (HBITMAP)SelectObject(hdc2, BIT_Frame); //메모리DC에 비트맵오브젝트를 넣는다.
	BitBlt(hdc, 0, 0, 1425, 700, hdc2, 0, 0, SRCCOPY); // DC로 복사(SRCCOPY)한다.


	POINT Life_XY = { 1025,100 };
	for (int i = 0; i < GetPlayerLife(); i++) // 채워져있는 하트 그리기
	{
		SelectObject(hdc2, BIT_Heart); //메모리DC에 비트맵오브젝트를 넣는다.
		BitBlt(hdc, Life_XY.x, Life_XY.y, 50, 50, hdc2, 0, 0, SRCCOPY); // DC로 복사(SRCCOPY)한다.    //하트1
		Life_XY.x += 50;

	}
	if (GetPlayerLife() != 3) // 비워져있는 하트 그리기
	{
		for (int i = 0; i < 3 - GetPlayerLife(); i++)
		{
			
			SelectObject(hdc2, BIT_NullHeart); //메모리DC에 비트맵오브젝트를 넣는다.
			BitBlt(hdc, Life_XY.x, Life_XY.y, 50, 50, hdc2, 0, 0, SRCCOPY); // DC로 복사(SRCCOPY)한다.    //하트1
			Life_XY.x += 50;
		}
	}

	SelectObject(hdc2, OldBitmap);
	
	DeleteDC(hdc2);
	if (start_num != 1) {
		start->DrawStart(hdc);
		return;
	}

	if (bGameover == true)
	{
		end->DrawEnd(hdc);
		return;
	}

	if (bGameclear == true)
	{
		clear->DrawClear(hdc);
		return;
	}

	player->DrawObject(hdc);
	WaitForSingleObject(Bullet_SemaHnd, INFINITE);
	for (auto it = Bullets.begin(); it != Bullets.end(); it++)
	{
		(*it).second->DrawObject(hdc);
	}
	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);

	WaitForSingleObject(Enemy_SemaHnd, INFINITE);
	for (auto it = Enemys.begin(); it != Enemys.end(); it++)
	{
		(*it).second->DrawObject(hdc);
	}
	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);


	
}

void GameHandler::OnKeyDown(WPARAM wParam)
{

	if (start_num != 1) {		//
		start_num = start->start_choose(wParam);
		if (start_num == 1) GameStart();
		if (start_num == 2)ExitProcess(0);
	}

	if (bGameover == true)
	{
		int x;
		x = end->end_choose(wParam);

		// 1이 게임 재시작, 2: 시작 화면 이동, 3: 게임 종료
		if (x == 1)
		{
			Sleep(300);		// 모든 스레드가 죽기를 기다림
			RestartGame();
		}
		else if (x == 2)
		{
			ResetGame();
		}
		else if (x == 3)
		{
			ExitProcess(0);
		}
	}

	if (bGameclear == true)
	{
		int clear_x;
		clear_x = clear->end_choose(wParam);

		if (clear_x == 1)
		{
			ResetGame();
		}
		else if (clear_x == 2)
		{
			ExitProcess(0);
		}
	}
	return;

}

GameHandler* GameHandler::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new GameHandler();
	}

	return Instance;
}
void GameHandler::DestroyInstance()
{
	if (Instance)
	{
		delete Instance;
	}
}

void GameHandler::InitBitmap(HINSTANCE hInst)
{
	this->hInst = hInst;
	BIT_Frame = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	BIT_Heart = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	BIT_NullHeart = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP6));//비트맵 리소스를 받아온다.

	Type0::SetCharacterBit(hInst);
	PageEnd::SetGameOverBit(hInst);
	PlayerBase::SetCharacterBit(hInst);
}

// 움직이는거 쓰레드로 구현
DWORD __stdcall GameHandler::test(LPVOID param)
{

	GameHandler* Instance = GetInstance();
	PlayerBase* player = Instance->player;



	while (1)
	{
		if (Instance->bGameend == true) break;
		if (player->IsDead()) continue;
		// 해당 키가 눌리면 0x8000을 반환함 해당 키들을 계속 확인하면서 키가 눌렸는지 확인함
		int MoveSpeed = 5;
		if (GetKeyState(VK_SHIFT) & 0x8000) //shift
		{
			MoveSpeed = 1;
		}

		if (GetKeyState(VK_UP) & 0x8000) //up
		{
			player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y - MoveSpeed });
			if (player->GetLocation().y <= 17)
			{
				player->SetLocation(POINT{ player->GetLocation().x, 17 });
			}
		}
		if (GetKeyState(VK_LEFT) & 0x8000) //left
		{
			player->SetLocation(POINT{ player->GetLocation().x - MoveSpeed, player->GetLocation().y });
			if (player->GetLocation().x <= 407)
			{
				player->SetLocation(POINT{407, player->GetLocation().y });
			}
		}
		if (GetKeyState(VK_DOWN) & 0x8000) //down
		{
			player->SetLocation(POINT{ player->GetLocation().x, player->GetLocation().y + MoveSpeed });
			if (player->GetLocation().y >= 668) // 여기다가 하면 됨
			{
				player->SetLocation(POINT{ player->GetLocation().x, 668 });
			}
		}
		if (GetKeyState(VK_RIGHT) & 0x8000) //right
		{
			player->SetLocation(POINT{ player->GetLocation().x + MoveSpeed, player->GetLocation().y });
			if (player->GetLocation().x >= 980) // 여기다가 하면 됨
			{
				player->SetLocation(POINT{ 980, player->GetLocation().y });
			}
		}
		Sleep(15);
		//https://mlpworld.tistory.com/entry/키보드-상태-조사
	}

	return 0;
}

DWORD WINAPI GameHandler::attack(LPVOID param)
{
	GameHandler* play = GetInstance();
	PlayerBase* player = play->player;

	while (1)
	{
		if (Instance->bGameend == true) break;
		if (player->IsDead()) continue;

		if (GetKeyState(0x5A) & 0x8000) //z
		{

			BulletBase* Bullet = player->Attack().Bullet;
			play->CreateBullet(Bullet);
		}
		Sleep(100);

	}

	return 0;
}

DWORD WINAPI GameHandler::enemy_attack(LPVOID param) // 적의 공격 스레드(1초마다 공격합니다)
{
	GameHandler* Instance = GetInstance();


	// Enemy가 가진 고유한 킷값을 매개변수로 받음
	int KeyCode = (int)(__int64)param;

	// 킷값을 이용하여 Enemy를 얻음
	EnemyBase* Enemy = nullptr;



	while (1)
	{
		if (Instance->bGameend == true) break;
		WaitForSingleObject(Instance->Enemy_SemaHnd, INFINITE);

		// 먼저 받았던 킷값을 가진 Enemy가 배열에 없으면 나감
		if (Instance->Enemys.count(KeyCode) < 1)
		{
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}

		if (Enemy == nullptr) Enemy = Instance->Enemys.at(KeyCode);

		// Enemy가 가진 패턴을 반환함
		PatternParam Param;
		Param.EntityRect = Enemy->GetRect();
		Param.PlayerRect = Instance->player->GetRect();

		PatternResult result = Enemy->Attack(Param);

		BulletBase* Bullet = result.Bullet;
		int Interval = result.Interval;
		if (Bullet == nullptr) {
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}
		Instance->CreateBullet(Bullet);

		ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
		Sleep(Interval);
	}
	return 0;
}


//적의 움직임을 담당하는 스레드
DWORD WINAPI GameHandler::enemy_move(LPVOID param)
{
	GameHandler* Instance = GetInstance();


	// Enemy가 가진 고유한 킷값을 매개변수로 받음
	int KeyCode = (int)(__int64)param;

	// 킷값을 이용하여 Enemy를 얻음
	EnemyBase* Enemy = nullptr;

	// 플레이어 받아옴
	PlayerBase* player = GetInstance()->player;

	while (1)
	{
		if (Instance->bGameend == true) break;
		
		WaitForSingleObject(Instance->Enemy_SemaHnd, INFINITE);


		// 먼저 받았던 킷값을 가진 Enemy가 배열에 없으면 나감
		if (Instance->Enemys.count(KeyCode) < 1)
		{
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}

		if (Enemy == nullptr) Enemy = Instance->Enemys.at(KeyCode);

		// Enemy를 다음 방향으로 이동시킴 / 맵밖에 나가면 false 반환
		bool result = Enemy->MoveNext();

		// false(맵밖 나가면) 스레드 종료
		if (result == false)
		{
			ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
			break;
		}


		// 플레이어와 부딪혔는지 검사 / 부딪히면 true 반환
		bool hitresult = GetInstance()->EnemyCollisionTest(Enemy);

		// true(부딪히면) 플레이어 5데미지 입히고 스레드 종료
		if (hitresult == true)
		{
			
			
			bool bLifeZero = player->GetDamages(5);
			if (bLifeZero == true) Instance->GameOver();
			if (Enemy->GetType() == 1)
			{
				ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);
				break;
			}
			
			
		}
		ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);

		Sleep(80);

	}
	
	Instance->DeleteEnemy(KeyCode);
	

	return 0;
}
void GameHandler::DeleteBullet(int KeyCode)
{
	WaitForSingleObject(Bullet_SemaHnd, INFINITE);

	// 해당 키코드가 존재할 경우에만 제거
	if (Instance->Bullets.count(KeyCode) > 0)
	{
		delete Bullets.at(KeyCode);
		Bullets.erase(KeyCode);
	}

	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);
}

void GameHandler::DeleteEnemy(int KeyCode)
{
	WaitForSingleObject(Enemy_SemaHnd, INFINITE);

	// 해당 키코드가 존재할 경우에만 제거
	if (Instance->Enemys.count(KeyCode) > 0)
	{
		delete Enemys.at(KeyCode);
		Enemys.erase(KeyCode);
	}

	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);
}

//bullet 생성
void GameHandler::CreateBullet(BulletBase* newBullet)
{
	int KeyCode = newBullet->GetKeyCode();
	WaitForSingleObject(Bullet_SemaHnd, INFINITE);

	// 생성된 Bullet을 배열로 관리하기 위해 map자료구조로 이뤄진 Bullets에 추가
	Bullets.insert(make_pair(KeyCode, newBullet));

	ReleaseSemaphore(Bullet_SemaHnd, 1, NULL);

	CreateThread(NULL, 0, BulletTR, (LPVOID)(__int64)KeyCode, 0, NULL);
}

//Enemy 생성
void GameHandler::CreateEnemy(EnemyBase* newEnemy)
{
	int KeyCode = newEnemy->GetKeyCode();
	WaitForSingleObject(Enemy_SemaHnd, INFINITE);

	// 생성된 Enemy를 배열로 관리하기 위해 map자료구조로 이뤄진 Enemys에 추가
	Enemys.insert(make_pair(KeyCode, newEnemy));

	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);

	CreateThread(NULL, 0, enemy_move, (LPVOID)(__int64)KeyCode, 0, NULL);
	CreateThread(NULL, 0, enemy_attack, (LPVOID)(__int64)KeyCode, 0, NULL);
}





//충돌판정
bool GameHandler::EnemyCollisionTest(EnemyBase* ColEnemy)
{

	if (player->IsDead()) return false;
	RECT HitBox;
	RECT EnemyRect = ColEnemy->GetRect();
	RECT PlayerRect = player->GetRect();
	if (IntersectRect(&HitBox, &EnemyRect, &PlayerRect))
		return true;
	else
		return false;
}

int GameHandler::BulletCollisionTestToEnemy(BulletBase* ColBullet)
{

	int resultKey = -1;
	WaitForSingleObject(Enemy_SemaHnd, INFINITE);
	for (auto it = Enemys.begin(); it != Enemys.end(); it++)
	{
		RECT HitBox;
		RECT EnemyRect = (*it).second->GetRect();
		RECT BulletRect = ColBullet->GetRect();
		(*it).second->GetLocation();
		if (IntersectRect(&HitBox, &EnemyRect, &BulletRect))
		{

			resultKey = (*it).second->GetKeyCode();
			break;
		}
	}
	ReleaseSemaphore(Enemy_SemaHnd, 1, NULL);

	return resultKey;
}
bool GameHandler::BulletCollisionTestToPlayer(BulletBase* ColBullet)
{
	if (player->IsDead()) return false;
	RECT HitBox;
	RECT PlayerRect = player->GetRect();
	RECT BulletRect = ColBullet->GetRect();
	if (IntersectRect(&HitBox, &PlayerRect, &BulletRect))
	{
		return true;
	}

	return false;
}


//
DWORD WINAPI GameHandler::BulletTR(LPVOID param)
{

	GameHandler* Instance = GetInstance();


	// Bullet 가진 고유한 킷값을 매개변수로 받음
	int KeyCode = (int)(__int64)param;

	// 킷값을 이용하여 Bullet를 얻음
	BulletBase* Bullet = Instance->Bullets.at(KeyCode);

	while (1)
	{
		if (Instance->bGameend == true) break;



		bool result = Bullet->MoveNext();


		if (result == false) break;


		// Bullet이 플레이어 소유일경우
		if (Bullet->IsPlayer())
		{



			// 모든 Enemy에 대해서 충돌검사를 한 뒤, 충돌난 Enemy의 KeyCode 반환 / 없을경우 -1 반환
			int colKeyCode = Instance->BulletCollisionTestToEnemy(Bullet);
			if (colKeyCode != -1)
			{
				WaitForSingleObject(Instance->Enemy_SemaHnd, INFINITE);

				EnemyBase* Enemy = nullptr;
				bool bDead = false;
				bool bBoss = false;				//Enemy 보스 확인

				// 해당 키코드가 Enemys에 존재하는지 검사
				if (Instance->Enemys.count(colKeyCode) > 0)
				{
					// 키코드에 해당하는 Enemy를 가져옴
					Enemy = Instance->Enemys.at(colKeyCode);

					// 1데미지를 준 뒤, 죽었으면 true  아니면 false 반환					
					bDead = Enemy->GetDamages(1);

					if (Enemy->GetType() == 3)
					{
						bBoss = true;

					}

				}

				ReleaseSemaphore(Instance->Enemy_SemaHnd, 1, NULL);

				// Enemy가 죽었을경우 Delete함		/      위 코드와 분리한 이유는 Delete 안에도 세마포가 있어서 중복이됨
				if (bDead == true)
				{
					Instance->DeleteEnemy(colKeyCode);
					if (bBoss == true)
					{
						Instance->GameClear();
					}
				}
				break;
			}

		}

		else  // Bullet이 플레이어 소유가 아닐경우
		{
			// 플레이어와 충돌검사를 한 뒤, 충돌시 true 아니면 false 반환
			bool colResult = Instance->BulletCollisionTestToPlayer(Bullet);
			if (colResult == true)
			{
				bool ck;
				ck = Instance->player->GetDamages(1);

				if (ck == true)
				{
					Instance->GameOver();
				}
				break;
			}
		}
		Sleep(10);
	}
	Instance->DeleteBullet(KeyCode);
	return 0;
}

DWORD WINAPI GameHandler::StageTR(LPVOID param)
{
	int Key = (int)(__int64)param;

	Stage* stage = new Stage();

	while (1)
	{
		if (Instance->bGameend == true || Instance->StageKey != Key) break;			// 게임이 종료 OR 현재 진행중인 스테이지와 다르면 종료
		EnemyBase* Enemy = stage->getMonsterBase();										// Sleep이 호출됨
		if (Instance->bGameend == true || Instance->StageKey != Key) break;			// Sleep중 게임이 종료될 수 있기때문에 한번더 검사함

		if (Enemy != nullptr)
		{
			GameHandler::GetInstance()->CreateEnemy(Enemy);
		}
		else
		{
			break;
		}

	}
	delete stage;
	return 0;
}

int GameHandler::GetPlayerLife()
{
	return this->player->GetLife();
}