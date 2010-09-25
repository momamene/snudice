#include <stdio.h>
#include "UIGame.h"
#include "Util.h"
#include "PlayerContainer.h"
#include "GameCore.h"
#include "Mouse.h"
#include "MainWin.h"
#include "SubjectContainer.h"

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
#define MAININFO_BARGUAGE_SIZE_W			150
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
#define SUBINFO_SUBWND_SIZE_H				216
#define SUBINFO_SUBWND_POS_X				((WNDSIZEW - SUBINFO_SUBWND_SIZE_W) / 2)
#define SUBINFO_SUBWND_POS_Y				((WNDSIZEH - SUBINFO_SUBWND_SIZE_H) / 2)
#define SUBINFO_ID_POS_X					200
#define SUBINFO_ID_POS_Y					200
#define SUBINFO_SUBNAME_POS_X				200
#define SUBINFO_GRADE_POS_X					300
#define SUBINFO_SUBNAME_POS_Y				220
#define SUBINFO_SUBNAME_TERM_Y				20
#define SUBINFO_AVGRADE_POS_X				300
#define SUBINFO_AVGRADE_POS_Y				360


#define PINFO_FILE_BACK						".\\Data\\Interface\\game_pinfo_back.img"
#define PINFO_SIZE_W						160
#define PINFO_SIZE_H						120
#define PINFO_POS_X							480
#define PINFO_POS_Y							360

#define DICEBTN_FILE						".\\Data\\Interface\\game_btn_dice.img"
#define DICEBTN_SIZE_W						100
#define DICEBTN_SIZE_H						101
#define DICEBTN_POS_X						515
#define DICEBTN_POS_Y						247


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

	// players info
	if(!m_ImgUI[UIIMG_PINFO].Load(PINFO_FILE_BACK))
		return false;
	SetRect(&m_rcPos[UIT_SUBINFO],
			PINFO_POS_X,
			PINFO_POS_Y,
			PINFO_POS_X + PINFO_SIZE_W,
			PINFO_POS_Y + PINFO_SIZE_H);

	// dice btn
	SetRect(&m_rcPos[UIT_DICE],
			DICEBTN_POS_X,
			DICEBTN_POS_Y,
			DICEBTN_POS_X + DICEBTN_SIZE_W,
			DICEBTN_POS_Y + DICEBTN_SIZE_H );
	if(!m_BtnUI[UIBTN_DICE].SetUp(DICEBTN_FILE, false, m_rcPos[UIT_DICE]))
		return false;

	return true;
}

void gUIGame::MainLoop()
{
	
}

void gUIGame::Draw()
{
	gPlayerContainer	*gPC	= gPlayerContainer::GetIF();
	gGameCore			*gc		= gGameCore::GetIF();
	gSubjectContainer	*sc		= gSubjectContainer::GetIF();

	// MainInfo
	gPC->m_ImgInfo[gPC->m_MyGamePlayer.ctype].ImgPic.Draw(MAININFO_PIC_POS_X, MAININFO_PIC_POS_Y);
	m_ImgUI[UIIMG_MAININFO].Draw(UI_POS_MAININFO_X, UI_POS_MAININFO_Y);

	m_rcBarDest.right = gPC->m_MyGamePlayer.nStamina * MAININFO_BARGUAGE_SIZE_W / 10;
	m_ImgUI[UIIMG_BARGUAGE].Draw(m_rcBarDest, m_rcBarSour);
	m_ImgUI[UIIMG_BAROUTLINE].Draw(MAININFO_BARLINE_POS_X, MAININFO_BARLINE_POS_Y);

	// Subinfo
	m_ImgUI[UIIMG_SUBINFO].Draw(SUBINFO_POS_X, SUBINFO_POS_Y);
	m_BtnUI[UIBTN_ITEMCARD].Draw();
	m_BtnUI[UIBTN_SUBJECT].Draw();

	if(m_bShowSubWnd)
		m_ImgUI[UIIMG_SUBWND].Draw(SUBINFO_SUBWND_POS_X, SUBINFO_SUBWND_POS_Y);

	// playersInfo
	m_ImgUI[UIIMG_PINFO].Draw(PINFO_POS_X, PINFO_POS_Y);
	
	// dice btn
	if(!gPC->isTurn(gc->m_nTurn))
		m_BtnUI[UIBTN_DICE].m_eBtnMode = EBM_CLICK;

	m_BtnUI[UIBTN_DICE].Draw();
	

	int		i;
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

	// sub - subwnd
		GAMEPLAYER	*gp = &gPC->m_GPlayerList[gPC->GetMyGPIndex()];
		for(i = 0; i < MAXSUBJECT; i++)
		{	
			gUtil::Text(SUBINFO_SUBNAME_POS_X, SUBINFO_SUBNAME_POS_Y + (SUBINFO_SUBNAME_TERM_Y * i),
					sc->m_subject[ gp->bySubIdx[i] ].subject);

			sprintf_s(szBuf, ".1f", gp->fGrade[i]);
			gUtil::Text(SUBINFO_GRADE_POS_X, SUBINFO_SUBNAME_POS_Y + (SUBINFO_SUBNAME_TERM_Y * i),
				szBuf);
		}
		//sprintf_s(szBuf, ".1f", )


	gUtil::EndText();
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

}

bool gUIGame::OnLButtonDown()
{
	gPlayerContainer	*gPC	= gPlayerContainer::GetIF();
	gMouse				*mouse	= gMouse::GetIF();
	gGameCore			*gc		= gGameCore::GetIF();

	if(m_BtnUI[UIBTN_DICE].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(gc->m_bMoving)
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

	return false;
}

void gUIGame::OnLButtonUp()
{

}

void gUIGame::OnMouseMove()
{
	gMouse		*mouse = gMouse::GetIF();

	int			i;

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