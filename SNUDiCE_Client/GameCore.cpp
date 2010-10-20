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
#include "PopUp.h"
#include "RoomCore.h"

#define MINMOVE					10
#define WORLDX					2228
#define WORLDY					1520

#define GAME_BUS_FILE			".\\Data\\Interface\\game_bus.img"
#define GAME_BUS_SIZE_W			222
#define GAME_BUS_SIZE_H			154
#define GAME_BUS_FRAMEX			4
#define GAME_BUS_TERM_X			0
#define GAME_BUS_TERM_Y			-110

#define BUSMOVETICK				200 * 3
#define BUSMOVEFRAME			8
#define BUSBOARDTICK			500 * 3
#define BUSMOVELENGTH			160

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
	m_bNextTurnKeep = false;

	if(!m_ImgBus.Load(GAME_BUS_FILE))
		return false;

	return true;
}

void gGameCore::MainLoop()
{
	if(m_spacor!=0)
		if(m_bMoving)
			StepOn();
//		if(m_bBusing)			-> DrawBus에서 처리
//			BusStepOn();
	if(m_bScrolling)
		ScrollOn();

	if(m_bNextTurnKeep)
	{
		if(GetTickCount() - m_nKeepStart > 1000)
		{
			m_bNextTurnKeep = false;
			pk_nextturn_rep(&m_pkNext);
		}
	}


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
			case EPOP_DISCONNECT: // == EPOP_EXIT:
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
			map->m_nAbsDrawlineX -= 3;
	}
	if(mouse->m_nPosY < MINMOVE)
	{
		if(map->m_nAbsDrawlineY > 0)
			map->m_nAbsDrawlineY -= 3;
	}
	if(mouse->m_nPosX > WNDSIZEW - MINMOVE)
	{ 
		if(map->m_nAbsDrawlineX < WORLDX - WNDSIZEW + MINMOVE)
			map->m_nAbsDrawlineX += 3;
	}
	if(mouse->m_nPosY > WNDSIZEH - MINMOVE)
	{ // 수학적 공식
		if(map->m_nAbsDrawlineY < WORLDY + FULLY * 2 - WNDSIZEH + MINMOVE)
			map->m_nAbsDrawlineY += 3;
	}
}



void gGameCore::Draw()
{
	gMap::GetIF()->Draw();
	DrawBus();
	if(!m_bBusing)
		gPlayerContainer::GetIF()->MainLoop();

//	gChat::GetIF()->Draw();
	gUIGame::GetIF()->Draw();
}

