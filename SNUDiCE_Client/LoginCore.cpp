#include "LoginCore.h"
#include "coreconst.h"
#include "PopUp.h"
#include "Mouse.h"
#include "Server.h"
#include "MainWin.h"
#include "Util.h"
#include "stringconst.h"
#include "Chat.h"
#include "PlayerContainer.h"


static gLoginCore s_LoginCore;

gLoginCore::gLoginCore()
{

}

gLoginCore::~gLoginCore()
{
	
}

gLoginCore *gLoginCore::GetIF()
{
	return &s_LoginCore;
}

bool gLoginCore::SetUp()
{
	// title img
	if(!m_ImgBack.Load(LOGIN_FILE_BACK))
		return false;

	// button setup
	RECT		rcBtn;

	SetRect(&rcBtn, LOGIN_POS_CONNECTBTNX,
					LOGIN_POS_CONNECTBTNY,
					LOGIN_POS_CONNECTBTNX + LOGIN_SIZE_CONNECTBTNW,
					LOGIN_POS_CONNECTBTNY + LOGIN_SIZE_CONNECTBTNH);

	if(!m_Btn[ELB_CONNECT].SetUp(LOGIN_FILE_CONNECTBTN, LOGIN_VERT_CONNECTBTN, rcBtn))
		return false;
	

// 	// button setup
// 	SetRect(&rcBtn, TITLE_POS_STARTBTNX,
// 					TITLE_POS_STARTBTNY,
// 					TITLE_POS_STARTBTNX + TITLE_SIZE_STARTBTNW,
// 					TITLE_POS_STARTBTNY + TITLE_SIZE_STARTBTNH );
// 
// 	if(!m_Btn[ELB_START].SetUp(TITLE_FILE_STARTBTN, TITLE_VERT_STARTBTN, rcBtn))
// 		return false;
// 	
// 	SetRect(&rcBtn, TITLE_POS_EXITBTNX,
// 					TITLE_POS_EXITBTNY,
// 					TITLE_POS_EXITBTNX + TITLE_SIZE_EXITBTNW,
// 					TITLE_POS_EXITBTNY + TITLE_SIZE_EXITBTNH );
// 
// 	if(!m_Btn[ELB_EXIT].SetUp(TITLE_FILE_EXITBTN, TITLE_VERT_EXITBTN, rcBtn))
// 		return false;

	// edit control
	RECT		rcDest;

	SetRect(&rcDest,
			LOGIN_EDIT_ID_X,
			LOGIN_EDIT_ID_Y,
			LOGIN_EDIT_ID_X + LOGIN_EDIT_ID_W,
			LOGIN_EDIT_ID_Y + LOGIN_EDIT_ID_H );

	if(!m_EditID.SetUp(rcDest, LOGIN_EDIT_IMG, LOGIN_EDIT_SZLENGTH, EDIT_STRING))
		return false;

	SetRect(&rcDest,
			LOGIN_EDIT_PW_X,
			LOGIN_EDIT_PW_Y,
			LOGIN_EDIT_PW_X + LOGIN_EDIT_PW_W,
			LOGIN_EDIT_PW_Y + LOGIN_EDIT_PW_H );
	
	if(!m_EditPW.SetUp(rcDest, LOGIN_EDIT_IMG, LOGIN_EDIT_SZLENGTH, EDIT_PASSWORD))
		return false;

	m_EditID.SetFocusOn();

	return true;
}

bool gLoginCore::PreTransMsg(MSG &msg)
{
		if(msg.hwnd == m_EditID.m_hEdit)
	{
		if(!gServer::GetIF()->m_bConnect)
			return true;

		if(msg.message == WM_KEYDOWN)
		{
			if(gPopUp::GetIF()->isPopUp())
			{
				if(msg.wParam == VK_RETURN)
					gPopUp::GetIF()->DoEnter();

				return true;
			}

			switch(msg.wParam)
			{
				case VK_RETURN:
					m_EditPW.SetFocusOn();
					return true;
				case VK_TAB:
					m_EditPW.SetFocusOn();
					return true;
				case VK_SPACE:
				case VK_ESCAPE:
					return true;
			}
		}
	}
	else if(msg.hwnd == m_EditPW.m_hEdit)
	{
		if(!gServer::GetIF()->m_bConnect)
			return true;
		
		if(msg.message == WM_KEYDOWN)
		{
			if(gPopUp::GetIF()->isPopUp())
			{
				if(msg.wParam == VK_RETURN)
					gPopUp::GetIF()->DoEnter();

				return true;
			}

			switch(msg.wParam)
			{
				case VK_RETURN:
					SendLogin();
					return true;
				case VK_TAB:
					m_EditID.SetFocusOn();
					return true;
				case VK_SPACE:
				case VK_ESCAPE:
					return true;
			}
		}
	}

	return false;
}

