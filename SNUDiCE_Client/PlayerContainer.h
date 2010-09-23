//------------------------------------------------------------------------------------
//	gDataContainer Class
//
//	2010. 08. 02	CoderK
//
//	플레이어 및 데이타 다루자
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Image.h"

struct CHARIMGINFO
{
	gImage			ImgCharSel;
	gImage			ImgDot;
};

class gDataContainer
{
public:
	static gDataContainer *GetIF();

	gDataContainer(void);
	virtual ~gDataContainer(void);
public:
	PLAYER			m_MyPlayer;		// 나
	CHANNEL			m_MyChannel;

	ROOM			m_MyRoom;
	PLAYER			m_PlayerList[ROOMMAXPLAYER];

	CHARINFO		m_CharInfo[MAXCHARNUM];
	CHARIMGINFO		m_ImgInfo[MAXCHARNUM];

	GAMEPLAYER		m_MyGamePlayer;
	GAMEPLAYER		m_GPlayerList[ROOMMAXPLAYER];

public:
	void			SetMyPlayer(PK_LOGIN_REP *rep);
	void			RefreshChannel(CHANNEL *channel);

	void			SetMyRoom(ROOM *room);
	void			SetPlayerList(PLAYER *list);

	void			SetMyGamePlayer(GAMEPLAYER* gp);
	void			SetGPList(GAMEPLAYER *list);

	bool			SetUp();
	void			Release();

private:
	bool			SetUpCharInfo();
	bool			SetUpCharImg();
};
