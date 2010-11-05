#include <stdio.h>
#include "UIGame.h"
#include "Util.h"
#include "PlayerContainer.h"
#include "GameCore.h"
#include "Mouse.h"
#include "MainWin.h"
#include "SubjectContainer.h"
#include "Chat.h"
#include "ItemContainer.h"
#include "Server.h"
#include "PopUp.h"
#include "stringconst.h"
#include "Map.h"

#define	UI_FILE_MAININFO					".\\Data\\Interface\\game_maininfo.img"
#define UI_SIZE_MAININFO_W					220
#define UI_SIZE_MAININFO_H					110
#define UI_POS_MAININFO_X					0
#define UI_POS_MAININFO_Y					0

#define MAININFO_ID_POS_X					102
#define MAININFO_ID_POS_Y					16
#define MAININFO_LANG_POS_X					102
#define MAININFO_LANG_POS_Y					32
#define MAININFO_MATH_POS_X					102
#define MAININFO_MATH_POS_Y					47
#define MAININFO_ART_POS_X					102
#define MAININFO_ART_POS_Y					62
#define MAININFO_DICE6_POS_X				180
#define MAININFO_DICE6_POS_Y				33
#define MAININFO_DICE4_POS_X				180
#define MAININFO_DICE4_POS_Y				53
#define MAININFO_NAME_POS_X					15
#define MAININFO_NAME_POS_Y					74
#define MAININFO_PIC_POS_X					15
#define MAININFO_PIC_POS_Y					9

#define MAININFO_FILE_BARLINE				".\\Data\\Interface\\game_bar_outline.img"
#define MAININFO_BARLINE_SIZE_W				150
#define MAININFO_BARLINE_SIZE_H				10
#define MAININFO_BARLINE_POS_X				13
#define MAININFO_BARLINE_POS_Y				91
#define MAININFO_FILE_BARGUAGE				".\\Data\\Interface\\game_bar_guage.img"
#define MAININFO_BARGUAGE_SIZE_W			148
#define MAININFO_BARGUAGE_SIZE_H			8
#define MAININFO_BARGUAGE_POS_X				14
#define MAININFO_BARGUAGE_POS_Y				92

#define SUBINFO_FILE_BACK					".\\Data\\Interface\\game_subinfo.img"
#define SUBINFO_SIZE_W						120
#define SUBINFO_SIZE_H						40
#define SUBINFO_POS_X						220
#define SUBINFO_POS_Y						0
#define SUBINFO_ITEM_FILE					".\\Data\\Interface\\game_sub_item.img"
#define SUBINFO_ITEM_SIZE_W					50
#define SUBINFO_ITEM_SIZE_H					30
#define SUBINFO_ITEM_POS_X					227
#define SUBINFO_ITEM_POS_Y					5
#define SUBINFO_SUBJECT_FILE				".\\Data\\Interface\\game_sub_subject.img"
#define SUBINFO_SUBJECT_SIZE_W				50
#define SUBINFO_SUBJECT_SIZE_H				30
#define SUBINFO_SUBJECT_POS_X				283
#define SUBINFO_SUBJECT_POS_Y				5

#define SUBINFO_SUBWND_FILE					".\\Data\\Interface\\game_sub_subwnd.img"
#define SUBINFO_SUBWND_SIZE_W				270
#define SUBINFO_SUBWND_SIZE_H				230
#define SUBINFO_SUBWND_POS_X				((WNDSIZEW - SUBINFO_SUBWND_SIZE_W) / 2)
#define SUBINFO_SUBWND_POS_Y				((WNDSIZEH - SUBINFO_SUBWND_SIZE_H) / 2)
#define SUBINFO_ID_POS_X					212
#define SUBINFO_ID_POS_Y					155
#define SUBINFO_BUILDING_POS_X				215
#define SUBINFO_SUBNAME_POS_X				270
#define SUBINFO_GRADE_POS_X					400
#define SUBINFO_SUBNAME_POS_Y				181
#define SUBINFO_SUBNAME_TERM_Y				18
#define SUBINFO_AVGRADE_FONTSIZE			22
#define SUBINFO_AVGRADE_POS_X				355
#define SUBINFO_AVGRADE_POS_Y				305
#define SUBINFO_BTN_FILE_PREV				".\\Data\\Interface\\game_btn_prev.img"
#define SUBINFO_BTN_FILE_NEXT				".\\Data\\Interface\\game_btn_next.img"
#define SUBINFO_BTN_PREV_SIZE_W				12
#define SUBINFO_BTN_PREV_SIZE_H				21
#define SUBINFO_BTN_PREV_POS_X				190
#define SUBINFO_BTN_PREV_POS_Y				220
#define SUBINFO_BTN_NEXT_POS_X				438
#define SUBINFO_BTN_NEXT_POS_Y				220

#define PINFO_FILE_BACK						".\\Data\\Interface\\game_pinfo_back.img"
#define PINFO_SIZE_W						160
#define PINFO_SIZE_H						120
#define PINFO_POS_X							480
#define PINFO_POS_Y							360
#define PINFO_INFO_POS_X					495
#define PINFO_INFO_POS_Y					378
#define PINFO_INFO_TERM_Y					42
#define PINFO_SCROLL_FILE					".\\Data\\Interface\\game_pinfo_scroll.img"
#define PINFO_SCROLL_POS_X					620
#define PINFO_SCROLL_POS_Y					370
#define PINFO_SCROLL_SIZE_H					100
#define PINFO_ID_TERM_X						20
#define PINFO_ID_TERM_Y						3

#define DICEBTN_FILE						".\\Data\\Interface\\game_btn_dice.img"
#define DICEBTN_SIZE_W						100
#define DICEBTN_SIZE_H						101
#define DICEBTN_POS_X						515
#define DICEBTN_POS_Y						247

#define MENUBTN_FILE						".\\Data\\Interface\\game_btn_menu.img"
#define MENUBTN_SIZE_W						80
#define MENUBTN_SIZE_H						30
#define MENUBTN_POS_X						(WNDSIZEW - MENUBTN_SIZE_W)
#define MENUBTN_POS_Y						0

#define UI_NUMBER_FILE						".\\Data\\Interface\\game_number.img"
#define UI_NUMBER_SIZE_W					16
#define UI_NUMBER_SIZE_H					16
#define UI_NUMBER_TERM_X					0
#define UI_NUMBER_TERM_Y					0

#define UI_POPINFO1_FILE					".\\Data\\Interface\\game_popinfo1.img"
#define UI_POPINFO1_SIZE_W					120
#define UI_POPINFO1_SIZE_H					48
#define UI_POPINFO1_TERM_X					0
#define UI_POPINFO1_TERM_Y					-70
#define UI_POPINFO2_FILE					".\\Data\\Interface\\game_popinfo2.img"
#define UI_POPINFO2_SIZE_W					120
#define UI_POPINFO2_SIZE_H					63
#define UI_POPINFO2_TERM_X					0
#define UI_POPINFO2_TERM_Y					-60
#define UI_POPSTR1_TERM_Y					14
#define UI_POPSTR2_1_TERM_Y					11
#define UI_POPSTR2_2_TERM_Y					29

