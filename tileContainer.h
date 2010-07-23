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
	
	// 좌표 관련 변수들
	int m_xSpacePos;
	int m_ySpacePos;
	int m_Next_xSpacePos;
	int m_Next_ySpacePos;
	int m_xInitSpacePos;
	int m_yInitSpacePos;

	// class 변수들
	int m_subjectN;
	int m_subject[MAXSAVOR_N];

public:
	static tileContainer *GetIF();	// 1
	void	Setup();			// setup
	void	Draw();				// 그리는 함수
	void	posSpacor();		// space를 누르면 해당 위치로 이동하고, 캐릭터의 이동을 잡아주는 등의 함수
	void	posMover(int frame);
	void	posStoper();

	
	//POINT	nextN_Tile(POINT ij, int n);

	// 좌표 변환 중요
	POINT	conToAbs(POINT ij);	
	POINT	absToCon();

	
private:
	// Setup의 떨거지 (subfunction)
	void	Load();				// 파일을 불러오는 함수
	void	LoadFileToBKS();	// Load의 떨거지들
	void	LoadBKSToTM();

		
	
	// Draw의 떨거지
	void	minimapDraw(int start_x,int start_y,int n);		// 잘못된 이름 => DrawMinimap (대문자 시작, 대문자 전환, 첫 이름은 mother name)
	void	DrawSubInfo();
	// 기타 중요
	//POINT	viewSpacor(int x, int y);	
	bool	isExisted(int i, int j);	// Tile (i,j) 호출은 유효한가? 
	
};

