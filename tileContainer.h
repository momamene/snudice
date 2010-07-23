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
	
	// ��ǥ ���� ������
	int m_xSpacePos;
	int m_ySpacePos;
	int m_Next_xSpacePos;
	int m_Next_ySpacePos;
	int m_xInitSpacePos;
	int m_yInitSpacePos;

	// class ������
	int m_subjectN;
	int m_subject[MAXSAVOR_N];

public:
	static tileContainer *GetIF();	// 1
	void	Setup();			// setup
	void	Draw();				// �׸��� �Լ�
	void	posSpacor();		// space�� ������ �ش� ��ġ�� �̵��ϰ�, ĳ������ �̵��� ����ִ� ���� �Լ�
	void	posMover(int frame);
	void	posStoper();

	
	//POINT	nextN_Tile(POINT ij, int n);

	// ��ǥ ��ȯ �߿�
	POINT	conToAbs(POINT ij);	
	POINT	absToCon();

	
private:
	// Setup�� ������ (subfunction)
	void	Load();				// ������ �ҷ����� �Լ�
	void	LoadFileToBKS();	// Load�� ��������
	void	LoadBKSToTM();

		
	
	// Draw�� ������
	void	minimapDraw(int start_x,int start_y,int n);		// �߸��� �̸� => DrawMinimap (�빮�� ����, �빮�� ��ȯ, ù �̸��� mother name)
	void	DrawSubInfo();
	// ��Ÿ �߿�
	//POINT	viewSpacor(int x, int y);	
	bool	isExisted(int i, int j);	// Tile (i,j) ȣ���� ��ȿ�Ѱ�? 
	
};

