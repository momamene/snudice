#include "LoginCore.h"
#include "PopUp.h"
#include "Mouse.h"
#include "Server.h"
#include "MainWin.h"
#include "Util.h"
#include "stringconst.h"
#include "Chat.h"
#include "Dice.h"
#include "PlayerContainer.h"
#include "PlaySoundCore.h"
#include "md5.h"


#define LOGIN_FILE_CONNECTBTN		".\\Data\\Login\\connect.img"
#define LOGIN_SIZE_CONNECTBTNW		160
#define LOGIN_SIZE_CONNECTBTNH		30
#define LOGIN_VERT_CONNECTBTN		false
#define LOGIN_POS_CONNECTBTNX		((WNDSIZEW - LOGIN_SIZE_CONNECTBTNW) / 2)
#define LOGIN_POS_CONNECTBTNY		360

// connect
#define LOGIN_FILE_BACK				".\\Data\\Login\\login_back2.img"

// id, pw edit control
#define LOGIN_EDIT_SZLENGTH			12			// 사실 바이트 수
#define LOGIN_FILE_LOGBOX			".\\Data\\Login\\login_loginbox.img"
#define LOGIN_SIZE_LOGBOX_W			200
#define LOGIN_SIZE_LOGBOX_H			150
#define LOGIN_POS_LOGBOX_X			((WNDSIZEW - LOGIN_SIZE_LOGBOX_W) / 2)
#define LOGIN_POS_LOGBOX_Y			260

#define LOGIN_EDIT_ID_W				120
#define LOGIN_EDIT_ID_H				20
#define LOGIN_EDIT_ID_X				((WNDSIZEW - LOGIN_EDIT_ID_W) / 2 + 25)
#define LOGIN_EDIT_ID_Y				300
#define LOGIN_EDIT_PW_W				120
#define LOGIN_EDIT_PW_H				20
#define LOGIN_EDIT_PW_X				((WNDSIZEW - LOGIN_EDIT_ID_W) / 2 + 25)
#define LOGIN_EDIT_PW_Y				330

#define LOGIN_VER_POS_X				10
#define LOGIN_VER_POS_Y				10


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

	if(!m_ImgLogBox.Load(LOGIN_FILE_LOGBOX))
		return false;

	// button setup
	RECT		rcBtn;

	SetRect(&rcBtn, LOGIN_POS_CONNECTBTNX,
					LOGIN_POS_CONNECTBTNY,
					LOGIN_POS_CONNECTBTNX + LOGIN_SIZE_CONNECTBTNW,
					LOGIN_POS_CONNECTBTNY + LOGIN_SIZE_CONNECTBTNH);

	if(!m_Btn[ELB_CONNECT].SetUp(LOGIN_FILE_CONNECTBTN, LOGIN_VERT_CONNECTBTN, rcBtn))
		return false;
	

	// edit control
	RECT		rcDest;

	SetRect(&rcDest,
			LOGIN_EDIT_ID_X,
			LOGIN_EDIT_ID_Y,
			LOGIN_EDIT_ID_X + LOGIN_EDIT_ID_W,
			LOGIN_EDIT_ID_Y + LOGIN_EDIT_ID_H );

	if(!m_EditID.SetUp(rcDest, NULL, LOGIN_EDIT_SZLENGTH, EDIT_STRING))
		return false;

	SetRect(&rcDest,
			LOGIN_EDIT_PW_X,
			LOGIN_EDIT_PW_Y,
			LOGIN_EDIT_PW_X + LOGIN_EDIT_PW_W,
			LOGIN_EDIT_PW_Y + LOGIN_EDIT_PW_H );
	
	if(!m_EditPW.SetUp(rcDest, NULL, LOGIN_EDIT_SZLENGTH, EDIT_PASSWORD))
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
	m_ImgLogBox.Draw(LOGIN_POS_LOGBOX_X, LOGIN_POS_LOGBOX_Y);

	m_EditID.Draw();
	m_EditPW.Draw();

	int		i;

	for(i = 0; i < ELB_END; i++)
		m_Btn[i].Draw();

	char	szBuf[32];
	wsprintf(szBuf, "Ver %s", SNUDICE_VERSION);
	gUtil::BeginText();
		gUtil::Text(LOGIN_VER_POS_Y, LOGIN_VER_POS_Y, szBuf);
	gUtil::EndText();
}

void gLoginCore::Release()
{
	int		i;

	m_ImgBack.Release();
	m_ImgLogBox.Release();

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

//	MDString(ask.szPW, ask.szPW);
//	MDString(ask.szPW, ask.szPW);

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
			ClearEdit();

			SetFocus(gMainWin::GetIF()->m_hWnd);
			gChat::GetIF()->m_bShow = true;
			gPlayerContainer::GetIF()->SetMyPlayer(rep);
			gPlaySoundCore::GetIF()->PlayEffectSound(EFFECT_FILE_7);

			gUtil::DebugMsg("login success\n");
			break;
	}
}

bool gLoginCore::Restore()
{
	int		i;

	if(!m_ImgBack.Restore())
		return false;
	if(!m_ImgLogBox.Restore())
		return false;

	for(i = 0; i < ELB_END; i++)
		if(!m_Btn[i].Restore())
			return false;

	if(!m_EditID.Restore())
		return false;
	if(!m_EditPW.Restore())
		return false;

	return true;
}

void gLoginCore::ClearEdit()
{
	m_EditID.Clear();
	m_EditPW.Clear();
}