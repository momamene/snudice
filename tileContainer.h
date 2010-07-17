#pragma once
#include "TILE.h"
#include "gImage.h"

#define MAXSAVOR_N 60

#define LEFTX 25
#define MIDDLEX 52
#define FULLX 102
#define WIDEX 152
#define HALFY 40
#define FULLY 80

#define LINEX 29
#define LINEY 19

class tileContainer
{
public:
	HANDLE	hFile;
	DWORD	dw;
	gImage	gimage[5];
	gImage	m_wallpaper;

	int		count;
	TILE	bmpKindSavor[MAXSAVOR_N];
	TILE	tileMap[LINEX*LINEY];

public:
	static tileContainer *GetIF();
	void	Setup();
	void	LoadFileToBKS();
	void	LoadBKSToTM();
	void	Load();
//	TILE	GetTileFromIJ(int i, int j);
//	TILE	GetPrevTileFromIJ(int i, int j);
//	TILE	GetNextTileFromIJ(int i, int j);
	void	Draw();
};

