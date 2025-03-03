#include "PlayerContainer.h"
#include "BattleNetCore.h"
#include "RoomCore.h"
#include "Chat.h"
#include "Server.h"
#include "PopUp.h"
#include "Mouse.h"
#include "stringconst.h"
#include "TopUI.h"


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

#define BNET_FILE_OUT				".\\Data\\BattleNet\\btn_out.img"
#define BNET_BTN_SIZE_OUT_W			104
#define BNET_BTN_SIZE_OUT_H			91
#define BNET_BTN_POS_OUT_X			193
#define BNET_BTN_POS_OUT_Y			265

#define BNET_FILE_OUTLINE			".\\Data\\BattleNet\\outline.img"
#define BNET_POS_OUTLINE_X			0
#define BNET_POS_OUTLINE_Y			60
#define BNET_POS_OUTLINE_W			480
#define BNET_POS_OUTLINE_H			300


static gBattleNetCore	s_BattleNetCore;

gBattleNetCore *gBattleNetCore::GetIF()
{
	return &s_BattleNetCore;
}

gBattleNetCore::gBattleNetCore()
{

}

gBattleNetCore::~gBattleNetCore()
{

}

bool gBattleNetCore::SetUp()
{
	if(!m_ImgBack.Load(BNET_FILE_BACK))
		return false;

	if(!m_ChannelUI.SetUp())
		return false;

	RECT	rcDest;

	SetRect(&rcDest,
			BNET_BTN_POS_ROOMMAKEX,
			BNET_BTN_POS_ROOMMAKEY,
			BNET_BTN_POS_ROOMMAKEX + BNET_BTN_SIZE_ROOMMAKEW,
			BNET_BTN_POS_ROOMMAKEY + BNET_BTN_SIZE_ROOMMAKEH );
	if(!m_ImgBtn[BBTN_ROOMMAKE].SetUp(BNET_FILE_ROOMMAKE, false, rcDest))
		return false;

	SetRect(&rcDest,
		BNET_BTN_POS_ROOMJOINX,
		BNET_BTN_POS_ROOMJOINY,
		BNET_BTN_POS_ROOMJOINX + BNET_BTN_SIZE_ROOMJOINW,
		BNET_BTN_POS_ROOMJOINY + BNET_BTN_SIZE_ROOMJOINH );
	if(!m_ImgBtn[BBTN_ROOMJOIN].SetUp(BNET_FILE_ROOMJOIN, false, rcDest))
		return false;

	SetRect(&rcDest,
		BNET_BTN_POS_DEVEL_X,
		BNET_BTN_POS_DEVEL_Y,
		BNET_BTN_POS_DEVEL_X + BNET_BTN_SIZE_DEVEL_W,
		BNET_BTN_POS_DEVEL_Y + BNET_BTN_SIZE_DEVEL_H );
	if(!m_ImgBtn[BBTN_DEVELOPER].SetUp(BNET_FILE_DEVEL, false, rcDest))
		return false;

	SetRect(&rcDest,
		BNET_BTN_POS_OUT_X,
		BNET_BTN_POS_OUT_Y,
		BNET_BTN_POS_OUT_X + BNET_BTN_SIZE_OUT_W,
		BNET_BTN_POS_OUT_Y + BNET_BTN_SIZE_OUT_H );
	if(!m_ImgBtn[BBTN_OUT].SetUp(BNET_FILE_OUT, false, rcDest))
		return false;

	if(!m_ImgOutline.Load(BNET_FILE_OUTLINE))
		return false;

	return true;
}

void gBattleNetCore::MainLoop()
{
	Draw();

	// popup â ó��
	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->MainLoop();
		return;
	}

	if(gPopUp::GetIF()->m_bReturn)
	{
		switch(gPopUp::GetIF()->m_ePop)
		{
			case EPOP_DISCONNECT:
				switch(gPopUp::GetIF()->m_eBtnClk)
				{
					case ECLK_OK:
						gMainWin::GetIF()->Exit();
						break;
				}
				break;
		}
		gPopUp::GetIF()->m_bReturn = false;
	}

	if(gMainWin::GetIF()->m_Keys[VK_RETURN])
	{
		gChat::GetIF()->m_Edit.SetFocusOn();
		gMainWin::GetIF()->m_Keys[VK_RETURN] = false;
	}
	else if(gMainWin::GetIF()->m_Keys[VK_ESCAPE])
	{
		//gTopUI::GetIF()->OnLButtonDown_Back();
		gMainWin::GetIF()->m_Keys[VK_ESCAPE] = false;
		return;
	}

	gChat::GetIF()->MainLoop();
}

void gBattleNetCore::Draw()
{
	m_ImgBack.Draw(BNET_POS_BACK_X, BNET_POS_BACK_Y);
	m_ImgOutline.Draw(BNET_POS_OUTLINE_X, BNET_POS_OUTLINE_Y);

	gChat::GetIF()->Draw();
	m_ChannelUI.Draw();

	int			i;

	for(i = 0; i < BBTN_END; i++)
		m_ImgBtn[i].Draw();

	gTopUI::GetIF()->Draw();
}