#define ITEMCARD_POS_X						22
#define ITEMCARD_POS_Y						120
#define ITEMCARD_SIZE_W						140
#define ITEMCARD_SIZE_H						196
#define ITEMCARD_TERM_X						10

#define TARGET_OUTLINE_FILE					".\\Data\\Interface\\game_face_outline.img"
#define TARGET_OUTLINE_SIZE_W				52
#define TARGET_OUTLINE_SIZE_H				62
#define TARGET_TERM_X						10
#define TARGET_TERM_Y						10
#define TARGET_POS_CENTER_X					320
#define TARGET_POS_CENTER_Y					200

#define USEINFO_CARD_POS_X					320
#define USEINFO_CARD_POS_Y					ITEMCARD_POS_Y
#define USEINFO_USER_POS_X					USEINFO_CARD_POS_X - 200													// 중점
#define USEINFO_USER_POS_Y					(ITEMCARD_POS_Y + (ITEMCARD_SIZE_H - TARGET_OUTLINE_SIZE_H) / 2)			// 중점
#define USEINFO_TARGET_POS_X				USEINFO_CARD_POS_X + 200													// 중점
#define USEINFO_TARGET_POS_Y				(USEINFO_USER_POS_Y + TARGET_OUTLINE_SIZE_H / 2)							// 중점
#define USEINFO_TARGET_TERM_X				10
#define USEINFO_TARGET_TERM_Y				10

#define USEINFO_TICK						3000	// 3초 보여줌
#define INFOCHANGE_TICK						3000

#define INFOCHANGE_POS_X					320
#define	INFOCHANGE_POS_Y					150
#define INFOCHANGE_TERM_X					10		
#define INFOCHANGE_TERM_Y					10
#define INFOCHANGE_INFOSIZE_W				50
#define INFOCHANGE_INFOSIZE_H				12		// info 하나당 높이
#define INFOCHANGE_INFOTERM_Y				10		// info끼리 텀

static gUIGame s_UIGame;

gUIGame *gUIGame::GetIF()
{
	return &s_UIGame;
}

gUIGame::gUIGame(void)
{
}

gUIGame::~gUIGame(void)
{
}

bool gUIGame::SetUp()
{
	RECT		rcDest;

	// Maininfo
	if(!m_ImgUI[UIIMG_MAININFO].Load(UI_FILE_MAININFO))
		return false;
	SetRect(&m_rcPos[UIT_MAININFO],
			UI_POS_MAININFO_X,
			UI_POS_MAININFO_Y,
			UI_POS_MAININFO_X + UI_SIZE_MAININFO_W,
			UI_POS_MAININFO_Y + UI_SIZE_MAININFO_H );

	if(!m_ImgUI[UIIMG_BAROUTLINE].Load(MAININFO_FILE_BARLINE))
		return false;
	if(!m_ImgUI[UIIMG_BARGUAGE].Load(MAININFO_FILE_BARGUAGE))
		return false;

	SetRect(&m_rcBarDest,
			MAININFO_BARGUAGE_POS_X,
			MAININFO_BARGUAGE_POS_Y,
			MAININFO_BARGUAGE_POS_X + MAININFO_BARGUAGE_SIZE_W,
			MAININFO_BARGUAGE_POS_Y + MAININFO_BARGUAGE_SIZE_H);
	SetRect(&m_rcBarSour,
			0, 0, MAININFO_BARGUAGE_SIZE_W, MAININFO_BARGUAGE_SIZE_H);

	// SubInfo
	if(!m_ImgUI[UIIMG_SUBINFO].Load(SUBINFO_FILE_BACK))
		return false;

	SetRect(&m_rcPos[UIT_SUBINFO],
			SUBINFO_POS_X,
			SUBINFO_POS_Y,
			SUBINFO_POS_X + SUBINFO_SIZE_W,
			SUBINFO_POS_Y + SUBINFO_SIZE_H);


	SetRect(&rcDest,
			SUBINFO_ITEM_POS_X,
			SUBINFO_ITEM_POS_Y,
			SUBINFO_ITEM_POS_X + SUBINFO_ITEM_SIZE_W,
			SUBINFO_ITEM_POS_Y + SUBINFO_ITEM_SIZE_H );
	if(!m_BtnUI[UIBTN_ITEMCARD].SetUp(SUBINFO_ITEM_FILE, false, rcDest))
		return false;
	SetRect(&rcDest,
		SUBINFO_SUBJECT_POS_X,
		SUBINFO_SUBJECT_POS_Y,
		SUBINFO_SUBJECT_POS_X + SUBINFO_SUBJECT_SIZE_W,
		SUBINFO_SUBJECT_POS_Y + SUBINFO_SUBJECT_SIZE_H );
	if(!m_BtnUI[UIBTN_SUBJECT].SetUp(SUBINFO_SUBJECT_FILE, false, rcDest))
		return false;

	// sub - subject window
	if(!m_ImgUI[UIIMG_SUBWND].Load(SUBINFO_SUBWND_FILE))
		return false;
	SetRect(&m_rcPos[UIT_SUBWND],
		SUBINFO_SUBWND_POS_X,
		SUBINFO_SUBWND_POS_Y,
		SUBINFO_SUBWND_POS_X + SUBINFO_SUBWND_SIZE_W,
		SUBINFO_SUBWND_POS_Y + SUBINFO_SUBWND_SIZE_H );

	SetRect(&rcDest,
		SUBINFO_BTN_PREV_POS_X,
		SUBINFO_BTN_PREV_POS_Y,
		SUBINFO_BTN_PREV_POS_X + SUBINFO_BTN_PREV_SIZE_W,
		SUBINFO_BTN_PREV_POS_Y + SUBINFO_BTN_PREV_SIZE_H );
	if(!m_BtnUI[UIBTN_SUBPREV].SetUp(SUBINFO_BTN_FILE_PREV, false, rcDest))
		return false;

	SetRect(&rcDest,
		SUBINFO_BTN_NEXT_POS_X,
		SUBINFO_BTN_NEXT_POS_Y,
		SUBINFO_BTN_NEXT_POS_X + SUBINFO_BTN_PREV_SIZE_W,
		SUBINFO_BTN_NEXT_POS_Y + SUBINFO_BTN_PREV_SIZE_H );
	if(!m_BtnUI[UIBTN_SUBNEXT].SetUp(SUBINFO_BTN_FILE_NEXT, false, rcDest))
		return false;

	// menu
	SetRect(&m_rcPos[UIT_MENU],
		MENUBTN_POS_X,
		MENUBTN_POS_Y,
		MENUBTN_POS_X + MENUBTN_SIZE_W,
		MENUBTN_POS_Y + MENUBTN_SIZE_H);
	if(!m_BtnUI[UIBTN_MENU].SetUp(MENUBTN_FILE, false, m_rcPos[UIT_MENU]))
		return false;

	// players info
	if(!m_ImgUI[UIIMG_PINFO].Load(PINFO_FILE_BACK))
		return false;
	SetRect(&m_rcPos[UIT_SUBINFO],
			PINFO_POS_X,
			PINFO_POS_Y,
			PINFO_POS_X + PINFO_SIZE_W,
			PINFO_POS_Y + PINFO_SIZE_H);

	if(!m_ImgUI[UIIMG_NUMBER].Load(UI_NUMBER_FILE))
		return false;

	if(!m_Scroll.SetUp(PINFO_SCROLL_POS_X, PINFO_SCROLL_POS_Y, PINFO_SCROLL_SIZE_H, PINFO_SCROLL_FILE))
		return false;

	// dice btn
	SetRect(&m_rcPos[UIT_DICE],
			DICEBTN_POS_X,
			DICEBTN_POS_Y,
			DICEBTN_POS_X + DICEBTN_SIZE_W,
			DICEBTN_POS_Y + DICEBTN_SIZE_H );
	if(!m_BtnUI[UIBTN_DICE].SetUp(DICEBTN_FILE, false, m_rcPos[UIT_DICE]))
		return false;

	// popinfo 말풍선 인포
	if(!m_ImgUI[UIIMG_POPINFO1].Load(UI_POPINFO1_FILE))
		return false;
	if(!m_ImgUI[UIIMG_POPINFO2].Load(UI_POPINFO2_FILE))
		return false;

	// item 사용, 타겟 charface img
	if(!m_ImgUI[UIIMG_FACEOUTLINE].Load(TARGET_OUTLINE_FILE))
		return false;

	m_nCurPInfo = 0;
	m_uimode = UIM_NONE;
	m_bTargetByMove = false;
	m_timer.SetUp();
	m_bItemUsed = false;

	return true;
}

