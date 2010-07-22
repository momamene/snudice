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


	// title setup
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

	m_eMode = ETM_TITLE;

	// playersel setup
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

	// charsel setup
	// sel img
	if(FAILED(m_ImgSel.Load(CHARSELBGFILE)))
		return false;
	// charid(button)

	// 언어계열 7넘
	SetRect(&rcBtn, IDCARDX1, IDCARDY1,
			IDCARDX1 + CHARIDCARDW, IDCARDY1 + CHARIDCARDH);
	m_ImgID[0].SetUp(IDCARDIMG1, true, rcBtn);
	SetRect(&rcBtn, IDCARDX2, IDCARDY2,
		IDCARDX2 + CHARIDCARDW, IDCARDY2 + CHARIDCARDH);
	m_ImgID[1].SetUp(IDCARDIMG2, true, rcBtn);
	SetRect(&rcBtn, IDCARDX3, IDCARDY3,
		IDCARDX3 + CHARIDCARDW, IDCARDY3 + CHARIDCARDH);
	m_ImgID[2].SetUp(IDCARDIMG3, true, rcBtn);
	SetRect(&rcBtn, IDCARDX4, IDCARDY4,
		IDCARDX4 + CHARIDCARDW, IDCARDY4 + CHARIDCARDH);
	m_ImgID[3].SetUp(IDCARDIMG4, true, rcBtn);
	SetRect(&rcBtn, IDCARDX5, IDCARDY5,
		IDCARDX5 + CHARIDCARDW, IDCARDY5 + CHARIDCARDH);
	m_ImgID[4].SetUp(IDCARDIMG5, true, rcBtn);
	SetRect(&rcBtn, IDCARDX6, IDCARDY6,
		IDCARDX6 + CHARIDCARDW, IDCARDY6 + CHARIDCARDH);
	m_ImgID[5].SetUp(IDCARDIMG6, true, rcBtn);
	SetRect(&rcBtn, IDCARDX7, IDCARDY7,
		IDCARDX7 + CHARIDCARDW, IDCARDY7 + CHARIDCARDH);
	m_ImgID[6].SetUp(IDCARDIMG7, true, rcBtn);
	// 수리계열 7넘
	SetRect(&rcBtn, IDCARDX8, IDCARDY8,
		IDCARDX8 + CHARIDCARDW, IDCARDY8 + CHARIDCARDH);
	m_ImgID[7].SetUp(IDCARDIMG8, true, rcBtn);
	SetRect(&rcBtn, IDCARDX9, IDCARDY9,
		IDCARDX9 + CHARIDCARDW, IDCARDY9 + CHARIDCARDH);
	m_ImgID[8].SetUp(IDCARDIMG9, true, rcBtn);
	SetRect(&rcBtn, IDCARDX10, IDCARDY10,
		IDCARDX10 + CHARIDCARDW, IDCARDY10 + CHARIDCARDH);
	m_ImgID[9].SetUp(IDCARDIMG10, true, rcBtn);
	SetRect(&rcBtn, IDCARDX11, IDCARDY11,
		IDCARDX11 + CHARIDCARDW, IDCARDY11 + CHARIDCARDH);
	m_ImgID[10].SetUp(IDCARDIMG11, true, rcBtn);
	SetRect(&rcBtn, IDCARDX12, IDCARDY12,
		IDCARDX12 + CHARIDCARDW, IDCARDY12 + CHARIDCARDH);
	m_ImgID[11].SetUp(IDCARDIMG12, true, rcBtn);
	SetRect(&rcBtn, IDCARDX13, IDCARDY13,
		IDCARDX13 + CHARIDCARDW, IDCARDY13 + CHARIDCARDH);
	m_ImgID[12].SetUp(IDCARDIMG13, true, rcBtn);
	SetRect(&rcBtn, IDCARDX14, IDCARDY14,
		IDCARDX14 + CHARIDCARDW, IDCARDY14 + CHARIDCARDH);
	m_ImgID[13].SetUp(IDCARDIMG14, true, rcBtn);

	// 예능계열 2넘
	SetRect(&rcBtn, IDCARDX15, IDCARDY15,
		IDCARDX15 + CHARIDCARDW, IDCARDY15 + CHARIDCARDH);
	m_ImgID[14].SetUp(IDCARDIMG15, true, rcBtn);
	SetRect(&rcBtn, IDCARDX16, IDCARDY16,
		IDCARDX16 + CHARIDCARDW, IDCARDY16 + CHARIDCARDH);
	m_ImgID[15].SetUp(IDCARDIMG16, true, rcBtn);

	m_nSel = 0;

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
		m_ImgTitle.Draw(0, 0);
		
		for(i = 0; i < ETB_END; i++)
			m_ImgBtn[i].Draw();
		break;
	case ETM_PLAYERSEL:
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

		break;
	case ETM_CHARSEL:
		{
			m_ImgSel.Draw(0, 0);

			m_ImgBtnPrev.Draw();
			m_ImgBtnNext.Draw();


			for(i = 0; i < CHARNUM; i++)
				m_ImgID[i].Draw();

			RECT		rcCharIllu = { SELCHARIMGX, SELCHARIMGY,
				SELCHARIMGX + SELCHARIMGW, SELCHARIMGY + SELCHARIMGH };

			gChar	charac = gCharManager::GetIF()->m_Chars[m_nSel];
			charac.DrawIllu(rcCharIllu);

			HDC			hdc;
			char		szBuf[128];

			gUtil::BeginText();
			wsprintf(szBuf, "이름 : %s", charac.m_Data.szName);
			gUtil::Text(CHARINFOX, CHARINFOY, szBuf);

			if(charac.m_Data.eSex == ESEX_MALE)
				wsprintf(szBuf, "성별 : ♂");
			else
				wsprintf(szBuf, "성별 : ♀");
			gUtil::Text(CHARINFOX + 150, CHARINFOY, szBuf);

			wsprintf(szBuf, "소속 : %s", charac.m_Data.szColleage);
			gUtil::Text(CHARINFOX, CHARINFOY + 20, szBuf);
			wsprintf(szBuf, "언어 : %d", charac.m_Data.nLang);
			gUtil::Text(CHARINFOX, CHARINFOY + 40, szBuf);
			wsprintf(szBuf, "수리 : %d", charac.m_Data.nMath);
			gUtil::Text(CHARINFOX, CHARINFOY + 60, szBuf);
			wsprintf(szBuf, "예능 : %d", charac.m_Data.nArt);
			gUtil::Text(CHARINFOX, CHARINFOY + 80, szBuf);
			wsprintf(szBuf, "체력 : %d", charac.m_Data.nStamina);
			gUtil::Text(CHARINFOX, CHARINFOY + 100, szBuf);
			wsprintf(szBuf, "이동 : %d", charac.m_Data.nMove);
			gUtil::Text(CHARINFOX, CHARINFOY + 120, szBuf);

			gUtil::Text(CHARINFOX, CHARINFOY + 140, charac.m_Data.szComment);



			gUtil::EndText();

			break;
		}
	}
}