void gLoginCore::MainLoop()
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
		switch(gPopUp::GetIF()->m_ePop)
		{
			case EPOP_RECONNECT:
				switch(gPopUp::GetIF()->m_eBtnClk)
				{
					case ECLK_OK:
						gServer::GetIF()->ReConnect();
						break;
					case ECLK_CANCEL:
						gMainWin::GetIF()->Exit();
						break;
				}
				break;
			case EPOP_DISCONNECT:
				switch(gPopUp::GetIF()->m_eBtnClk)
				{
					case ECLK_OK:
						gMainWin::GetIF()->Exit();
						break;
				}
				break;
		}
		gPopUp::GetIF()->m_bReturn = false;
	}

	if(gMainWin::GetIF()->m_Keys[VK_TAB])
	{
		m_EditID.SetFocusOn();
		gMainWin::GetIF()->m_Keys[VK_TAB] = false;
	}

	// 서버랑 연결 안되었으면 입력 막자
	if(!gServer::GetIF()->m_bConnect)
		return;


}

void gLoginCore::Draw()
{
	m_ImgBack.Draw();

	m_EditID.Draw();
	m_EditPW.Draw();

	int		i;

	for(i = 0; i < ELB_END; i++)
		m_Btn[i].Draw();

}

void gLoginCore::Release()
{
	int		i;

	m_ImgBack.Release();

	for(i = 0; i < ELB_END; i++)
		m_Btn[i].Release();

	m_EditID.Release();
	m_EditPW.Release();

}

void gLoginCore::SendLogin()
{
	PK_LOGIN_ASK	ask;
	
	strcpy(ask.szID, m_EditID.m_szEdit);
	strcpy(ask.szPW, m_EditPW.m_szEdit);
	gServer::GetIF()->Send(PL_LOGIN_ASK, sizeof(ask), &ask);
}

void gLoginCore::OnLButtonDown()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;

	gMouse	*mouse = gMouse::GetIF();
	
	if(m_EditID.isPointInEdit(mouse->m_nPosX, mouse->m_nPosY))
		m_EditID.SetFocusOn();
	else if(m_EditPW.isPointInEdit(mouse->m_nPosX, mouse->m_nPosY))
		m_EditPW.SetFocusOn();

//	gServer::GetIF()->Send();

	if(m_Btn[ELB_CONNECT].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		SendLogin();
}

void gLoginCore::OnLButtonUp()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;
}

void gLoginCore::OnMouseMove()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;
	
	gMouse	*mouse = gMouse::GetIF();
	int		i;
	
	for(i = 0; i < ELB_END; i++)
	{
		if(m_Btn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_Btn[i].m_eBtnMode = EBM_HOVER;
		else
			m_Btn[i].m_eBtnMode = EBM_NONE;
	}
}

void gLoginCore::OnRButtonDown()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;

}

void gLoginCore::pk_login_rep(PK_LOGIN_REP *rep)
{
	switch(rep->error)
	{
		case ELE_OVERCONNECT:
			gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_5);
			break;
		case ELE_USEROVER:
			break;
		case ELE_NOID:
			gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_6);
			m_EditID.SetFocusOn();
			break;
		case ELE_PWERROR:
			gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_7);
			m_EditPW.SetFocusOn();
			break;
		case ELE_SUCCESS:
			gMainWin::GetIF()->m_eCoreMode = ECM_BATTLENET;
			SetFocus(gMainWin::GetIF()->m_hWnd);
			gChat::GetIF()->m_bShow = true;
			gPlayerContainer::GetIF()->SetMyPlayer(rep);

			gUtil::DebugMsg("login success\n");
			break;
	}
}