void gUIGame::MainLoop()
{
	if(m_bPopInfo)
	{
		if((int)GetTickCount() - m_nTimer > m_nShowTime)
			m_bPopInfo = false;
	}
	static int tick=GetTickCount();
	const int MouseTick=300;
//	gMouse *mouse=gMouse::GetIF();
//	RECT rcTemp;

//	if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, rcTemp)) {
		switch(m_Scroll.whatIsClicked())
		{
			case SCR_DOWN:
				if(GetTickCount() - tick > MouseTick) 
				{
					if(m_nCurPInfo < m_nMaxPInfo - 2) {
						m_nCurPInfo++;
						m_Scroll.ChangeCursor(m_nCurPInfo, m_nMaxPInfo-2);
					}
					tick=GetTickCount();
				}
				break;
			case SCR_UP:
				if(GetTickCount() - tick > MouseTick) 
				{
					if(m_nCurPInfo > 0) {
						m_nCurPInfo--;
						m_Scroll.ChangeCursor(m_nCurPInfo, m_nMaxPInfo-2);
					}
					tick=GetTickCount();
				}
				break;
				//m_nMaxPInfo가 2인 경우에는 아예 SCR_DOWN으로 들어가질 않으므로 m_nSize가 0으로 보내지는 일 없고 안심.
			case SCR_BAR:
				int		nScrollSize = m_Scroll.m_rcPosScroll.bottom - m_Scroll.m_rcPosScroll.top;
				int		nCur = m_Scroll.m_ImgBtn[SCR_BAR].m_rcPos.top + SCROLL_SIZE_BAR_H - m_Scroll.m_rcPosScroll.top;
		
				if(nCur == nScrollSize) {
					m_nCurPInfo = m_nMaxPInfo - 2;
					break;
				}
				float	fTemp = (float)nCur / nScrollSize;	
				m_nCurPInfo = (int)((m_nMaxPInfo-2) * fTemp);
				break;
		}
//	}

					
}

