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
	gImage			ImgPic;				// ���� ���̹���. ui�����°�
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

	int				m_nNoDraw;			// �ش� index�� ĳ���� �� �׸�. default == -1
	int				m_nNoDraw2;

public:
	int				GetMyItemNum();		// �� ������ ����
	void			DeleteGamePlayer(int index);

	int				GetGPNum();			// ���� �÷��̾� ��
	int				GetMyGPIndex();		// ���� �÷��̾� �ε���
	int				GetCoupleIndex(int nTurn); //Ŀ�� ��������
	int				GetMyPIndex();		// �� �÷��̾� �ε���
	int				GetGPIndex(char* id); // id �� ���� �÷��̾� ã��
	bool			isTurn(int turn);				

	void			SetMyPlayer(PK_LOGIN_REP *rep);
	void			RefreshChannel(CHANNEL *channel);

	void			SetMyRoom(ROOM *room);
	void			SetPlayerList(PLAYER *list);

	void			SetMyGamePlayer(GAMEPLAYER* gp);
	void			SetGPList(GAMEPLAYER *list);

	bool			SetUp();
	void			Release();

	void			Clear();

	bool			Restore();

	void			MainLoop();
	void			MainLoop_Busing(gImage *bus, RECT *rcDest, RECT *rcSour, int turn);
	void			MainLoop_Warp(int charidx, int dY = 0);
	void			MainLoop_WarpList(int *dest, bool drawAll, int dY = 0);

	void			Draw();
	void			Draw_Busing(gImage *bus, RECT *rcDest, RECT *rcSour, int turn);
	void			Draw_Warp(int charidx, int dY);
	void			Draw_WarpList(int *dest, bool drawAll, int dY = 0);

	void			FootClear();			// �̵��Ϸ���� ��, ���ִ� ������ �ƴ� ��� �־, ������

	void			PacketalDrawFix();		
	// Packet�� ���ؼ� ��ũ�γ����� �Ǹ�, m_nAbsDrawline ������ ��ũ�γ����� ���ִ� �Լ�
	void			SyncronizeToMap(int nInRoomIndex, int pairIndex=-1);
	// gMap class�� m_nAbsDrawline�� �� class�� m_nAbsDrawline ���� ��ũ�γ����� ���ִ� �Լ�
	void			PutFootPosition(int nInRoomIndex,int nframe,int nCutline, int couple=-1);
	// frame���� nCutline (�Ƹ� nCutline�� 15����?) �� �־ gGameCore���� ĳ������ ���� ��°� ���ִ� �Լ�

	int				GetCharNumPos(int nPos);		// nPos�� �ִ� ĳ���� ���� return
	GAMEPLAYER*		GetPlayerByPos(int nPos);		// nPos�� �ִ� ĳ���� ���� return. �� ���� ����.!!!

	bool			IsNokdu(int nPlayerIndex);

private:
	bool			SetUpCharInfo();
	bool			SetUpCharImg();
	bool			SetupCharDesc();
};
