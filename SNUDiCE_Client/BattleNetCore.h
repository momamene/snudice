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
	BBTN_DEVELOPER,				// ??? �����̵� ����
	BBTN_OUT,

	BBTN_END,
};


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