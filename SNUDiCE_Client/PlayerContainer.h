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
#define	SCRIPT_CHAR_NUM 30

struct CHARIMGINFO
{
	gImage			ImgCharSel;
	gImage			ImgDot;
};

class gPlayerContainer
{
public:
	static gPlayerContainer *GetIF();

	gPlayerContainer(void);
	virtual ~gPlayerContainer(void);
public:
	PLAYER			m_MyPlayer;		// 나
	CHANNEL			m_MyChannel;

	ROOM			m_MyRoom;
	PLAYER			m_PlayerList[ROOMMAXPLAYER];

	CHARINFO		m_CharInfo[MAXCHARNUM];
	CHARIMGINFO		m_ImgInfo[MAXCHARNUM];
	char			m_script1[MAXCHARNUM][SCRIPT_CHAR_NUM], m_script2[MAXCHARNUM][SCRIPT_CHAR_NUM];
	
	GAMEPLAYER		m_MyGamePlayer;
	GAMEPLAYER		m_GPlayerList[ROOMMAXPLAYER];

	int				m_nAbsDrawlineX[ROOMMAXPLAYER];
	int				m_nAbsDrawlineY[ROOMMAXPLAYER];

	int				m_moveFoot[ROOMMAXPLAYER];
	int				m_movePosition[ROOMMAXPLAYER];

public:
	void			SetMyPlayer(PK_LOGIN_REP *rep);
	void			RefreshChannel(CHANNEL *channel);

	void			SetMyRoom(ROOM *room);
	void			SetPlayerList(PLAYER *list);

	void			SetMyGamePlayer(GAMEPLAYER* gp);
	void			SetGPList(GAMEPLAYER *list);

	bool			SetUp();
	void			Release();

	void			MainLoop();
	void			Draw();

	void			PacketalDrawFix();		
	// Packet을 통해서 싱크로나이즈 되면, m_nAbsDrawline 값들을 싱크로나이즈 해주는 함수
	void			SyncronizeToMap(int nInRoomIndex);
	// gMap class의 m_nAbsDrawline과 본 class의 m_nAbsDrawline 값을 싱크로나이즈 해주는 함수
	void			PutFootPosition(int nInRoomIndex,int nframe,int nCutline);
	// frame값과 nCutline (아마 nCutline은 15겠지?) 을 넣어서 gGameCore에서 캐릭터의 발을 결맞게 해주는 함수

private:
	bool			SetUpCharInfo();
	bool			SetUpCharImg();
	bool			SetupCharDesc();
};
