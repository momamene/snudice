#include "Dice.h"


static gDice s_Dice;

gDice *gDice::GetIF()
{
	return &s_Dice;
}

bool gDice::SetUp()
{
	m_ImgHed[0].Load(DICE_FILE_HED1);
	m_ImgHed[1].Load(DICE_FILE_HED2);
	m_ImgHed[2].Load(DICE_FILE_HED3);
	m_ImgHed[3].Load(DICE_FILE_HED4);

	m_ImgCube[0].Load(DICE_FILE_CUBE1);
	m_ImgCube[1].Load(DICE_FILE_CUBE2);
	m_ImgCube[2].Load(DICE_FILE_CUBE3);
	m_ImgCube[3].Load(DICE_FILE_CUBE4);
	m_ImgCube[4].Load(DICE_FILE_CUBE5);
	m_ImgCube[5].Load(DICE_FILE_CUBE6);

	m_nPos = 0;
	m_ImgCubeWin.Load(DICE_FILE_CUBWIN);
	m_ImgHedWin.Load(DICE_FILE_HEDWIN);

	SetRect(&m_winPos,
		WIN_POS_X, WIN_POS_Y,
		WIN_POS_X + m_ImgHedWin.m_nWidth,
		WIN_POS_Y + m_ImgHedWin.m_nHeight);

	SetRect(&m_winPos1,
		WIN_POS_X1, WIN_POS_Y,
		WIN_POS_X1 + m_ImgHedWin.m_nWidth,
		WIN_POS_Y + m_ImgHedWin.m_nHeight);

	SetRect(&m_winPos2,
		WIN_POS_X2, WIN_POS_Y,
		WIN_POS_X2 + m_ImgHedWin.m_nWidth,
		WIN_POS_Y + m_ImgHedWin.m_nHeight);

	m_frametime.SetUp();
	m_start=false;

	return true;
}

void gDice::Release()
{
	int		i;

	for(i = 0; i < 4; i++)
		m_ImgHed[i].Release();

	for(i = 0; i < 6; i++)
		m_ImgCube[i].Release();
}

void gDice::DiceStart(bool hedron, bool cube, int n1, int n2)
{
	//It must be 
//	ASSERT(n1<4 && n2<6);

	if(!m_start)
	{
		m_frametime.SetUp();
		m_frametime.frameStart(2300, 23); //위에서 해주세요도
		m_start = true;
	}
	m_hedron	= hedron;
	m_cube		= cube;
	m_nCube = n2;
	m_nHed	= n1;
}

void gDice::DiceThrow()
{
	RECT	rcSour;
	int		n1, n2;

	if(!m_start)
		return;

	n1 = m_nHed, n2 = m_nCube;
	
	m_nPos = m_frametime.frame();

	if(m_nPos == DICE_FRAME)
	{
		m_frametime.frameEnd();
		m_start = false;
		return;
	}
	
	//three case consideration
	if(m_hedron && m_cube)
	{
		SetRect(&rcSour, m_ImgHed[n1].m_nWidth/(DICE_FRAME)*m_nPos, 0, 
			m_ImgHed[n1].m_nWidth/(DICE_FRAME)*(m_nPos+1), m_ImgHed[n1].m_nHeight);
		m_ImgHed[n1].Draw(m_winPos1, rcSour);

		SetRect(&rcSour, m_ImgCube[n2].m_nWidth/(DICE_FRAME)*m_nPos, 0, 
			m_ImgCube[n1].m_nWidth/(DICE_FRAME)*(m_nPos+1), m_ImgCube[n2].m_nHeight);
		m_ImgCube[n2].Draw(m_winPos2, rcSour);

		SetRect(&rcSour, 0, 0, 
			m_ImgCubeWin.m_nWidth, m_ImgCubeWin.m_nHeight);

		m_ImgHedWin.Draw(m_winPos1, rcSour);
		m_ImgCubeWin.Draw(m_winPos2, rcSour);
	}
	else if(m_hedron)
	{
		SetRect(&rcSour, m_ImgHed[n1].m_nWidth/(DICE_FRAME)*m_nPos, 0, 
			m_ImgHed[n1].m_nWidth/(DICE_FRAME)*(m_nPos+1), m_ImgHed[n1].m_nHeight);
		m_ImgHed[n1].Draw(m_winPos, rcSour);

		SetRect(&rcSour, 0, 0, 
			m_ImgCubeWin.m_nWidth, m_ImgCubeWin.m_nHeight);
		m_ImgHedWin.Draw(m_winPos, rcSour);
	}
	else if(m_cube)
	{
		SetRect(&rcSour, m_ImgCube[n2].m_nWidth/(DICE_FRAME)*m_nPos, 0, 
			m_ImgCube[n2].m_nWidth/(DICE_FRAME)*(m_nPos+1), m_ImgCube[n2].m_nHeight);
		m_ImgCube[n2].Draw(m_winPos, rcSour);

		SetRect(&rcSour, 0, 0, 
			m_ImgCubeWin.m_nWidth, m_ImgCubeWin.m_nHeight);
		m_ImgCubeWin.Draw(m_winPos, rcSour);
	}
}