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

	// ������
	int		m_xInitSpacePos;
	int		m_yInitSpacePos;

	bool	Setup();			// setup

	int		distance(int mapA,int mapB);		// spacor�� find
	int		destination(int mapA,int spacor);	// mapB�� find

private:
	// Setup�� ������ (subfunction)
	void	Load();				// ������ �ҷ����� �Լ�
	void	LoadFileToBKS();	// Load�� ��������
	void	LoadBKSToTM();
};