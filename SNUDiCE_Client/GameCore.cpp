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
#include "PlaySoundCore.h"

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

#define MAPSCROLLSPEED			10 // 마우스로 화면 스크롤 속도
#define MAPSCROLLTICK			50

#define WARPTICK				500 * 3
#define WARPFRAME				8
#define WARPDIST				10
#define SLEEPTIMEMAX			50000	//최대 잠수 시간:10초 

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
	m_bWarping	= false;
	m_bWarpingList = false;

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

	gUIGame::GetIF()->MainLoop();	//쓸데없음...

	MainLoopMouse();		// 마우스 스크롤
	
	Draw();
	
	// popup 창 처리
 	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->MainLoop();
//		if(GetTickCount - SLEEPTIMEMAX >= m_turnTime_CoupleAsk) 
		return;
	}

	if(gPopUp::GetIF()->m_bReturn)
	{
		switch(gPopUp::GetIF()->m_ePop)
		{
			//방나가고돌아오기수정
			case EPOP_ROOMBACK: // 게임 끝:
				switch(gPopUp::GetIF()->m_eBtnClk)
				{
					case ECLK_OK:
						gMainWin::GetIF()->m_eCoreMode = ECM_ROOM;//클라이언트에서룸상태변경
						gPlaySoundCore::GetIF()->StartBGM(BGM_FILE_0);
						break;
				}
				break;
				//수정 ; 아직 건들지 않고 있음.
			case EPOP_DISCONNECT:
				switch(gPopUp::GetIF()->m_eBtnClk)
				{
					case ECLK_OK:
						gMainWin::GetIF()->Exit();
						break;
				}
				break;
			// couple
			case EPOP_COUPLEASK:
				switch(gPopUp::GetIF()->m_eBtnClk)
				{
					case ECLK_OK:
						{
							PK_ANSCOUPLE_ASK	ask;
							ask.bYes = true;
							gServer::GetIF()->Send(PL_ANSCOUPLE_ASK, sizeof(ask), &ask);
						}
						break;
					case ECLK_CANCEL:
						{
							PK_ANSCOUPLE_ASK	ask;
							ask.bYes = false;
							gServer::GetIF()->Send(PL_ANSCOUPLE_ASK, sizeof(ask), &ask);
						}
						break;
				}
		}
		gPopUp::GetIF()->m_bReturn = false;
	}

	if(gMainWin::GetIF()->m_Keys[VK_RETURN])
	{
		gChat::GetIF()->m_Edit.SetFocusOn();
		gMainWin::GetIF()->m_Keys[VK_RETURN] = false;
	}
	
	if((int)GetTickCount() - SLEEPTIMEMAX >= m_turnTime || gMainWin::GetIF()->m_Keys[VK_SPACE])
	{
		SendMoveAsk();
		gMainWin::GetIF()->m_Keys[VK_SPACE] = false;
	}

	gChat::GetIF()->MainLoop();
	gDice::GetIF()->DiceThrow();

	if(GetTickCount() - m_turnTime_Bus>=SLEEPTIMEMAX && m_bBusSel) {
		PK_BUSMOVESELECT_ASK		ask;
		gPlayerContainer *gPC = gPlayerContainer::GetIF();
		int nPos = gPC->m_GPlayerList[ m_nTurn ].nPos;

		ask.nPos = nPos;
		strcpy(ask.szID, gPC->m_MyGamePlayer.szID);

		gServer::GetIF()->Send(PL_BUSMOVESELECT_ASK, sizeof ask, &ask);
		m_bBusSel = false;
	}
//////////////////////////////////////////////////////////////////////////////버스 잠수
}

