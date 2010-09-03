#include "RoomCore.h"
#include "PopUp.h"
#include "Mouse.h"
#include "Server.h"
#include "PlayerContainer.h"
#include "Util.h"

static gRoomCore s_RoomCore;

gRoomCore *gRoomCore::GetIF()
{
	return &s_RoomCore;
}

gRoomCore::gRoomCore(void)
{
}

gRoomCore::~gRoomCore(void)
{
}

bool gRoomCore::SetUp()
{
	if(!m_ImgBack.Load(ROOM_FILE_BACK))
		return false;

	RECT		rcDest;

	SetRect(&rcDest,
		LOGIN_EDIT_ID_X,
		LOGIN_EDIT_ID_Y,
		LOGIN_EDIT_ID_X + LOGIN_EDIT_ID_W,
		LOGIN_EDIT_ID_Y + LOGIN_EDIT_ID_H );

	if(!m_EditRoom.SetUp(rcDest, LOGIN_EDIT_IMG, LOGIN_EDIT_SZLENGTH, EDIT_STRING))
		return false;

	SetRect(&rcDest,
		LOGIN_EDIT_PW_X,
		LOGIN_EDIT_PW_Y,
		LOGIN_EDIT_PW_X + LOGIN_EDIT_PW_W,
		LOGIN_EDIT_PW_Y + LOGIN_EDIT_PW_H );

	if(!m_EditPass.SetUp(rcDest, LOGIN_EDIT_IMG, LOGIN_EDIT_SZLENGTH, EDIT_PASSWORD))
		return false;

	//m_EditRoom.SetFocusOn();

	return true;
}

void gRoomCore::MainLoop()
{
	Draw();
}

void gRoomCore::Draw()
{
	m_ImgBack.Draw();

	m_EditRoom.Draw();
	m_EditPass.Draw();
}

void gRoomCore::Release()
{
	m_ImgBack.Release();

	m_EditRoom.Release();
	m_EditPass.Release();
}

void gRoomCore::OnLButtonDown()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;

	gMouse	*mouse = gMouse::GetIF();

	if(m_EditRoom.isPointInEdit(mouse->m_nPosX, mouse->m_nPosY))
		m_EditRoom.SetFocusOn();
	else if(m_EditPass.isPointInEdit(mouse->m_nPosX, mouse->m_nPosY))
		m_EditPass.SetFocusOn();
}

void gRoomCore::OnLButtonUp()
{

}

void gRoomCore::OnMouseMove()
{

}

void gRoomCore::OnRButtonDown()
{

}

bool gRoomCore::PreTransMsg(MSG &msg)
{
	if(msg.hwnd == m_EditRoom.m_hEdit)
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
				m_EditPass.SetFocusOn();
				return true;
			case VK_TAB:
				m_EditPass.SetFocusOn();
				return true;
			case VK_SPACE:
			case VK_ESCAPE:
				return true;
			}
		}
	}
	else if(msg.hwnd == m_EditPass.m_hEdit)
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
				SendRoomMake();
				return true;
			case VK_TAB:
				//m_EditRoom.SetFocusOn();
				return true;
			case VK_SPACE:
			case VK_ESCAPE:
				return true;
			}
		}
	}

	return false;
}

void gRoomCore::SendRoomMake()
{
	PK_ROOMMAKER_ASK	ask;

	memset(&ask, 0, sizeof(ask));
	ask.room.nMaxPlayer = 8;
	strcpy(ask.room.szRoomMaxPlayer[0], gPlayerContainer::GetIF()->m_MyPlayer.szID);
	strcpy(ask.room.szRoomName, m_EditRoom.m_szEdit);
	if(strlen(m_EditPass.m_szEdit) == 0)
	{
		ask.room.isPass = false;
	}
	else
	{
		ask.room.isPass = true;
		strcpy(ask.room.szRoomPass, m_EditPass.m_szEdit);
	}

	gServer::GetIF()->Send(PL_ROOMMAKER_ASK, sizeof(PK_ROOMMAKER_ASK), &ask);
}

void gRoomCore::pk_roommake_rep(PK_ROOMMAKER_REP *rep)
{
	if(rep->result == ERM_USINGNAME)
	{
		gUtil::DebugMsg("Using Name\n");
	}
	else
	{
		gUtil::DebugMsg("Success\n");
	}
}