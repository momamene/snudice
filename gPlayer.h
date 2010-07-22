//#include <windows.h>
//#include "gImage.h"
#pragma once
#include "gChar.h"
#include "const.h"

class gPlayer
{
public:

	gChar	m_charInfo;

//	int		m_positionTempMoved;
//	POINT	m_position;
	int		m_xSpacePos;
	int		m_ySpacePos;
	int		m_Next_xSpacePos;
	int		m_Next_ySpacePos;
	int		m_xDrawline;
	int		m_yDrawline;
	
//	POINT	m_positionRare;
//	POINT	m_positionFinal;
	int		m_myItem[MAXPLAYER];
	
public:
	bool	SetUp (gChar gchar);
	void	Draw  ();
	void	posSpacor();		// space를 누르면 해당 위치로 이동하고, 캐릭터의 이동을 잡아주는 등의 함수
	void	posMover(int frame);
	void	posStoper();
	// illu imgfile
	// bool gPlayer::SetUp(CHARDATA data,char *szIllu);
	// void gPlayer::Draw();
	// void gPlayer::DrawIllu(RECT rcScr);
};
