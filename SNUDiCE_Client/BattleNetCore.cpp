#include "PlayerContainer.h"
#include "BattleNetCore.h"
#include "Chat.h"
#include "Server.h"
#include "PopUp.h"
#include "Mouse.h"
#include "stringconst.h"

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
}

void gBattleNetCore::Draw()
{
	m_ImgBack.Draw();
	gChat::GetIF()->Draw();
	m_ChannelUI.Draw();
	
}

void gBattleNetCore::Release()
{
	m_ChannelUI.Release();
	m_ImgBack.Release();
}

void gBattleNetCore::OnLButtonDown()
{
	gMouse		*mouse = gMouse::GetIF();

	if(m_ChannelUI.isPointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		m_ChannelUI.OnLButtonDown(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
}

void gBattleNetCore::OnLButtonUp()
{
	gMouse		*mouse = gMouse::GetIF();

	if(m_ChannelUI.isPointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		m_ChannelUI.OnLButtonUp(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
}

void gBattleNetCore::OnMouseMove()
{
	gMouse		*mouse = gMouse::GetIF();

	if(m_ChannelUI.isPointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		m_ChannelUI.OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);
		return;
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
	char		szTemp[128];
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