#pragma warning(disable:4828)
#include "Stage.h"
#include "Type0.h"
#include "Enemy_mage.h"
#include "Enemy_bird.h"
#include "Enemy_bird2.h"
#include "Enemy_turret.h"
#include "Enemy_MiddleBoss.h"
#include "Enemy_Boss.h"
#include "Enemy_BossTurret.h"

/*
 Rectangle(hdc, 400, 10, 1000, 690)// 게임 배경

 게임 핸들러가 모든 정보를 다 가지고 있음(몬스터, 플레이어, 총알에 관한 정보 등을)

 이 상태에서 스테이지를 클래스로 따로 만들려고 만지작거리면 거릴수록 드는 생각이
 스테이지 클래스 안에 GameHandler를 넣는 수 밖에 없다는 생각이 듦
 이럴경우 스테이지를 클래스로 따로 만드는 의미가 없음 그냥 GameHandler가 하나의 스테이지임
 GameHandler 안에 보스몹이랑 잡몹 추가하면 끝나는거임


 만약,
 스테이지를 클래스로 만든다하면 몬스터, 플레이어, 총알정보 등을 클래스로 만들어두고
 스테이지 안에서 new로 불러서 해야될것 같음


*/

Stage::Stage()
{
	Monster_Number = 0;
}

Stage::~Stage()
{
	
}


EnemyBase* Stage::getMonsterBase()
{
	EnemyBase* Enemy = nullptr;
	// case 뒤에 숫자가 순서임 만약 슬라임 슬라임 소환하고 싶으면 case 0,1을 슬라임으로 두면 됨
	// 소환할 몹을 쭈르륵 나열하면 됨
	switch (Monster_Number)
	{
	case 0:
	{
		Enemy = new Enemy_bird(); // 생성
		Enemy->SetLocation(POINT{ 700,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
	break;
	case 1:
	{
		Sleep(0);
		Enemy = new Enemy_bird2(); // 생성
		Enemy->SetLocation(POINT{ 700,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
	break;
	case 2:
	{
		Sleep(500);
		Enemy = new Enemy_bird(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
	break;
	case 3: {
		Sleep(0);
		Enemy = new Enemy_bird2(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		  break;
	case 4: {
		Sleep(500);
		Enemy = new Enemy_bird(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		  break;
	case 5: {
		Sleep(0);
		Enemy = new Enemy_bird2(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		  break;
	case 6: {
		Sleep(500);
		Enemy = new Enemy_bird(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		  break;
	case 7: {
		Sleep(0);
		Enemy = new Enemy_bird2(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		  break;
	case 8: {
		Sleep(500);
		Enemy = new Enemy_bird(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		  break;
	case 9: {
		Sleep(0);
		Enemy = new Enemy_bird2(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		  break;
	case 10: {
		Sleep(500);
		Enemy = new Enemy_bird(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		   break;
	case 11: {
		Sleep(0);
		Enemy = new Enemy_bird2(); // 생성
		Enemy->SetLocation(POINT{ 400,10 }); // 좌표 설정
		Enemy->SetHealth(100);
	}
		   break;

		   /////////////////////////////////////////////////////////////////////// 
	case 12: {
		Sleep(1000);
		//new 초록버섯;
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 900,40 }); // 좌표 설정
		Enemy->SetHealth(10);

	}
		   break;
	case 13: {
		Sleep(0);
		//new 초록버섯;
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 450,40 }); // 좌표 설정
		Enemy->SetHealth(10);
	}
		   break;
	case 14: {
		Sleep(1000);
		Enemy = new Enemy_MiddleBoss(); // 생성
		Enemy->SetLocation(POINT{ 400,50 }); // 좌표 설정	
		Enemy->SetHealth(15);
		Enemy->SetSize(50, 50);
	}
		   break;

	case 15: {
		Sleep(0);
		Enemy = new Enemy_MiddleBoss(); // 생성
		Enemy->SetLocation(POINT{ 900,50 }); // 좌표 설정	
		Enemy->SetHealth(15);
		Enemy->SetSize(50, 50);
	}
		   break;
		   /////////////////////////////////////////////////////////////////////// 터렛을 마름모꼴로 배치하여 탄환을 피하는 구간
	case 16: {
		Sleep(20000);
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 675,10 }); // 좌표 설정
		Enemy->SetHealth(1000);
	}
		   break;
	case 17: {
		Sleep(5000);
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 550,10 }); // 좌표 설정
		Enemy->SetHealth(1000);
	}
		   break;
	case 18: {
		Sleep(0);
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 800,10 }); // 좌표 설정
		Enemy->SetHealth(1000);
	}
		   break;
	case 19: {
		Sleep(5000);
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 900,10 }); // 좌표 설정
		Enemy->SetHealth(1000);
	}
		   break;
	case 20: {
		Sleep(0);
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 450,10 }); // 좌표 설정
		Enemy->SetHealth(1000);
	}
		   break;
	case 21: {
		Sleep(5000);
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 550,10 }); // 좌표 설정
		Enemy->SetHealth(1000);
	}
		   break;
	case 22: {
		Sleep(0);
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 800,10 }); // 좌표 설정
		Enemy->SetHealth(1000);
	}
		   break;
	case 23: {
		Sleep(5000);
		Enemy = new Enemy_turret();
		Enemy->SetLocation(POINT{ 675,10 }); // 좌표 설정
		Enemy->SetHealth(1000);
	}
		   break;

///////////////////////////////////////////////////////////////////////

	case 24: {
		Sleep(35000);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 675,50 });
		Enemy->SetHealth(1);
	}
		   break;
	case 25: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,300 });
		Enemy->SetHealth(1);
	}
		   break;
	case 26: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,300 });
		Enemy->SetHealth(1);
	}
		   break;
	case 27: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 675,600 });
		Enemy->SetHealth(1);
	}
		break;

