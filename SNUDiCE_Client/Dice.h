//------------------------------------------------------------------------------------
//	gDice Class
//
//	2010. 09. 24	권정렬
//
//	주사위 굴리자
//------------------------------------------------------------------------------------

#pragma once
#include "Image.h"
#include "Timer.h"
#define DebugDice 1

#define DICE_FILE_HED1		".\\data\\dice\\hedron1.img"
#define DICE_FILE_HED2		".\\data\\dice\\hedron2.img"
#define DICE_FILE_HED3		".\\data\\dice\\hedron3.img"
#define DICE_FILE_HED4		".\\data\\dice\\hedron4.img"

#define DICE_FILE_CUBE1		".\\data\\dice\\cube1.img"
#define DICE_FILE_CUBE2		".\\data\\dice\\cube2.img"
#define DICE_FILE_CUBE3		".\\data\\dice\\cube3.img"
#define DICE_FILE_CUBE4		".\\data\\dice\\cube4.img"
#define DICE_FILE_CUBE5		".\\data\\dice\\cube5.img"
#define DICE_FILE_CUBE6		".\\data\\dice\\cube6.img"

#define DICE_FILE_HEDWIN	".\\data\\dice\\hedronwindow.img"
#define DICE_FILE_CUBWIN	".\\data\\dice\\cubewindow.img"

#define WIN_POS_X			250
#define WIN_POS_Y			100
#define WIN_POS_X1			200
#define WIN_POS_X2			350

#define DICE_POS_X			15
#define DICE_POS_Y			15

#define DICE_FRAME			23

class gDice {
public:
	static gDice	*GetIF();
	int			m_n1;
	int			m_n2;
	bool		m_start;

public:
	bool		SetUp();
	void		Release();
	void		DiceStart(int, int, int, int);
	void		DiceThrow();

private:
	gImage		m_ImgHed[4];
	gImage		m_ImgHedWin;
	gImage		m_ImgCubeWin;
	gImage		m_ImgCube[6];
	int			m_nPos;

	int			m_hedron, m_cube;

	gTimer		m_frametime;

	RECT		m_winPos;
	RECT		m_winPos1;
	RECT		m_winPos2;
};