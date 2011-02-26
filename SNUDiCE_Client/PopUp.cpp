#include <windows.h>
#include "PopUp.h"
#include "Util.h"
#include "MainWin.h"
#include "Mouse.h"

#define POPUP_IMG_BACK			".\\Data\\Interface\\popup.img"
#define POPUP_IMG_OK			".\\Data\\Interface\\popup_ok.img"
#define POPUP_IMG_CANCEL		".\\Data\\Interface\\popup_cancel.img"
#define POPUP_WIDTH				242
#define POPUP_HEIGHT			122
#define POPUP_X					((WNDSIZEW - POPUP_WIDTH) / 2)
#define POPUP_Y					((WNDSIZEH - POPUP_HEIGHT) / 2)
#define POPUP_BTNW				60
#define POPUP_BTNH				24
#define POPUP_ONEBTNX			(POPUP_X + (POPUP_WIDTH - POPUP_BTNW) / 2)
#define POPUP_ONEBTNY			(POPUP_Y + 83)
#define POPUP_1STBTNX			(WNDSIZEW / 2 - 70)
#define POPUP_1STBTNY			POPUP_ONEBTNY
#define POPUP_2NDBTNX			(WNDSIZEW / 2 + 10)
#define POPUP_2NDBTNY			POPUP_ONEBTNY
#define POPUP_1STTEXTY			(POPUP_Y + 32)
#define POPUP_2NDTEXTY			(POPUP_Y + 52)
#define POPUP_IMG_W				35			// popup창에 띄우는 이미지
#define POPUP_IMG_H				42
#define POPUP_IMG_X				(POPUP_X + 29)
#define POPUP_IMG_Y				(POPUP_Y + 29)
#define POPUP_PIXEL_PER_LETTER	6

gPopUp::gPopUp()
{

}

gPopUp::~gPopUp()
{

}

static gPopUp	s_PopUp;

gPopUp *gPopUp::GetIF()
{
	return &s_PopUp;
}


bool gPopUp::SetUp()
{
	m_bPopup	= false;
	m_bReturn	= false;
	m_Img		= NULL;
	
	if(!m_ImgPopup.Load(POPUP_IMG_BACK))
		return false;
	
	RECT		rc = {0, 0, 0, 0};
	// 버튼 위치는 차후에 셋팅
	if(!m_ImgBtn[ECLK_OK].SetUp(POPUP_IMG_OK, false, rc))
		return false;
	if(!m_ImgBtn[ECLK_CANCEL].SetUp(POPUP_IMG_CANCEL, false, rc))
		return false;

	SetRect(&m_rcDest,
		POPUP_IMG_X, POPUP_IMG_Y,
		POPUP_IMG_X + POPUP_IMG_W, POPUP_IMG_Y + POPUP_IMG_H);

	return true;
}

bool gPopUp::SetPopUp(BTNCLK btn, ePOPTYPE pop, char *szLine1, char *szLine2)
{
	if(m_bPopup)
		return false;
	
	m_eBtnClk	= btn;
	m_bReturn	= false;
	m_ePop		= pop;

	switch(btn)
	{
		case ECLK_OK:			// just one ok button
			SetRect(&m_ImgBtn[ECLK_OK].m_rcPos,
				POPUP_ONEBTNX,
				POPUP_ONEBTNY,
				POPUP_ONEBTNX + POPUP_BTNW,
				POPUP_ONEBTNY + POPUP_BTNH	);
			break;
		case ECLK_CANCEL:		// two button, ok and cancel button
			SetRect(&m_ImgBtn[ECLK_OK].m_rcPos,
				POPUP_1STBTNX,
				POPUP_1STBTNY,
				POPUP_1STBTNX + POPUP_BTNW,
				POPUP_1STBTNY + POPUP_BTNH	);
			
			SetRect(&m_ImgBtn[ECLK_CANCEL].m_rcPos,
				POPUP_2NDBTNX,
				POPUP_2NDBTNY,
				POPUP_2NDBTNX + POPUP_BTNW,
				POPUP_2NDBTNY + POPUP_BTNH	);
			break;
	}
	if(szLine1)
		strcpy(m_szLine1, szLine1);
	if(szLine2)
		strcpy(m_szLine2, szLine2);
	
	TextPosX();
	
	m_bPopup = true;
	return true;
}

bool gPopUp::SetImgPopUp(BTNCLK btn, ePOPTYPE pop, gImage *img, char *szLine1, char *szLine2)
{
	m_Img		= img;

	bool ret = SetPopUp(btn, pop, szLine1, szLine2);

	return ret;
}

void gPopUp::Release()
{
	m_ImgPopup.Release();
	m_ImgBtn[ECLK_OK].Release();
	m_ImgBtn[ECLK_CANCEL].Release();
}

