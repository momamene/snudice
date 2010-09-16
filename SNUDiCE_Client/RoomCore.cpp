#include "RoomCore.h"
#include "PopUp.h"
#include "Mouse.h"
#include "Server.h"
#include "PlayerContainer.h"
#include "Util.h"
#include "TopUI.h"
#include "Chat.h"

#define ROOM_FILE_BACK				".\\Data\\Room\\room_back.img"

// make
#define	ROOM_FILE_MAKE_BACK			".\\Data\\Room\\make_back.img" 
#define ROOM_POS_MAKE_X				0
#define ROOM_POS_MAKE_Y				60

#define ROOM_FILE_BTN_OK			".\\Data\\Room\\make_btn_ok.img"
#define ROOM_BTN_SIZE_OK_W			99
#define	ROOM_BTN_SIZE_OK_H			40
#define ROOM_BTN_POS_OK_X			322
#define ROOM_BTN_POS_OK_Y			410

#define ROOM_FILE_BTN_CANCEL		".\\Data\\Room\\make_btn_cancel.img"
#define ROOM_BTN_SIZE_CANCEL_W		99
#define	ROOM_BTN_SIZE_CANCEL_H		40
#define ROOM_BTN_POS_CANCEL_X		475
#define ROOM_BTN_POS_CANCEL_Y		410

#define ROOM_EDIT_LEN_ID			26
#define ROOM_EDIT_SIZE_ID_W			190
#define ROOM_EDIT_SIZE_ID_H			15
#define ROOM_EDIT_POS_ID_X			33
#define ROOM_EDIT_POS_ID_Y			167

#define ROOM_EDIT_LEN_PW			16
#define ROOM_EDIT_SIZE_PW_W			110
#define ROOM_EDIT_SIZE_PW_H			15
#define ROOM_EDIT_POS_PW_X			98
#define ROOM_EDIT_POS_PW_Y			388

// join
#define ROOM_FILE_JOIN_BACK			".\\Data\\Room\\join_back.img"
#define ROOM_POS_JOIN_X				0
#define ROOM_POS_JOIN_Y				60

// room
#define ROOM_FILE_ROOM_BACK			".\\Data\\Room\\room_back.img"
#define ROOM_POS_ROOM_X				0
#define ROOM_POS_ROOM_Y				60


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
	if(!SetUp_Make())
		return false;
	if(!SetUp_Join())
		return false;
	if(!SetUp_Room())
		return false;

	return true;
}

void gRoomCore::MainLoop()
{
	switch(m_eRoom)
	{
		case ERM_MAKE:
			MainLoop_Make();			
			break;
		case ERM_JOIN:
			MainLoop_Join();
			break;
		case ERM_ROOM:
			MainLoop_Room();
			break;
	}
}

void gRoomCore::Draw()
{
	
}

void gRoomCore::Release()
{
	int		i;

	for(i = 0; i < ERM_END; i++)
		m_ImgBack[i].Release();

	for(i = 0; i < BMM_END; i++)
		m_MakeBtn[i].Release();

	m_EditRoom.Release();
	m_EditPass.Release();
}

void gRoomCore::OnLButtonDown()
{
	if(!gServer::GetIF()->m_bConnect)	// 서버랑 연결 안되었으면 입력 막자
		return;

	switch(m_eRoom)
	{
		case ERM_MAKE:
			OnLButtonDown_Make();
			break;
	}
}

void gRoomCore::OnLButtonUp()
{

}

void gRoomCore::OnMouseMove()
{
	switch(m_eRoom)
	{
		case ERM_MAKE:
			OnMouseMove_Make();
			break;
	}
}

void gRoomCore::OnRButtonDown()
{
	switch(m_eRoom)
	{
		case ERM_MAKE:
			OnLButtonDown_Make();
		break;
	}
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
				case VK_ESCAPE:
					{
						Cancel_Make();
					}
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
					m_EditRoom.SetFocusOn();
					return true;
				case VK_SPACE:
					return true;
				case VK_ESCAPE:
					{
						Cancel_Make();
					}
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
	ask.room.nMaxPlayer = 6;
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
		m_eRoom = ERM_ROOM;
	}
}

