#pragma once
#include "TILE.h"
#include "gImage.h"

#define MAXSAVOR_N 100

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
	static tileContainer *GetIF();	// 1

	tileContainer();
	virtual ~tileContainer();
public:
	HANDLE	hFile;
	DWORD	dw;
	gImage	gimage[9];
	gImage	m_wallpaper;

	int		count; // �Ƹ� �̰��� tile�� ��������.

	
	//bool	m_minimapOn;
	TILE	bmpKindSavor[MAXSAVOR_N];
	TILE	tileMap[LINEX*LINEY];
	
	// ��ǥ ���� ������
	int		m_xSpacePos;
	int		m_ySpacePos;
	int		m_Next_xSpacePos;
	int		m_Next_ySpacePos;
	int		m_xInitSpacePos;
	int		m_yInitSpacePos;

	// class ������
	int		m_subjectN;
	int		m_subject[MAXSAVOR_N];

public:
	void	Setup();			// setup
	void	Draw();				// �׸��� �Լ�

	// Draw Position set colony
	void	posSpacor();		// space�� ������ �ش� ��ġ�� �̵��ϰ�, ĳ������ �̵��� ����ִ� ���� �Լ�
	void	posMover(int frame);
	void	posStoper();		// �׻� posSpacor -> posMover -> posStoper ������ �����
	
	// subject function colony
	int		flagToRow (int index);
	int		rowToFirstTile(int row);
	int		flagToFirstTile(int index);

	// abs,con function colony
	POINT	conToAbs(POINT ij);	
	POINT	absToCon();

	
private:
	// Setup�� ������ (subfunction)
	void	Load();				// ������ �ҷ����� �Լ�
	void	LoadFileToBKS();	// Load�� ��������
	void	LoadBKSToTM();

	// Draw�� ������
	void	DrawSubInfo();
	void    DrawSubmit();
	void	DrawHexagon(int x0,int y0,int n,bool boolo=false);

	// ��Ÿ �߿�
	bool	isExisted(int i, int j);	// Tile (i,j) ȣ���� ��ȿ�Ѱ�? 
	bool	isExisted(int line);
	
};

