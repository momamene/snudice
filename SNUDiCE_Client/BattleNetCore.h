//------------------------------------------------------------------------------------
//	gBattleNetCore Class
//
//	2010. 08. 10	CoderK
//
//	�α��� �Ǹ� ��Ʋ�� ����.
//	�游��� ä���ϰ�, �� ����.. ���� �޴��ְ� �׷���
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
	BBTN_ROOMWAITING,			// ���� �÷��� ��, �� ���. ĳ���� ����......

	BBTN_END,
};

#define	BNET_FILE_ROOMMAKE			".\\Data\\BattleNet\\btn_roommake.img"
#define BNET_BTN_SIZE_ROOMMAKEW		100
#define BNET_BTN_SIZE_ROOMMAKEH		30
#define BNET_BTN_POS_ROOMMAKEX		160
#define BNET_BTN_POS_ROOMMAKEY		100

#define	BNET_FILE_ROOMJOIN			".\\Data\\BattleNet\\btn_roomjoin.img"
#define BNET_BTN_SIZE_ROOMJOINW		100
#define BNET_BTN_SIZE_ROOMJOINH		30
#define BNET_BTN_POS_ROOMJOINX		160
#define BNET_BTN_POS_ROOMJOINY		150

class gBattleNetCore : Core
{
public:
	static gBattleNetCore	*GetIF();
	
	gBattleNetCore();
	virtual ~gBattleNetCore();

public:
	gImage		m_ImgBack;
	gImgButton	m_ImgBtn[BBTN_END];
	
	gChannelUI	m_ChannelUI;
	
public:
	// overriding
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();
	
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