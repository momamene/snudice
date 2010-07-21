#pragma once
#include "TILE.h"
#include "gImage.h"

#define MAXSAVOR_N 60

#define LEFTX 25
#define MIDDLEX 52
#define HALFX 52 // 25+ 52/2 = 52 
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
	void	Setup();			// setup
	void	Draw();				// �׸��� �Լ�
	void	posSpacor();		// space�� ������ �ش� ��ġ�� �̵��ϰ�, ĳ������ �̵��� ����ִ� ���� �Լ�

	POINT	conToAbs(POINT ij);
	void	DrawSubInfo();
	POINT	absToCon();
private:					
	// Setup�� ������ (subfunction)
	void	Load();				// ������ �ҷ����� �Լ�
	void	LoadFileToBKS();	// Load�� ��������
	void	LoadBKSToTM();
	// posSpacor�� ������
	void	viewSpacor();		
	// Draw�� ������
	void	minimapDraw(int start_x,int start_y,int n);	
	// ��Ÿ �߿�
	bool	isExisted(int i, int j);	// Tile (i,j) ȣ���� ��ȿ�Ѱ�? 
	
};

