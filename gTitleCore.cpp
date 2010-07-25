#include "const.h"
#include "gTitleCore.h"
#include "gMainWin.h"
#include "gMouse.h"
#include "gCharManager.h"
#include "gUtil.h"

//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------

static gTitleCore s_TitleCore;

gTitleCore::gTitleCore()
{

}

gTitleCore::~gTitleCore()
{

}

gTitleCore *gTitleCore::GetIF()
{
	return &s_TitleCore;
}

bool gTitleCore::SetUp()
{
	m_eMode = ETM_TITLE;

	if(FAILED(SetUp_Title()))
		return false;
	if(FAILED(SetUp_PlayerSelect()))
		return false;

	return true;
}

void gTitleCore::MainLoop()
{
	Draw();
}

void gTitleCore::Draw()
{
	int			i;

	switch(m_eMode)
	{
	case ETM_TITLE:
		Draw_Title();
		break;
	case ETM_PLAYERSEL:
		Draw_PlayerSelect();
		break;
	}
}

//------------------------------------------------------------------------------------
//	Mouse
//------------------------------------------------------------------------------------
void gTitleCore::OnLButtonDown()
{
	switch(m_eMode)
	{
		case ETM_TITLE:
			OnLButtonDown_Title();
			break;

		case ETM_PLAYERSEL:
			OnLButtonDown_PlayerSelect();
			break;
	}
		/*
	case ETM_CHARSEL:
		if(m_ImgBtnPrev.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			m_ImgBtnPrev.m_eBtnMode = EBM_NONE;
			m_eMode = ETM_PLAYERSEL;
			break;
		}
		if(m_ImgBtnNext.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			gMainWin::GetIF()->m_eCoreMode = EMC_GAME;
			break;
		}

// 		for(i = 0; i < CHARNUM; i++)
// 			if(m_ImgID[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
// 				gMainWin::GetIF()->m_eCoreMode = EMC_GAME;

		break;
		*/
}

void gTitleCore::OnLButtonUp()
{

}

void gTitleCore::OnMouseMove()
{
	switch(m_eMode)
	{
		case ETM_TITLE:
			OnMouseMove_Title();
			break;

		case ETM_PLAYERSEL:
			OnMouseMove_PlayerSelect();
			break;
	}
	
}

void gTitleCore::OnRButtonDown()
{

}

bool gTitleCore::SetUp_Title()
{
	RECT		rcBtn;

	// title img
	if(FAILED(m_ImgTitle.Load(TITLE_IMG_TITLE)))
		return false;
	
	// button setup
	SetRect(&rcBtn, TBT_START_X, TBT_START_Y,
		TBT_START_X + TBT_START_SIZEW, TBT_START_Y + TBT_START_SIZEH);
	if(FAILED(m_ImgBtn[ETB_START].SetUp(TBT_START_IMG, TBT_START_VERTICAL, rcBtn)))
		return false;
	
	SetRect(&rcBtn, TBT_EXIT_X, TBT_EXIT_Y,
		TBT_EXIT_X + TBT_EXIT_SIZEW, TBT_EXIT_Y + TBT_EXIT_SIZEH);
	if(FAILED(m_ImgBtn[ETB_EXIT].SetUp(TBT_EXIT_IMG, TBT_EXIT_VERTICAL, rcBtn)))
		return false;

	return true;
}

bool gTitleCore::SetUp_PlayerSelect()
{
	RECT	rcBtn;
	// prev next button setup
	SetRect(&rcBtn, TITLE_POS_PREVX, TITLE_POS_PREVY,
		TITLE_POS_PREVX + TITLE_POS_PREVW, TITLE_POS_PREVY + TITLE_POS_PREVH);
	if(FAILED(m_ImgBtnPrev.SetUp(TITLE_IMG_PREV, false, rcBtn)))
		return false;
	
	SetRect(&rcBtn, TITLE_POS_NEXTX, TITLE_POS_NEXTY,
		TITLE_POS_NEXTX + TITLE_POS_NEXTW, TITLE_POS_NEXTY + TITLE_POS_NEXTH);
	if(FAILED(m_ImgBtnNext.SetUp(TITLE_IMG_NEXT, false, rcBtn)))
		return false;


	if(FAILED(m_ImgPlayer.Load(PSEL_IMG_BACK)))
		return false;
	
	if(FAILED(m_ImgMode.Load(PSEL_IMG_MODE)))
		return false;
	
	if(FAILED(m_ImgNP[0].Load(PSEL_IMG_1P)))			//  0 -> 1p
		return false;
	if(FAILED(m_ImgNP[1].Load(PSEL_IMG_2P)))
		return false;
	if(FAILED(m_ImgNP[2].Load(PSEL_IMG_3P)))
		return false;
	if(FAILED(m_ImgNP[3].Load(PSEL_IMG_4P)))
		return false;
	
	// check
	if(FAILED(m_ImgCheck.Load(PSEL_IMG_CHECK)))
		return false;
	
	m_ePlayer[0] = EPS_PLAYER;
	m_ePlayer[1] = EPS_PLAYER;
	m_ePlayer[2] = EPS_PLAYER;
	m_ePlayer[3] = EPS_PLAYER;

	return true;
}