void gGameCore::MainLoopMouse()
{
	if(!gMainWin::GetIF()->m_bActive)
		return;
	if(gDice::GetIF()->m_start)
		return;

	gMouse	*mouse	= gMouse::GetIF();
	gMap	*map	= gMap::GetIF();

	static DWORD tick = GetTickCount();

	if(GetTickCount() - tick > MAPSCROLLTICK)
	{
		if(mouse->m_nPosX < MINMOVE)
		{
			if(map->m_nAbsDrawlineX > 0)
				map->m_nAbsDrawlineX -= MAPSCROLLSPEED;
		}
		if(mouse->m_nPosY < MINMOVE)
		{
			if(map->m_nAbsDrawlineY > 0)
				map->m_nAbsDrawlineY -= MAPSCROLLSPEED;
		}
		if(mouse->m_nPosX > WNDSIZEW - MINMOVE)
		{ 
			if(map->m_nAbsDrawlineX < WORLDX - WNDSIZEW + MINMOVE)
				map->m_nAbsDrawlineX += MAPSCROLLSPEED;
		}
		if(mouse->m_nPosY > WNDSIZEH - MINMOVE)
		{
			if(map->m_nAbsDrawlineY < WORLDY + FULLY * 2 - WNDSIZEH + MINMOVE)
				map->m_nAbsDrawlineY += MAPSCROLLSPEED;
		}
		tick = GetTickCount();
	}
}



void gGameCore::Draw()
{
	gMap::GetIF()->Draw();

	if(m_bBusing)
		DrawBus();
	else if(m_bWarping)
		DrawWarp();
	else if(m_bWarpingList)
		DrawWarpList();
	else
		gPlayerContainer::GetIF()->MainLoop();

//	gChat::GetIF()->Draw();
	gUIGame::GetIF()->Draw();
}

void gGameCore::DrawWarp()
{
	if(!m_bWarping)
		return;

	gTimer				*gt = gTimer::GetIF();
	gPlayerContainer	*pc = gPlayerContainer::GetIF();
	gMap				*map = gMap::GetIF();

	switch(m_warp)
	{
		case WARP_DISAPPEAR:
			{
				int		nFrame = gt->frame();

				if(nFrame >= WARPFRAME)
				{
					m_warp = WARP_SCROLLSTART;
					gt->frameEnd();
					ScrollStart(m_warpDest);
					pc->m_nNoDraw = m_warpCharIdx;
				}
				pc->MainLoop_Warp(m_warpCharIdx, -WARPDIST*nFrame);
			}
			break;
		case WARP_SCROLLSTART:
			{
				if(!m_bScrolling)
				{
					m_warp = WARP_SCROLLEND;
					gt->frameStart(500, 2);
				}
				pc->MainLoop_Warp(m_warpCharIdx);
			}
			break;
		case WARP_SCROLLEND:
			{
				int		nFrame = gt->frame();

				if(nFrame >= 1)
				{
					gt->frameEnd();
					gt->frameStart(WARPTICK, WARPFRAME + 1);
					m_warp = WARP_APPEAR;

					pc->m_GPlayerList[m_warpCharIdx].nPos = m_warpDest;
					if(strcmp(pc->m_MyGamePlayer.szID, pc->m_GPlayerList[m_warpCharIdx].szID) == 0)
						pc->m_MyGamePlayer.nPos = pc->m_GPlayerList[m_warpCharIdx].nPos;

					map->posSetter(m_warpDest / LINEY, m_warpDest % LINEY);
					pc->SyncronizeToMap(m_warpCharIdx);
				}
				pc->MainLoop_Warp(m_warpCharIdx);
			}
			break;
		case WARP_APPEAR:
			{
				int		nFrame = gt->frame();

				if(nFrame >= WARPFRAME)
				{
					gt->frameEnd();
					m_bWarping = false;

					PK_WARPEND_ASK		ask;

					strcpy(ask.szID, pc->m_MyGamePlayer.szID);
					ask.nDestPos = pc->m_GPlayerList[m_warpCharIdx].nPos;

					gServer::GetIF()->Send(PL_WARPEND_ASK, sizeof(ask), &ask);
				}
				if(nFrame >= 1)
				{
					pc->m_nNoDraw = -1;
				}
				pc->MainLoop_Warp(m_warpCharIdx, (nFrame - WARPFRAME)*WARPDIST);
			}
			break;
	}
}

