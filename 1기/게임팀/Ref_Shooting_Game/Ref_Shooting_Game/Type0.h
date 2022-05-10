#pragma once
#include "EnemyBase.h"

class Type0 : public EnemyBase
{
public:
	Type0();
	~Type0();


	static void SetCharacterBit(HINSTANCE hInst);

	void DrawObject(HDC hdc);
	
private:
	bool MoveNext();
	PatternResult Attack(PatternParam Param);

	class PatternNormal* patternNormal;
};