void gUIGame::Draw()
{
	gPlayerContainer	*gPC	= gPlayerContainer::GetIF();
	gGameCore			*gc		= gGameCore::GetIF();
	gSubjectContainer	*sc		= gSubjectContainer::GetIF();
	gMap				*map	= gMap::GetIF();

	int		i;

	// popinfo
	if(m_bPopInfo)
	{
		char	szPop[2][32];
		int		nPopX, nPopY;
		int		nCount = 0;

		int		playeridx	= gPC->GetGPIndex(m_popinfo.szID);
		int		nPos		= gPC->m_GPlayerList[playeridx].nPos;
		if(playeridx != -1)
		{
			if(m_popinfo.nStamina != 0)
			{
				if(m_popinfo.nStamina > 0)
					wsprintf(szPop[nCount], "체력 +%d", m_popinfo.nStamina);
				else
					wsprintf(szPop[nCount], "체력 %d", m_popinfo.nStamina);

				nCount++;
			}
			if(m_popinfo.nGrade != 0)
			{
				if(m_popinfo.nGrade > 0)
					wsprintf(szPop[nCount], "%s +%d", map->tileMap[nPos].subject, m_popinfo.nGrade);
				else
					wsprintf(szPop[nCount], "%s %d", map->tileMap[nPos].subject, m_popinfo.nGrade);

				nCount++;
			}

			POINT	ptTemp;
			switch(nCount)
			{
			case 1:
				ptTemp = map->ConToViewabs(nPos);
				nPopX = ptTemp.x + UI_POPINFO1_TERM_X;
				nPopY = ptTemp.y + UI_POPINFO1_TERM_Y;
				m_ImgUI[UIIMG_POPINFO1].Draw(nPopX, nPopY);
				break;
			case 2:
				ptTemp = map->ConToViewabs(nPos);
				nPopX = ptTemp.x + UI_POPINFO2_TERM_X;
				nPopY = ptTemp.y + UI_POPINFO2_TERM_Y;
				m_ImgUI[UIIMG_POPINFO2].Draw(nPopX, nPopY);
				break;
			}
		}
		gUtil::BeginText();
		int		len;
		switch(nCount)
		{
		case 1:
			{
				len = gUtil::TextLength(szPop[0]);
				gUtil::Text( nPopX + (UI_POPINFO1_SIZE_W - len) / 2, nPopY + UI_POPSTR1_TERM_Y, szPop[0]);
			}
			break;
		case 2:
			{
				len = gUtil::TextLength(szPop[0]);
				gUtil::Text( nPopX + (UI_POPINFO1_SIZE_W - len) / 2, nPopY + UI_POPSTR2_1_TERM_Y, szPop[0]);
				len = gUtil::TextLength(szPop[1]);
				gUtil::Text( nPopX + (UI_POPINFO1_SIZE_W - len) / 2, nPopY + UI_POPSTR2_2_TERM_Y, szPop[1]);
			}
			break;
		}
		gUtil::EndText();
	}

	gChat::GetIF()->Draw();


	RECT	rcDest, rcSour;

	// image
	// show always
		// MainInfo
		gPC->m_ImgInfo[gPC->m_MyGamePlayer.ctype].ImgPic.Draw(MAININFO_PIC_POS_X, MAININFO_PIC_POS_Y);
		m_ImgUI[UIIMG_MAININFO].Draw(UI_POS_MAININFO_X, UI_POS_MAININFO_Y);

		m_rcBarDest.right = m_rcBarDest.left + gPC->m_MyGamePlayer.nStamina * MAININFO_BARGUAGE_SIZE_W / 10;
		m_ImgUI[UIIMG_BARGUAGE].Draw(m_rcBarDest, m_rcBarSour);
		m_ImgUI[UIIMG_BAROUTLINE].Draw(MAININFO_BARLINE_POS_X, MAININFO_BARLINE_POS_Y);

		// playersInfo
		m_ImgUI[UIIMG_PINFO].Draw(PINFO_POS_X, PINFO_POS_Y);
		SetRect(&rcDest,
			PINFO_INFO_POS_X,
			PINFO_INFO_POS_Y,
			PINFO_INFO_POS_X + UI_NUMBER_SIZE_W,
			PINFO_INFO_POS_Y + UI_NUMBER_SIZE_H );
		OffsetRect(&rcDest, UI_NUMBER_TERM_X, UI_NUMBER_TERM_Y);
		SetRect(&rcSour,
			0, 0, UI_NUMBER_SIZE_W, UI_NUMBER_SIZE_H);
		OffsetRect(&rcSour, (gPC->m_GPlayerList[ m_rankIdx[m_nCurPInfo] ].nRank - 1) * UI_NUMBER_SIZE_W, 0);
		m_ImgUI[UIIMG_NUMBER].Draw(rcDest, rcSour);
		
		if(m_rankIdx[m_nCurPInfo + 1] != -1)
		SetRect(&rcDest,
			PINFO_INFO_POS_X,
			PINFO_INFO_POS_Y,
			PINFO_INFO_POS_X + UI_NUMBER_SIZE_W,
			PINFO_INFO_POS_Y + UI_NUMBER_SIZE_H );
		OffsetRect(&rcDest, UI_NUMBER_TERM_X, UI_NUMBER_TERM_Y + PINFO_INFO_TERM_Y);
		SetRect(&rcSour,
			0, 0, UI_NUMBER_SIZE_W, UI_NUMBER_SIZE_H);
		OffsetRect(&rcSour, (gPC->m_GPlayerList[ m_rankIdx[m_nCurPInfo + 1] ].nRank - 1) * UI_NUMBER_SIZE_W, 0);
		m_ImgUI[UIIMG_NUMBER].Draw(rcDest, rcSour);
		m_Scroll.Draw();
		
		// menu
		m_BtnUI[UIBTN_MENU].Draw();

		// dice btn
		if(!gPC->isTurn(gc->m_nTurn))
			m_BtnUI[UIBTN_DICE].m_eBtnMode = EBM_CLICK;

		m_BtnUI[UIBTN_DICE].Draw();

		m_ImgUI[UIIMG_SUBINFO].Draw(SUBINFO_POS_X, SUBINFO_POS_Y);
		m_BtnUI[UIBTN_ITEMCARD].Draw();
		m_BtnUI[UIBTN_SUBJECT].Draw();

	// show always end

	switch(m_uimode)
	{
		case UIM_SUGANG:
			{
				m_ImgUI[UIIMG_SUBWND].Draw(SUBINFO_SUBWND_POS_X, SUBINFO_SUBWND_POS_Y);
				m_BtnUI[UIBTN_SUBPREV].Draw();
				m_BtnUI[UIBTN_SUBNEXT].Draw();
			}
			break;
		case UIM_ITEM:
			{
				gItemContainer	*ic = gItemContainer::GetIF();
				int		j = 0;
				for(i = 0; i < MAXITEMNUM; i++)
				{
					if(gPC->m_MyGamePlayer.nItem[i] == -1)
						continue;

					ic->m_ItemImg[ gPC->m_MyGamePlayer.nItem[i] ].Draw(ITEMCARD_POS_X + (ITEMCARD_TERM_X + ITEMCARDIMG_W) * j, ITEMCARD_POS_Y);
					j++;
				}
			}
			break;
		case UIM_TARGETSELECT_MULTI:
			{
				DrawTargetButton();
			}
			break;
		case UIM_ITEMUSEINFO:
			{
				int nFrame = m_timer.frame();

				if(nFrame >= 1)
				{
					m_timer.frameEnd();
					PK_ITEMUSESTART_ASK		ask;

					strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
					gServer::GetIF()->Send(PL_ITEMUSESTART_ASK, sizeof(ask), &ask);
					m_uimode = UIM_NONE;
				}
				gItemContainer	*ic = gItemContainer::GetIF();
				gImage			*cardimg = &ic->m_ItemImg[m_nCardIdx];
				DrawTargetButton();

				m_itemuser.img->Draw(m_itemuser.rcPos.left + 1, m_itemuser.rcPos.top + 1);
				m_ImgUI[UIIMG_FACEOUTLINE].Draw(m_itemuser.rcPos.left, m_itemuser.rcPos.top);

				cardimg->Draw(USEINFO_CARD_POS_X - ITEMCARD_SIZE_W/2, USEINFO_CARD_POS_Y);
			}
			break;
		case UIM_INFOCHANGE:
			{
				int nFrame = m_timer.frame();

				if(nFrame >= 1)
				{
					m_timer.frameEnd();
					PK_INFOCHANGEEND_ASK		ask;

					strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
					gServer::GetIF()->Send(PL_INFOCHANGEEND_ASK, sizeof(ask), &ask);
					m_uimode = UIM_NONE;
				}
				Draw_InfoChange();
			}
			break;
	}
	

	// text
	char	szBuf[128];
	gUtil::BeginText();

	// MainInfo
		gUtil::Text(MAININFO_ID_POS_X, MAININFO_ID_POS_Y, gPC->m_MyGamePlayer.szID);
		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nLang);
		gUtil::Text(MAININFO_LANG_POS_X, MAININFO_LANG_POS_Y, szBuf);
		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nMath);
		gUtil::Text(MAININFO_MATH_POS_X, MAININFO_MATH_POS_Y, szBuf);
		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nArt);
		gUtil::Text(MAININFO_ART_POS_X, MAININFO_ART_POS_Y, szBuf);

		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nDice6);
		gUtil::Text(MAININFO_DICE6_POS_X, MAININFO_DICE6_POS_Y, szBuf);
		wsprintf(szBuf, "%d", gPC->m_MyGamePlayer.nDice4);
		gUtil::Text(MAININFO_DICE4_POS_X, MAININFO_DICE4_POS_Y, szBuf);

		if(strlen(gPC->m_CharInfo[gPC->m_MyGamePlayer.ctype].szName) < 7)
			gUtil::Text(MAININFO_NAME_POS_X + 8, MAININFO_NAME_POS_Y, gPC->m_CharInfo[gPC->m_MyGamePlayer.ctype].szName);
		else
			gUtil::Text(MAININFO_NAME_POS_X, MAININFO_NAME_POS_Y, gPC->m_CharInfo[gPC->m_MyGamePlayer.ctype].szName);

	// pinfo
		gUtil::Text(PINFO_INFO_POS_X + PINFO_ID_TERM_X, PINFO_INFO_POS_Y + PINFO_ID_TERM_Y,
					gPC->m_GPlayerList[ m_rankIdx[m_nCurPInfo] ].szID);
		if(m_rankIdx[ m_nCurPInfo + 1 ] != -1)
			gUtil::Text(PINFO_INFO_POS_X + PINFO_ID_TERM_X, PINFO_INFO_POS_Y + PINFO_ID_TERM_Y + PINFO_INFO_TERM_Y,
				gPC->m_GPlayerList[ m_rankIdx[m_nCurPInfo + 1] ].szID);


	// sub - subwnd
		if(m_uimode == UIM_SUGANG)
		{
			GAMEPLAYER	*gp = &gPC->m_GPlayerList[m_nSubSel];

			gUtil::Text(SUBINFO_ID_POS_X, SUBINFO_ID_POS_Y, gp->szID);
			for(i = 0; i < MAXSUBJECT; i++)
			{	
				gUtil::Text(SUBINFO_BUILDING_POS_X, SUBINFO_SUBNAME_POS_Y + (SUBINFO_SUBNAME_TERM_Y * i),
						sc->m_subject[ gp->bySubIdx[i] ].building);

				gUtil::Text(SUBINFO_SUBNAME_POS_X, SUBINFO_SUBNAME_POS_Y + (SUBINFO_SUBNAME_TERM_Y * i),
						sc->m_subject[ gp->bySubIdx[i] ].subject);

				sprintf_s(szBuf, "%.1f", gp->fGrade[i]);
				gUtil::Text(SUBINFO_GRADE_POS_X, SUBINFO_SUBNAME_POS_Y + (SUBINFO_SUBNAME_TERM_Y * i),
					szBuf);
			}
			sprintf_s(szBuf, "%.1f", gp->fAvGrade);
		}
		//sprintf_s(szBuf, ".1f", )

	gUtil::EndText();

	if(m_uimode == UIM_SUGANG)
	{
		gUtil::SetSize(SUBINFO_AVGRADE_FONTSIZE);
		gUtil::BeginText();
			gUtil::Text(SUBINFO_AVGRADE_POS_X, SUBINFO_AVGRADE_POS_Y, szBuf);
		gUtil::EndText();
		gUtil::SetDefaultFont();
	}
}


