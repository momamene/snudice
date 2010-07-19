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
	
	//bool	m_minimapOn;
	TILE	bmpKindSavor[MAXSAVOR_N];
	TILE	tileMap[LINEX*LINEY];


	int m_xSpacePos;
	int m_ySpacePos;

	int m_xInitSpacePos;
	int m_yInitSpacePos;

public:
	static tileContainer *GetIF();
	void	Setup();
	void	Draw();
	void	minimapDraw(int start_x,int start_y,int n);
	bool	isExisted(int i, int j);
	void	posSpacor();

private:
	void	Load();
	void	viewSpacor();
	void	LoadFileToBKS();
	void	LoadBKSToTM();
};