void gGameCore::DrawBus()
{
	if(!m_bBusing)
		return;

	gTimer			 *gt = gTimer::GetIF();
	gMap			*map = gMap::GetIF();
	gPlayerContainer *pc = gPlayerContainer::GetIF();

	switch(m_busmode)
	{
		// 출발
		case BUS_COME:
			{
				int		dist = BUSMOVELENGTH / BUSMOVEFRAME;	// 1프레임당 가는 픽셀

				int		nPos		= pc->m_GPlayerList[m_nTurn].nPos;
				POINT	pt = map->ConToViewabs(nPos);
				pt.x	-= GAME_BUS_SIZE_W / 2;
				pt.x	+= GAME_BUS_TERM_X;
				pt.y	+= GAME_BUS_TERM_Y;
				pt.x	-= BUSMOVELENGTH;

				int		nFrame = gt->frame();

				if(nFrame >= BUSMOVEFRAME)
				{
					m_busmode = BUS_BOARD;
					gt->frameEnd();
					gt->frameStart(BUSBOARDTICK, 4);

					RECT	rcDest, rcSour;

					SetRect(&rcDest,
						pt.x + dist * (BUSMOVEFRAME - 1),
						pt.y,
						pt.x + dist * (BUSMOVEFRAME - 1) + GAME_BUS_SIZE_W,
						pt.y + GAME_BUS_SIZE_H);
					SetRect(&rcSour,
						0, 0, GAME_BUS_SIZE_W, GAME_BUS_SIZE_H);
					OffsetRect(&rcSour, GAME_BUS_SIZE_W * m_curframe, 0);

					pc->MainLoop_Busing(&m_ImgBus, &rcDest, &rcSour, m_nTurn);
					m_curframe = 0;
				}
				else
				{
					RECT	rcDest, rcSour;

					SetRect(&rcDest,
							pt.x + dist * nFrame,
							pt.y,
							pt.x + dist * nFrame + GAME_BUS_SIZE_W,
							pt.y + GAME_BUS_SIZE_H);
					SetRect(&rcSour,
							0, 0, GAME_BUS_SIZE_W, GAME_BUS_SIZE_H);
					m_curframe = nFrame % GAME_BUS_FRAMEX;
					OffsetRect(&rcSour, GAME_BUS_SIZE_W * m_curframe, 0);

					pc->MainLoop_Busing(&m_ImgBus, &rcDest, &rcSour, m_nTurn);
				} 
			}
			break;
		case BUS_BOARD:
			{
				int		nFrame = gt->frame();

				int		nPos		= pc->m_GPlayerList[m_nTurn].nPos;
				POINT	pt = map->ConToViewabs(nPos);
				pt.x	-= GAME_BUS_SIZE_W / 2;
				pt.x	+= GAME_BUS_TERM_X;
				pt.y	+= GAME_BUS_TERM_Y;

				if(nFrame >= 3)
				{
					gt->frameEnd();
					m_curframe = 0;
					gt->frameStart(BUSMOVETICK, BUSMOVEFRAME + 1);
					m_busmode = BUS_START;
				}
				if(nFrame >= 2)
				{
					pc->m_nNoDraw = m_nTurn;
				}
				if(nFrame >= 1)
				{
					pc->m_movePosition[m_nTurn] = 2; 
				}

				RECT	rcDest, rcSour;

				SetRect(&rcDest,
					pt.x,
					pt.y,
					pt.x + GAME_BUS_SIZE_W,
					pt.y + GAME_BUS_SIZE_H);
				SetRect(&rcSour,
					0, 0, GAME_BUS_SIZE_W, GAME_BUS_SIZE_H);
				OffsetRect(&rcSour, GAME_BUS_SIZE_W * m_curframe, 0);
				
				pc->MainLoop_Busing(&m_ImgBus, &rcDest, &rcSour, m_nTurn);
			}
			break;
		case BUS_START:
			{
				int		dist = BUSMOVELENGTH / BUSMOVEFRAME;	// 1프레임당 가는 픽셀

				int		nPos		= pc->m_GPlayerList[m_nTurn].nPos;
				POINT	pt = map->ConToViewabs(nPos);
				pt.x	-= GAME_BUS_SIZE_W / 2;
				pt.x	+= GAME_BUS_TERM_X;
				pt.y	+= GAME_BUS_TERM_Y;

				int		nFrame = gt->frame();

				if(nFrame >= BUSMOVEFRAME)
				{
					m_busmode = BUS_SCROLLSTART;
					gt->frameEnd();
					m_curframe = 0;
					ScrollStart(m_buspos);
				}
				else
				{
					RECT	rcDest, rcSour;

					SetRect(&rcDest,
						pt.x + dist * nFrame,
						pt.y,
						pt.x + dist * nFrame + GAME_BUS_SIZE_W,
						pt.y + GAME_BUS_SIZE_H);
					SetRect(&rcSour,
						0, 0, GAME_BUS_SIZE_W, GAME_BUS_SIZE_H);
					m_curframe = nFrame % GAME_BUS_FRAMEX;
					OffsetRect(&rcSour, GAME_BUS_SIZE_W * m_curframe, 0);
					
					pc->MainLoop_Busing(&m_ImgBus, &rcDest, &rcSour, m_nTurn);
				} 

			}
			break;

			// 스크롤
		case BUS_SCROLLSTART:
			{
				if(!m_bScrolling)
				{
					m_busmode = BUS_SCROLLEND;
					gt->frameStart(500, 2);
				}
				pc->MainLoop_Busing(NULL, NULL, NULL, m_nTurn);
			}
			break;
		case BUS_SCROLLEND:
			{
				int		nPos		= pc->m_GPlayerList[m_nTurn].nPos;
				POINT	pt = map->ConToViewabs(nPos);
				pt.x	-= GAME_BUS_SIZE_W / 2;
				pt.x	+= GAME_BUS_TERM_X;
				pt.y	+= GAME_BUS_TERM_Y;
				pt.x	-= BUSMOVELENGTH;

				int		nFrame = gt->frame();

				if(nFrame >= 1)
				{
					gTimer::GetIF()->frameStart(BUSMOVETICK, BUSMOVEFRAME + 1);
					m_curframe = 0;	
					m_busmode = BUS_COME2;
					pc->m_GPlayerList[m_nTurn].nPos = m_buspos;
					map->posSetter(m_buspos / LINEY, m_buspos % LINEY);
					pc->SyncronizeToMap(m_nTurn);
				}
				pc->MainLoop_Busing(NULL, NULL, NULL, m_nTurn);
			}
			break;

			// 도착
		case BUS_COME2:
			{
				int		dist = BUSMOVELENGTH / BUSMOVEFRAME;	// 1프레임당 가는 픽셀

				int		nPos		= pc->m_GPlayerList[m_nTurn].nPos;
				POINT	pt = map->ConToViewabs(nPos);
				pt.x	-= GAME_BUS_SIZE_W / 2;
				pt.x	+= GAME_BUS_TERM_X;
				pt.y	+= GAME_BUS_TERM_Y;
				pt.x	-= BUSMOVELENGTH;

				int		nFrame = gt->frame();

				if(nFrame >= BUSMOVEFRAME)
				{
					m_busmode = BUS_BOARD2;
					gt->frameEnd();
					gt->frameStart(BUSBOARDTICK, 4);

					RECT	rcDest, rcSour;

					SetRect(&rcDest,
						pt.x + dist * (BUSMOVEFRAME - 1),
						pt.y,
						pt.x + dist * (BUSMOVEFRAME - 1) + GAME_BUS_SIZE_W,
						pt.y + GAME_BUS_SIZE_H);
					SetRect(&rcSour,
						0, 0, GAME_BUS_SIZE_W, GAME_BUS_SIZE_H);
					OffsetRect(&rcSour, GAME_BUS_SIZE_W * m_curframe, 0);

					pc->MainLoop_Busing(&m_ImgBus, &rcDest, &rcSour, m_nTurn);
					m_curframe = 0;
				}
				else
				{
					RECT	rcDest, rcSour;

					SetRect(&rcDest,
						pt.x + dist * nFrame,
						pt.y,
						pt.x + dist * nFrame + GAME_BUS_SIZE_W,
						pt.y + GAME_BUS_SIZE_H);
					SetRect(&rcSour,
						0, 0, GAME_BUS_SIZE_W, GAME_BUS_SIZE_H);
					m_curframe = nFrame % GAME_BUS_FRAMEX;
					OffsetRect(&rcSour, GAME_BUS_SIZE_W * m_curframe, 0);
					
					pc->MainLoop_Busing(&m_ImgBus, &rcDest, &rcSour, m_nTurn);
				} 
			}
			break;
		case BUS_BOARD2:
			{
				int		nFrame = gt->frame();

				int		nPos		= pc->m_GPlayerList[m_nTurn].nPos;
				POINT	pt = map->ConToViewabs(nPos);
				pt.x	-= GAME_BUS_SIZE_W / 2;
				pt.x	+= GAME_BUS_TERM_X;
				pt.y	+= GAME_BUS_TERM_Y;

				if(nFrame >= 3)
				{
					gt->frameEnd();
					m_curframe = 0;
					gt->frameStart(BUSMOVETICK, BUSMOVEFRAME + 1);
					m_busmode = BUS_START2;
				}
				if(nFrame >= 1)
				{
					pc->m_nNoDraw = -1;
					pc->m_movePosition[m_nTurn] = 0; 
				}

				RECT	rcDest, rcSour;

				SetRect(&rcDest,
					pt.x,
					pt.y,
					pt.x + GAME_BUS_SIZE_W,
					pt.y + GAME_BUS_SIZE_H);
				SetRect(&rcSour,
					0, 0, GAME_BUS_SIZE_W, GAME_BUS_SIZE_H);
				OffsetRect(&rcSour, GAME_BUS_SIZE_W * m_curframe, 0);
				
				pc->MainLoop_Busing(&m_ImgBus, &rcDest, &rcSour, m_nTurn);
			}
			break;
		case BUS_START2:
			{
				int		dist = BUSMOVELENGTH / BUSMOVEFRAME;	// 1프레임당 가는 픽셀

				int		nPos		= pc->m_GPlayerList[m_nTurn].nPos;
				POINT	pt = map->ConToViewabs(nPos);
				pt.x	-= GAME_BUS_SIZE_W / 2;
				pt.x	+= GAME_BUS_TERM_X;
				pt.y	+= GAME_BUS_TERM_Y;

				int		nFrame = gt->frame();

				if(nFrame >= BUSMOVEFRAME)
				{
					gt->frameEnd(); 
					pc->FootClear();
					m_bBusing = false;

//					pc->m_GPlayerList[ m_nTurn ].nPos = map->m_xSpacePos * LINEY + map->m_ySpacePos;

					if(strcmp(pc->m_MyGamePlayer.szID, pc->m_GPlayerList[m_nTurn].szID) == 0)
						pc->m_MyGamePlayer.nPos = pc->m_GPlayerList[ m_nTurn ].nPos;

					// TODO : BusEnd의 패킷을 보냄

					PK_BUSMOVEEND_ASK   ask;

					ask.nDestPos = pc->m_GPlayerList[ m_nTurn ].nPos;
					strcpy(ask.szID, pc->m_MyGamePlayer.szID);

					gServer::GetIF()->Send(PL_BUSMOVEEND_ASK, sizeof ask, &ask);
				}
				else
				{
					RECT	rcDest, rcSour;

					SetRect(&rcDest,
						pt.x + dist * nFrame,
						pt.y,
						pt.x + dist * nFrame + GAME_BUS_SIZE_W,
						pt.y + GAME_BUS_SIZE_H);
					SetRect(&rcSour,
						0, 0, GAME_BUS_SIZE_W, GAME_BUS_SIZE_H);
					m_curframe = nFrame % GAME_BUS_FRAMEX;
					OffsetRect(&rcSour, GAME_BUS_SIZE_W * m_curframe, 0);
					
					pc->MainLoop_Busing(&m_ImgBus, &rcDest, &rcSour, m_nTurn);
				} 

			}
			break;
	}
}