/*
#define SUBINFO_ID_POS_X					200
#define SUBINFO_ID_POS_Y					200
#define SUBINFO_SUBNAME_POS_X				200
#define SUBINFO_GRADE_POS_X					300
#define SUBINFO_SUBNAME_POS_Y				220
#define SUBINFO_SUBNAME_TERM_Y				20
#define SUBINFO_AVGRADE_POS_X				300
#define SUBINFO_AVGRADE_POS_Y				360
*/

void gUIGame::Release()
{
	int			i;

	for(i = 0; i < UIIMG_END; i++)
		m_ImgUI[i].Release();

	for(i = 0; i < UIBTN_END; i++)
		m_BtnUI[i].Release();

	m_Scroll.Release();
}

bool gUIGame::OnLButtonDown()
{
	gPlayerContainer	*gPC	= gPlayerContainer::GetIF();
	gMouse				*mouse	= gMouse::GetIF();
	gGameCore			*gc		= gGameCore::GetIF();
	gItemContainer		*ic		= gItemContainer::GetIF();
	gMap				*map	= gMap::GetIF();

	m_Scroll.OnLbuttonDown(mouse->m_nPosX, mouse->m_nPosY);

	if(m_uimode == UIM_INFOCHANGE
		|| m_uimode == UIM_ITEMUSEINFO)
		return false;
	
	if(m_BtnUI[UIBTN_DICE].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(gc->m_bMoving || gc->m_bBusing)
			return true;
		if(gPC->isTurn(gc->m_nTurn))
			gc->SendMoveAsk();

		return true;
	}
	if(m_BtnUI[UIBTN_SUBJECT].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(m_uimode != UIM_SUGANG)
		{
			m_nSubSel	= gPC->GetMyGPIndex();
			m_uimode	= UIM_SUGANG;
		}
		else
			m_uimode	= UIM_NONE;

		return true;
	}
	if(m_BtnUI[UIBTN_ITEMCARD].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(m_uimode != UIM_ITEM)
		{
			if(gPC->GetMyItemNum() > 0)
				m_uimode	= UIM_ITEM;
			else
				gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_20);
		}
		else
			m_uimode	= UIM_NONE;

		return true;
	}

	switch(m_uimode)
	{
		case UIM_ITEM:				// 아이템 모드
			{
				if(gPC->GetMyGPIndex() != gGameCore::GetIF()->m_nTurn)
					return true;
				if(gGameCore::GetIF()->m_bMoved)
					return true;
				if(m_bItemUsed)
					return true;

				m_bTargetByMove = false;

				int		i;
				for(i = 0; i < MAXITEMNUM; i++)
				{
					if(gPC->m_MyGamePlayer.nItem[i] == -1)
						continue;

					RECT	rcTemp;
					rcTemp.left		= ITEMCARD_POS_X + (ITEMCARD_POS_X + ITEMCARDIMG_W) * i;
					rcTemp.right	= rcTemp.left + ITEMCARDIMG_W;
					rcTemp.top		= ITEMCARD_POS_Y;
					rcTemp.bottom	= rcTemp.top + ITEMCARDIMG_H;

					if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, rcTemp))
					{
						int					ItemIdx = gPC->m_MyGamePlayer.nItem[i];
						ITEMCARD			*item = &ic->m_ItemList[ ItemIdx ];
						PK_ITEMUSE_ASK		ask;

						switch(item->type)
						{
							case ITEM_STAT: case ITEM_STAMINA: case ITEM_NOCLASS: case ITEM_TOGETHERCLASS:
								{
									if(item->target == TARGET_OTHER || item->target == TARGET_MEOTHER)
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_TARGETSELECT;
									}
									else
									{
										strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
										ask.nItemID = ItemIdx;

										gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof ask, &ask);
										m_bItemUsed = true;
									}
								}
								break;
							case ITEM_MOVEPLACE:
								{
									if(item->target == TARGET_OTHER || item->target == TARGET_MEOTHER)
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_TARGETSELECT;
										m_bTargetByMove = true;
									}
									else
									{
										strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
										ask.nItemID = ItemIdx;

										gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof ask, &ask);
										m_bItemUsed = true;
									}
								}
								break;
							case ITEM_MOVESELECT:
								{
									if(item->target == TARGET_OTHER || item->target == TARGET_MEOTHER)
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_TARGETSELECT;
										m_bTargetByMove = true;
									}
									else
									{
										m_nItemID	= ItemIdx;
										m_uimode	= UIM_PLACESELECT;
									}
								}
								break;
						}
						return true;
					}
				}
			}
		break;
	case UIM_TARGETSELECT:
		{
			POINT		pt;
			pt.x = mouse->m_nPosX;
			pt.y = mouse->m_nPosY;

			int		nPos = map->viewabsToCon(pt);
			int		numchar = gPC->GetCharNumPos(nPos);

			if(gPC->m_MyGamePlayer.nPos == nPos)
				numchar--;

			if(numchar <= 0)
				break;
			else if(numchar == 1)
			{
				GAMEPLAYER	*target = gPC->GetPlayerByPos(nPos);

				if(m_bTargetByMove)
				{
					strcpy(m_szTarget, target->szID);
					m_uimode = UIM_PLACESELECT;
				}
				else
				{
					PK_ITEMUSE_ASK		ask;
					ask.nItemID	= m_nItemID;
					strcpy(ask.szID, gPC->m_MyPlayer.szID);
					strcpy(ask.szTarget, target->szID);

					gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof(ask), &ask);
					m_uimode = UIM_NONE;
					m_bItemUsed = true;
				}
			}
			else
			{
				m_uimode = UIM_TARGETSELECT_MULTI;
				SetTargetButton(nPos, numchar);
			}
		}
		break;
	case UIM_TARGETSELECT_MULTI:
		{
			int		i;

			for(i = 0; i < m_nTargetNum; i++)
			{
				if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, m_target[i].rcPos))
				{
					if(m_bTargetByMove)
					{
						strcpy(m_szTarget, gPC->m_GPlayerList[ m_target[i].idx ].szID);
						m_uimode = UIM_PLACESELECT;

						break;
					}
					else
					{
						PK_ITEMUSE_ASK		ask;

						strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
						strcpy(ask.szTarget, gPC->m_GPlayerList[ m_target[i].idx ].szID);
						ask.nItemID = m_nItemID;

						gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof(ask), &ask);
						m_uimode = UIM_NONE;
						m_bItemUsed = true;
						break;
					}
				}
			}
		}
		break;
	case UIM_PLACESELECT:
		{
			PK_ITEMUSE_ASK		ask;

			POINT	pt;
			pt.x = mouse->m_nPosX;
			pt.y = mouse->m_nPosY;

			int		nPos = map->viewabsToCon(pt);
			if(map->tileMap[nPos].tileType != TY_NONE)
			{
				strcpy(ask.szID, gPC->m_MyGamePlayer.szID);
				ask.nStartPos	= gPC->m_MyGamePlayer.nPos;
				ask.nDestPos	= nPos;
				if(m_bTargetByMove)
				{
					strcpy(ask.szTarget, m_szTarget);
					m_bTargetByMove = false;
				}
				ask.nItemID = m_nItemID;
				gServer::GetIF()->Send(PL_ITEMUSE_ASK, sizeof(ask), &ask);
				m_uimode = UIM_NONE;
				m_bItemUsed = true;
			}
		}
		break;
	case UIM_SUGANG:				// 수강현황 모드
		{
			if(m_BtnUI[UIBTN_SUBPREV].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				while(true)
				{
					m_nSubSel--;
					if(m_nSubSel < 0)
						m_nSubSel = ROOMMAXPLAYER - 1;

					if(strlen(gPC->m_GPlayerList[m_nSubSel].szID) == 0)
						continue;

					break;
				}
				return true;
			}
			if(m_BtnUI[UIBTN_SUBNEXT].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				while(true)
				{
					m_nSubSel++;
					if(m_nSubSel >= ROOMMAXPLAYER)
						m_nSubSel = 0;

					if(strlen(gPC->m_GPlayerList[m_nSubSel].szID) == 0)
						continue;

					break;
				}
				return true;
			}
		}
		break;
	}

	return false;
}