bool gRoomCore::SetUp_Make()
{
	if(!m_ImgBack[ERM_MAKE].Load(ROOM_FILE_MAKE_BACK))
		return false;

	RECT	rcDest;

	// btn
	SetRect(&rcDest,
		ROOM_BTN_POS_OK_X,
		ROOM_BTN_POS_OK_Y,
		ROOM_BTN_POS_OK_X + ROOM_BTN_SIZE_OK_W,
		ROOM_BTN_POS_OK_Y + ROOM_BTN_SIZE_OK_H );
	if(!m_MakeBtn[BMM_OK].SetUp(ROOM_FILE_BTN_OK, false, rcDest))
		return false;

	SetRect(&rcDest,
		ROOM_BTN_POS_CANCEL_X,
		ROOM_BTN_POS_CANCEL_Y,
		ROOM_BTN_POS_CANCEL_X + ROOM_BTN_SIZE_CANCEL_W,
		ROOM_BTN_POS_CANCEL_Y + ROOM_BTN_SIZE_CANCEL_H );
	if(!m_MakeBtn[BMM_CANCEL].SetUp(ROOM_FILE_BTN_CANCEL, false, rcDest))
		return false;

	// edit
	SetRect(&rcDest,
		ROOM_EDIT_POS_ID_X,
		ROOM_EDIT_POS_ID_Y,
		ROOM_EDIT_POS_ID_X + ROOM_EDIT_SIZE_ID_W,
		ROOM_EDIT_POS_ID_Y + ROOM_EDIT_SIZE_ID_H );

	if(!m_EditRoom.SetUp(rcDest, NULL, ROOM_EDIT_LEN_ID, EDIT_AVAILSPACESTRING))
		return false;

	SetRect(&rcDest,
		ROOM_EDIT_POS_PW_X,
		ROOM_EDIT_POS_PW_Y,
		ROOM_EDIT_POS_PW_X + ROOM_EDIT_SIZE_PW_W,
		ROOM_EDIT_POS_PW_Y + ROOM_EDIT_SIZE_PW_H );

	if(!m_EditPass.SetUp(rcDest, NULL, ROOM_EDIT_LEN_PW, EDIT_PASSWORD))
		return false;

//	m_EditRoom.SetFocusOn();

	return true;
}

void gRoomCore::MainLoop_Make()
{
	Draw_Make();
}

void gRoomCore::Draw_Make()
{
	m_ImgBack[ERM_MAKE].Draw(ROOM_POS_MAKE_X, ROOM_POS_MAKE_Y);

	int		i;

	for(i = 0; i < BMM_END; i++)
		m_MakeBtn[i].Draw();

	gTopUI::GetIF()->Draw();

	m_EditRoom.Draw();
	m_EditPass.Draw();
}

void gRoomCore::OnLButtonDown_Make()
{
	gMouse	*mouse = gMouse::GetIF();
	int		i;

	if(m_MakeBtn[BMM_OK].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		if(strlen(m_EditRoom.m_szEdit) > 0)
		{
			SendRoomMake();
		}
		return;
	}
	else if(m_MakeBtn[BMM_CANCEL].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
	{
		Cancel_Make();
		return;
	}

	if(m_EditRoom.isPointInEdit(mouse->m_nPosX, mouse->m_nPosY))
		m_EditRoom.SetFocusOn();
	else if(m_EditPass.isPointInEdit(mouse->m_nPosX, mouse->m_nPosY))
		m_EditPass.SetFocusOn();

}

void gRoomCore::OnLButtonUp_Make()
{

}

void gRoomCore::OnMouseMove_Make()
{
	gMouse	*mouse = gMouse::GetIF();

	int		i;

	for(i = 0; i < BMM_END; i++)
	{
		if(m_MakeBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_MakeBtn[i].m_eBtnMode = EBM_HOVER;
		else
			m_MakeBtn[i].m_eBtnMode = EBM_NONE;
	}
}

void gRoomCore::Clear_Make()
{
	m_EditRoom.Clear();
	m_EditPass.Clear();
}

void gRoomCore::Cancel_Make()
{
	int			i;

	gMainWin::GetIF()->m_eCoreMode = ECM_BATTLENET;
	SetFocus(gMainWin::GetIF()->m_hWnd);

	Clear_Make();
	for(i = 0; i < BMM_END; i++)
		m_MakeBtn[i].m_eBtnMode = EBM_NONE;

}

bool gRoomCore::SetUp_Join()
{
	if(!m_ImgBack[ERM_JOIN].Load(ROOM_FILE_JOIN_BACK))
		return false;

	return true;
}

void gRoomCore::MainLoop_Join()
{
	Draw_Join();
}

void gRoomCore::Draw_Join()
{
	m_ImgBack[ERM_JOIN].Draw(ROOM_POS_JOIN_X, ROOM_POS_JOIN_Y);
}

bool gRoomCore::SetUp_Room()
{
	if(!m_ImgBack[ERM_ROOM].Load(ROOM_FILE_ROOM_BACK))
		return false;

	return true;
}

void gRoomCore::MainLoop_Room()
{
	Draw_Room();
}

void gRoomCore::Draw_Room()
{
	m_ImgBack[ERM_ROOM].Draw(ROOM_POS_ROOM_X, ROOM_POS_ROOM_Y);
}
