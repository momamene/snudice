//------------------------------------------------------------------------------------
//	gBattleNetCore Class
//
//	2010. 08. 10	CoderK
//
//	로그인 되면 배틀넷 모드로.
//	방만들고 채팅하고, 방 들어가고.. 여러 메뉴있고 그런곳
//------------------------------------------------------------------------------------
#include "Core.h"
#include "coreconst.h"
#include "Image.h"
#include "ImgButton.h"
#include "ChannelUI.h"

enum BNET_BTN
{
	BBTN_ROOMMAKE,
	BBTN_ROOMJOIN,
	BBTN_DEVELOPER,				// ??? 만든이들 보기
//	BBTN_ROOMWAITING,			// 게임 플레이 전, 방 모습. 캐릭터 고르고......

	BBTN_END,
};

#define	BNET_FILE_ROOMMAKE			".\\Data\\BattleNet\\btn_roommake.img"
#define BNET_BTN_SIZE_ROOMMAKEW		124
#define BNET_BTN_SIZE_ROOMMAKEH		97
#define BNET_BTN_POS_ROOMMAKEX		38
#define BNET_BTN_POS_ROOMMAKEY		133

#define	BNET_FILE_ROOMJOIN			".\\Data\\BattleNet\\btn_roomjoin.img"
#define BNET_BTN_SIZE_ROOMJOINW		140
#define BNET_BTN_SIZE_ROOMJOINH		112
#define BNET_BTN_POS_ROOMJOINX		288
#define BNET_BTN_POS_ROOMJOINY		127

#define BNET_FILE_DEVEL				".\\Data\\BattleNet\\btn_developer.img"
#define BNET_BTN_SIZE_DEVEL_W		68
#define BNET_BTN_SIZE_DEVEL_H		74
#define BNET_BTN_POS_DEVEL_X		208
#define BNET_BTN_POS_DEVEL_Y		68

#define BNET_FILE_OUTLINE			".\\Data\\BattleNet\\outline.img"
#define BNET_POS_OUTLINE_X			0
#define BNET_POS_OUTLINE_Y			60
#define BNET_POS_OUTLINE_W			480
#define BNET_POS_OUTLINE_H			300


class gBattleNetCore : Core
{
public:
	static gBattleNetCore	*GetIF();
	
	gBattleNetCore();
	virtual ~gBattleNetCore();

public:
	gImage		m_ImgOutline;
	gImage		m_ImgBack;
	gImgButton	m_ImgBtn[BBTN_END];
	
	gChannelUI	m_ChannelUI;
	
public:
	// overriding
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	bool		Restore();
	
	//about mouse
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	// end overriding

	bool		PreTransMsg(MSG &msg);

	void		pk_channelrefresh_rep(PK_CHANNELREFRESH_REP* rep);
	void		pk_channelchange_rep(PK_CHANNELCHANGE_REP* rep);
};