void gPopUp::TextPosX()
{
	int		length;
	int		i;
	
	if(m_szLine1 != NULL)
	{
		length = strlen(m_szLine1);
		length *= POPUP_PIXEL_PER_LETTER;		// 글자 하나당 6pixel이라고 가정(한글기준)

		for(i = 0; i < (int)strlen(m_szLine1); i++)
			if(m_szLine1[i] == ' ' || m_szLine1[i] == ',' || m_szLine1[i] == '.')
				length -= 2;

		if(m_Img)
			m_nLine1X = POPUP_X + POPUP_IMG_W + (POPUP_WIDTH - POPUP_IMG_W - length) / 2;
		else
			m_nLine1X = POPUP_X + (POPUP_WIDTH - length) / 2;
	}

	if(m_szLine2 != NULL)	
	{
		length = strlen(m_szLine2);
		length *= POPUP_PIXEL_PER_LETTER;		// 글자 하나당 6pixel이라고 가정(한글기준)

		for(i = 0; i < (int)strlen(m_szLine1); i++)
			if(m_szLine2[i] == ' ' || m_szLine2[i] == ',' || m_szLine2[i] == '.')
				length -= 2;
	
		if(m_Img)
			m_nLine2X = POPUP_X + POPUP_IMG_W + (POPUP_WIDTH - POPUP_IMG_W - length) / 2;
		else
			m_nLine2X = POPUP_X + (POPUP_WIDTH - length) / 2;
	}
}

bool gPopUp::isPopUp()
{
	return m_bPopup;
}

void gPopUp::MainLoop()
{
	if(!m_bPopup) return;

	if(gMainWin::GetIF()->m_Keys[VK_RETURN])	// ok
		DoEnter();
	else if(gMainWin::GetIF()->m_Keys[VK_ESCAPE])	// cancel
		DoEsc();

	Draw();
}

void gPopUp::Ok()
{
	m_ePop		= EPOP_NONE;
	m_eBtnClk	= ECLK_OK;
	m_bPopup	= false;
	memset(m_szLine1, 0, 128);
	memset(m_szLine2, 0, 128);
	m_bReturn	= true;
	m_Img		= NULL;
	m_ImgBtn[ECLK_OK].m_eBtnMode = EBM_NONE;
	m_ImgBtn[ECLK_CANCEL].m_eBtnMode = EBM_NONE;
}

void gPopUp::Cancel()
{
	m_ePop		= EPOP_NONE;
	m_eBtnClk	= ECLK_CANCEL;
	m_bPopup	= false;
	memset(m_szLine1, 0, 128);
	memset(m_szLine2, 0, 128);
	m_bReturn	= true;
	m_Img		= NULL;
	m_ImgBtn[ECLK_OK].m_eBtnMode = EBM_NONE;
	m_ImgBtn[ECLK_CANCEL].m_eBtnMode = EBM_NONE;
}

void gPopUp::Draw()
{
	if(!m_bPopup)
		return;

	m_ImgPopup.Draw(POPUP_X, POPUP_Y);

	switch(m_eBtnClk)
	{
		case ECLK_OK:
			m_ImgBtn[ECLK_OK].Draw();
			break;
		case ECLK_CANCEL:
			m_ImgBtn[ECLK_OK].Draw();
			m_ImgBtn[ECLK_CANCEL].Draw();
			break;
	}

	if(m_Img != NULL)
	{
		RECT	rcSour;
		SetRect(&rcSour,
			0, 0, m_Img->m_nWidth, m_Img->m_nHeight);
		m_Img->Draw(m_rcDest, rcSour);
	}

	gUtil::BeginText();
		if(m_szLine1)
			gUtil::Text(m_nLine1X, POPUP_1STTEXTY, m_szLine1);
		if(m_szLine2)
			gUtil::Text(m_nLine2X, POPUP_2NDTEXTY, m_szLine2);
	gUtil::EndText();
}

void gPopUp::OnLButtonDown()
{
	if(!m_bPopup)
		return;

	gMouse	*mouse = gMouse::GetIF();

	switch(m_eBtnClk)
	{
		case ECLK_OK:
			if(m_ImgBtn[ECLK_OK].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				Ok();
			break;
		case ECLK_CANCEL:
			if(m_ImgBtn[ECLK_OK].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				Ok();
			else if(m_ImgBtn[ECLK_CANCEL].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				Cancel();
			break;
	}
}


void gPopUp::OnMouseMove()
{
	if(!m_bPopup)
		return;
	
	gMouse	*mouse = gMouse::GetIF();
	
	switch(m_eBtnClk)
	{
		case ECLK_OK:
			if(m_ImgBtn[ECLK_OK].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_ImgBtn[ECLK_OK].m_eBtnMode = EBM_HOVER;
			else
				m_ImgBtn[ECLK_OK].m_eBtnMode = EBM_NONE;
			break;
		case ECLK_CANCEL:
			if(m_ImgBtn[ECLK_OK].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_ImgBtn[ECLK_OK].m_eBtnMode = EBM_HOVER;
			else
				m_ImgBtn[ECLK_OK].m_eBtnMode = EBM_NONE;

			if(m_ImgBtn[ECLK_CANCEL].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_ImgBtn[ECLK_CANCEL].m_eBtnMode = EBM_HOVER;
			else
				m_ImgBtn[ECLK_CANCEL].m_eBtnMode = EBM_NONE;
			break;
	}
}

void gPopUp::OnRButtonDown()
{

}

void gPopUp::OnLButtonUp()
{
	
}

void gPopUp::DoEnter()
{
	switch(m_eBtnClk)
	{
		case ECLK_OK:
		case ECLK_CANCEL:
			Ok();
			break;
	}
}

void gPopUp::DoEsc()
{

	switch(m_eBtnClk)
	{
		case ECLK_OK:
			break;
		case ECLK_CANCEL:
			Cancel();
			break;
	}		
}


bool gPopUp::Restore()
{
	if(!m_ImgPopup.Restore())
		return false;
	if(!m_ImgBtn[ECLK_OK].Restore())
		return false;
	if(!m_ImgBtn[ECLK_CANCEL].Restore())
		return false;

	return true;
}