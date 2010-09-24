#include "UIGame.h"
#include "Util.h"
#include "PlayerContainer.h"
#include "GameCore.h"

#define	UI_FILE_MAININFO					".\\Data\\Interface\\game_maininfo.img"
#define UI_SIZE_MAININFO_W					220
#define UI_SIZE_MAININFO_H					110
#define UI_POS_MAININFO_X					0
#define UI_POS_MAININFO_Y					0

#define MAININFO_ID_POS_X					100
#define MAININFO_ID_POS_Y					18
#define MAININFO_LANG_POS_X					100
#define MAININFO_LANG_POS_Y					33
#define MAININFO_MATH_POS_X					100
#define MAININFO_MATH_POS_Y					48
#define MAININFO_ART_POS_X					100
#define MAININFO_ART_POS_Y					63
#define MAININFO_DICE6_POS_X				180
#define MAININFO_DICE6_POS_Y				33
#define MAININFO_DICE4_POS_X				180
#define MAININFO_DICE4_POS_Y				51
#define MAININFO_NAME_POS_X					17
#define MAININFO_NAME_POS_Y					76

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
	// Maininfo
	if(!m_ImgUI[UIIMG_MAININFO].Load(UI_FILE_MAININFO))
		return false;
	SetRect(&m_rcPos[UIT_MAININFO],
			UI_POS_MAININFO_X,
			UI_POS_MAININFO_Y,
			UI_POS_MAININFO_X + UI_SIZE_MAININFO_W,
			UI_POS_MAININFO_Y + UI_SIZE_MAININFO_H );



	return true;
}

void gUIGame::MainLoop()
{
	
}

void gUIGame::Draw()
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	// MainInfo
	m_ImgUI[UIIMG_MAININFO].Draw(UI_POS_MAININFO_X, UI_POS_MAININFO_Y);
	

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

		gUtil::Text(MAININFO_NAME_POS_X, MAININFO_NAME_POS_Y, gPC->m_CharInfo[gPC->m_MyGamePlayer.ctype].szName);

	gUtil::EndText();
}

void gUIGame::Release()
{
	int			i;

	for(i = 0; i < UIIMG_END; i++)
		m_ImgUI[i].Release();

}

void gUIGame::OnLButtonDown()
{

}

void gUIGame::OnLButtonUp()
{

}

void gUIGame::OnMouseMove()
{

}

void gUIGame::OnRButtonDown()
{

}

bool gUIGame::IsUIRange(int x, int y)
{
	int			i;

	for(i = 0; i < UIT_END; i++)
	{
		if(gUtil::PointInRect(x, y, m_rcPos[i]))
			return true;
	}

	return false;
}