void gGameCore::DrawWarpList()
{
	if(!m_bWarpingList)
		return;

	gTimer				*gt = gTimer::GetIF();
	gPlayerContainer	*pc = gPlayerContainer::GetIF();
	gMap				*map = gMap::GetIF();

	switch(m_warplist)
	{
		case WARPLIST_DISAPPEAR:
			{
				int		nFrame = gt->frame();
				bool	bDrawAll = true;

				if(nFrame >= WARPFRAME)
				{
					m_warplist = WARPLIST_SCROLLSTART;
					gt->frameEnd();
					ScrollStart(m_warpDest);
					bDrawAll = false;
				}
				pc->MainLoop_WarpList(m_warplistDest, bDrawAll, -WARPDIST*nFrame);
			}
			break;
		case WARPLIST_SCROLLSTART:
			{
				if(!m_bScrolling)
				{
					m_warplist = WARPLIST_SCROLLEND;
					gt->frameStart(500, 2);
				}
				pc->MainLoop_WarpList(m_warplistDest, false);
			}
			break;
		case WARPLIST_SCROLLEND:
			{
				int		nFrame = gt->frame();

				if(nFrame >= 1)
				{
					gt->frameEnd();
					gt->frameStart(WARPTICK, WARPFRAME + 1);
					m_warplist = WARPLIST_APPEAR;

					map->posSetter(m_warpDest / LINEY, m_warpDest % LINEY);
					int		i;
					for(i = 0; i < ROOMMAXPLAYER; i++)
					{
						if(strlen(pc->m_GPlayerList[i].szID) != 0)
						{
							if(m_warplistDest[i] != -1)
							{
								pc->m_GPlayerList[i].nPos = m_warplistDest[i];
								pc->SyncronizeToMap(i);
								if(strcmp(pc->m_MyGamePlayer.szID, pc->m_GPlayerList[i].szID) == 0)
									pc->m_MyGamePlayer.nPos = pc->m_GPlayerList[i].nPos;
							}
						}
					}
				}
				pc->MainLoop_WarpList(m_warplistDest, false);
			}
			break;
		case WARPLIST_APPEAR:
			{
				int		nFrame = gt->frame();
				bool	bDrawAll = false;

				if(nFrame >= WARPFRAME)
				{
					gt->frameEnd();
					m_bWarpingList = false;

					PK_WARPLISTEND_ASK		ask;

					strcpy(ask.szID, pc->m_MyGamePlayer.szID);
					int		i;
					for(i = 0; i < ROOMMAXPLAYER; i++)
					{
						if(strlen(pc->m_GPlayerList[i].szID) != 0)
						{
							ask.nDestPos[i] = pc->m_GPlayerList[i].nPos;
						}
						else
						{
							ask.nDestPos[i] = -1;
						}
					}
					gServer::GetIF()->Send(PL_WARPLISTEND_ASK, sizeof(ask), &ask);
				}
				if(nFrame >= 1)
				{
					bDrawAll = true;
				}
				pc->MainLoop_WarpList(m_warplistDest, bDrawAll, -(WARPFRAME - nFrame)*WARPDIST);
			}
			break;
	}
}

