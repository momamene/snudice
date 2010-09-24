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
	m_spacor = 0;
	return true;
}

void gGameCore::MainLoop()
{
	if(m_spacor!=0)
		StepOn();

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
	int d1=0,d2=0, c1,c2;

	if(rep->Dice4_1) d1++; if(rep->Dice4_2) d1++;
	if(rep->Dice6_1) d2++; if(rep->Dice6_2) d2++;
	if(d1==1 && d2==1) c1=rep->Dice4_1, c2=rep->Dice6_1;
	else if(d1==2) c1=rep->Dice4_1, c2=rep->Dice4_2;
	else if(d2==2) c1=rep->Dice6_1, c2=rep->Dice6_2;
	else if(d1==1) c1=rep->Dice4_1, c2=0;
	else c1=0, c2=rep->Dice6_1;

	gDice::GetIF()->DiceStart(d1, d2, c1-1, c2-1);
}

void	gGameCore::Start (int spacor) {
	m_spacor = spacor;
	//gMap::GetIF()->posSpacor();
	gTimer::GetIF()->frameStart(500,60);
	StepStart();
}

void	gGameCore::Start (int spacor,int conPosX, int conPosY)
{
	gMap::GetIF()->posSetter(conPosX,conPosY);
	Start(spacor);
}

void	gGameCore::StepStart () {
	if(m_spacor>=0)
		gMap::GetIF()->posSpacor();
	else 
		gMap::GetIF()->posSpacor(true);
}

void	gGameCore::StepOn () {
	gTimer *gt = gTimer::GetIF();
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	int l_frame = gt->frame();
	if(gt->m_turn>0) {
		StepEnd();
	}
	else {
		gMap::GetIF()->posMover(l_frame,gt->m_frame);
		gPlayerContainer::GetIF()->SyncronizeToMap(m_nTurn);
	}	
}

void	gGameCore::StepEnd () {
	gTimer *gt = gTimer::GetIF();
	gMap::GetIF()->posStoper();
	if(m_spacor>0)
		m_spacor--;
	else if(m_spacor<0)
		m_spacor++;
	gt->m_turn--;
	if(m_spacor!=0) StepStart();
	else End();
}

void	gGameCore::End () {
	gTimer::GetIF()->frameEnd();
	gMap *gtc = gMap::GetIF();
	//pk_stepFinish_ask(gtc->m_xSpacePos,gtc->m_ySpacePos);
}