void gGameCore::Release()
{
	m_ImgBus.Release();
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

	if(m_bMoving || m_bBusing)
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
	gUIGame::GetIF()->OnLButtonUp();
		
	if(m_bMoving || m_bBusing)
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
	if(m_bMoving || m_bBusing)
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
					gChat::GetIF()->MsgClear();
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
	// 이미 움직였음, 스크롤링 중임
	if(m_bMoved) //|| m_bScrolling)
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
	gDice::GetIF()->DiceStart(d1, d2, c1 - 1, c2 - 1, rep->nDist);
	m_bMoving = true;
}

void gGameCore::Start(int spacor)
{
	m_spacor = spacor;
	//gMap::GetIF()->posSpacor();
	gTimer::GetIF()->frameStart(400, 60);
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
	gPC->FootClear();

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
	if(m_bNextTurnKeep)
	{
		m_pkNext = *rep;
		m_nKeepStart = GetTickCount();
		return;
	}

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
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	int  nPos = gPC->m_GPlayerList[m_nTurn].nPos;

	if(rep->nDist == 0)
	{
		PK_BUSMOVEEND_ASK   ask;

		ask.nDestPos = gPC->m_GPlayerList[ m_nTurn ].nPos;
		strcpy(ask.szID, gPC->m_MyGamePlayer.szID);

		gServer::GetIF()->Send(PL_BUSMOVEEND_ASK, sizeof ask, &ask);
		m_bBusing = false;
	}
	else
	{
		m_bBusing = true;
		BusComeStart(nPos);
		m_buspos = gMap::GetIF()->Destination(nPos, rep->nDist);
		if(rep->nDist >= 0)
			gMap::GetIF()->posSpacor();
		else 
			gMap::GetIF()->posSpacor(true);
	}
}

void gGameCore::BusComeStart(int nPos)
{
	gMap				*map = gMap::GetIF();
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	map->posSetter(nPos / LINEY, nPos % LINEY);
	gTimer::GetIF()->frameStart(BUSMOVETICK, BUSMOVEFRAME + 1);

	m_curframe = 0;	

	m_busmode = BUS_COME;
}

void gGameCore::pk_gameplayerinfo_rep(PK_GAMEPLAYERINFO_REP *rep)
{
	gPlayerContainer::GetIF()->SetGPList(rep->list);
}

void gGameCore::pk_popinfo_rep(PK_POPINFO_REP *rep)
{
	m_bNextTurnKeep = true;
	gUIGame::GetIF()->SetPopInfo(rep);
}

void gGameCore::pk_gameend_rep(PK_GAMEEND_REP *rep)
{
	gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_EXIT, rep->szID, STR_17);
}

bool gGameCore::Restore()
{
	if(!m_ImgBus.Restore())
		return false;

	return true;
}