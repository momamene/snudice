//------------------------------------------------------------------------------------
//	gDataContainer Class
//
//	2010. 08. 02	CoderK
//
//	�÷��̾� �� ����Ÿ �ٷ���
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
	PLAYER			m_MyPlayer;		// ��
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
	// Packet�� ���ؼ� ��ũ�γ����� �Ǹ�, m_nAbsDrawline ������ ��ũ�γ����� ���ִ� �Լ�
	void			SyncronizeToMap(int nInRoomIndex);
	// gMap class�� m_nAbsDrawline�� �� class�� m_nAbsDrawline ���� ��ũ�γ����� ���ִ� �Լ�
	void			PutFootPosition(int nInRoomIndex,int nframe,int nCutline);
	// frame���� nCutline (�Ƹ� nCutline�� 15����?) �� �־ gGameCore���� ĳ������ ���� ��°� ���ִ� �Լ�

private:
	bool			SetUpCharInfo();
	bool			SetUpCharImg();
	bool			SetupCharDesc();
};
