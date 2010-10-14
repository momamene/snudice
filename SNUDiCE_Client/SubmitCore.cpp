#include "SubmitCore.h"
#include "GameCore.h"
#include "Mouse.h"
#include "SubjectContainer.h"
#include "Util.h"
#include "Map.h"
#include "PlayerContainer.h"
#include "Server.h"
#include "PopUp.h"
#include "MainWin.h"
#include "stringconst.h"
#include "Chat.h"
#include "UIGame.h"

#define SUB_FILE_BACK				".\\Data\\Submit\\sub_back.img"

#define SUB_BTN_FILE_SELECT			".\\Data\\Submit\\sub_btn_select.img"
#define SUB_BTN_SIZE_SELECT_W		314
#define SUB_BTN_SIZE_SELECT_H		24
#define SUB_BTN_POS_SELECT_X		18
#define SUB_BTN_POS_SELECT_Y		85
#define SUB_BTN_TERM_SELECT_Y		20

#define SUB_TERM_SUBNAME_X			5
#define SUB_TERM_SUBNAME_Y			6
#define SUB_TERM_COLLEGE_X			105
#define SUB_TERM_COLLEGE_Y			6

#define SUB_POS_INFO_X				368
#define SUB_POS_INFO_Y				88

#define SUB_MINI_START_X			366
#define SUB_MINI_START_Y			193
#define SUB_MINI_SOLUTION			9

#define SUB_FILE_ICONPLAYER			".\\Data\\Submit\\sub_icon_player.img"
#define SUB_SIZE_ICONPLAYER_W		40
#define SUB_SIZE_ICONPLAYER_H		14
#define SUB_POS_ICONPLAYER_X		210
#define SUB_POS_ICONPLAYER_Y		88

#define SUB_BTN_FILE_CHANGE			".\\Data\\Submit\\sub_btn_change.img"
#define SUB_BTN_SIZE_CHANGE_W		125
#define SUB_BTN_SIZE_CHANGE_H		60
#define SUB_BTN_POS_CHANGE_X		363
#define SUB_BTN_POS_CHANGE_Y		400
#define SUB_BTN_FILE_READY			".\\Data\\Submit\\sub_btn_ready.img"
#define SUB_BTN_SIZE_READY_W		125
#define SUB_BTN_SIZE_READY_H		60
#define SUB_BTN_POS_READY_X			490
#define SUB_BTN_POS_READY_Y			400

#define SCRIPT_SUBJECT_COUNT_X		550
#define SCRIPT_SUBJECT_COUNT_Y		62
#define SCRIPT_SUBJECT_SCRIPT_X		365
#define SCRIPT_SUBJECT_SCRIPT_Y		86

#define SUB_FILE_MINIMAP			".\\Data\\Map\\minimap.img"
#define SUB_POS_MINIMAP_X			365
#define SUB_POS_MINIMAP_Y			190

static gSubmitCore s_SubmitCore;

gSubmitCore *gSubmitCore::GetIF()
{
	return &s_SubmitCore;
}

gSubmitCore::gSubmitCore(void)
{
}

gSubmitCore::~gSubmitCore(void)
{
}

bool gSubmitCore::SetUp()
{
	if(!m_ImgBack.Load(SUB_FILE_BACK))
		return false;

	if(!m_ImgMiniMap.Load(SUB_FILE_MINIMAP))
		return false;

	int		i;

	RECT	rcDest;

	SetRect(&rcDest,
			SUB_BTN_POS_SELECT_X,
			SUB_BTN_POS_SELECT_Y,
			SUB_BTN_POS_SELECT_X + SUB_BTN_SIZE_SELECT_W,
			SUB_BTN_POS_SELECT_Y + SUB_BTN_TERM_SELECT_Y );

	for(i = 0; i < CLASSNUM; i++)
	{
		if(!m_BtnClass[i].SetUp(SUB_BTN_FILE_SELECT, false, rcDest))
			return false;

		OffsetRect(&rcDest, 0, SUB_BTN_TERM_SELECT_Y);
	}

	m_nSelected = -1;

	if(!m_ImgIconPlayer.Load(SUB_FILE_ICONPLAYER))
		return false;

	SetRect(&rcDest,
			SUB_BTN_POS_CHANGE_X,
			SUB_BTN_POS_CHANGE_Y,
			SUB_BTN_POS_CHANGE_X + SUB_BTN_SIZE_CHANGE_W,
			SUB_BTN_POS_CHANGE_Y + SUB_BTN_SIZE_CHANGE_H);
	if(!m_BtnSub[BSUB_CHANGE].SetUp(SUB_BTN_FILE_CHANGE, false, rcDest))
		return false;

	SetRect(&rcDest,
		SUB_BTN_POS_READY_X,
		SUB_BTN_POS_READY_Y,
		SUB_BTN_POS_READY_X + SUB_BTN_SIZE_READY_W,
		SUB_BTN_POS_READY_Y + SUB_BTN_SIZE_READY_H);
	if(!m_BtnSub[BSUB_READY].SetUp(SUB_BTN_FILE_READY, false, rcDest))
		return false;

	m_bChange	= false;
	m_bReady	= false;

	return true;
}

