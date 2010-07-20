#include "gInterface.h"
#include "const.h"
#include "gMouse.h"
#include "gUtil.h"

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

	return true;
}

void gInterface::Draw()
{
	m_ImgMenuback.Draw(IF_POS_MENUBACKX, IF_POS_MENUBACKY);

	int		i;
	for(i = 0; i < EBTN_END; i++)
		m_BtnMenu[i].Draw();

	if(m_eMenuMode != EMM_END)
		m_ImgMenu[m_eMenuMode].Draw(IF_POS_BACKX, IF_POS_BACKY);
}

void gInterface::MainLoop()
{

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
			m_eMenuMode = EMM_END;
	}
}