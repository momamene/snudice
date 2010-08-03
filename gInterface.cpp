#include "gInterface.h"
#include "const.h"
#include "gMouse.h"
#include "gUtil.h"
#include "gGameCore.h"
#include "gPlayerManager.h"
#include "gTimer.h"
#include <stdio.h>
#include "gPopUp.h"

//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------

gInterface	s_Interface;

gInterface *gInterface::GetIF()
{
	return &s_Interface;
}


gInterface::gInterface()
{

}

gInterface::~gInterface()
{

}

bool gInterface::SetUp()
{
	m_bMenu = false;

	// menu img
	if(FAILED(m_ImgMenuback.Load(IF_IMG_MENUBACK)))
		return false;

	// menu btn 수강, 아이템, 시스템
	RECT	rcPos;
	SetRect(&rcPos, IF_POS_SUGANGX, IF_POS_SUGANGY,
		IF_POS_SUGANGX + IF_POS_MENUBTNW, IF_POS_SUGANGY + IF_POS_MENUBTNH);
	if(FAILED(m_BtnMenu[EBTN_SUGANG].SetUp(IF_IMG_SUGANG, false, rcPos)))
		return false;

	SetRect(&rcPos, IF_POS_ITEMX, IF_POS_ITEMY,
		IF_POS_ITEMX + IF_POS_MENUBTNW, IF_POS_ITEMY + IF_POS_MENUBTNH);
	if(FAILED(m_BtnMenu[EBTN_ITEMCARD].SetUp(IF_IMG_ITEM, false, rcPos)))
		return false;

	SetRect(&rcPos, IF_POS_SYSTEMX, IF_POS_SYSTEMY,
		IF_POS_SYSTEMX + IF_POS_MENUBTNW, IF_POS_SYSTEMY + IF_POS_MENUBTNH);
	if(FAILED(m_BtnMenu[EBTN_SYSTEM].SetUp(IF_IMG_SYSTEM, false, rcPos)))
		return false;

	// menu mode
	m_eMenuMode = EMM_END;

	// popup image (pop up 메뉴)
	if(FAILED(m_ImgMenu[EMM_ITEMCARD].Load(IF_IMG_ITEMBACK)))
		return false;
	if(FAILED(m_ImgMenu[EMM_SUGANG].Load(IF_IMG_SUGANGBACK)))
		return false;
	if(FAILED(m_ImgMenu[EMM_SYSTEM].Load(IF_IMG_SYSBACK)))
		return false;

	// tooltip
	if(!m_ImgTooltipBack.Load(TOOLTIP_IMG_BACK))
		return false;
	if(!m_ImgActive.Load(TOOLTIP_IMG_ACTIVE))
		return false;

	memset(&m_tooltip, 0, sizeof(TOOLTIP));
	m_bTooltip = false;

	return true;
}

void gInterface::DrawWindow(int mode){
	gGameCore *gameCore = gGameCore::GetIF();		// 스켈톤? 
	gPlayerManager *gplayerManager = gPlayerManager::GetIF();
	tileContainer *tilecontainer = tileContainer::GetIF();
	m_ImgMenu[mode].Draw(IF_POS_BACKX, IF_POS_BACKY);
	//RECT rc;
	if(mode == EMM_SUGANG){

		int tempIndex;
		char buf[128];
		int tile;
		double temp;
	
		
		gUtil::BeginText();
		for(int i = 0 ; i < gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.m_subjectN ; i++){
			if(1){	// 과목이 있다면.
				tile=tilecontainer->flagToFirstTile(gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.m_subject[i]);
				//gUtil::SetSize(10);
				gUtil::Text(IF_POS_BACKX+220,IF_POS_BACKY+60+i*15,tilecontainer->tileMap[tile].building);
				gUtil::Text(IF_POS_BACKX+220+70,IF_POS_BACKY+60+i*15,tilecontainer->tileMap[tile].subject);
				temp = gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.gradeExpectOne(i);
				sprintf(buf,"%.1f",temp);
				gUtil::Text(IF_POS_BACKX+220+70+120,IF_POS_BACKY+60+i*15,buf);
				temp = gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.gradeAverage();
				sprintf(buf,"%.1f",temp);
				//gUtil::SetSize(20);
				gUtil::Text(IF_POS_BACKX+220,IF_POS_BACKY+60+150,buf);
			}
		}
		gUtil::EndText();
	}
}


void gInterface::Draw()
{
	if(!gPopUp::GetIF()->isPopUp())
		DrawTooltip();

	m_ImgMenuback.Draw(IF_POS_MENUBACKX, IF_POS_MENUBACKY);

	int		i;
	for(i = 0; i < EBTN_END; i++)
			m_BtnMenu[i].Draw();

	if(m_eMenuMode != EMM_END)
		DrawWindow(m_eMenuMode);

}

void gInterface::MainLoop()
{
	Draw();
}

