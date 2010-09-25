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
#include "UIGame.h"

#define MINMOVE			5
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
	m_spacor	= 0;
	m_bMoved	= false;
	m_bMoving	= false;
	m_bScrolling = false;
	m_bBusSel	= false;
	m_bBusing   = false;

	return true;
}

void gGameCore::MainLoop()
{
	if(m_spacor!=0)
		if(m_bMoving)
			StepOn();
		if(m_bBusing)
			BusStepOn();
	if(m_bScrolling)
		ScrollOn();


	gUIGame::GetIF()->MainLoop();

	MainLoopMouse();		// 마우스 스크롤
	
	Draw();
	
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
	if(!gMainWin::GetIF()->m_bActive)
		return;
	if(gDice::GetIF()->m_start)
		return;

	gMouse	*mouse	= gMouse::GetIF();
	gMap	*map	= gMap::GetIF();

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
	gPlayerContainer::GetIF()->MainLoop();
	gChat::GetIF()->Draw();
	gUIGame::GetIF()->Draw();
}

void gGameCore::Release()
{

}

void gGameCore::OnLButtonDown()
{
	gMouse				*mouse	= gMouse::GetIF();
	gChat				*chat	= gChat::GetIF();
	gPlayerContainer	*gPC	= gPlayerContainer::GetIF();

	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnLbuttonDown(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
	if(gUIGame::GetIF()->OnLButtonDown())
		return;

	if(m_bMoving)
		return;

	if(m_bBusSel)
	{
		POINT	ptTemp;
		
		ptTemp.x = mouse->m_nPosX;
		ptTemp.y = mouse->m_nPosY;

		int		nPos = gMap::GetIF()->viewabsToCon(ptTemp);

		if(gMap::GetIF()->tileMap[nPos].tileType == TY_BUS)
		{
			PK_BUSMOVESELECT_ASK		ask;

			ask.nPos = nPos;
			strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
			
			gServer::GetIF()->Send(PL_BUSMOVESELECT_ASK, sizeof ask, &ask);
			m_bBusSel = false;
		}
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
	if(m_bMoving)
		return;
}

void gGameCore::OnMouseMove()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();
	gUIGame		*ui		= gUIGame::GetIF();


	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}

	ui->OnMouseMove();

}

void gGameCore::OnRButtonDown()
{
	gUIGame		*ui		= gUIGame::GetIF();

	ui->OnRButtonDown();
	if(m_bMoving)
		return;
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
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	// 내 차례가 아님
	if(strcmp(gPC->m_MyGamePlayer.szID, gPC->m_GPlayerList[m_nTurn].szID) != 0)
		return;
	if(m_bMoved)		// 움직이는 중임
		return;

	PK_MOVESTART_ASK		ask;

	strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyGamePlayer.szID);
	ask.nCurPos		= gPlayerContainer::GetIF()->m_MyGamePlayer.nPos;

	gServer::GetIF()->Send(PL_MOVESTART_ASK, sizeof ask, &ask);

	m_bMoved = true;
}

void gGameCore::pk_movestart_rep(PK_MOVESTART_REP *rep)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	
	if(m_bMoving)
		return;

	int d1 = 0, d2 = 0;		// 4 ,6 면체 갯수
	int	c1, c2;				// 주사위 1,2의 눈

	if(rep->Dice4_1)
		d1++;
	if(rep->Dice4_2)
		d1++;

	if(rep->Dice6_1)
		d2++;
	if(rep->Dice6_2)
		d2++;


	if(d1 == 1 && d2 == 1)
		c1 = rep->Dice4_1, c2 = rep->Dice6_1;
	else if(d1 == 2)
		c1 = rep->Dice4_1, c2 = rep->Dice4_2;
	else if(d2 == 2)
		c1 = rep->Dice6_1, c2 = rep->Dice6_2;
	else if(d1 == 1)
		c1 = rep->Dice4_1, c2 = 0;
	else
		c1 = 0, c2 = rep->Dice6_1;

	int ntPos = gPC->m_GPlayerList[ gGameCore::GetIF()->m_nTurn ].nPos;
	gMap::GetIF()->posSetter(ntPos / LINEY, ntPos % LINEY);
	gDice::GetIF()->DiceStart(d1, d2, c1 - 1, c2 - 1);
	m_bMoving = true;
}

void gGameCore::Start(int spacor)
{
	m_spacor = spacor;
	//gMap::GetIF()->posSpacor();
	gTimer::GetIF()->frameStart(500,60);
	StepStart();
}

void gGameCore::Start(int spacor,int conPosX, int conPosY)
{
	gMap::GetIF()->posSetter(conPosX,conPosY);
	Start(spacor);
}

void gGameCore::StepStart()
{
	if(m_spacor>=0)
		gMap::GetIF()->posSpacor();
	else 
		gMap::GetIF()->posSpacor(true);
}

void gGameCore::StepOn()
{
	gTimer				*gt = gTimer::GetIF();
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();


	int l_frame = gt->frame();

	if(gt->m_turn > 0)
	{
		StepEnd();
	}
	else
	{
		gMap::GetIF()->posMover(l_frame, gt->m_frame);
		gPC->SyncronizeToMap(m_nTurn);
		gPC->PutFootPosition(m_nTurn,l_frame,60/4);
	}	
}

