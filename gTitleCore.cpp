#include "const.h"
#include "gTitleCore.h"
#include "gMainWin.h"
#include "gMouse.h"

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
	// title img
	if(FAILED(m_ImgTitle.Load(TITLE_IMG_TITLE)))
		return false;

	// button setup
	RECT	rcBtn;
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

void gTitleCore::MainLoop()
{
	Draw();
}

void gTitleCore::Draw()
{
	m_ImgTitle.Draw(0, 0);
	
	for(int i = 0; i < ETB_END; i++)
		m_ImgBtn[i].Draw();
}

//------------------------------------------------------------------------------------
//	Mouse
//------------------------------------------------------------------------------------
void gTitleCore::OnLButtonDown()
{
	gMouse *mouse = gMouse::GetIF();

	for(int i = 0; i < ETB_END; i++)
	{
		if(m_ImgBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			break;
	}
	switch((eTITLE_BTN)i)
	{
	case ETB_START:
		gMainWin::GetIF()->m_eCoreMode = EMC_GAME;
		break;
	case ETB_EXIT:
		gMainWin::GetIF()->Exit();
		break;
	}

}

void gTitleCore::OnLButtonUp()
{

}

void gTitleCore::OnMouseMove()
{
	gMouse *mouse = gMouse::GetIF();
	
	for(int i = 0; i < ETB_END; i++)
	{
		if(m_ImgBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_ImgBtn[i].m_eBtnMode = EBM_HOVER;
		else
			m_ImgBtn[i].m_eBtnMode = EBM_NONE;
	}
}

void gTitleCore::OnRButtonDown()
{

}