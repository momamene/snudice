#include "gInterface.h"
#include "const.h"
#include "gMouse.h"

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

	return true;
}

void gInterface::Draw()
{
	m_ImgMenuback.Draw(IF_POS_MENUBACKX, IF_POS_MENUBACKY);

	int		i;
	for(i = 0; i < EBTN_END; i++)
		m_BtnMenu[i].Draw();
}

void gInterface::MainLoop()
{

}

void gInterface::OnLButtonDown()
{

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

}