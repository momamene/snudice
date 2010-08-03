//------------------------------------------------------------------------------------
//	gPlayer Class
//
//	2010. 07. 25	CoderK
//
//	�÷��̾�
//------------------------------------------------------------------------------------
#pragma once
#include "gChar.h"
#include "const.h"
#include "gGrade.h"

class gPlayer
{
public:

	gChar	*m_charInfo;

	int		m_nNP;				// ���° �÷��̾��.			-1�̸� ��ŵ
								// �Ƹ� -1 == none, n == n + 1player
	bool	m_bUser;			// ������ �ϳ�(true) ��ǻ�Ͱ� �ϳ�(false)

	int		m_xSpacePos;
	int		m_ySpacePos;
	int		m_Next_xSpacePos;
	int		m_Next_ySpacePos;
	int		m_xDrawline;
	int		m_yDrawline;

	bool	m_isNokdu;

	int		m_moveFoot;
	int		m_movePosition;
/*
	int		m_subjectN;
	int		m_subject[6];		// ��ȣ�� tileMap�� ��ȣ�� �����ϴ�. (tileMap�� ��ȣ�� key�� ������.)
*/
	gGrade	m_subjectGrader;

	int		m_myItem[MAXPLAYER];

	int		m_itemCardIndex[MAXCARDPOSSESS];
	int		m_itemCooltime[MAXCARD];
	
public:
	bool	SetUp (gChar *gchar);

	void	Draw  ();
	void	posSpacor();		// space�� ������ �ش� ��ġ�� �̵��ϰ�, ĳ������ �̵��� ����ִ� ���� �Լ�
	void	posMover(int frame);
	void	posStoper();

	bool	isMySubject(int flag);

	void	Release();
	void	meet();
private:
	int		meetItemCalculator(int classType,int originalVal);
};