void gSubmitCore::MainLoop()
{
	Draw();

	// popup â ó��
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
}

void gSubmitCore::Draw()
{
	m_ImgMiniMap.Draw(SUB_POS_MINIMAP_X, SUB_POS_MINIMAP_Y);
	m_ImgBack.Draw();

	int		i, j, count=0;


	RECT	rcDest, rcSour;

	// ������û��ư
	for(i = 0; i < CLASSNUM; i++)
	{
		for(j = 0; j < CLASSSEAT; j++)
		{
			if(m_subject[i][j] == AVAILSEAT)
				continue;

			SetRect(&rcDest,
					SUB_POS_ICONPLAYER_X,
					SUB_POS_ICONPLAYER_Y,
					SUB_POS_ICONPLAYER_X + SUB_SIZE_ICONPLAYER_W,
					SUB_POS_ICONPLAYER_Y + SUB_SIZE_ICONPLAYER_H );

			OffsetRect(&rcDest, j * SUB_SIZE_ICONPLAYER_W, i * SUB_BTN_TERM_SELECT_Y);

			SetRect(&rcSour,
					0, 0, SUB_SIZE_ICONPLAYER_W, SUB_SIZE_ICONPLAYER_H);

			if(m_subject[i][j] == NOSEAT)
			{
				OffsetRect(&rcSour, 0, ROOMMAXPLAYER * SUB_SIZE_ICONPLAYER_H);
			}
			else
			{
				if(m_subject[i][j]==gPlayerContainer::GetIF()->GetMyPIndex()) {
					count++;
				}
				OffsetRect(&rcSour, 0, m_subject[i][j] * SUB_SIZE_ICONPLAYER_H);
			}
			m_ImgIconPlayer.Draw(rcDest, rcSour);
		}
	}
	char szTemp[50]={0,};
	wsprintf(szTemp,"%d / 6 ����", count);

	for(i = 0; i < CLASSNUM; i++)
		m_BtnClass[i].Draw();

	if(m_bReady)
	{
		m_BtnSub[BSUB_READY].m_eBtnMode = EBM_CLICK;
	}

	if(m_bChange)
	{
		m_BtnSub[BSUB_CHANGE].m_eBtnMode = EBM_CLICK;
	}

	for(i = 0; i < BSUB_END; i++)
		m_BtnSub[i].Draw();


	// map
	//gMap::GetIF()->DrawHexagon(SUB_MINI_START_X, SUB_MINI_START_Y, SUB_MINI_SOLUTION, true);
	gMap::GetIF()->DrawSubmit(SUB_MINI_START_X, SUB_MINI_START_Y, SUB_MINI_SOLUTION, m_nSelected);

	gUtil::BeginText();
		for(i = 0; i < CLASSNUM; i++)
		{
			gUtil::Text(m_BtnClass[i].m_rcPos.left + SUB_TERM_SUBNAME_X, m_BtnClass[i].m_rcPos.top + SUB_TERM_SUBNAME_Y,
				gSubjectContainer::GetIF()->m_subject[i].subject);

			gUtil::Text(m_BtnClass[i].m_rcPos.left + SUB_TERM_COLLEGE_X, m_BtnClass[i].m_rcPos.top + SUB_TERM_COLLEGE_Y,
				gSubjectContainer::GetIF()->m_subject[i].college);
		}
		gUtil::Text(SCRIPT_SUBJECT_COUNT_X, SCRIPT_SUBJECT_COUNT_Y, szTemp, 15); //Modified
		
		if(m_nSelected!=-1) {
			i=m_nSelected;
			char szScript[200]={0,};
			gSubjectContainer *gSC=gSubjectContainer::GetIF();

			wsprintf(szScript, "���� ���: %s", gSC->m_subject[i].building);
			gUtil::Text(SCRIPT_SUBJECT_SCRIPT_X, SCRIPT_SUBJECT_SCRIPT_Y, szScript);
			wsprintf(szScript,"��米��: %s", gSC->m_subject[i].professor);
			gUtil::Text(SCRIPT_SUBJECT_SCRIPT_X+120, SCRIPT_SUBJECT_SCRIPT_Y, szScript);
			wsprintf(szScript,"%s", gSC->m_subject[i].script);
			
			int len=strlen(szScript), y=SCRIPT_SUBJECT_SCRIPT_Y+20, c=0;
			bool lineChange=0;
			char imsi[120]={0,}, temp2[200]={0,};

			for(i=0;i<len;i++) {
				if(i>23 && szScript[i]>0 && !lineChange) {
					imsi[c]=0; lineChange=1;
					wsprintf(temp2,"������: %s", imsi);
					gUtil::Text(SCRIPT_SUBJECT_SCRIPT_X, y, temp2);
					y+=12; c=0;
				}
				else imsi[c++]=szScript[i];
			}
			if(c) {
				imsi[c]=0;
				gUtil::Text(SCRIPT_SUBJECT_SCRIPT_X, y, imsi);
			}
		}

	gUtil::EndText();
}