void gBattleNetCore::Release()
{
	m_ChannelUI.Release();
	m_ImgBack.Release();
	m_ImgOutline.Release();

	int		i;

	for(i = 0; i < BBTN_END; i++)
		m_ImgBtn[i].Release();

}

void gBattleNetCore::OnLButtonDown()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();
	gTopUI		*top	= gTopUI::GetIF();

	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnLbuttonDown(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}

	if(m_ChannelUI.isPointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		m_ChannelUI.OnLButtonDown(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}

	if(top->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		top->OnLButtonDown(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}

	if(m_ImgBtn[BBTN_ROOMMAKE].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		gMainWin::GetIF()->m_eCoreMode	= ECM_ROOMMAKE;
		gRoomCore::GetIF()->m_eRoom		= ERM_MAKE;
		gRoomCore::GetIF()->m_EditRoom.SetFocusOn();
		m_ImgBtn[BBTN_ROOMMAKE].m_eBtnMode	= EBM_NONE;
		return;
	}
	else if(m_ImgBtn[BBTN_ROOMJOIN].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		PK_ROOMLIST_ASK		ask;

		strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);
		ask.nPage = 0;

		gServer::GetIF()->Send(PL_ROOMLIST_ASK, sizeof ask, &ask);

		m_ImgBtn[BBTN_ROOMJOIN].m_eBtnMode	= EBM_NONE;
		gMainWin::GetIF()->m_eCoreMode	= ECM_ROOMJOIN;
		gRoomCore::GetIF()->m_eRoom		= ERM_JOIN;
		gRoomCore::GetIF()->m_bEnteringPass = false;
		return;
	}
	else if(m_ImgBtn[BBTN_OUT].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		PK_GOLOGIN_ASK		ask;

		strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);
		gServer::GetIF()->Send(PL_GOLOGIN_ASK, sizeof(ask), &ask);

		chat->MsgStackClear();
		gMainWin::GetIF()->m_eCoreMode = ECM_LOGIN;		

		return;
	}
}

void gBattleNetCore::OnLButtonUp()
{
	gMouse		*mouse = gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();

	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnLbuttonUp(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}

	if(m_ChannelUI.isPointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		m_ChannelUI.OnLButtonUp(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
}

void gBattleNetCore::OnMouseMove()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();
	gTopUI		*top	= gTopUI::GetIF();

	if(top->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		top->OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}

	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}

	if(m_ChannelUI.isPointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		m_ChannelUI.OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
	int			i;
	
	for(i = 0; i < BBTN_END; i++)
	{
		if(m_ImgBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_ImgBtn[i].m_eBtnMode = EBM_HOVER;
		else
			m_ImgBtn[i].m_eBtnMode = EBM_NONE;
	}
}

void gBattleNetCore::OnRButtonDown()
{
	gMouse		*mouse = gMouse::GetIF();
	gTopUI		*top	= gTopUI::GetIF();

	top->OnRButtonDown(mouse->m_nPosX, mouse->m_nPosY);
	if(m_ChannelUI.isPointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		m_ChannelUI.OnRButtonDown(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
}

bool gBattleNetCore::PreTransMsg(MSG &msg)
{
//	char		szTemp[128];
	HWND		hChat = gChat::GetIF()->m_Edit.m_hEdit;

	if(msg.hwnd == hChat)
	{
		if(!gServer::GetIF()->m_bConnect)
			return true;

		if(msg.message == WM_KEYDOWN)
		{
			if(gPopUp::GetIF()->isPopUp())
			{
				if(msg.wParam == VK_RETURN)
					gPopUp::GetIF()->DoEnter();

				return true;
			}

			switch(msg.wParam)
			{
			case VK_RETURN:
				SetFocus(gMainWin::GetIF()->m_hWnd);
				gChat::GetIF()->SendMsg();
				return true;
			case VK_TAB:
				return true;
			case VK_ESCAPE:
				SetFocus(gMainWin::GetIF()->m_hWnd);
				gChat::GetIF()->MsgClear();
				return true;
			}
		}
	}

	return false;
}

void gBattleNetCore::pk_channelrefresh_rep(PK_CHANNELREFRESH_REP* rep)
{
	gPlayerContainer::GetIF()->RefreshChannel(&rep->channel);
}

void gBattleNetCore::pk_channelchange_rep(PK_CHANNELCHANGE_REP* rep)
{
	switch(rep->error)
	{
		case ECE_CHANNELISOVER:
			gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_8);
			break;
		case ECE_SUCCESS:
			gPlayerContainer::GetIF()->RefreshChannel(&rep->channel);
			m_ChannelUI.m_eChannel = CM_CHANNEL;
			break;
	}
}

bool gBattleNetCore::Restore()
{
	if(!m_ImgOutline.Restore())
		return false;
	if(!m_ImgBack.Restore())
		return false;

	int		i;

	for(i = 0; i < BBTN_END; i++)
		if(!m_ImgBtn[i].Restore())
			return false;

	if(!m_ChannelUI.Restore())
		return false;

	return true;
}