void gGameCore::DrawBus()
{
	if(!m_bBusing)
		return;

	gTimer			 *gt = gTimer::GetIF();
	gMap			*map = gMap::GetIF();
	gPlayerContainer *pc = gPlayerContainer::GetIF();
	gPlaySoundCore	*sound = gPlaySoundCore::GetIF();

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

					sound->StopEffectSound(EFFECT_FILE_1);
					sound->PlayEffectSound(EFFECT_FILE_2);

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

					sound->PlayEffectSound(EFFECT_FILE_1);

					m_curframe = 0;
					gt->frameStart(BUSMOVETICK, BUSMOVEFRAME + 1);
					m_busmode = BUS_START;
				}
				if(nFrame >= 2)
				{
					if(strlen(pc->m_GPlayerList[m_nTurn].szCouple) != 0)
					{
						int		coupleidx = pc->GetGPIndex(pc->m_GPlayerList[m_nTurn].szCouple);
						pc->m_nNoDraw2 = coupleidx;
					}
					pc->m_nNoDraw = m_nTurn;
				}
				if(nFrame >= 1)
				{
					if(strlen(pc->m_GPlayerList[m_nTurn].szCouple) != 0)
					{
						int		coupleidx = pc->GetGPIndex(pc->m_GPlayerList[m_nTurn].szCouple);
						pc->m_movePosition[coupleidx] = 2;
					}
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

					sound->StopEffectSound(EFFECT_FILE_1);

					m_curframe = 0;
					ScrollStart(m_buspos);

					pc->MainLoop_Busing(NULL, NULL, NULL, m_nTurn);
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
					sound->PlayEffectSound(EFFECT_FILE_1);

					gTimer::GetIF()->frameStart(BUSMOVETICK, BUSMOVEFRAME + 1);
					m_curframe = 0;	
					m_busmode = BUS_COME2;
					pc->m_GPlayerList[m_nTurn].nPos = m_buspos;
					map->posSetter(m_buspos / LINEY, m_buspos % LINEY);
					pc->SyncronizeToMap(m_nTurn);
					// couple
					if(strlen(pc->m_GPlayerList[m_nTurn].szCouple) != 0)
					{
						int		coupleIdx = pc->GetGPIndex(pc->m_GPlayerList[m_nTurn].szCouple);
						pc->m_GPlayerList[coupleIdx].nPos = m_buspos;
						pc->SyncronizeToMap(coupleIdx);
					}
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

					sound->StopEffectSound(EFFECT_FILE_1);
					sound->PlayEffectSound(EFFECT_FILE_2);

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

					sound->PlayEffectSound(EFFECT_FILE_1);

					m_curframe = 0;
					gt->frameStart(BUSMOVETICK, BUSMOVEFRAME + 1);
					m_busmode = BUS_START2;
				}
				if(nFrame >= 1)
				{
					if(strlen(pc->m_GPlayerList[m_nTurn].szCouple) != 0)
					{
						int		coupleidx = pc->GetGPIndex(pc->m_GPlayerList[m_nTurn].szCouple);
						pc->m_nNoDraw2 = -1;
						pc->m_movePosition[coupleidx] = 0;
					}
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

					sound->StopEffectSound(EFFECT_FILE_1);

//					pc->m_GPlayerList[ m_nTurn ].nPos = map->m_xSpacePos * LINEY + map->m_ySpacePos;

					if(strcmp(pc->m_MyGamePlayer.szID, pc->m_GPlayerList[m_nTurn].szID) == 0)
						pc->m_MyGamePlayer.nPos = pc->m_GPlayerList[ m_nTurn ].nPos;

					// TODO : BusEnd의 패킷을 보냄

					PK_BUSMOVEEND_ASK   ask;

					ask.nDestPos = pc->m_GPlayerList[ m_nTurn ].nPos;
					strcpy(ask.szID, pc->m_MyGamePlayer.szID);

					if(strlen(pc->m_GPlayerList[m_nTurn].szCouple) != 0)
						gServer::GetIF()->Send(PL_BUSMOVEENDCOUPLE_ASK, sizeof ask, &ask);
					else
						gServer::GetIF()->Send(PL_BUSMOVEEND_ASK, sizeof ask, &ask);

					pc->MainLoop_Busing(NULL, NULL, NULL, m_nTurn);
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
//	int				couple = gPC->GetCoupleIndex(m_nTurn);

	// 내 차례가 아님
	m_turnTime = 0x7fffffff;
	if(strcmp(gPC->m_MyGamePlayer.szID, gPC->m_GPlayerList[m_nTurn].szID) != 0) {
		return;
	}
	// 이미 움직였음, 스크롤링 중임
	if(m_bMoved) //|| m_bScrolling)
		return;
	if(gUIGame::GetIF()->m_bItemUsed)
		return;

	PK_MOVESTART_ASK		ask;

	strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyGamePlayer.szID);
	ask.nCurPos		= gPlayerContainer::GetIF()->m_MyGamePlayer.nPos;

	gServer::GetIF()->Send(PL_MOVESTART_ASK, sizeof ask, &ask);

	if(gUIGame::GetIF()->m_uimode == UIM_TARGETSELECT ||
		gUIGame::GetIF()->m_uimode == UIM_TARGETSELECT_MULTI)
		gUIGame::GetIF()->m_uimode = UIM_NONE;

	m_bMoved = true;
}