//////////////////////////	

	case 28: {
		Sleep(1500);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,50 });
		Enemy->SetHealth(1);
	}
		   break;
	case 29: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,50 });
		Enemy->SetHealth(1);
	}
		   break;
	case 30: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,600 });
		Enemy->SetHealth(1);
	}
		   break;
	case 31: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,600 });
		Enemy->SetHealth(1);
	}
		   break;

//////////////////////////	

	case 32: {
		Sleep(2500);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 675,50 });
		Enemy->SetHealth(1);
	}
		   break;
	case 33: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,50 });
		Enemy->SetHealth(1);
	}
		   break;
	case 34: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,50 });
		Enemy->SetHealth(1);
	}

		   break;
	case 35: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,300 });
		Enemy->SetHealth(1);
	}
		   break;
	case 36: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,300 });
		Enemy->SetHealth(1);
	}
		   break;

	case 37: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 675,600 });
		Enemy->SetHealth(1);
	}
		   break;
	case 38: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,600 });
		Enemy->SetHealth(1);
	}
		   break;
	case 39: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,600 });
		Enemy->SetHealth(1);
	}
		   break;

	case 40: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,600 });
		Enemy->SetHealth(1);
	}
		   break;
///////////////////////////////////////////////////////////////////////
	case 41: {
		Sleep(5000);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 675,10 });
		Enemy->SetHealth(1);
	}
		   break;

	case 42: {
		Sleep(500);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 450,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 43: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 44: {
		Sleep(500);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 900,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 45: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 46: {
		Sleep(500);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 500,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 47: {
		Sleep(500);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 750,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 48: {
		Sleep(0);
		Enemy = new Enemy_mage(); 
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 49: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 50: {
		Sleep(500);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 675,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 51: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 52: {
		Sleep(500);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 450,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 53: {
		Sleep(500);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 900,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 54: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,200 });
		Enemy->SetHealth(1);
	}
		   break;
	
	case 55: {
		Sleep(500);
		Enemy = new Enemy_bird(); //bird
		Enemy->SetLocation(POINT{ 700,10 });
	}
		   break;
	case 56: {
		Sleep(0);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 550,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 57: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 58: {
		Sleep(500);
		Enemy = new Enemy_bird(); //bird
		Enemy->SetLocation(POINT{ 700,10 });
	}
		   break;
	case 59: {
		Sleep(0);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 750,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 60: {
		Sleep(250);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 675,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 61: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 62: {
		Sleep(250);
		Enemy = new Enemy_bird(); //bird
		Enemy->SetLocation(POINT{ 450,10 });
	}
		   break;
	case 63: {
		Sleep(0);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 700,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 64: {
		Sleep(250);
		Enemy = new Enemy_mage(); 
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 65: {
		Sleep(250);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 66: {
		Sleep(0);
		Enemy = new Enemy_bird(); //bird
		Enemy->SetLocation(POINT{ 700,10 });
	}
		   break;
///////////////////////////////////////////////////////////////////////

	case 67: {
		Sleep(500);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 450,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 68: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 900,200 });
		Enemy->SetHealth(1);
	}
		   break;

	case 69: {
		Sleep(500);
		Enemy = new Enemy_bird2(); //bird
		Enemy->SetLocation(POINT{ 700,10 });
	}
		   break;
	case 70: {
		Sleep(0);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 750,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 71: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 72: {
		Sleep(500);
		Enemy = new Enemy_bird2(); //bird
		Enemy->SetLocation(POINT{ 700,10 });
	}
		   break;
	case 73: {
		Sleep(0);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 550,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 74: {
		Sleep(250);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 800,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 75: {
		Sleep(0);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 76: {
		Sleep(250);
		Enemy = new Enemy_bird2(); //bird
		Enemy->SetLocation(POINT{ 700,10 });
	}
		   break;
	case 77: {
		Sleep(0);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 450,10 });
		Enemy->SetHealth(1);
	}
		   break;
	case 78: {
		Sleep(250);
		Enemy = new Type0(); //globe
		Enemy->SetLocation(POINT{ 500,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 79: {
		Sleep(250);
		Enemy = new Enemy_mage();
		Enemy->SetLocation(POINT{ 450,200 });
		Enemy->SetHealth(1);
	}
		   break;
	case 80: {
		Sleep(0);
		Enemy = new Enemy_bird2(); //bird
		Enemy->SetLocation(POINT{ 700,10 });
	}
		   break;
///////////////////////////////////////////////////////////////////////
	case 81: {
		Sleep(10000);
		Enemy = new Enemy_Boss();
		Enemy->SetLocation(POINT{ 600,40 });
	}
		  break;
	case 82: {
		Sleep(0);
		Enemy = new Enemy_BossTurret();
		Enemy->SetLocation(POINT{ 550,150 });
	}
		  break;
	case 83: {
		Sleep(0);
		Enemy = new Enemy_BossTurret();
		Enemy->SetLocation(POINT{ 800,150 });
	}
		   break;
	default:

		break;
	}
	Monster_Number++;

	return Enemy;
}