//------------------------------------------------------------------------------------
//	Mouse
//------------------------------------------------------------------------------------
void gTitleCore::OnLButtonDown()
{
	gMouse *mouse = gMouse::GetIF();
	int		i;

	switch(m_eMode)
	{
	case ETM_TITLE:
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
		break;

	case ETM_PLAYERSEL:
		{
			if(m_ImgBtnPrev.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				m_eMode = ETM_TITLE;
				m_ImgBtnPrev.m_eBtnMode = EBM_NONE;
				break;
			}
			if(m_ImgBtnNext.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				m_eMode = ETM_CHARSEL;
				m_ImgBtnNext.m_eBtnMode = EBM_NONE;
				break;
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
			break;
		}
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
	}


}

void gTitleCore::OnLButtonUp()
{

}

void gTitleCore::OnMouseMove()
{
	gMouse *mouse = gMouse::GetIF();
	int		i;

	switch(m_eMode)
	{
	case ETM_TITLE:
		for(i = 0; i < ETB_END; i++)
		{
			if(m_ImgBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_ImgBtn[i].m_eBtnMode = EBM_HOVER;
			else
				m_ImgBtn[i].m_eBtnMode = EBM_NONE;
		}
		break;
	case ETM_PLAYERSEL:
		if(m_ImgBtnPrev.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_ImgBtnPrev.m_eBtnMode = EBM_HOVER;
		else
			m_ImgBtnPrev.m_eBtnMode = EBM_NONE;

		if(m_ImgBtnNext.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_ImgBtnNext.m_eBtnMode = EBM_HOVER;
		else
			m_ImgBtnNext.m_eBtnMode = EBM_NONE;


		break;
	case ETM_CHARSEL:
		if(m_ImgBtnPrev.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_ImgBtnPrev.m_eBtnMode = EBM_HOVER;
		else
			m_ImgBtnPrev.m_eBtnMode = EBM_NONE;
		
		if(m_ImgBtnNext.PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_ImgBtnNext.m_eBtnMode = EBM_HOVER;
		else
			m_ImgBtnNext.m_eBtnMode = EBM_NONE;

		for(i = 0; i < CHARNUM; i++)
		{
			if(m_ImgID[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				m_ImgID[i].m_eBtnMode = EBM_HOVER;
				m_nSel = i;
			}
			else
				m_ImgID[i].m_eBtnMode = EBM_NONE;
		}
		break;
	}
	
}

void gTitleCore::OnRButtonDown()
{

}