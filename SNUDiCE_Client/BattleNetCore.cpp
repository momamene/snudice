#include "PlayerContainer.h"
#include "BattleNetCore.h"
#include "RoomCore.h"
#include "Chat.h"
#include "Server.h"
#include "PopUp.h"
#include "Mouse.h"
#include "stringconst.h"
#include "TopUI.h"

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

	if(!m_ImgOutline.Load(BNET_FILE_OUTLINE))
		return false;

	return true;
}

void gBattleNetCore::MainLoop()
{
	Draw();

	// popup Ã¢ Ã³¸®
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

	gChat::GetIF()->MainLoop();
}

void gBattleNetCore::Draw()
{
	m_ImgBack.Draw(BNET_POS_BACK_X, BNET_POS_BACK_Y);
	m_ImgOutline.Draw(BNET_POS_OUTLINE_X, BNET_POS_OUTLINE_Y);

	gTopUI::GetIF()->Draw();
	gChat::GetIF()->Draw();
	m_ChannelUI.Draw();

	int			i;

	for(i = 0; i < BBTN_END; i++)
		m_ImgBtn[i].Draw();
	
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
		//gMainWin::GetIF()->m_eCoreMode	= ECM_ROOMJOIN;
		//m_ImgBtn[BBTN_ROOMJOIN].m_eBtnMode	= EBM_NONE;
		// get roomlist
		// send ask_roomlist
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
	gMouse		*mouse = gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();

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