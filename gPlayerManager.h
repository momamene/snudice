// gPlayerManager.h: interface for the gPlayerManager class.
//
//////////////////////////////////////////////////////////////////////

#include "gPlayer.h"
#include "const.h"
#include "gTitleCore.h" // �ֳ��ϸ�, ePLAYERSEL ������

//////////////////////////////////////////////////////////////////////

class gPlayerManager  
{
public:
	int			m_playerN;
	gPlayer		m_player[MAXPLAYER];
	ePLAYERSEL	m_playerState[MAXPLAYER];

public:
	static gPlayerManager *GetIF();	// 1
	void SetUp();
	void Draw();
	//gPlayerManager();
	//virtual ~gPlayerManager();

};