void gUIGame::SetTargetButton(int nPos, int charmax)
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	m_nTargetNum = charmax;

	int			i;
	int			nCount = 0;

	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(pc->m_GPlayerList[i].szID) != 0)
		{
			if(pc->m_GPlayerList[i].nPos == nPos)
			{
				if(strcmp(pc->m_GPlayerList[i].szID, pc->m_MyGamePlayer.szID) != 0)
				{
					m_target[nCount].img = &pc->m_ImgInfo[ pc->m_GPlayerList[i].ctype ].ImgPic;
					m_target[nCount].idx = i;
					nCount++;
				}
			}
		}
	}

	// pos set - 구찮다. 케이스별로 하드코딩하자
	int		startx, starty;
	switch(m_nTargetNum)
	{
		case 2:
			{
				// ㅁ ㅁ
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W - TARGET_TERM_X/2;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H / 2;
				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 3:
			{
				// ㅁ ㅁ ㅁ 
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H / 2;
				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 4:
			{
				// ㅁ ㅁ ㅁ ㅁ
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 2 - TARGET_TERM_X * 3/2;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H / 2;
				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 5:
			{
				//  ㅁ ㅁ
				// ㅁ ㅁ ㅁ 
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W - TARGET_TERM_X/2;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H - TARGET_TERM_Y/2;
				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty += (TARGET_TERM_Y + TARGET_OUTLINE_SIZE_H);
				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 6:
			{
				// ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ 
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H - TARGET_TERM_Y/2;
				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty += (TARGET_TERM_Y + TARGET_OUTLINE_SIZE_H);
				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
		case 7:
			{
				//  ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ ㅁ
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 3/2 - TARGET_TERM_X;
				starty = TARGET_POS_CENTER_Y - TARGET_OUTLINE_SIZE_H - TARGET_TERM_Y/2;
				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
				startx = TARGET_POS_CENTER_X - TARGET_OUTLINE_SIZE_W * 2 - TARGET_TERM_X * 3/2;
				starty += (TARGET_TERM_Y + TARGET_OUTLINE_SIZE_H);
				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X),
						starty,
						startx + i * (TARGET_OUTLINE_SIZE_W + TARGET_TERM_X) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H);
				}
			}
			break;
	}
}

void gUIGame::OnLButtonUp()
{
	gMouse				*mouse	= gMouse::GetIF();

	m_Scroll.OnLbuttonUp(mouse->m_nPosX, mouse->m_nPosY);
}

void gUIGame::OnMouseMove()
{
	gMouse		*mouse = gMouse::GetIF();

	int			i;

	m_Scroll.OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);

	for(i = 0; i < UIBTN_END; i++)
	{
		if(!m_BtnUI[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_BtnUI[i].m_eBtnMode = EBM_NONE;
		else
			m_BtnUI[i].m_eBtnMode = EBM_HOVER;
	}

}

void gUIGame::OnRButtonDown()
{
	if(m_uimode == UIM_TARGETSELECT)
	{
		m_uimode = UIM_ITEM;
		return;
	}
	if(m_uimode == UIM_TARGETSELECT_MULTI)
	{
		m_uimode = UIM_TARGETSELECT;
		return;
	}
	if(m_uimode == UIM_PLACESELECT)
	{
		if(m_bTargetByMove)
			m_uimode = UIM_TARGETSELECT;
		else
			m_uimode = UIM_ITEM;
		return;
	}
	if(m_uimode != UIM_NONE)
		m_uimode = UIM_NONE;
}

bool gUIGame::IsUIRange(int x, int y)
{
	int			i;

	for(i = 0; i < UIT_END; i++)
	{
		if( i == UIT_SUBWND && m_uimode != UIM_SUGANG )
			continue;

		if(gUtil::PointInRect(x, y, m_rcPos[i]))
			return true;
	}

	return false;
}

void gUIGame::SetRankList()
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	memset(m_rankIdx, -1, sizeof(int) * ROOMMAXPLAYER);

	int			nRank = 1;
	int			nCount = 0;
	int			i;

	while(true)
	{
		for(i = 0; i < ROOMMAXPLAYER; i++)
		{
			if(strlen(gPC->m_GPlayerList[i].szID) == 0)
				continue;

			if(gPC->m_GPlayerList[i].nRank == nRank)
				m_rankIdx[nCount++] = i;

			if(nCount >= m_nMaxPInfo)
				return;
		}
		nRank++;
	}

}

void gUIGame::FirstInit()
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	m_nCurPInfo = 0;
	m_nMaxPInfo	= gPlayerContainer::GetIF()->GetGPNum();
// 
// 	int		i;
// 
// 	for(i = m_nCurPInfo; i < ROOMMAXPLAYER; i++)
// 	{
// 		if(strlen(gPC->m_GPlayerList[i].szID) != 0)
// 		{
// 			m_nCurPInfo = i;
// 			return;
// 		}
// 	}
}