void gSubmitCore::Release()
{
	m_ImgBack.Release();
	m_ImgMiniMap.Release();

	int			i;
	
	for(i = 0; i < CLASSNUM; i++)
		m_BtnClass[i].Release();

	m_ImgIconPlayer.Release();

	for(i = 0; i < BSUB_END; i++)
		m_BtnSub[i].Release();
}

void gSubmitCore::OnLButtonDown()
{
	gMouse		*mouse = gMouse::GetIF();

	int			i;

	if(m_bReady)
	{
		if(m_BtnSub[BSUB_READY].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			m_bReady = false;
		}
	}
	else
	{
		for(i = 0; i < CLASSNUM; i++)
		{
			if(m_BtnClass[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				PK_SUBMIT_ASK		ask;

				ask.nSubjectIdx	= i;
				strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);
				ask.bSubmit		= !m_bChange;

				gServer::GetIF()->Send(PL_SUBMIT_ASK, sizeof ask, &ask);
				return;
			}
		}

		if(m_BtnSub[BSUB_CHANGE].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			if(!m_bReady)
				m_bChange = !m_bChange;
		}
		if(m_BtnSub[BSUB_READY].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			if(!m_bChange)
			{
				PK_SUBMITREADY_ASK		ask;

				strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);

				gServer::GetIF()->Send(PL_SUBMITREADY_ASK, sizeof ask, &ask);
			}
		}
	}
}

void gSubmitCore::OnLButtonUp()
{

}

void gSubmitCore::OnMouseMove()
{
	gMouse		*mouse = gMouse::GetIF();

	int			i;

	for(i = 0; i < CLASSNUM; i++)
	{
		if(!m_BtnClass[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_BtnClass[i].m_eBtnMode = EBM_NONE;
		else
		{
			m_BtnClass[i].m_eBtnMode = EBM_HOVER;
			m_nSelected		= i;
		}
	}

	for(i = 0; i < BSUB_END; i++)
	{
		if(!m_BtnSub[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_BtnSub[i].m_eBtnMode = EBM_NONE;
		else
			m_BtnSub[i].m_eBtnMode = EBM_HOVER;
	}
}

void gSubmitCore::OnRButtonDown()
{

}

void gSubmitCore::SetSubject(BYTE *subj)
{
	memcpy(m_subject, subj, sizeof(BYTE) * CLASSNUM * CLASSSEAT);
}

void gSubmitCore::pk_submit_rep(PK_SUBMIT_REP *rep)
{
	SetSubject((BYTE*)rep->subject);
}

void gSubmitCore::pk_submitready_rep(PK_SUBMITREADY_REP *rep)
{
	switch(rep->result)
	{
		case ESUB_LESSCLASS:
			gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_16);
			break;
		case ESUB_SUCCESS:
			m_bReady = true;
			break;
	}
}

void gSubmitCore::pk_maingametart_rep(PK_MAINGAMESTART_REP *rep)
{
	gPlayerContainer::GetIF()->SetGPList(rep->list);
	gPlayerContainer::GetIF()->PacketalDrawFix();
	gGameCore::GetIF()->m_nTurn		= rep->nTurn;
	gMainWin::GetIF()->m_eCoreMode	= ECM_GAME;
	gChat::GetIF()->MsgStackClear();
	gUIGame::GetIF()->FirstInit();
	gUIGame::GetIF()->SetRankList();

}