void gGameCore::pk_movestart_rep(PK_MOVESTART_REP *rep)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	m_turnTime = 0x7fffffff; m_bMoved = true;
	if(m_bMoving)
		return;

	if(rep->Dice4_1 == 0 && rep->Dice4_2 == 0
		&& rep->Dice6_1 == 0 && rep->Dice6_2 == 0)
	{
		int ntPos = gPC->m_GPlayerList[ m_nTurn ].nPos;
		gMap::GetIF()->posSetter(ntPos / LINEY, ntPos % LINEY);
		m_bMoving = true; m_remain = -1;
		gPC->PacketalDrawFix();
		gGameCore::GetIF()->Start(rep->nDist,ntPos/LINEY,ntPos%LINEY);
		return;
	}

	if(rep->nDist == 0)
	{
		if(strlen(gPC->m_GPlayerList[ m_nTurn ].szCouple) != 0)
		{
			PK_MOVEENDCOUPLE_ASK	ask;
			ask.nDestPos = gPC->m_GPlayerList[ m_nTurn ].nPos;
			strcpy(ask.szID, gPC->m_MyGamePlayer.szID);

			gServer::GetIF()->Send(PL_MOVEENDCOUPLE_ASK, sizeof ask, &ask);
		}
		else
		{
			PK_MOVEEND_ASK	ask;
			ask.nDestPos = gPC->m_GPlayerList[ m_nTurn ].nPos;
			strcpy(ask.szID, gPC->m_MyGamePlayer.szID);

			gServer::GetIF()->Send(PL_MOVEEND_ASK, sizeof ask, &ask);
		}
		m_bMoving = false;
	}


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
	m_bMoving = true; m_remain = -1;
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
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();
	int couple = gPC->GetCoupleIndex(m_nTurn);

	if(couple != -1)
	{
		gPlaySoundCore::GetIF()->PlayEffectSound(EFFECT_FILE_11, true);
		gPlaySoundCore::GetIF()->PlayEffectSound(EFFECT_FILE_12, true);
	}
	else
	{
		if(gPC->m_CharInfo[ gPC->m_GPlayerList[m_nTurn].ctype ].bMale)
			gPlaySoundCore::GetIF()->PlayEffectSound(EFFECT_FILE_11, true);
		else
			gPlaySoundCore::GetIF()->PlayEffectSound(EFFECT_FILE_12, true);
	}

	gMap::GetIF()->posSetter(conPosX,conPosY);
	Start(spacor);
}


void gGameCore::StepStart()
{
	if(m_spacor>=0)
		gMap::GetIF()->posSpacor(false);
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
		int couple = gPC->GetCoupleIndex(m_nTurn);

//		if(couple == m_nTurn) couple = gPC->GetMyGPIndex();
		gMap::GetIF()->posMover(l_frame, gt->m_frame);

		if(m_remain > 0) { //fucking couple
			gPC->SyncronizeToMap(-2, couple);
			gPC->PutFootPosition(-2, l_frame, 60/4, couple);
			m_remain--;
		}
		else if(m_remain<0) {
			gPC->SyncronizeToMap(m_nTurn, couple);
			gPC->PutFootPosition(m_nTurn,l_frame, 60/4, couple);
		}
	}
}

void gGameCore::StepEnd()
{
	if(!m_bMoving) return;
	gTimer *gt = gTimer::GetIF();
	gMap::GetIF()->posStoper();

	if(m_spacor > 0)
		m_spacor--;
	else if(m_spacor < 0)
		m_spacor++;

	gt->m_turn--;

	if(m_spacor != 0)
		Start(m_spacor);
	else
		End();
}

void gGameCore::End(bool Abnormal_End)		// 이동 끝남
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();
	gMap				*map = gMap::GetIF();
	int					couple = gPC->GetCoupleIndex(m_nTurn);
	PK_MOVEEND_ASK		ask;
	static int			newPos;

	if(couple != -1)
	{
		gPlaySoundCore::GetIF()->StopEffectSound(EFFECT_FILE_11);
		gPlaySoundCore::GetIF()->StopEffectSound(EFFECT_FILE_12);
	}
	else
	{
		if(gPC->m_CharInfo[ gPC->m_GPlayerList[m_nTurn].ctype ].bMale)
			gPlaySoundCore::GetIF()->StopEffectSound(EFFECT_FILE_11);
		else
			gPlaySoundCore::GetIF()->StopEffectSound(EFFECT_FILE_12);
	}


