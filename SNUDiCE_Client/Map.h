//////////////////////////////////////////////////////////////////////////
/// 10.09.21 01:13 
/// class gTile, gMap
/// Coder : �峭�˼�
/// tileContainer���� �� ���� �Լ����� ����.
/// ������ m_xPos�� ��Ȱ�� ������ gMap class�� m_nAbsDrawlineX �� �ð� �Ǿ���.
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <windows.h> // �ߺ� include (first case) ����?
#include "networkconst.h"
#include "Image.h"

#define MAPMAXSTRBUFFER		128

enum ETILETYPE
{
	TY_NONE	= -1,
	TY_STAMINA,		// �Ĵ�
	TY_ITEM,		// ������
	//TY_GRASS,
	TY_DRINK,		// ���
	TY_BUS,			// ��Ʋ
	TY_MAINGATE,	// ����
	TY_MOUNTAIN,	// ���ǻ�
	TY_CLASS,		// ����
	TY_END,
};

class gTile
{
public:
	ETILETYPE		tileType;
	POINT			prevTile;
	POINT			ptPos;
	POINT			nextTile;

	int				flag1;
	int				flag2;
	int				flag3;
	char			college[MAPMAXSTRBUFFER];
	char			building[MAPMAXSTRBUFFER];
	char			subject[MAPMAXSTRBUFFER];
public:
	void			init(int xo, int yo);
};

#define MAXSAVOR_N	100

#define LEFTX		25
#define MIDDLEX		52
#define HALFX		52 // 25+ 52/2 = 52 
#define FULLX		102
#define WIDEX		154
#define HALFY		40
#define FULLY		80

#define LINEX		29
#define LINEY		19


class gMap
{
public:
	static gMap *GetIF();	// 1

public:
	HANDLE	hFile;
	DWORD	dw;
	gImage	m_ImgTile[9];
//	gImage	m_ImgTileBack;
	gImage	m_ImgSmallTile;

	int		count; // �Ƹ� �̰��� tile�� ��������.

	//bool	m_minimapOn;
	gTile	bmpKindSavor[MAXSAVOR_N];	// �ӽ������� Load�� �ʿ��� Ÿ�ϵ� (���� ���ӿ����� ������ ����)
	gTile	tileMap[LINEX*LINEY];		// ���� Ÿ�ϵ�

	// ������ - (������ �����ǥ) (������, (5,14))
	int		m_xInitSpacePos;
	int		m_yInitSpacePos;

	// ��ǥ ���� ������ 
	// m_xSpacePos , m_ySpacePos �� ���� ��ǥ��
	// m_Next_xSpacePos, m_Next_ySpacePos �� �����Ϸ��� ��ǥ�� �ǹ��Ѵ�.
	int		m_xSpacePos;
	int		m_ySpacePos;
	int		m_Next_xSpacePos;
	int		m_Next_ySpacePos;

//private:
	// ��ǥ ���� ������ �װ��� frame���� �̿��Ͽ� ���� �Ѹ��� ȭ���� ��ǥ�� �����Ѵ�.
	int		m_nAbsDrawlineX;
	int		m_nAbsDrawlineY;


public:
	bool	Setup();			// setup
	void	MainLoop();
	void	Draw();				// �׸��� �Լ�

	// Draw Position set colony
	void	posSetter(int xSpacePos, int ySpacePos);
	void	posSpacor(bool isNokdu=false);		// space�� ������ �ش� ��ġ�� �̵��ϰ�, ĳ������ �̵��� ����ִ� ���� �Լ�
	void	posSpacor(int xNextSpacePos, int yNextSpacePos); // ����ĭ�� �ƴ� Ư�� ĭ���� �̵�.
	void	posMover();
	void	posMover(int frame,int frameN);
	void	posStoper();		// �׻� posSpacor -> posMover -> posStoper ������ �����

	// abs,con function colony
	POINT	conToAbs(POINT ij);
	POINT	absToCon(POINT ij); 

	// ����� ���� ���� �Լ���
	//int		distance(int mapA,int mapB);	
	// �Ÿ��� ���. mapA�� ������, mapB�� ������
	// return ���� ����ϰ�� ��θ� ��ġ�� �ʴ� ���, �����ϰ�� ��θ� �������ϴ� ���
	// ���� �������� �ϴ� ���� �ǹ��Ѵ�. 1�� ��ĭ, 0�� 0ĭ, -3�� 3ĭ�ε� ��θ� ������ ������.

	void	Release();	

	void	DrawHexagon(int x0,int y0,int n,bool boolo=false);

	int		PositionFor_gPC();

private:
	// Setup�� ������ (subfunction)
	void	Load();				// ������ �ҷ����� �Լ�
	void	LoadFileToBKS();	// Load�� ��������
	void	LoadBKSToTM();

	// Draw�� ������
	
	void	DrawHexagonOne(int x0,int y0,int i,int j,int n,bool boolo,int type=0);	// 0�� �⺻ 1�� ���õ� ǥ��


	// ��Ÿ �߿�
	/*
	bool	isExisted(int i, int j);	// Tile (i,j) ȣ���� ��ȿ�Ѱ�? 
	bool	isExisted(int line);
	*/

};