void gTitleCore::Draw_Title()
{
	int		i;

	m_ImgTitle.Draw(0, 0);
	
	for(i = 0; i < ETB_END; i++)
			m_ImgBtn[i].Draw();
}

void gTitleCore::Draw_PlayerSelect()
{
	m_ImgPlayer.Draw(0, 0);
	
	m_ImgNP[0].Draw(PSEL_POS_1PX, PSEL_POS_1PY);				// 0 -> 1p
	m_ImgNP[1].Draw(PSEL_POS_2PX, PSEL_POS_2PY);
	m_ImgNP[2].Draw(PSEL_POS_3PX, PSEL_POS_3PY);
	m_ImgNP[3].Draw(PSEL_POS_4PX, PSEL_POS_4PY);
	
	m_ImgMode.Draw(PSEL_POS_1MODEX, PSEL_POS_1PY);
	m_ImgMode.Draw(PSEL_POS_2MODEX, PSEL_POS_2PY);
	m_ImgMode.Draw(PSEL_POS_3MODEX, PSEL_POS_3PY);
	m_ImgMode.Draw(PSEL_POS_4MODEX, PSEL_POS_4PY);
	
	// btn
	m_ImgBtnPrev.Draw();
	m_ImgBtnNext.Draw();
	
	switch(m_ePlayer[0])
	{
		case EPS_PLAYER:
			m_ImgCheck.Draw(PSEL_POS_1MODEX + PSEL_POS_CHECKHELPX(1), PSEL_POS_CHECKHELPY(PSEL_POS_1PY));
			break;
		case EPS_COM:
			m_ImgCheck.Draw(PSEL_POS_1MODEX + PSEL_POS_CHECKHELPX(2), PSEL_POS_CHECKHELPY(PSEL_POS_1PY));
			break;
		case EPS_NONE:
			m_ImgCheck.Draw(PSEL_POS_1MODEX + PSEL_POS_CHECKHELPX(3), PSEL_POS_CHECKHELPY(PSEL_POS_1PY));
			break;
	}
	
	switch(m_ePlayer[1])
	{
		case EPS_PLAYER:
			m_ImgCheck.Draw(PSEL_POS_2MODEX + PSEL_POS_CHECKHELPX(1), PSEL_POS_CHECKHELPY(PSEL_POS_2PY));
			break;
		case EPS_COM:
			m_ImgCheck.Draw(PSEL_POS_2MODEX + PSEL_POS_CHECKHELPX(2), PSEL_POS_CHECKHELPY(PSEL_POS_2PY));
			break;
		case EPS_NONE:
			m_ImgCheck.Draw(PSEL_POS_2MODEX + PSEL_POS_CHECKHELPX(3), PSEL_POS_CHECKHELPY(PSEL_POS_2PY));
			break;
	}
	
	switch(m_ePlayer[2])
	{
		case EPS_PLAYER:
			m_ImgCheck.Draw(PSEL_POS_3MODEX + PSEL_POS_CHECKHELPX(1), PSEL_POS_CHECKHELPY(PSEL_POS_3PY));
			break;
		case EPS_COM:
			m_ImgCheck.Draw(PSEL_POS_3MODEX + PSEL_POS_CHECKHELPX(2), PSEL_POS_CHECKHELPY(PSEL_POS_3PY));
			break;
		case EPS_NONE:
			m_ImgCheck.Draw(PSEL_POS_3MODEX + PSEL_POS_CHECKHELPX(3), PSEL_POS_CHECKHELPY(PSEL_POS_3PY));
			break;
	}
	
	switch(m_ePlayer[3])
	{
		case EPS_PLAYER:
			m_ImgCheck.Draw(PSEL_POS_4MODEX + PSEL_POS_CHECKHELPX(1), PSEL_POS_CHECKHELPY(PSEL_POS_4PY));
			break;
		case EPS_COM:
			m_ImgCheck.Draw(PSEL_POS_4MODEX + PSEL_POS_CHECKHELPX(2), PSEL_POS_CHECKHELPY(PSEL_POS_4PY));
			break;
		case EPS_NONE:
			m_ImgCheck.Draw(PSEL_POS_4MODEX + PSEL_POS_CHECKHELPX(3), PSEL_POS_CHECKHELPY(PSEL_POS_4PY));
			break;
	}
}

void gTitleCore::OnLButtonDown_Title()
{
	gMouse	*mouse = gMouse::GetIF();

	int		i;

	for(i = 0; i < ETB_END; i++)
	{
		if(m_ImgBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			m_ImgBtn[i].m_eBtnMode = EBM_NONE;
			break;
		}
	}
	
	switch((eTITLE_BTN)i)
	{
		case ETB_START:
			m_eMode = ETM_PLAYERSEL;
			break;
		case ETB_EXIT:
			gMainWin::GetIF()->Exit();
			break;
	}
}

