//------------------------------------------------------------------------------------
//	gPlayerManager Class
//
//	2010. 07. 25	CoderK
//
//	플레이어 관리
//	stl list로 플레이어 관리 1p -> 2p -> 3p -> 4p -> 1p ...
//------------------------------------------------------------------------------------
#pragma once
#include "gPlayer.h"
#include "const.h"
#include "gTitleCore.h" // 왜냐하면, ePLAYERSEL 때문에

class gPlayerManager  
{
public:
	static gPlayerManager *GetIF();	// 1
	
	gPlayerManager();
	virtual ~gPlayerManager();

public:

	int				m_playerN;				// player 수
	gPlayer			m_player[MAXPLAYER];	// 얘가 컴?사람?안해? -> 얘는 gPlayer 내부에서 확인
											// gPlayer->m_nNP == -1 -> 안해
public:
	void			SetUp();

	void			Draw();

	int				StudentNum(int flag);

	void			Release();
	void			CooltimePass(); 
	
};
