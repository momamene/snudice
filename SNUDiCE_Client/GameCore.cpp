#include "GameCore.h"
#include "PopUp.h"
#include "Util.h"
#include "stringconst.h"
#include "MainWin.h"
#include "Map.h"
#include "Mouse.h"
#include "PlayerContainer.h"
#include "Server.h"
#include "Chat.h"
#include "Dice.h"

#define MINMOVE			20
#define WORLDX			2228
#define WORLDY			1520

static gGameCore s_GameCore;

gGameCore *gGameCore::GetIF()
{
	return &s_GameCore;
}

gGameCore::gGameCore(void)
{
}

gGameCore::~gGameCore(void)
{
}

bool gGameCore::SetUp()
{
	return true;
}

void gGameCore::MainLoop()
{
	MainLoopMouse();		// 마우스 스크롤
	
	Draw();
	gPlayerContainer::GetIF()->MainLoop();

	// popup 창 처리
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
	
	if(gMainWin::GetIF()->m_Keys[VK_SPACE])
	{
		SendMoveAsk();
		gMainWin::GetIF()->m_Keys[VK_SPACE] = false;
	}

	gChat::GetIF()->MainLoop();
	gDice::GetIF()->DiceThrow();
}

void gGameCore::MainLoopMouse()
{
	gMouse	*mouse = gMouse::GetIF();
	gMap	*map = gMap::GetIF();

	if(mouse->m_nPosX < MINMOVE)
	{
		if(map->m_nAbsDrawlineX > 0)
			map->m_nAbsDrawlineX -= 2;
	}
	if(mouse->m_nPosY < MINMOVE)
	{
		if(map->m_nAbsDrawlineY > 0)
			map->m_nAbsDrawlineY -= 2;
	}
	if(mouse->m_nPosX > WNDSIZEW - MINMOVE)
	{ 
		if(map->m_nAbsDrawlineX < WORLDX - WNDSIZEW + MINMOVE)
			map->m_nAbsDrawlineX += 2;
	}
	if(mouse->m_nPosY > WNDSIZEH - MINMOVE)
	{ // 수학적 공식
		if(map->m_nAbsDrawlineY < WORLDY + FULLY * 2 - WNDSIZEH + MINMOVE)
			map->m_nAbsDrawlineY += 2;
	}
}



void gGameCore::Draw()
{
	gMap::GetIF()->Draw();
}

void gGameCore::Release()
{

}

void gGameCore::OnLButtonDown()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();

	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnLbuttonDown(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
}

void gGameCore::OnLButtonUp()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();

	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnLbuttonUp(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
}

void gGameCore::OnMouseMove()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();

	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
}

void gGameCore::OnRButtonDown()
{

}

bool gGameCore::PreTransMsg(MSG &msg)
{
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

void gGameCore::SendMoveAsk()
{
	PK_MOVESTART_ASK		ask;

	strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyGamePlayer.szID);
	ask.nCurPos		= gPlayerContainer::GetIF()->m_MyGamePlayer.nPos;

	gServer::GetIF()->Send(PL_MOVESTART_ASK, sizeof ask, &ask);
}

void gGameCore::pk_movestart_rep(PK_MOVESTART_REP *rep)
{


	//gDice::GetIF()->DiceStart(bDice4, bDice6, rep->nDice4, rep->nDice6);
}