#include "TitleCore.h"
#include "coreconst.h"
#include "PopUp.h"
#include "Mouse.h"
#include "Server.h"
#include "MainWin.h"

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

void gTitleCore::MainLoop()
{
	Draw();

	// popup 창 처리
	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->MainLoop();
		return;
	}

	if(gPopUp::GetIF()->m_bReturn)
	{
		switch(gPopUp::GetIF()->m_eBtnClk)
		{
			case ECLK_OK:
				gServer::GetIF()->ReConnect();
				break;
			case ECLK_CANCEL:
				gMainWin::GetIF()->Exit();
				break;
		}

		gPopUp::GetIF()->m_bReturn = false;
	}

	// 서버랑 연결 안되었으면 입력 막자
	if(!gServer::GetIF()->m_bConnect)
		return;

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
	int		i;

	m_ImgBack.Release();

	for(i = 0; i < ETB_END; i++)
		m_Btn[i].Release();

}

void gTitleCore::OnLButtonDown()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;

	gMouse	*mouse = gMouse::GetIF();
	int		i;

	for(i = 0; i < ETB_END; i++)
	{
		if(m_Btn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{

		}
	}

}

void gTitleCore::OnLButtonUp()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;
}

void gTitleCore::OnMouseMove()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;
	
	gMouse	*mouse = gMouse::GetIF();
	int		i;
	
	for(i = 0; i < ETB_END; i++)
	{
		if(m_Btn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_Btn[i].m_eBtnMode = EBM_HOVER;
		else
			m_Btn[i].m_eBtnMode = EBM_NONE;
	}
}

void gTitleCore::OnRButtonDown()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;

}