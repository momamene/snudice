#pragma once
#include "TILE.h"
#include "gImage.h"

#define MAXSAVOR_N 100

#define LEFTX 25
#define MIDDLEX 52
#define HALFX 52 // 25+ 52/2 = 52 
#define FULLX 102
#define WIDEX 154
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
	gImage	m_wallpaperSubmit;
	gImage	m_buttonSubmit;

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
	int		m_selectReadySubjectFlag;

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
	
	// subject function colony - �������! (�� �����ϰ�, ���ư��� ��� ������ ;;;)
	int		flagToRow (int index);
	int		rowToFlag (int row);
	int		rowToFirstTile(int row);
	int		rowToSecondTile(int row);
	int		flagToFirstTile(int index);
	int		flagToSecondTile(int index);
	
	// abs,con function colony
	POINT	conToAbs(POINT ij);
	POINT	absToCon(POINT ij); 

	// ����� ���� ���� �Լ���
	int		busClickProcessor(int x,int y);
	int		distance(int mapA,int mapB);	// ġ������ ��� ����. ��� ���� ���ѷ��� ������ �� ������ �� �� ����

	void	Release();	


private:
	// Setup�� ������ (subfunction)
	void	Load();				// ������ �ҷ����� �Լ�
	void	LoadFileToBKS();	// Load�� ��������
	void	LoadBKSToTM();

	// Draw�� ������
	void	DrawSubInfo();
	void    DrawSubmit();
	void	DrawSubmitButton(int io,int tile);
	void	DrawSubmitButtonOne (int x0,int y0,int type);

	void	DrawHexagon(int x0,int y0,int n,bool boolo=false);
	void	DrawHexagonOne(int x0,int y0,int i,int j,int n,bool boolo,int type=0);	// 0�� �⺻ 1�� ���õ� ǥ��
	void	DrawHexagonBus();
	
	// ��Ÿ �߿�
	bool	isExisted(int i, int j);	// Tile (i,j) ȣ���� ��ȿ�Ѱ�? 
	bool	isExisted(int line);
	POINT	absToCon();			// terrible Problem. where is input Point? (gmouse�� mouse���� gGameCore�� x_Pos�� �о� �ڵ� ��� �ϴ� ���� �Լ�)

};

