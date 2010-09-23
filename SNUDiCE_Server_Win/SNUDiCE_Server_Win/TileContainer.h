#pragma once
#include "Tile.h"

#define MAXSAVOR_N 100


#define LINEX 29
#define LINEY 19

class gTileContainer 
{
public: 
	static gTileContainer *GetIF();	// 1

public:
	TILE	m_bmpKindSavor[MAXSAVOR_N];
	TILE	m_tileMap[LINEX*LINEY];

//	int		m_subject[MAXSUBJECT_N];	

	int		m_TileNum;

	// 시작점
	int		m_xInitSpacePos;
	int		m_yInitSpacePos;

	bool	Setup();			// setup

	int		distance(int mapA,int mapB);		// spacor를 find
	int		destination(int mapA,int spacor);	// mapB를 find

private:
	// Setup의 떨거지 (subfunction)
	void	Load();				// 파일을 불러오는 함수
	void	LoadFileToBKS();	// Load의 떨거지들
	void	LoadBKSToTM();
};