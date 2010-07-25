//------------------------------------------------------------------------------------
//	gPlayer Class
//
//	2010. 07. 25	CoderK
//
//	플레이어
//------------------------------------------------------------------------------------
#pragma once
#include "gChar.h"
#include "const.h"
#include "gGrade.h"

class gPlayer
{
public:

	gChar	m_charInfo;

	int		m_nNP;				// 몇번째 플레이어냐.			-1이면 스킵
	bool	m_bUser;			// 유저가 하냐 컴퓨터가 하냐

	int		m_xSpacePos;
	int		m_ySpacePos;
	int		m_Next_xSpacePos;
	int		m_Next_ySpacePos;
	int		m_xDrawline;
	int		m_yDrawline;
/*
	int		m_subjectN;
	int		m_subject[6];		// 번호는 tileMap의 번호와 같습니다. (tileMap의 번호가 key인 셈이죠.)
*/
	gGrade	m_subjectGrader;

	int		m_myItem[MAXPLAYER];
	
public:
	bool	SetUp (gChar gchar);
	void	Draw  ();
	void	posSpacor();		// space를 누르면 해당 위치로 이동하고, 캐릭터의 이동을 잡아주는 등의 함수
	void	posMover(int frame);
	void	posStoper();
};
