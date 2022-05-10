#pragma once
#include "EnemyBase.h"
#include "GameHandler.h"


class Stage
{
public:
	EnemyBase* getMonsterBase();
	
	Stage();
	~Stage();
private:
	int Monster_Number;
};