//	if(couple == m_nTurn) couple = gPC->GetMyGPIndex();
	if(couple >= 0) {
		if(m_remain == -1) {
			newPos = map->m_xSpacePos * LINEY + map->m_ySpacePos;
			m_remain = 4;
		}
		if(m_remain>0) {
			m_spacor = 1;
			return;
		}
	}
	else newPos = map->m_xSpacePos * LINEY + map->m_ySpacePos;

	gTimer::GetIF()->frameEnd();
	gPC->FootClear();
	m_bMoving = false;

	gPC->SyncronizeToMap(m_nTurn, couple);
	gPC->m_GPlayerList[ m_nTurn ].nPos = newPos;

	if(couple>=0) {
		gPC->m_GPlayerList[ couple ].nPos = newPos;
	}

	if(strcmp(gPC->m_MyGamePlayer.szID, gPC->m_GPlayerList[m_nTurn].szID) == 0)
		gPC->m_MyGamePlayer.nPos = gPC->m_GPlayerList[ m_nTurn ].nPos;

	ask.nDestPos = gPC->m_GPlayerList[ m_nTurn ].nPos;
	strcpy(ask.szID, gPC->m_MyGamePlayer.szID);

	/*if(couple>=0) {
		gServer::GetIF()->Send(PL_MOVEENDCOUPLE_ASK, sizeof ask, &ask);
	}*/
//	else {
	if(!Abnormal_End) {
		if(strlen(gPC->m_GPlayerList[m_nTurn].szCouple) != 0)
			gServer::GetIF()->Send(PL_MOVEENDCOUPLE_ASK, sizeof ask, &ask);
		else
			gServer::GetIF()->Send(PL_MOVEEND_ASK, sizeof ask, &ask);
	}
//	}
	
	//pk_stepFinish_ask(gtc->m_xSpacePos,gtc->m_ySpacePos);
}

void gGameCore::pk_nextturn_rep(PK_NEXTTURN_REP *rep)
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	if(m_bBreak)
	{
		if(m_nTurn == gPC->GetMyGPIndex())
		{
			m_nCoupleDebuffRemain--;
			if(m_nCoupleDebuffRemain < 0)
			{
				m_bBreak = false;
				gPlaySoundCore	*sound = gPlaySoundCore::GetIF();
				if(gPC->IsNokdu(m_nTurn))
					sound->StartBGM(BGM_FILE_1);
				else
					sound->StartBGM(BGM_FILE_2);
			}
		}
	}
	gPlaySoundCore	*sound = gPlaySoundCore::GetIF();
	bool	bMeInNokdu = gPC->IsNokdu(gPC->GetMyGPIndex());
	// 녹두 -> !녹두
	if(!m_bBreak && !gUIGame::GetIF()->m_bCouple)
	{
		if(m_bPrevInNokdu && !bMeInNokdu)
			sound->StartBGM(BGM_FILE_2);
		// !녹두 -> 녹두
		else if(!m_bPrevInNokdu && bMeInNokdu)
			sound->StartBGM(BGM_FILE_1);
	}
	
	m_bPrevInNokdu = bMeInNokdu;

	m_turnTime = GetTickCount();		//잠수타는 시간 재기 시작
//	if(m_nTurn == rep->nNowTurn) {		//why this?
		m_nTurn		= rep->nNextTurn;
		m_bMoved	= false;

		gUIGame::GetIF()->m_bItemUsed = false;
//	}
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

	if(m_nTurn == rep->nNowTurn) {
		m_bBusSel = true;
		m_turnTime_Bus = GetTickCount();
	}
}

// 상우의  주요 작업 부분 시작

