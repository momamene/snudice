#include "TILE.h"


void TILE::init(int xo,int yo) {
	tileType=TY_NONE;
	ptPos.x=xo;
	ptPos.y=yo;
	prevTile.x=-1;
	prevTile.y=-1;
	nextTile.x=-1;
	nextTile.y=-1;
	flag1=0;
	flag2=0;
	flag3=0;

	memset(college,0,sizeof(college));
	memset(building,0,sizeof(building));
	memset(subject,0,sizeof(subject));
}
void TILEPREV::init(int xo,int yo) {
	tileType=TY_NONE;
	ptPos.x=xo;
	ptPos.y=yo;
	prevTile.x=-1;
	prevTile.y=-1;
	nextTile.x=-1;
	nextTile.y=-1;
	flag1=0;
	flag2=0;


	memset(college,0,sizeof(college));
	memset(building,0,sizeof(building));
	memset(subject,0,sizeof(subject));
}
