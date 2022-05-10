#pragma once
#include "framework.h"

struct POINTF
{
	float x;
	float y;
};


static int start_num;
static int end_num;


class Object
{
public:
	Object();
	virtual void DrawObject(HDC hdc);
	POINT GetLocation();
	void SetLocation(POINT point);
	void SetSize(int width, int height);
	POINT GetSize();
	RECT GetRect();
	bool IsPlayer();
	void SetPlayer();

protected:
	POINT Location;
	int width;
	int height;
	bool bPlayer;
};

