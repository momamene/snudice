//#include <windows.h>
//#include "gImage.h"
#pragma once
#include "gChar.h"
#include "const.h"
#include "gGrade.h"

class gPlayer
{
public:

	gChar	m_charInfo;

	int		m_xSpacePos;
	int		m_ySpacePos;
	int		m_Next_xSpacePos;
	int		m_Next_ySpacePos;
	int		m_xDrawline;
	int		m_yDrawline;
/*
	int		m_subjectN;
	int		m_subject[6];		// ��ȣ�� tileMap�� ��ȣ�� �����ϴ�. (tileMap�� ��ȣ�� key�� ������.)
*/
	gGrade	m_subjectGrader;

	int		m_myItem[MAXPLAYER];
	
public:
	bool	SetUp (gChar gchar);
	void	Draw  ();
	void	posSpacor();		// space�� ������ �ش� ��ġ�� �̵��ϰ�, ĳ������ �̵��� ����ִ� ���� �Լ�
	void	posMover(int frame);
	void	posStoper();
};
