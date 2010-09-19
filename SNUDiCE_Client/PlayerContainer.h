//------------------------------------------------------------------------------------
//	gPlayerContainer Class
//
//	2010. 08. 02	CoderK
//
//	�÷��̾� �� ����Ÿ �ٷ���
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Image.h"

struct CHARIMGINFO
{
	gImage			ImgCharSel;
};

class gPlayerContainer
{
public:
	static gPlayerContainer *GetIF();

	gPlayerContainer(void);
	virtual ~gPlayerContainer(void);
public:
	PLAYER			m_MyPlayer;		// ��
	CHANNEL			m_MyChannel;

	ROOM			m_MyRoom;
	PLAYER			m_PlayerList[ROOMMAXPLAYER];

	CHARINFO		m_CharInfo[MAXCHARNUM];
	CHARIMGINFO		m_ImgInfo[MAXCHARNUM];

public:
	void			SetMyPlayer(PK_LOGIN_REP *rep);
	void			RefreshChannel(CHANNEL *channel);

	void			SetMyRoom(ROOM *room);
	void			SetPlayerList(PLAYER *list);

	bool			SetUp();
	void			Release();

private:
	bool			SetUpCharInfo();
	bool			SetUpCharImg();
};