void gGameCore::StepEnd()
{
	gTimer *gt = gTimer::GetIF();

	gMap::GetIF()->posStoper();

	if(m_spacor > 0)
		m_spacor--;
	else if(m_spacor < 0)
		m_spacor++;

	gt->m_turn--;

	if(m_spacor!=0)
		StepStart();
	else
		End();
}

void gGameCore::End()		// 이동 끝남
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();
	gMap				*map = gMap::GetIF();

	gTimer::GetIF()->frameEnd(); 

	gPC->m_GPlayerList[ m_nTurn ].nPos = map->m_xSpacePos * LINEY + map->m_ySpacePos;

	if(strcmp(gPC->m_MyGamePlayer.szID, gPC->m_GPlayerList[m_nTurn].szID) == 0)
		gPC->m_MyGamePlayer.nPos = gPC->m_GPlayerList[ m_nTurn ].nPos;

	PK_MOVEEND_ASK			ask;

	ask.nDestPos = gPC->m_GPlayerList[ m_nTurn ].nPos;
	strcpy(ask.szID, gPC->m_MyGamePlayer.szID);

	gServer::GetIF()->Send(PL_MOVEEND_ASK, sizeof ask, &ask);

	m_bMoving = false;
	

	//pk_stepFinish_ask(gtc->m_xSpacePos,gtc->m_ySpacePos);
}

void gGameCore::pk_nextturn_rep(PK_NEXTTURN_REP *rep)
{
	if(m_nTurn == rep->nNowTurn)
	{
		m_nTurn		= rep->nNextTurn;
		m_bMoved	= false;
	}
	
	int nTempPos = gPlayerContainer::GetIF()->m_GPlayerList[m_nTurn].nPos;
	ScrollStart(nTempPos);
}

void gGameCore::ScrollStart(int nPos)
{
	m_bScrolling = true;
	gMap::GetIF()->posSpacor(nPos/LINEY,nPos%LINEY);
	gTimer::GetIF()->frameStart(1000,60);
}

void gGameCore::ScrollOn()
{
	gTimer				*gt = gTimer::GetIF();
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();


	int l_frame = gt->frame();

	if(gt->m_turn > 0)
	{
		ScrollEnd();
	}
	else
	{
		gMap::GetIF()->posMover(l_frame, gt->m_frame);
	}	
}

void gGameCore::ScrollEnd()
{
	m_bScrolling = false;
	gMap::GetIF()->posStoper();
}

void gGameCore::pk_busmovechoose_rep(PK_BUSMOVECHOOSE_REP *rep)
{
	if(m_bBusSel)
		return;

	if(m_nTurn == rep->nNowTurn)
		m_bBusSel = true;
}

// 상우의  주요 작업 부분 시작

void gGameCore::pk_busmovestart_rep(PK_BUSMOVESTART_REP *rep)
{
	m_bMoving = true;

	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	int  nPos = gPC->m_GPlayerList[m_nTurn].nPos;
	m_bBusing = true;
	BusStart(rep->nDist,nPos/LINEY,nPos%LINEY);
}

void gGameCore::BusStart(int spacor)
{
	m_spacor = spacor;
	//gMap::GetIF()->posSpacor();
	gTimer::GetIF()->frameStart(250,60);
	BusStepStart();
}

void gGameCore::BusStart(int spacor,int conPosX, int conPosY)
{
	gMap::GetIF()->posSetter(conPosX,conPosY);
	BusStart(spacor);
}

void gGameCore::BusStepStart()
{
	if(m_spacor>=0)
		gMap::GetIF()->posSpacor();
	else 
		gMap::GetIF()->posSpacor(true);
}

void gGameCore::BusStepOn()
{
	gTimer    *gt = gTimer::GetIF();
	gPlayerContainer *gPC = gPlayerContainer::GetIF();


	int l_frame = gt->frame();

	if(gt->m_turn > 0)
	{
		BusStepEnd();
	}
	else
	{
		gMap::GetIF()->posMover(l_frame, gt->m_frame);
		gPC->SyncronizeToMap(m_nTurn);
		gPC->PutFootPosition(m_nTurn,l_frame,60/4);
	} 
}

void gGameCore::BusStepEnd()
{
	gTimer *gt = gTimer::GetIF();

	gMap::GetIF()->posStoper();

	if(m_spacor > 0)
		m_spacor--;
	else if(m_spacor < 0)
		m_spacor++;

	gt->m_turn--;

	if(m_spacor!=0)
		BusStepStart();
	else
		BusEnd();
}

void gGameCore::BusEnd()  // 이동 끝남
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	gMap    *map = gMap::GetIF();

	gTimer::GetIF()->frameEnd(); 
	m_bBusing = false;

	gPC->m_GPlayerList[ m_nTurn ].nPos = map->m_xSpacePos * LINEY + map->m_ySpacePos;

	if(strcmp(gPC->m_MyGamePlayer.szID, gPC->m_GPlayerList[m_nTurn].szID) == 0)
		gPC->m_MyGamePlayer.nPos = gPC->m_GPlayerList[ m_nTurn ].nPos;

	// TODO : BusEnd의 패킷을 보냄

	PK_BUSMOVEEND_ASK   ask;

	ask.nDestPos = gPC->m_GPlayerList[ m_nTurn ].nPos;
	strcpy(ask.szID, gPC->m_MyGamePlayer.szID);

	gServer::GetIF()->Send(PL_BUSMOVEEND_ASK, sizeof ask, &ask);

	m_bBusing = false;
	//pk_stepFinish_ask(gtc->m_xSpacePos,gtc->m_ySpacePos);
}

// - 끝 - 