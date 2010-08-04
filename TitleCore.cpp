#include "TitleCore.h"
#include "coreconst.h"


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
	RECT		rcBtn;
	
	// title img
	if(!m_ImgBack.Load(TITLE_FILE_BACK))
		return false;
	
	// button setup
	SetRect(&rcBtn, TITLE_POS_STARTBTNX,
					TITLE_POS_STARTBTNY,
					TITLE_POS_STARTBTNX + TITLE_SIZE_STARTBTNW,
					TITLE_POS_STARTBTNY + TITLE_SIZE_STARTBTNH );

	if(!m_Btn[ETB_START].SetUp(TITLE_FILE_STARTBTN, TITLE_VERT_STARTBTN, rcBtn))
		return false;
	
	SetRect(&rcBtn, TITLE_POS_EXITBTNX,
					TITLE_POS_EXITBTNY,
					TITLE_POS_EXITBTNX + TITLE_SIZE_EXITBTNW,
					TITLE_POS_EXITBTNY + TITLE_SIZE_EXITBTNH );

	if(!m_Btn[ETB_EXIT].SetUp(TITLE_FILE_EXITBTN, TITLE_VERT_EXITBTN, rcBtn))
		return false;

	return true;
}

bool gTitleCore::MainLoop()
{
	Draw();

	return true;
}

void gTitleCore::Draw()
{
	m_ImgBack.Draw();

	int		i;

	for(i = 0; i < ETB_END; i++)
		m_Btn[i].Draw();
}

void gTitleCore::Release()
{

}

void gTitleCore::OnLButtonDown()
{

}

void gTitleCore::OnLButtonUp()
{

}

void gTitleCore::OnMouseMove()
{

}

void gTitleCore::OnRButtonDown()
{

}