void gUIGame::SetPopInfo(PK_POPINFO_REP *rep, int ms)
{
	if(m_bPopInfo)
		return;

	m_bPopInfo	= true;
	m_nTimer	= GetTickCount();
	m_nShowTime	= ms;

	memcpy(&m_popinfo, rep, sizeof(PK_POPINFO_REP));
}

bool gUIGame::Restore()
{
	int			i;

	for(i = 0; i < UIIMG_END; i++)
		if(!m_ImgUI[i].Restore())
			return false;
	for(i = 0; i < UIBTN_END; i++)
		if(!m_BtnUI[i].Restore())
			return false;

	if(!m_Scroll.Restore())
		return false;

	return true;
}

void gUIGame::DrawTargetButton()
{
	int		i;

	for(i = 0; i < m_nTargetNum; i++)
	{
		m_target[i].img->Draw(m_target[i].rcPos.left + 1, m_target[i].rcPos.top + 1);
		m_ImgUI[UIIMG_FACEOUTLINE].Draw(m_target[i].rcPos.left, m_target[i].rcPos.top);
	}
}

void gUIGame::pk_itemuse_rep(PK_ITEMUSE_REP* rep)
{
	gItemContainer		*ic = gItemContainer::GetIF();
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	ITEMCARD	*item = &ic->m_ItemList[rep->nItemID];
	int			userIdx	= pc->GetGPIndex(rep->szUser);

	m_nCardIdx = rep->nItemID;

	// 사용자 셋팅
	m_itemuser.idx = userIdx;
	m_itemuser.img = &pc->m_ImgInfo[ pc->m_GPlayerList[userIdx].ctype ].ImgPic;
	SetRect(&m_itemuser.rcPos,
		USEINFO_USER_POS_X - TARGET_OUTLINE_SIZE_W/2,
		USEINFO_USER_POS_Y,
		USEINFO_USER_POS_X - TARGET_OUTLINE_SIZE_W/2 + TARGET_OUTLINE_SIZE_W,
		USEINFO_USER_POS_Y + TARGET_OUTLINE_SIZE_H );


	switch(item->target)
	{
		case TARGET_ME:
			{
				m_nTargetNum = 1;
				m_target[0] = m_itemuser;
				m_target[0].rcPos.left = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				m_target[0].rcPos.right = m_target[0].rcPos.left + TARGET_OUTLINE_SIZE_W;
			}
			break;
		case TARGET_OTHER:
			{
				m_nTargetNum = 1;
				int	targetIdx = pc->GetGPIndex(rep->szTarget);

				m_target[0].idx = targetIdx;
				m_target[0].img = &pc->m_ImgInfo[ pc->m_GPlayerList[targetIdx].ctype ].ImgPic;
				m_target[0].rcPos = m_itemuser.rcPos;
				m_target[0].rcPos.left = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				m_target[0].rcPos.right = m_target[0].rcPos.left + TARGET_OUTLINE_SIZE_W;
			}
			break;
		case TARGET_MEOTHER:
			{
				m_nTargetNum = 2;
				// 나
				m_target[0] = m_itemuser;

				// 상대
				int	targetIdx = pc->GetGPIndex(rep->szTarget);

				m_target[1].idx = targetIdx;
				m_target[1].img = &pc->m_ImgInfo[ pc->m_GPlayerList[targetIdx].ctype ].ImgPic;

				int		i;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case TARGET_ALL:
			{
				m_nTargetNum = pc->GetGPNum();

				// 나
				m_target[0] = m_itemuser;
				// 다른 애들
				int		i;
				int		nCount = 1;
				for(i = 0; i < ROOMMAXPLAYER; i++)
				{
					if(strlen(pc->m_GPlayerList[i].szID) != 0)
					{
						if(strcmp(pc->m_GPlayerList[i].szID, pc->m_MyGamePlayer.szID) == 0)
							continue;

						m_target[nCount].idx = i;
						m_target[nCount].img = &pc->m_ImgInfo[ pc->m_GPlayerList[i].ctype ].ImgPic;
						nCount++;
					}
				}
				SetTargetButton_UseInfo();
			}
			break;
		case TARGET_ALLEXCEPTME:
			{
				m_nTargetNum = pc->GetGPNum() - 1;

				int		i, j;
				j = 0;
				for(i = 0; i < ROOMMAXPLAYER; i++)
				{
					if(strlen(pc->m_GPlayerList[i].szID) != 0)
					{
						if(strcmp(pc->m_GPlayerList[i].szID, pc->m_MyGamePlayer.szID) == 0)
							continue;

						m_target[j].idx = i;
						m_target[j].img = &pc->m_ImgInfo[ pc->m_GPlayerList[i].ctype ].ImgPic;
						j++;
					}
				}
				SetTargetButton_UseInfo();
			}
			break;
	}
	m_uimode = UIM_ITEMUSEINFO;
	m_timer.frameStart(USEINFO_TICK, 2);
}

void gUIGame::SetTargetButton_UseInfo()
{
	switch(m_nTargetNum)
	{
		case 1:
			{
				// ㅁ
				m_target[0].rcPos = m_itemuser.rcPos;
				m_target[0].rcPos.left = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				m_target[0].rcPos.right = m_target[0].rcPos.left + TARGET_OUTLINE_SIZE_W;

			}
			break;
		case 2:
			{
				// ㅁ
				// ㅁ
				int		i;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 3:
			{
				// ㅁ
				// ㅁ
				// ㅁ
				int		i;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 4:
			{
				// ㅁ ㅁ
				// ㅁ ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}

				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 5:
			{
				//   ㅁ
				// ㅁ
				//   ㅁ 
				// ㅁ
				//   ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}

				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 6:
			{
				// ㅁ ㅁ
				// ㅁ ㅁ
				// ㅁ ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;

				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}

				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 7:
			{
				//       ㅁ
				// ㅁ ㅁ
				//       ㅁ
				// ㅁ ㅁ
				//       ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}

				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;
				for(j = 0; i < 4; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
		case 8:
			{
				//    ㅁ ㅁ
				// ㅁ 
				//    ㅁ ㅁ 
				// ㅁ
				//    ㅁ ㅁ
				int		i, j;
				int		startx = USEINFO_TARGET_POS_X - TARGET_OUTLINE_SIZE_W - USEINFO_TARGET_TERM_X/2;
				int		starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H - USEINFO_TARGET_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + i * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;

				for(j = 0; i < 5; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
				startx += (TARGET_OUTLINE_SIZE_W + USEINFO_TARGET_TERM_X);
				starty = USEINFO_TARGET_POS_Y - TARGET_OUTLINE_SIZE_H*3/2 - USEINFO_TARGET_TERM_Y;
				for(j = 0; i < m_nTargetNum; i++, j++)
				{
					SetRect(&m_target[i].rcPos,
						startx,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y),
						startx + TARGET_OUTLINE_SIZE_W,
						starty + j * (TARGET_OUTLINE_SIZE_H + USEINFO_TARGET_TERM_Y) + TARGET_OUTLINE_SIZE_H );
				}
			}
			break;
	}
}

void gUIGame::pk_infochange_rep(PK_INFOCHANGE_REP *rep)
{
	int		i;
	int		nCount = 0;
	
	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(rep->info[i].szID) == 0)
			continue;

		m_info[nCount] = rep->info[i];
		nCount++;
	}
	m_uimode = UIM_INFOCHANGE;
	m_timer.frameStart(INFOCHANGE_TICK, 2);
	m_nTargetNum = nCount;
	SetTargetButton_InfoChange();
}

void gUIGame::SetTargetButton_InfoChange()
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();

	int		i;

	for(i = 0; i < m_nTargetNum; i++)
	{
		m_target[i].idx		= pc->GetGPIndex(m_info[i].szID);
		m_target[i].img		= &pc->m_ImgInfo[ pc->m_GPlayerList[ m_target[i].idx ].ctype ].ImgPic;
	}

	switch(m_nTargetNum)
	{
		case 1:
			{
				//	ㅁ
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H/2;

				SetRect(&m_target[0].rcPos,
					startx, starty,
					startx + TARGET_OUTLINE_SIZE_W,
					starty + TARGET_OUTLINE_SIZE_H );
			}
			break;
		case 2:
			{
				// ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W) - INFOCHANGE_TERM_X/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 3:
			{
				// ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 4:
			{
				// ㅁ ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*2 - INFOCHANGE_TERM_X/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H/2;

				for(i = 0; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 5:
			{
				//  ㅁ ㅁ
				// ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W) - INFOCHANGE_TERM_X/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H - INFOCHANGE_TERM_Y/2;

				for(i = 0; i < 2; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}

				startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				starty += (TARGET_OUTLINE_SIZE_H + INFOCHANGE_TERM_Y);

				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 6:
			{
				// ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H - INFOCHANGE_TERM_Y/2;

				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}

				startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				starty += (TARGET_OUTLINE_SIZE_H + INFOCHANGE_TERM_Y);

				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 7:
			{
				//  ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*3/2 - INFOCHANGE_TERM_X;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H - INFOCHANGE_TERM_Y/2;

				for(i = 0; i < 3; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}

				startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*2 - INFOCHANGE_TERM_X/2;
				starty += (TARGET_OUTLINE_SIZE_H + INFOCHANGE_TERM_Y);

				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
		case 8:
			{
				// ㅁ ㅁ ㅁ ㅁ
				// ㅁ ㅁ ㅁ ㅁ
				int		i;
				int		startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*2 - INFOCHANGE_TERM_X/2;
				int		starty = INFOCHANGE_POS_Y - TARGET_OUTLINE_SIZE_H - INFOCHANGE_TERM_Y/2;

				for(i = 0; i < 4; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}

				startx = INFOCHANGE_POS_X - (TARGET_OUTLINE_SIZE_W + INFOCHANGE_INFOSIZE_W)*2 - INFOCHANGE_TERM_X/2;
				starty += (TARGET_OUTLINE_SIZE_H + INFOCHANGE_TERM_Y);

				for(; i < m_nTargetNum; i++)
				{
					SetRect(&m_target[i].rcPos,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W),
						starty,
						startx + i * (INFOCHANGE_INFOSIZE_W + INFOCHANGE_TERM_X + TARGET_OUTLINE_SIZE_W) + TARGET_OUTLINE_SIZE_W,
						starty + TARGET_OUTLINE_SIZE_H	);
				}
			}
			break;
	}
}

void gUIGame::Draw_InfoChange()
{
	DrawTargetButton();

	int		i, j;
	int		nCount;		// change info갯수

	char	szBuf[5][64];
	gUtil::BeginText();
	for(i = 0; i < m_nTargetNum; i++)
	{
		nCount = 0;
		if(m_info[i].nLang != 0)
		{
			if(m_info[i].nLang > 0)
				wsprintf(szBuf[nCount], "언어 + %d", m_info[i].nLang);
			else
				wsprintf(szBuf[nCount], "언어 - %d", -m_info[i].nLang);
			nCount++;
		}
		if(m_info[i].nMath != 0)
		{
			if(m_info[i].nMath > 0)
				wsprintf(szBuf[nCount], "수리 + %d", m_info[i].nMath);
			else
				wsprintf(szBuf[nCount], "수리 - %d", -m_info[i].nMath);
			nCount++;
		}
		if(m_info[i].nArt != 0)
		{
			if(m_info[i].nArt > 0)
				wsprintf(szBuf[nCount], "예술 + %d", m_info[i].nArt);
			else
				wsprintf(szBuf[nCount], "예술 - %d", -m_info[i].nArt);
			nCount++;
		}
		if(m_info[i].nStamina != 0)
		{
			if(m_info[i].nStamina > 0)
				wsprintf(szBuf[nCount], "체력 + %d", m_info[i].nStamina);
			else
				wsprintf(szBuf[nCount], "체력 - %d", -m_info[i].nStamina);
			nCount++;
		}
		if(m_info[i].nGrade != 0)
		{
			if(m_info[i].nGrade > 0)
				wsprintf(szBuf[nCount], "수업 + %d", m_info[i].nGrade);
			else
				wsprintf(szBuf[nCount], "수업 - %d", -m_info[i].nGrade);
			nCount++;
		}
		int		startx, starty;

		startx = m_target[i].rcPos.right + 10;
		starty = m_target[i].rcPos.top + TARGET_OUTLINE_SIZE_H/2
					- INFOCHANGE_INFOSIZE_H * nCount/2 - INFOCHANGE_INFOTERM_Y * (nCount - 1)/2;

		for(j = 0; j < nCount; j++)
			gUtil::Text(startx, starty + j * (INFOCHANGE_INFOSIZE_H + INFOCHANGE_INFOTERM_Y), szBuf[j]);
	}
	gUtil::EndText();
}