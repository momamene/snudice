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
	gImage			ImgPic;				// 작은 얼굴이미지. ui에들어가는거
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

	int				m_nNoDraw;			// 해당 index인 캐릭터 안 그림. default == -1
	int				m_nNoDraw2;

public:
	int				GetMyItemNum();		// 내 아이템 갯수
	void			DeleteGamePlayer(int index);

	int				GetGPNum();			// 게임 플레이어 수
	int				GetMyGPIndex();		// 게임 플레이어 인덱스
	int				GetCoupleIndex(int nTurn); //커플 가져오기
	int				GetMyPIndex();		// 걍 플레이어 인덱스
	int				GetGPIndex(char* id); // id 로 게임 플레이어 찾기
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

	void			FootClear();			// 이동완료됬을 때, 서있는 프레임 아닐 경우 있어서, 막아줌

	void			PacketalDrawFix();		
	// Packet을 통해서 싱크로나이즈 되면, m_nAbsDrawline 값들을 싱크로나이즈 해주는 함수
	void			SyncronizeToMap(int nInRoomIndex, int pairIndex=-1);
	// gMap class의 m_nAbsDrawline과 본 class의 m_nAbsDrawline 값을 싱크로나이즈 해주는 함수
	void			PutFootPosition(int nInRoomIndex,int nframe,int nCutline, int couple=-1);
	// frame값과 nCutline (아마 nCutline은 15겠지?) 을 넣어서 gGameCore에서 캐릭터의 발을 결맞게 해주는 함수

	int				GetCharNumPos(int nPos);		// nPos에 있는 캐릭터 갯수 return
	GAMEPLAYER*		GetPlayerByPos(int nPos);		// nPos에 있는 캐릭터 정보 return. 단 나는 제외.!!!

	bool			IsNokdu(int nPlayerIndex);

private:
	bool			SetUpCharInfo();
	bool			SetUpCharImg();
	bool			SetupCharDesc();
};
