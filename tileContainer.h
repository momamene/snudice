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

	int		count; // 아마 이것이 tile의 갯수갰지.

	//bool	m_minimapOn;
	TILE	bmpKindSavor[MAXSAVOR_N];
	TILE	tileMap[LINEX*LINEY];
	
	// 좌표 관련 변수들
	int		m_xSpacePos;
	int		m_ySpacePos;
	int		m_Next_xSpacePos;
	int		m_Next_ySpacePos;
	int		m_xInitSpacePos;
	int		m_yInitSpacePos;
	int		m_selectReadySubjectFlag;

	// class 변수들
	int		m_subjectN;
	int		m_subject[MAXSAVOR_N];



public:
	void	Setup();			// setup
	void	Draw();				// 그리는 함수

	// Draw Position set colony
	void	posSpacor();		// space를 누르면 해당 위치로 이동하고, 캐릭터의 이동을 잡아주는 등의 함수
	void	posMover(int frame);
	void	posStoper();		// 항상 posSpacor -> posMover -> posStoper 순으로 써야함
	
	// subject function colony - 수정대상! (뭐 간단하고, 돌아가면 상관 없지만 ;;;)
	int		flagToRow (int index);
	int		rowToFlag (int row);
	int		rowToFirstTile(int row);
	int		rowToSecondTile(int row);
	int		flagToFirstTile(int index);
	int		flagToSecondTile(int index);
	
	// abs,con function colony
	POINT	conToAbs(POINT ij);
	POINT	absToCon(POINT ij); 

	// 상우의 막장 돌진 함수군
	int		busClickProcessor(int x,int y);
	int		distance(int mapA,int mapB);	// 치명적인 녹두 문제. 녹두 들어가면 무한루프 때문에 그 오류를 알 수 있음

	void	Release();	


private:
	// Setup의 떨거지 (subfunction)
	void	Load();				// 파일을 불러오는 함수
	void	LoadFileToBKS();	// Load의 떨거지들
	void	LoadBKSToTM();

	// Draw의 떨거지
	void	DrawSubInfo();
	void    DrawSubmit();
	void	DrawSubmitButton(int io,int tile);
	void	DrawSubmitButtonOne (int x0,int y0,int type);

	void	DrawHexagon(int x0,int y0,int n,bool boolo=false);
	void	DrawHexagonOne(int x0,int y0,int i,int j,int n,bool boolo,int type=0);	// 0은 기본 1은 선택된 표시
	void	DrawHexagonBus();
	
	// 기타 중요
	bool	isExisted(int i, int j);	// Tile (i,j) 호출은 유효한가? 
	bool	isExisted(int line);
	POINT	absToCon();			// terrible Problem. where is input Point? (gmouse의 mouse군과 gGameCore의 x_Pos를 읽어 자동 출력 하는 놀라운 함수)

};

