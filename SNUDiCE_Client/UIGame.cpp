#include <stdio.h>
#include "UIGame.h"
#include "Util.h"
#include "PlayerContainer.h"
#include "GameCore.h"
#include "Mouse.h"
#include "MainWin.h"
#include "SubjectContainer.h"
#include "Chat.h"

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

#define ITEMCARD_POS_X						10
#define ITEMCARD_POS_Y						50
#define ITEMCARD_TERM_X						10


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

	m_bShowSubWnd = false;

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

	m_bPopInfo = false;

	m_nCurPInfo = 0;

	m_bItem = false;

	return true;
}

void gUIGame::MainLoop()
{
	if(m_bPopInfo)
	{
		if((int)GetTickCount() - m_nTimer > m_nShowTime)
			m_bPopInfo = false;
	}
	
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

	// MainInfo
	gPC->m_ImgInfo[gPC->m_MyGamePlayer.ctype].ImgPic.Draw(MAININFO_PIC_POS_X, MAININFO_PIC_POS_Y);
	m_ImgUI[UIIMG_MAININFO].Draw(UI_POS_MAININFO_X, UI_POS_MAININFO_Y);

	m_rcBarDest.right = m_rcBarDest.left + gPC->m_MyGamePlayer.nStamina * MAININFO_BARGUAGE_SIZE_W / 10;
	m_ImgUI[UIIMG_BARGUAGE].Draw(m_rcBarDest, m_rcBarSour);
	m_ImgUI[UIIMG_BAROUTLINE].Draw(MAININFO_BARLINE_POS_X, MAININFO_BARLINE_POS_Y);

	// Subinfo
	m_ImgUI[UIIMG_SUBINFO].Draw(SUBINFO_POS_X, SUBINFO_POS_Y);
	m_BtnUI[UIBTN_ITEMCARD].Draw();
	m_BtnUI[UIBTN_SUBJECT].Draw();

	if(m_bShowSubWnd)
	{
		m_ImgUI[UIIMG_SUBWND].Draw(SUBINFO_SUBWND_POS_X, SUBINFO_SUBWND_POS_Y);
		m_BtnUI[UIBTN_SUBPREV].Draw();
		m_BtnUI[UIBTN_SUBNEXT].Draw();
	}

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

	// item
	if(m_bItem)
	{
		for(i = 0; i < MAXITEMNUM; i++)
		{
			if(gPC->m_MyGamePlayer.nItem[i] == -1)
				continue;
			
			//ITEMCARD_POS_X

		}
	}

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
		if(m_bShowSubWnd)
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

	gUtil::SetSize(SUBINFO_AVGRADE_FONTSIZE);
	gUtil::BeginText();
	if(m_bShowSubWnd)
	{
		gUtil::Text(SUBINFO_AVGRADE_POS_X, SUBINFO_AVGRADE_POS_Y, szBuf);
	}
	gUtil::EndText();
	gUtil::SetDefaultFont();
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

	m_Scroll.OnLbuttonDown(mouse->m_nPosX, mouse->m_nPosY);

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
		if(!m_bShowSubWnd)
			m_nSubSel = gPC->GetMyGPIndex();

		m_bShowSubWnd = !m_bShowSubWnd;
		return true;
	}
	if(m_BtnUI[UIBTN_ITEMCARD].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(m_bShowSubWnd)
			m_bShowSubWnd = false;
		m_bItem = !m_bItem;
		return true;
	}

	if(m_bShowSubWnd)
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

	return false;
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
	if(m_bShowSubWnd)
		m_bShowSubWnd = !m_bShowSubWnd;
}

bool gUIGame::IsUIRange(int x, int y)
{
	int			i;

	for(i = 0; i < UIT_END; i++)
	{
		if( i == UIT_SUBWND && !m_bShowSubWnd )
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