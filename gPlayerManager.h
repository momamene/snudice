//------------------------------------------------------------------------------------
//	gPlayerManager Class
//
//	2010. 07. 25	CoderK
//
//	�÷��̾� ����
//	stl list�� �÷��̾� ���� 1p -> 2p -> 3p -> 4p -> 1p ...
//------------------------------------------------------------------------------------
#pragma once
#include "gPlayer.h"
#include "const.h"
#include "gTitleCore.h" // �ֳ��ϸ�, ePLAYERSEL ������

class gPlayerManager  
{
public:
	static gPlayerManager *GetIF();	// 1
	
	gPlayerManager();
	virtual ~gPlayerManager();

public:

	int				m_playerN;				// player ��
	gPlayer			m_player[MAXPLAYER];	// �갡 ��?���?����? -> ��� gPlayer ���ο��� Ȯ��
											// gPlayer->m_nNP == -1 -> ����
public:
	void			SetUp();

	void			Draw();

	int				StudentNum(int flag);

	void			Release();
	void			CooltimePass(); 
	
};