void gGameCore::pk_busmovestart_rep(PK_BUSMOVESTART_REP *rep)
{
	gPlayerContainer *gPC = gPlayerContainer::GetIF();

	int  nPos = gPC->m_GPlayerList[m_nTurn].nPos;

	m_turnTime_Bus = 0x7fffffff;
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
		gPlaySoundCore	*sound = gPlaySoundCore::GetIF();
		sound->PlayEffectSound(EFFECT_FILE_1);
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


void gGameCore::pk_gameend_rep(PK_GAMEEND_REP *rep)
{
	char str2[IDLENGTH]={0,};
	strcpy(str2, rep->szID);

	gRoomCore::GetIF()->SendRoomBack();	//방나가고돌아오기수정
//	MessageBox(gMainWin::GetIF()->m_hWnd, "시발", "발시발시", MB_OK);
	gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_ROOMBACK, str2, STR_17);	//방나가고돌아오기수정
	m_bMoved	= false;
	gUIGame::GetIF()->m_bItemUsed = false;
}

void gGameCore::pk_exit_rep(PK_EXIT_REP *rep)
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();
	gChat				*ct = gChat::GetIF();

	int		id = pc->GetGPIndex(rep->szID), i;
	bool	make_next_turn = true;

	for(i=0;i<ROOMMAXPLAYER; i++)
		if(pc->GetCoupleIndex(i) == id) {
			make_next_turn = false;
			if(id==m_nTurn) m_nTurn = i;
			break;
		}
	//커플상태인 두 사람중 하나가 나갔다면 m_nTurn은 커플에게 강제적으로 넘어간다.
	//그리고 커플은 강제적으로 깨져야 한다. 여기에는 정상적으로 커플을 깨는 frame이 삽입되지 않는다.
	if(make_next_turn && id==m_nTurn) {
		if(m_spacor > 0) {
			End(true);
			gDice::GetIF()->m_start = false;
			m_spacor = 0;
		}
		gTimer::GetIF()->frameEnd();
		m_bBusing	= false;
		m_bScrolling = false;
		m_bMoving = false;
		m_bWarping	= false;
	}
	else if(make_next_turn==false && pc->GetMyGPIndex() == i) {
		gUIGame::GetIF()->SetbCouple(false);
	}

	ct->AddStr(rep->szID, "님이 나가셨습니다.");
	pc->DeleteGamePlayer(id);
}

bool gGameCore::Restore()
{
	if(!m_ImgBus.Restore())
		return false;

	return true;
}

void gGameCore::pk_warpstart_rep(PK_WARPSTART_REP *rep)
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	m_warpDest = rep->nDest;
	m_bWarping = true;

	gTimer::GetIF()->frameStart(WARPTICK, WARPFRAME + 1);
	m_warp = WARP_DISAPPEAR;
	m_warpCharIdx = pc->GetGPIndex(rep->szID);
}

void gGameCore::pk_warpliststart_rep(PK_WARPLISTSTART_REP* rep)
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	int		i;
	memset(m_warplistDest, -1, sizeof(int) * ROOMMAXPLAYER);
	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(rep->nDestPos[i] == -1)
			continue;

		m_warplistDest[i] = rep->nDestPos[i];
	}
	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(m_warplistDest[i] != -1)
		{
			m_warpDest = m_warplistDest[i];
			break;
		}
	}

	m_bWarpingList = true;
	m_warplist = WARPLIST_DISAPPEAR;
	gTimer::GetIF()->frameStart(WARPTICK, WARPFRAME + 1);
}

void gGameCore::pk_askcouple_rep(PK_ASKCOUPLE_REP* rep)
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();
	gImage				*img;

	int		idx = pc->GetGPIndex(rep->szCouple);
	img = &pc->m_ImgInfo[ pc->m_GPlayerList[idx].ctype ].ImgPic;
	gPopUp::GetIF()->SetImgPopUp(ECLK_CANCEL, EPOP_COUPLEASK, img, STR_21);
}

void gGameCore::pk_movestartcouple_rep(PK_MOVESTART_REP *rep)
{
	pk_movestart_rep(rep);
}

void gGameCore::pk_busmovestartcouple_rep(PK_BUSMOVESTART_REP *rep)
{
	pk_busmovestart_rep(rep);
}

void gGameCore::Clear(int newTurn)
{
	m_nTurn		= newTurn;
	m_turnTime	= GetTickCount();
	m_bBreak	= false;
	m_bPrevInNokdu = false;
}