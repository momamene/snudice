#include "BattleNetCore.h"
#include "Chat.h"
#include "Server.h"
#include "PopUp.h"

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
	
}

void gBattleNetCore::Release()
{
	m_ImgBack.Release();

}

void gBattleNetCore::OnLButtonDown()
{

}

void gBattleNetCore::OnLButtonUp()
{


}

void gBattleNetCore::OnMouseMove()
{

}

void gBattleNetCore::OnRButtonDown()
{

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