#pragma once
#include <windows.h> // 중복 include (first case) 성공?

enum ETILETYPE {
	TY_NONE=0,
		TY_CLASS,
		TY_ITEM,
		TY_STAMINA,
		TY_BUS,
		TY_MAINGATE
};

class TILE {
public:
	ETILETYPE tileType;
	POINT prevTile;
	POINT ptPos;
	POINT nextTile;
	//HBITMAP* img;
	//int img;
	int flag1;
	int flag2;
	char college[128];
	char building[128];
	char subject[128];
public:
	//TILE();
	void init(int xo, int yo);
};