void gInterface::OnLButtonDown()
{
	gMouse	*mouse = gMouse::GetIF();

	int		i;
	for(i = 0; i < EBTN_END; i++)
	{
		if(m_BtnMenu[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			m_eMenuMode = (eMENUMODE)i;
			break;
		}
	}
}

void gInterface::OnLButtonUp()
{

}

void gInterface::OnMouseMove()
{
	gMouse	*mouse = gMouse::GetIF();

	int		i;
	for(i = 0 ; i < EBTN_END; i++)
	{
		if(m_BtnMenu[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_BtnMenu[i].m_eBtnMode = EBM_HOVER;
		else
			m_BtnMenu[i].m_eBtnMode = EBM_NONE;
	}
}

void gInterface::OnRButtonDown()
{
	gMouse	*mouse = gMouse::GetIF();

	if(m_eMenuMode != EMM_END)	// EMM_END means EMM_NONE
	{
		RECT	rcTemp;
		SetRect(&rcTemp, IF_POS_BACKX, IF_POS_BACKY,
			IF_POS_BACKX + IF_POS_SCARDW, IF_POS_BACKY + IF_POS_SCARDH);

		if(!gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, rcTemp))
		{
			m_eMenuMode		= EMM_END;
		}
	}
}

void gInterface::Release()
{
	int		i;

	m_ImgMenuback.Release();
	
	for(i = 0; i < EBTN_END; i++)
		m_BtnMenu[i].Release();

	for(i = 0; i < EMM_END; i++)
		m_ImgMenu[i].Release();

	m_ImgTooltipBack.Release();
	m_ImgActive.Release();

}

void gInterface::DrawTooltip()
{
	int			i, j;	
	char		szBuf[128];

	for(i = 0; i < EBTN_END; i++)
		if(m_BtnMenu[i].m_eBtnMode == EBM_HOVER)
			return;

	if(m_bTooltip && !gTimer::GetIF()->m_on
		&& m_eMenuMode == EMM_END)
	{
		RECT		rcDest;
		RECT		rcSour;
		
		SetRect(&rcDest, m_tooltip.nX,
			m_tooltip.nY,
			m_tooltip.nX + TOOLTIP_WIDTH,
			m_tooltip.nY + TOOLTIP_HEIGHT );
		
		SetRect(&rcSour, 0, 0, TOOLTIP_WIDTH, TOOLTIP_HEIGHT);
		
		OffsetRect(&rcSour, TOOLTIP_WIDTH * m_tooltip.type, 0);
		
		m_ImgTooltipBack.Draw(rcDest, rcSour, false);

		switch(m_tooltip.type)
		{
			case ETIP_LANG: case ETIP_MATH: case ETIP_ART:
				{
					RECT		rcDestAc;		// active
					RECT		rcSourAc;
					
			
					for(i = 0; i < 3; i++)		// 3 == 수강정원.... define으로 해야하는데 못찾겟다  상우야
					{
						if(m_tooltip.pPlayer[i])
						{
							SetRect(&rcDestAc,
								rcDest.left + 8,
								rcDest.top + 95,
								rcDest.left + 8 + TOOLTIP_ACTIVEW,
								rcDest.top + 95 + TOOLTIP_ACTIVEH );
							
							SetRect(&rcSourAc,
								0, 0, TOOLTIP_ACTIVEW, TOOLTIP_ACTIVEH);

							OffsetRect(&rcDestAc, i * (TOOLTIP_ACTIVEW + 4), 0);
							m_ImgActive.Draw(rcDestAc, rcSourAc, false);

							SetRect(&rcSourAc,
									0, 0, TOOLTIP_CHARIMGW, TOOLTIP_CHARIMGH);	// img

							OffsetRect(&rcDestAc, 0, -36);						// img
							m_tooltip.pPlayer[i]->m_charInfo->m_ImgTooltip.Draw(rcDestAc, rcSourAc, false);
						}
					}
					gUtil::BeginText();
						gUtil::Text(rcDest.left + 13, rcDest.top + 11, m_tooltip.szSubject);
						gUtil::Text(rcDest.left + 13, rcDest.top + 28, m_tooltip.szColleage);
						gUtil::Text(rcDest.left + 13, rcDest.top + 43, m_tooltip.szBuilding);

						int		nX, nY;
						int		temp, index;

						for(i = 0; i < 3; i++)
						{
							if(m_tooltip.pPlayer[i])
							{
								nX = rcDest.left + 8 + (TOOLTIP_ACTIVEW + 4) * i;
								nY = rcDest.bottom + 8;

							}
						}
						
					gUtil::EndText();
					break;
				}
		}

	}
}

/*
for(int i = 0 ; i < gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.m_subjectN ; i++){
if(1){	// 과목이 있다면.
tile=tilecontainer->flagToFirstTile(gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.m_subject[i]);
//gUtil::SetSize(10);
gUtil::Text(IF_POS_BACKX+220,IF_POS_BACKY+60+i*15,tilecontainer->tileMap[tile].building);
gUtil::Text(IF_POS_BACKX+220+70,IF_POS_BACKY+60+i*15,tilecontainer->tileMap[tile].subject);
temp = gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.gradeExpectOne(i);
sprintf(buf,"%.1f",temp);
gUtil::Text(IF_POS_BACKX+220+70+120,IF_POS_BACKY+60+i*15,buf);
temp = gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.gradeAverage();
sprintf(buf,"%.1f",temp);
//gUtil::SetSize(20);
gUtil::Text(IF_POS_BACKX+220,IF_POS_BACKY+60+150,buf);
			}
*/
void gInterface::ClearTooltip()
{
	m_bTooltip	= false;
	memset(&m_tooltip, 0, sizeof(TOOLTIP));
}

bool gInterface::isMenu()
{
	return m_bMenu;
}