void gTitleCore::OnLButtonDown_PlayerSelect()
{
	gMouse	*mouse = gMouse::GetIF();
	int		i;

	if(m_ImgBtnPrev.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		m_eMode = ETM_TITLE;
		m_ImgBtnPrev.m_eBtnMode = EBM_NONE;
		return;
	}
	if(m_ImgBtnNext.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		// gamecore로 넘어가기 전에, 플레이어 체크.
		// 최소 2인, 플레이어 1인이상
		int			nCount = 0;
		int			nPlayer = 0;
		for(i = 0; i < MAXPLAYER; i++)
		{
			if(m_ePlayer[i] == EPS_COM)
			{
				nCount++;
			}
			else if(m_ePlayer[i] == EPS_PLAYER)
			{
				nCount++;
				nPlayer++;
			}
		}

		if(nCount < 2)
		{
			MessageBox(gMainWin::GetIF()->m_hWnd, "플레이어가 2명 이상이어야 합니다.", "Error", MB_OK);
			return;
		}
		if(nPlayer < 1)
		{
			MessageBox(gMainWin::GetIF()->m_hWnd, "컴퓨터만으로는 플레이할 수 없습니다.", "Error", MB_OK);
			return;
		}

		gMainWin::GetIF()->m_eCoreMode = EMC_GAME;
		m_ImgBtnNext.m_eBtnMode = EBM_NONE;
		return;
	}
	
	//1p 줄
	int		mouseX;
	int		onecell = PSEL_POS_MODEW / 3;	// 한칸 길이(사람, 컴퓨터, 안해 각각)
	if(PSEL_POS_1MODEX < mouse->m_nPosX && mouse->m_nPosX < PSEL_POS_1MODEX + PSEL_POS_MODEW
		&& PSEL_POS_1PY < mouse->m_nPosY && mouse->m_nPosY < PSEL_POS_1PY + PSEL_POS_MODEH )
	{
		mouseX = mouse->m_nPosX - PSEL_POS_1MODEX;
		if(mouseX - onecell < 0)			m_ePlayer[0] = EPS_PLAYER;
		else if(mouseX - onecell * 2 < 0)	m_ePlayer[0] = EPS_COM;
		else								m_ePlayer[0] = EPS_NONE;
	}
	//2p
	if(PSEL_POS_2MODEX < mouse->m_nPosX && mouse->m_nPosX < PSEL_POS_2MODEX + PSEL_POS_MODEW
		&& PSEL_POS_2PY < mouse->m_nPosY && mouse->m_nPosY < PSEL_POS_2PY + PSEL_POS_MODEH )
	{
		mouseX = mouse->m_nPosX - PSEL_POS_2MODEX;
		if(mouseX - onecell < 0)			m_ePlayer[1] = EPS_PLAYER;
		else if(mouseX - onecell * 2 < 0)	m_ePlayer[1] = EPS_COM;
		else								m_ePlayer[1] = EPS_NONE;
	}
	//3p
	if(PSEL_POS_3MODEX < mouse->m_nPosX && mouse->m_nPosX < PSEL_POS_3MODEX + PSEL_POS_MODEW
		&& PSEL_POS_3PY < mouse->m_nPosY && mouse->m_nPosY < PSEL_POS_3PY + PSEL_POS_MODEH )
	{
		mouseX = mouse->m_nPosX - PSEL_POS_3MODEX;
		if(mouseX - onecell < 0)			m_ePlayer[2] = EPS_PLAYER;
		else if(mouseX - onecell * 2 < 0)	m_ePlayer[2] = EPS_COM;
		else								m_ePlayer[2] = EPS_NONE;
	}
	//4p
	if(PSEL_POS_4MODEX < mouse->m_nPosX && mouse->m_nPosX < PSEL_POS_4MODEX + PSEL_POS_MODEW
		&& PSEL_POS_4PY < mouse->m_nPosY && mouse->m_nPosY < PSEL_POS_4PY + PSEL_POS_MODEH )
	{
		mouseX = mouse->m_nPosX - PSEL_POS_4MODEX;
		if(mouseX - onecell < 0)			m_ePlayer[3] = EPS_PLAYER;
		else if(mouseX - onecell * 2 < 0)	m_ePlayer[3] = EPS_COM;
		else								m_ePlayer[3] = EPS_NONE;
	}
}

void gTitleCore::OnMouseMove_Title()
{
	gMouse	*mouse = gMouse::GetIF();

	int		i;

	for(i = 0; i < ETB_END; i++)
	{
		if(m_ImgBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_ImgBtn[i].m_eBtnMode = EBM_HOVER;
		else
			m_ImgBtn[i].m_eBtnMode = EBM_NONE;
		}

}

void gTitleCore::OnMouseMove_PlayerSelect()
{
	gMouse	*mouse = gMouse::GetIF();

	if(m_ImgBtnPrev.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		m_ImgBtnPrev.m_eBtnMode = EBM_HOVER;
	else
		m_ImgBtnPrev.m_eBtnMode = EBM_NONE;
	
	if(m_ImgBtnNext.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		m_ImgBtnNext.m_eBtnMode = EBM_HOVER;
	else
		m_ImgBtnNext.m_eBtnMode = EBM_NONE;

}