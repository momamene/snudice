#include "RoomCore.h"
#include "PopUp.h"
#include "Mouse.h"
#include "Server.h"
#include "PlayerContainer.h"
#include "Util.h"
#include "TopUI.h"
#include "Chat.h"
#include "stringconst.h"

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

#define ROOM_EDIT_LEN_ID			26					// 방이름...
#define ROOM_EDIT_SIZE_ID_W			190
#define ROOM_EDIT_SIZE_ID_H			15
#define ROOM_EDIT_POS_ID_X			33
#define ROOM_EDIT_POS_ID_Y			166

#define ROOM_EDIT_LEN_PW			16
#define ROOM_EDIT_SIZE_PW_W			110
#define ROOM_EDIT_SIZE_PW_H			15
#define ROOM_EDIT_POS_PW_X			98
#define ROOM_EDIT_POS_PW_Y			387

#define ROOM_FILE_BTN_LIST			".\\Data\\Room\\make_btn_list.img"
#define ROOM_BTN_SIZE_LIST_W		20
#define ROOM_BTN_SIZE_LIST_H		20
#define ROOM_BTN_POS_LIST_X			185
#define ROOM_BTN_POS_LIST_Y			215

#define ROOM_FILE_BTN_2				".\\Data\\Room\\make_btn_2.img"
#define ROOM_FILE_BTN_3				".\\Data\\Room\\make_btn_3.img"
#define ROOM_FILE_BTN_4				".\\Data\\Room\\make_btn_4.img"
#define ROOM_FILE_BTN_5				".\\Data\\Room\\make_btn_5.img"
#define ROOM_FILE_BTN_6				".\\Data\\Room\\make_btn_6.img"
#define ROOM_FILE_BTN_7				".\\Data\\Room\\make_btn_7.img"
#define ROOM_FILE_BTN_8				".\\Data\\Room\\make_btn_8.img"
#define ROOM_BTN_SIZE_NUM_W			98
#define ROOM_BTN_SIZE_NUM_H			22
#define ROOM_BTN_POS_NUM_X			105
#define ROOM_BTN_POS_NUM_Y			235

#define ROOM_FILE_NUMS				".\\Data\\Room\\make_listnum.img"
#define ROOM_SIZE_NUM_W				16
#define ROOM_SIZE_NUM_H				16
#define ROOM_POS_NUM_X				142
#define ROOM_POS_NUM_Y				217

#define ROOM_FILE_PASS				".\\Data\\Room\\make_pass.img"
#define ROOM_SIZE_PASS_W			20
#define ROOM_SIZE_PASS_H			20
#define ROOM_POS_PASS_X				95
#define ROOM_POS_PASS_Y				335

// join
#define ROOM_FILE_JOIN_BACK			".\\Data\\Room\\join_back.img"
#define ROOM_POS_JOIN_X				0
#define ROOM_POS_JOIN_Y				60

#define JOIN_BTN_FILE_RNAME			".\\Data\\Room\\join_btn_rname.img"
#define JOIN_FILE_RNAME				".\\Data\\Room\\join_roomname.img"
#define JOIN_SIZE_RNAME_W			220
#define JOIN_SIZE_RNAME_H			80
#define JOIN_POS_RNAME_X			12
#define JOIN_POS_RNAME_Y			72
#define JOIN_TERM_RNAME_X			15
#define JOIN_TERM_RNAME_Y			6
#define JOIN_TERM_RNAMETEXT_X		20
#define JOIN_TERM_RNAMETEXT_Y		18
#define JOIN_TERM_PLAYERNUM_X		39
#define JOIN_TERM_PLAYERNUM_Y		53

#define JOIN_POS_PAGE_X				226
#define JOIN_POS_PAGE_Y				440

#define JOIN_POS_MAKERNAME_X		500
#define JOIN_POS_MAKERNAME_Y		130
#define JOIN_POS_ROOMUSER_X			505
#define JOIN_POS_ROOMUSER_Y			170
#define JOIN_TERM_ROOMUSER_Y		20

#define JOIN_BTN_FILE_PREV			".\\Data\\Room\\join_btn_prev.img"
#define JOIN_BTN_FILE_NEXT			".\\Data\\Room\\join_btn_next.img"
#define JOIN_BTN_SIZE_PREV_W		13
#define JOIN_BTN_SIZE_PREV_H		20
#define JOIN_BTN_POS_PREV_X			178
#define JOIN_BTN_POS_PREV_Y			435
#define JOIN_BTN_POS_NEXT_X			287
#define JOIN_BTN_POS_NEXT_Y			435

#define JOIN_BTN_FILE_JOIN			".\\Data\\Room\\join_btn_join.img"
#define JOIN_BTN_SIZE_JOIN_W		120
#define JOIN_BTN_SIZE_JOIN_H		120
#define JOIN_BTN_POS_JOIN_X			500
#define JOIN_BTN_POS_JOIN_Y			340

#define JOIN_FILE_PASSBACK			".\\Data\\Room\\join_pass_back.img"
#define JOIN_SIZE_PASSBACK_W		200
#define JOIN_SIZE_PASSBACK_H		60

#define JOIN_BTN_FILE_PASS			".\\Data\\Room\\join_btn_pass.img"
#define JOIN_BTN_SIZE_PASS_W		20
#define JOIN_BTN_SIZE_PASS_H		20

#define JOIN_TERM_PASS_X			30
#define JOIN_TERM_PASS_Y			30
#define JOIN_TERM_BTN_PASS_X		170
#define JOIN_TERM_BTN_PASS_Y		27
#define JOIN_TERM_EDIT_PASS_X		20
#define JOIN_TERM_EDIT_PASS_Y		28


// room
#define ROOM_FILE_ROOM_BACK			".\\Data\\Room\\room_back.img"
#define ROOM_POS_ROOM_X				0
#define ROOM_POS_ROOM_Y				60

#define WAIT_POS_USER_X				498
#define WAIT_POS_USER_Y				108
#define WAIT_TERM_USER_Y			20

#define WAIT_BTN_FILE_READY			".\\Data\\Room\\wait_btn_ready.img"
#define WAIT_BTN_FILE_START			".\\Data\\Room\\wait_btn_start.img"
#define WAIT_BTN_SIZE_READY_W		120
#define WAIT_BTN_SIZE_READY_H		120
#define WAIT_BTN_POS_READY_X		500
#define WAIT_BTN_POS_READY_Y		340

#define WAIT_FILE_CHARBACK			".\\Data\\Room\\wait_char_back.img"
#define WAIT_SIZE_CHARBACK_W		110
#define WAIT_SIZE_CHARBACK_H		140
#define WAIT_POS_CHARBACK_X			11
#define WAIT_POS_CHARBACK_Y			68
#define WAIT_TERM_CHARBACK_X		6
#define WAIT_TERM_CHARBACK_Y		4
#define WAIT_TERM_CHARNAMEBACK_X	10
#define WAIT_TERM_CHARNAMEBACK_Y	10

// room - select
#define WAIT_FILE_SELBACK			".\\Data\\Room\\wait_charselback.img"
#define WAIT_SIZE_SELBACK_W			265
#define WAIT_SIZE_SELBACK_H			445
#define WAIT_POS_SELBACK_X			360
#define WAIT_POS_SELBACK_Y			20

#define SEL_FILE_STUDY				".\\Data\\Room\\wait_bar_study.img"
#define SEL_FILE_STAMINA			".\\Data\\Room\\wait_bar_stamina.img"
#define SEL_FILE_MOVE				".\\Data\\Room\\wait_bar_move.img"
#define SEL_SIZE_BAR_W				102
#define SEL_SIZE_BAR_H				12

#define SEL_POS_BAR_X				(WAIT_POS_SELBACK_X + 139)
#define SEL_POS_LANG_Y				(WAIT_POS_SELBACK_Y + 278)
#define SEL_POS_MATH_Y				(WAIT_POS_SELBACK_Y + 298)
#define SEL_POS_ART_Y				(WAIT_POS_SELBACK_Y + 318)
#define SEL_POS_STAMINA_Y			(WAIT_POS_SELBACK_Y + 346)
#define SEL_POS_MOVE_Y				(WAIT_POS_SELBACK_Y + 366)

#define SEL_FILE_OUTLINE			".\\Data\\Room\\wait_btn_outline.img"
#define SEL_BTN_FILE_LANG			".\\Data\\Room\\wait_btn_lang.img"
#define SEL_BTN_FILE_MATH			".\\Data\\Room\\wait_btn_math.img"
#define SEL_BTN_FILE_ART			".\\Data\\Room\\wait_btn_art.img"
#define SEL_BTN_SIZE_LANG_W			81
#define SEL_BTN_SIZE_LANG_H			21
#define SEL_BTN_POS_CHARSEL_X		375
#define SEL_BTN_POS_CHARSEL_Y		54
#define SEL_BTN_TERM_CHARSEL_Y		4

#define SEL_BTN_FILE_SELECT			".\\Data\\Room\\wait_btn_select.img"
#define SEL_BTN_SIZE_SELECT_W		110
#define SEL_BTN_SIZE_SELECT_H		30
#define SEL_BTN_POS_SELECT_X		485
#define SEL_BTN_POS_SELECT_Y		405

#define SEL_POS_CHARIMG_X			478
#define SEL_POS_CHARIMG_Y			62

#define SEL_TERM_CHARNAME_X			6
#define SEL_TERM_CHARNAME_Y			6

#define SEL_POS_COLLEGE_X			479
#define SEL_POS_COLLEGE_Y			220
#define SEL_POS_SEX_X				550
#define SEL_POS_SEX_Y				220

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

	// make
	for(i = 0; i < BMM_END; i++)
		m_MakeBtn[i].Release();

	m_ImgNum.Release();
	m_ImgPass.Release();

	m_EditRoom.Release();
	m_EditPass.Release();

	// join
	m_ImgRoomName.Release();

	for(i = 0; i < BJM_END; i++)
		m_JoinBtn[i].Release();

	m_ImgPassBack.Release();
	m_EditPassEnter.Release();

	// room == wait
	for(i = 0; i < BWM_END; i++)
		m_WaitBtn[i].Release();

	m_ImgSelBack.Release();
	m_ImgCharBack.Release();

	m_ImgBarStudy.Release();
	m_ImgBarStamina.Release();
	m_ImgBarMove.Release();

	m_ImgMySel.Release();

	for(i = 0; i < BSM_END; i++)
		m_SelBtn[i].Release();

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
		case ERM_JOIN:
			OnLButtonDown_Join();
			break;
		case ERM_ROOM:
			OnLButtonDown_Room();
			break;
	}
}

void gRoomCore::OnLButtonUp()
{
	switch(m_eRoom)
	{
		case ERM_MAKE:
			break;
		case ERM_JOIN:
			break;
		case ERM_ROOM:
			OnLButtonUp_Room();
			break;
	}
}

void gRoomCore::OnMouseMove()
{
	switch(m_eRoom)
	{
		case ERM_MAKE:
			OnMouseMove_Make();
			break;
		case ERM_JOIN:
			OnMouseMove_Join();
			break;
		case ERM_ROOM:
			OnMouseMove_Room();
			break;
	}
}

void gRoomCore::OnRButtonDown()
{
	switch(m_eRoom)
	{
		case ERM_ROOM:
			OnRButtonDown_Room();
		break;
	}
}

bool gRoomCore::PreTransMsg(MSG &msg)
{
	switch(m_eRoom)
	{
		case ERM_MAKE:
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
			}
			break;


		case ERM_JOIN:
			{
				if(msg.hwnd == m_EditPassEnter.m_hEdit)
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
								SendRoomJoin();
								return true;
							case VK_TAB:
							case VK_SPACE:
								return true;
							case VK_ESCAPE:
								{
									m_bEnteringPass = false;
									SetFocus(gMainWin::GetIF()->m_hWnd);
								}
								return true;
						}
					}
				}
			}
			break;
		case ERM_ROOM:
			{
				if(msg.hwnd == gChat::GetIF()->m_Edit.m_hEdit)
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
							SetFocus(gMainWin::GetIF()->m_hWnd);
							gChat::GetIF()->SendMsg();
							return true;
						case VK_TAB:
							return true;
						case VK_ESCAPE:
							SetFocus(gMainWin::GetIF()->m_hWnd);
							return true;
						}
					}
				}
			}
			break;
	}

	return false;
}

void gRoomCore::SendRoomMake()
{
	PK_ROOMMAKER_ASK	ask;

	memset(&ask, 0, sizeof(ask));


	strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);

	ask.room.nMaxPlayer = m_nPlayer;
	ask.room.nNowPlayer	= 1;

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
		gUtil::DebugMsg("aUsing Name\n");
		gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_9);
	}
	else
	{
		gUtil::DebugMsg("Success\n");
		m_eRoom = ERM_ROOM;
		gPlayerContainer::GetIF()->SetMyRoom(&rep->room);
		gPlayerContainer::GetIF()->SetPlayerList(rep->playerlist);
		SetFocus(gMainWin::GetIF()->m_hWnd);
		gChat::GetIF()->MsgStackClear();
	}
}

bool gRoomCore::SetUp_Make()
{
	if(!m_ImgBack[ERM_MAKE].Load(ROOM_FILE_MAKE_BACK))
		return false;

	// pass check
	if(!m_ImgPass.Load(ROOM_FILE_PASS))
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

	// list
	if(!m_ImgNum.Load(ROOM_FILE_NUMS))
		return false;

	m_nPlayer = 2;

	// list btn
	SetRect(&rcDest,
		ROOM_BTN_POS_LIST_X,
		ROOM_BTN_POS_LIST_Y,
		ROOM_BTN_POS_LIST_X + ROOM_BTN_SIZE_LIST_W,
		ROOM_BTN_POS_LIST_Y + ROOM_BTN_SIZE_LIST_H );

	if(!m_MakeBtn[BMM_LIST].SetUp(ROOM_FILE_BTN_LIST, false, rcDest))
		return false;

	SetRect(&rcDest,
		ROOM_BTN_POS_NUM_X,
		ROOM_BTN_POS_NUM_Y,
		ROOM_BTN_POS_NUM_X + ROOM_BTN_SIZE_NUM_W,
		ROOM_BTN_POS_NUM_Y + ROOM_BTN_SIZE_NUM_H );

	for(int i = BMM_NUM2; i <= BMM_NUM8; i++)
	{
		RECT	rcTemp = rcDest;
		OffsetRect(&rcTemp, 0, ROOM_BTN_SIZE_NUM_H * (i - BMM_NUM2) );

		switch(i)
		{
			case BMM_NUM2:
				if(!m_MakeBtn[i].SetUp(ROOM_FILE_BTN_2, false, rcTemp))
					return false;
				break;
			case BMM_NUM3:
				if(!m_MakeBtn[i].SetUp(ROOM_FILE_BTN_3, false, rcTemp))
					return false;
				break;
			case BMM_NUM4:
				if(!m_MakeBtn[i].SetUp(ROOM_FILE_BTN_4, false, rcTemp))
					return false;
				break;
			case BMM_NUM5:
				if(!m_MakeBtn[i].SetUp(ROOM_FILE_BTN_5, false, rcTemp))
					return false;
				break;
			case BMM_NUM6:
				if(!m_MakeBtn[i].SetUp(ROOM_FILE_BTN_6, false, rcTemp))
					return false;
				break;
			case BMM_NUM7:
				if(!m_MakeBtn[i].SetUp(ROOM_FILE_BTN_7, false, rcTemp))
					return false;
				break;
			case BMM_NUM8:
				if(!m_MakeBtn[i].SetUp(ROOM_FILE_BTN_8, false, rcTemp))
					return false;
				break;
		}
	}

	m_bIsPull = false;

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
}

void gRoomCore::Draw_Make()
{
	m_ImgBack[ERM_MAKE].Draw(ROOM_POS_MAKE_X, ROOM_POS_MAKE_Y);

	if(strlen(m_EditPass.m_szEdit) > 0)
	{
		m_ImgPass.Draw(ROOM_POS_PASS_X, ROOM_POS_PASS_Y);
	}

	int		i;

	RECT	rcDest, rcSour;

	SetRect(&rcDest,
			ROOM_POS_NUM_X,
			ROOM_POS_NUM_Y,
			ROOM_POS_NUM_X + ROOM_SIZE_NUM_W,
			ROOM_POS_NUM_Y + ROOM_SIZE_NUM_H );
	SetRect(&rcSour,
			0, 0, ROOM_SIZE_NUM_W, ROOM_SIZE_NUM_H );

	OffsetRect(&rcSour, (m_nPlayer - 2) * ROOM_SIZE_NUM_W, 0);

	m_ImgNum.Draw(rcDest, rcSour, false);


	if(m_bIsPull)
	{
		for(i = 0; i < BMM_END; i++)
			m_MakeBtn[i].Draw();
	}
	else
	{
		for(i = 0; i < BMM_NUM2; i++)
			m_MakeBtn[i].Draw();
	}

	gTopUI::GetIF()->Draw();

	m_EditRoom.Draw();
	m_EditPass.Draw();
}

void gRoomCore::OnLButtonDown_Make()
{
	gMouse	*mouse = gMouse::GetIF();
	int		i;

	if(m_bIsPull)
	{
		if(m_MakeBtn[BMM_LIST].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			m_bIsPull = !m_bIsPull;
			return;
		}

		for(i = BMM_NUM2; i <= BMM_NUM8; i++)
		{
			if(m_MakeBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				m_nPlayer = i - BMM_NUM2 + 2;
				m_bIsPull = false;
				return;
			}
		}
		return;
	}
	else
	{
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
		else if(m_MakeBtn[BMM_LIST].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			m_bIsPull = !m_bIsPull;
			return;
		}
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

	if(m_bIsPull)
	{
		for(i = 0; i < BMM_END; i++)
		{
			if(m_MakeBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_MakeBtn[i].m_eBtnMode = EBM_HOVER;
			else
				m_MakeBtn[i].m_eBtnMode = EBM_NONE;
		}
	}
	else
	{
		for(i = 0; i < BMM_NUM2; i++)
		{
			if(m_MakeBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_MakeBtn[i].m_eBtnMode = EBM_HOVER;
			else
				m_MakeBtn[i].m_eBtnMode = EBM_NONE;
		}
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
	int		i;

	if(!m_ImgBack[ERM_JOIN].Load(ROOM_FILE_JOIN_BACK))
		return false;

	if(!m_ImgRoomName.Load(JOIN_FILE_RNAME))
		return false;

	if(!m_ImgPassBack.Load(JOIN_FILE_PASSBACK))
		return false;

	m_nSelected		= -1;
	m_bEnteringPass	= false;

	// btn
	RECT	rcDest, rcTemp;

	SetRect(&rcTemp, 
			JOIN_POS_RNAME_X,
			JOIN_POS_RNAME_Y,
			JOIN_POS_RNAME_X + JOIN_SIZE_RNAME_W,
			JOIN_POS_RNAME_Y + JOIN_SIZE_RNAME_H );

	for(i = BJM_ROOM1; i <= BJM_ROOM8; i++)
	{
		rcDest = rcTemp;
		OffsetRect(&rcDest,
				((i - BJM_ROOM1) % 2) * (JOIN_SIZE_RNAME_W + JOIN_TERM_RNAME_X) , 
				((i - BJM_ROOM1) / 2) * (JOIN_SIZE_RNAME_H + JOIN_TERM_RNAME_Y) );
		if(!m_JoinBtn[i].SetUp(JOIN_BTN_FILE_RNAME, false, rcDest))
			return false;
	}

	// prev, next
	SetRect(&rcDest,
			JOIN_BTN_POS_PREV_X,
			JOIN_BTN_POS_PREV_Y,
			JOIN_BTN_POS_PREV_X + JOIN_BTN_SIZE_PREV_W,
			JOIN_BTN_POS_PREV_Y + JOIN_BTN_SIZE_PREV_H );
	if(!m_JoinBtn[BJM_PREV].SetUp(JOIN_BTN_FILE_PREV, false, rcDest))
		return false;

	SetRect(&rcDest,
		JOIN_BTN_POS_NEXT_X,
		JOIN_BTN_POS_NEXT_Y,
		JOIN_BTN_POS_NEXT_X + JOIN_BTN_SIZE_PREV_W,
		JOIN_BTN_POS_NEXT_Y + JOIN_BTN_SIZE_PREV_H );
	if(!m_JoinBtn[BJM_NEXT].SetUp(JOIN_BTN_FILE_NEXT, false, rcDest))
		return false;

	// join
	SetRect(&rcDest,
			JOIN_BTN_POS_JOIN_X,
			JOIN_BTN_POS_JOIN_Y,
			JOIN_BTN_POS_JOIN_X + JOIN_BTN_SIZE_JOIN_W,
			JOIN_BTN_POS_JOIN_Y + JOIN_BTN_SIZE_JOIN_H );
	if(!m_JoinBtn[BJM_JOIN].SetUp(JOIN_BTN_FILE_JOIN, false, rcDest))
		return false;

	// pass
	// 이넘은 위치 셋팅 나중에
	if(!m_JoinBtn[BJM_PASS].SetUp(JOIN_BTN_FILE_PASS, false, rcDest))
		return false;

	// edit
	// 이넘도 위치 바뀐다. 대충 셋팅
	SetRect(&rcDest,
			ROOM_EDIT_POS_ID_X,
			ROOM_EDIT_POS_ID_Y,
			ROOM_EDIT_POS_ID_X + ROOM_EDIT_SIZE_ID_W,
			ROOM_EDIT_POS_ID_Y + ROOM_EDIT_SIZE_ID_H );

	if(!m_EditPassEnter.SetUp(rcDest, NULL, ROOM_EDIT_LEN_PW, EDIT_PASSWORD))
		return false;


	return true;
}

void gRoomCore::MainLoop_Join()
{
	Draw_Join();

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
}

void gRoomCore::Draw_Join()
{
	m_ImgBack[ERM_JOIN].Draw(ROOM_POS_JOIN_X, ROOM_POS_JOIN_Y);
	gTopUI::GetIF()->Draw();

	int			i, j;

	RECT		rcSour;


	for(i = BJM_ROOM1; i <= BJM_ROOM8; i++)
	{
		SetRect(&rcSour,
			0, 0, JOIN_SIZE_RNAME_W, JOIN_SIZE_RNAME_H);

		int		nRoomIdx = i - BJM_ROOM1;

		if(strlen(m_Room[nRoomIdx].szRoomName) == 0)
		{

		}
		else if(m_Room[nRoomIdx].isPass)
		{
			OffsetRect(&rcSour, 0, JOIN_SIZE_RNAME_H);
		}
		else if(!m_Room[nRoomIdx].isGaming &&
				m_Room[nRoomIdx].nNowPlayer != m_Room[nRoomIdx].nMaxPlayer)		// wait
		{
			OffsetRect(&rcSour, 0, JOIN_SIZE_RNAME_H * 2);
		}
		else if(m_Room[nRoomIdx].isGaming)			// playing
		{
			OffsetRect(&rcSour, 0, JOIN_SIZE_RNAME_H * 3);
		}
		else if(m_Room[nRoomIdx].nNowPlayer == m_Room[nRoomIdx].nMaxPlayer)	//full
		{
			OffsetRect(&rcSour, 0, JOIN_SIZE_RNAME_H * 4);
		}

		m_ImgRoomName.Draw(m_JoinBtn[nRoomIdx].m_rcPos, rcSour, false);
	}
	for(i = BJM_PREV; i <= BJM_JOIN;i ++)
	{
		m_JoinBtn[i].Draw();
	}

	if(m_nSelected != -1)
	{
		m_JoinBtn[m_nSelected + BJM_ROOM1].Draw();
	}

	char	szBuf[128];
	gUtil::BeginText();
		// page
		wsprintf(szBuf, "%d / %d", m_nPage + 1, MAXPAGE);
		gUtil::Text(JOIN_POS_PAGE_X, JOIN_POS_PAGE_Y, szBuf);

		// roomname
		int		nRoomIdx;
		int		nRoomArrIdx;
		for(i = 0; i < MAXROOMFORPAGE; i++)
		{
			nRoomArrIdx	= i + BJM_ROOM1;

			if(strlen(m_Room[i].szRoomName) == 0)
				continue;

			nRoomIdx	= (m_nPage * MAXROOMFORPAGE) + i + 1;

			if(nRoomIdx > 10)
				wsprintf(szBuf, "[0%d] ", nRoomIdx);
			else
				wsprintf(szBuf, "[00%d] ", nRoomIdx);

			strcat(szBuf, m_Room[i].szRoomName);

			gUtil::Text(m_JoinBtn[nRoomArrIdx].m_rcPos.left + JOIN_TERM_RNAMETEXT_X, 
						m_JoinBtn[nRoomArrIdx].m_rcPos.top + JOIN_TERM_RNAMETEXT_Y,	szBuf);

			wsprintf(szBuf, "%d / %d", m_Room[i].nNowPlayer, m_Room[i].nMaxPlayer);

			gUtil::Text(m_JoinBtn[nRoomArrIdx].m_rcPos.left + JOIN_TERM_PLAYERNUM_X,
						m_JoinBtn[nRoomArrIdx].m_rcPos.top + JOIN_TERM_PLAYERNUM_Y, szBuf);

		}

		// selected room
		if(m_nSelected != -1)
		{
			gUtil::Text(JOIN_POS_MAKERNAME_X, JOIN_POS_MAKERNAME_Y,
								m_Room[m_nSelected].szRoomMaxPlayer[ m_Room[m_nSelected].nMakerIndex ]);

			int			k = 0;
			for(j = 0; j < m_Room[m_nSelected].nMaxPlayer; j++)
			{
				if(j == m_Room[m_nSelected].nMakerIndex)
					continue;

				gUtil::Text(JOIN_POS_ROOMUSER_X, JOIN_POS_ROOMUSER_Y + JOIN_TERM_ROOMUSER_Y * k, m_Room[m_nSelected].szRoomMaxPlayer[j]);
				k++;
			}
		}

	gUtil::EndText();

	if(m_bEnteringPass)
	{
		m_ImgPassBack.Draw(m_ptPass.x, m_ptPass.y);
		m_JoinBtn[BJM_PASS].Draw();
		m_EditPassEnter.Draw();
	}
}

bool gRoomCore::SetUp_Room()
{
	if(!m_ImgBack[ERM_ROOM].Load(ROOM_FILE_ROOM_BACK))
		return false;

	if(!m_ImgCharBack.Load(WAIT_FILE_CHARBACK))
		return false;

	int			i;

	RECT		rcDest;

	SetRect(&rcDest,
			WAIT_BTN_POS_READY_X,
			WAIT_BTN_POS_READY_Y,
			WAIT_BTN_POS_READY_X + WAIT_BTN_SIZE_READY_W,
			WAIT_BTN_POS_READY_Y + WAIT_BTN_SIZE_READY_H );
	if(!m_WaitBtn[BWM_READY].SetUp(WAIT_BTN_FILE_READY, false, rcDest))
		return false;
	if(!m_WaitBtn[BWM_START].SetUp(WAIT_BTN_FILE_START, false, rcDest))
		return false;

	if(!m_ImgSelBack.Load(WAIT_FILE_SELBACK))
		return false;

	m_bCharSel	= false;
	m_nSelUser	= -1;

	// sel

	if(!m_ImgBarStudy.Load(SEL_FILE_STUDY))
		return false;
	if(!m_ImgBarStamina.Load(SEL_FILE_STAMINA))
		return false;
	if(!m_ImgBarMove.Load(SEL_FILE_MOVE))
		return false;

	if(!m_ImgMySel.Load(SEL_FILE_OUTLINE))
		return false;

	SetRect(&rcDest,
			SEL_BTN_POS_CHARSEL_X,
			SEL_BTN_POS_CHARSEL_Y,
			SEL_BTN_POS_CHARSEL_X + SEL_BTN_SIZE_LANG_W,
			SEL_BTN_POS_CHARSEL_Y + SEL_BTN_SIZE_LANG_H );

	RECT		rcTemp;

	for(i = 0; i < BSM_SELECT; i++)
	{
		rcTemp = rcDest;
		OffsetRect(&rcTemp, 0, (SEL_BTN_SIZE_LANG_H + SEL_BTN_TERM_CHARSEL_Y) * i);

		if(i <= BSM_FREE)
		{
			if(!m_SelBtn[i].SetUp(SEL_BTN_FILE_LANG, false, rcTemp))
				return false;
			continue;
		}
		if(i <= BSM_FARM)
		{
			if(!m_SelBtn[i].SetUp(SEL_BTN_FILE_MATH, false, rcTemp))
				return false;
			continue;
		}
		if(i <= BSM_ART)
		{
			if(!m_SelBtn[i].SetUp(SEL_BTN_FILE_ART, false, rcTemp))
				return false;
			continue;
		}
	}

	SetRect(&rcDest,
			SEL_BTN_POS_SELECT_X,
			SEL_BTN_POS_SELECT_Y,
			SEL_BTN_POS_SELECT_X + SEL_BTN_SIZE_SELECT_W,
			SEL_BTN_POS_SELECT_Y + SEL_BTN_SIZE_SELECT_H );

	if(!m_SelBtn[BSM_SELECT].SetUp(SEL_BTN_FILE_SELECT, false, rcDest))
		return false;

	m_nSelChar	= -1;

	return true;
}

void gRoomCore::MainLoop_Room()
{
	Draw_Room();

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

	if(gMainWin::GetIF()->m_Keys[VK_RETURN])
	{
		gChat::GetIF()->m_Edit.SetFocusOn();
		gMainWin::GetIF()->m_Keys[VK_RETURN] = false;
	}

	gChat::GetIF()->MainLoop();
}

void gRoomCore::Draw_Room()
{
	m_ImgBack[ERM_ROOM].Draw(ROOM_POS_ROOM_X, ROOM_POS_ROOM_Y);
	gTopUI::GetIF()->Draw();

	int			i;

	ROOM	*room = &gPlayerContainer::GetIF()->m_MyRoom;


	// 뒤에 캐릭터정보 배경
	for(i = 0; i < room->nMaxPlayer; i++)
	{
		RECT		rcDest, rcSour;

		SetRect(&rcDest,
				WAIT_POS_CHARBACK_X,
				WAIT_POS_CHARBACK_Y,
				WAIT_POS_CHARBACK_X + WAIT_SIZE_CHARBACK_W,
				WAIT_POS_CHARBACK_Y + WAIT_SIZE_CHARBACK_H );
		OffsetRect(&rcDest,
			(i % 4) * (WAIT_TERM_CHARBACK_X + WAIT_SIZE_CHARBACK_W), (i / 4) * (WAIT_TERM_CHARBACK_Y + WAIT_SIZE_CHARBACK_H));

		SetRect(&rcSour,
				0, 0, WAIT_SIZE_CHARBACK_W, WAIT_SIZE_CHARBACK_H);
		if(strlen(room->szRoomMaxPlayer[i]) > 0)
		{
			OffsetRect(&rcSour, WAIT_SIZE_CHARBACK_W, 0);
		}
		m_ImgCharBack.Draw(rcDest, rcSour);
	}

	// 내가 방장
	if(strcmp(room->szRoomMaxPlayer[room->nMakerIndex], gPlayerContainer::GetIF()->m_MyPlayer.szID) == 0)
	{
		m_WaitBtn[BWM_START].Draw();
	}
	else
	{
		m_WaitBtn[BWM_READY].Draw();
	}

	// 캐릭터 이름
	gUtil::BeginText();
	for(i = 0; i < room->nMaxPlayer; i++)
	{
		if(strlen(room->szRoomMaxPlayer[i]) > 0)
		{
			int		x, y;

			x = WAIT_POS_CHARBACK_X + (i % 4) * (WAIT_TERM_CHARBACK_X + WAIT_SIZE_CHARBACK_W) + WAIT_TERM_CHARNAMEBACK_X;
			y = WAIT_POS_CHARBACK_Y + (i / 4) * (WAIT_TERM_CHARBACK_Y + WAIT_SIZE_CHARBACK_H) + WAIT_TERM_CHARNAMEBACK_Y;

			gUtil::Text(x, y, room->szRoomMaxPlayer[i]);
		}
	}
	gUtil::EndText();

	gChat::GetIF()->Draw();

	if(m_bCharSel)
	{
		PLAYER	*list = gPlayerContainer::GetIF()->m_PlayerList;

		m_ImgSelBack.Draw(WAIT_POS_SELBACK_X, WAIT_POS_SELBACK_Y);

		for(i = 0; i < ROOMMAXPLAYER; i++)
		{
			if(list[i].classtype != -1)
			{
				m_SelBtn[ list[i].classtype ].m_eBtnMode = EBM_CLICK;
			}
		}

		for(i = 0; i < BSM_SELECT; i++)
		{
			m_SelBtn[i].Draw();
		}
		if(m_nSelChar != -1)
		{
			m_ImgMySel.Draw(m_SelBtn[ m_nSelChar ].m_rcPos.left, m_SelBtn[ m_nSelChar ].m_rcPos.top);

			// char img
			gPlayerContainer::GetIF()->m_ImgInfo[ m_nSelChar ].ImgCharSel.Draw(SEL_POS_CHARIMG_X, SEL_POS_CHARIMG_Y);

			// stat
			RECT	rcSour, rcDest, rcTemp;

			SetRect(&rcTemp,
				0, 0, SEL_SIZE_BAR_W, SEL_SIZE_BAR_H );

			//	lang
			rcSour = rcTemp;
			OffsetRect(&rcSour, 0, gPlayerContainer::GetIF()->m_CharInfo[m_nSelChar].nLang * SEL_SIZE_BAR_H );
			SetRect(&rcDest,
					SEL_POS_BAR_X,
					SEL_POS_LANG_Y,
					SEL_POS_BAR_X + SEL_SIZE_BAR_W,
					SEL_POS_LANG_Y + SEL_SIZE_BAR_H);

			m_ImgBarStudy.Draw(rcDest, rcSour);

			// math
			rcSour = rcTemp;
			OffsetRect(&rcSour, 0, gPlayerContainer::GetIF()->m_CharInfo[m_nSelChar].nMath * SEL_SIZE_BAR_H );
			SetRect(&rcDest,
				SEL_POS_BAR_X,
				SEL_POS_MATH_Y,
				SEL_POS_BAR_X + SEL_SIZE_BAR_W,
				SEL_POS_MATH_Y + SEL_SIZE_BAR_H);

			m_ImgBarStudy.Draw(rcDest, rcSour);

			// art
			rcSour = rcTemp;
			OffsetRect(&rcSour, 0, gPlayerContainer::GetIF()->m_CharInfo[m_nSelChar].nArt * SEL_SIZE_BAR_H );
			SetRect(&rcDest,
					SEL_POS_BAR_X,
					SEL_POS_ART_Y,
					SEL_POS_BAR_X + SEL_SIZE_BAR_W,
					SEL_POS_ART_Y + SEL_SIZE_BAR_H);
			m_ImgBarStudy.Draw(rcDest, rcSour);

			// stamina
			rcSour = rcTemp;
			OffsetRect(&rcSour, 0, gPlayerContainer::GetIF()->m_CharInfo[m_nSelChar].nStamina * SEL_SIZE_BAR_H );
			SetRect(&rcDest,
				SEL_POS_BAR_X,
				SEL_POS_STAMINA_Y,
				SEL_POS_BAR_X + SEL_SIZE_BAR_W,
				SEL_POS_STAMINA_Y + SEL_SIZE_BAR_H);
			m_ImgBarStamina.Draw(rcDest, rcSour);					

			// move
			rcSour = rcTemp;
			int		nMove = gPlayerContainer::GetIF()->m_CharInfo[m_nSelChar].nDice4 * 4 + 
							gPlayerContainer::GetIF()->m_CharInfo[m_nSelChar].nDIce6 * 6;

			OffsetRect(&rcSour, 0, (nMove - 2) * SEL_SIZE_BAR_H );
			SetRect(&rcDest,
				SEL_POS_BAR_X,
				SEL_POS_MOVE_Y,
				SEL_POS_BAR_X + SEL_SIZE_BAR_W,
				SEL_POS_MOVE_Y + SEL_SIZE_BAR_H);
			m_ImgBarMove.Draw(rcDest, rcSour);
		}

		// select
		m_SelBtn[BSM_SELECT].Draw();

		// string
		gUtil::BeginText();
			for(i = 0; i < BSM_SELECT; i++)
			{
				gUtil::Text(m_SelBtn[i].m_rcPos.left + SEL_TERM_CHARNAME_X, m_SelBtn[i].m_rcPos.top + SEL_TERM_CHARNAME_Y,
					gPlayerContainer::GetIF()->m_CharInfo[i].szName);	
			}

			if(m_nSelChar != -1)
			{
				gUtil::Text(SEL_POS_COLLEGE_X, SEL_POS_COLLEGE_Y, gPlayerContainer::GetIF()->m_CharInfo[m_nSelChar].szCollege);

				char	szBuf[8];
				if(gPlayerContainer::GetIF()->m_CharInfo[m_nSelChar].bMale)
					wsprintf(szBuf, "♂");
				else
					wsprintf(szBuf, "♀");

				gUtil::Text(SEL_POS_SEX_X, SEL_POS_SEX_Y, szBuf);
			}
		gUtil::EndText();
	}
}


void gRoomCore::pk_roomlist_rep(PK_ROOMLIST_REP *rep)
{
	memcpy(m_Room, rep->roomlist, sizeof(ROOM) * MAXROOMFORPAGE );
	m_nPage	= rep->nPage;
}

void gRoomCore::OnLButtonDown_Join()
{
	gMouse		*mouse = gMouse::GetIF();

	int			i;

	if(m_bEnteringPass)
	{
		if(m_JoinBtn[BJM_PASS].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			SendRoomJoin();
		}
		else if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, m_EditPassEnter.m_rcPos))
		{
			m_EditPassEnter.SetFocusOn();
		}
	}
	else
	{
		for(i = BJM_ROOM1; i <= BJM_ROOM8; i++)
		{
			if(m_JoinBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				if(strlen(m_Room[i - BJM_ROOM1].szRoomName) > 0)
				{
					m_JoinBtn[i].m_eBtnMode = EBM_CLICK;
					m_nSelected = i - BJM_ROOM1;
					return;
				}
			}
		}

		if(m_JoinBtn[BJM_PREV].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			if(m_nPage == 0)
				return;
			else
			{
				PK_ROOMLIST_ASK			ask;

				ask.nPage	= m_nPage - 1;
				strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);
				
				gServer::GetIF()->Send(PL_ROOMLIST_ASK, sizeof(ask), &ask);
				return;
			}
		}
		else if(m_JoinBtn[BJM_NEXT].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			if(m_nPage == MAXPAGE - 1)
				return;
			else
			{
				PK_ROOMLIST_ASK			ask;

				ask.nPage = m_nPage + 1;
				strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);

				gServer::GetIF()->Send(PL_ROOMLIST_ASK, sizeof(ask), &ask);
				return;
			}
		}
		else if(m_JoinBtn[BJM_JOIN].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
		{
			if(m_Room[m_nSelected].isPass)
			{
				m_ptPass.x = m_JoinBtn[m_nSelected + BJM_ROOM1].m_rcPos.left + JOIN_TERM_PASS_X;
				m_ptPass.y = m_JoinBtn[m_nSelected + BJM_ROOM1].m_rcPos.top + JOIN_TERM_PASS_Y;
				SetRect(&m_JoinBtn[BJM_PASS].m_rcPos,
						m_ptPass.x + JOIN_TERM_BTN_PASS_X,
						m_ptPass.y + JOIN_TERM_BTN_PASS_Y,
						m_ptPass.x + JOIN_TERM_BTN_PASS_X + JOIN_BTN_SIZE_PASS_W,
						m_ptPass.y + JOIN_TERM_BTN_PASS_Y + JOIN_BTN_SIZE_PASS_H );

				m_EditPassEnter.SetFocusOn();
				m_EditPassEnter.Clear();
				SetRect(&m_EditPassEnter.m_rcPos,
						m_ptPass.x + JOIN_TERM_EDIT_PASS_X,
						m_ptPass.y + JOIN_TERM_EDIT_PASS_Y,
						m_ptPass.x + JOIN_TERM_EDIT_PASS_X + ROOM_EDIT_SIZE_ID_W,
						m_ptPass.y + JOIN_TERM_EDIT_PASS_Y + ROOM_EDIT_SIZE_ID_H );

				m_bEnteringPass = true;
				return;
			}
			else
			{
				SendRoomJoin();
			}
		}
	}
}

void gRoomCore::OnMouseMove_Join()
{
	gMouse*		mouse = gMouse::GetIF();

	int		i;

	if(m_bEnteringPass)
	{
		if(m_JoinBtn[BJM_PASS].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_JoinBtn[BJM_PASS].m_eBtnMode = EBM_HOVER;
		else
			m_JoinBtn[BJM_PASS].m_eBtnMode = EBM_NONE;
	}
	else
	{
		for(i = BJM_PREV; i < BJM_END; i++)
		{
			if(m_JoinBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_JoinBtn[i].m_eBtnMode = EBM_HOVER;
			else
				m_JoinBtn[i].m_eBtnMode = EBM_NONE;
		}
	}
}

void gRoomCore::SendRoomJoin()
{
	PK_ROOMJOIN_ASK			ask;

	ask.nIdx	= m_nSelected;
	ask.nPage	= m_nPage;
	strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);
	if(m_bEnteringPass)
		strcpy(ask.szPass, m_EditPassEnter.m_szEdit);

	gServer::GetIF()->Send(PL_ROOMJOIN_ASK, sizeof ask, &ask);
}

void gRoomCore::pk_roomjoin_rep(PK_ROOMJOIN_REP *rep)
{
	switch(rep->result)
	{
		case ERJ_SUCCESS:
			{
				m_bEnteringPass = false;
				SetFocus(gMainWin::GetIF()->m_hWnd);
				m_eRoom = ERM_ROOM;
				gPlayerContainer::GetIF()->SetMyRoom(&rep->joinroom);
				gPlayerContainer::GetIF()->SetPlayerList(rep->playerlist);
				gChat::GetIF()->MsgStackClear();
			}
			break;
		case ERJ_PASSWRONG:
			{
				gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_10);
			}
			break;
		case ERJ_FULL:
			{
				gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_11);
			}
			break;
		case ERJ_PLAYING:
			{
				gPopUp::GetIF()->SetPopUp(ECLK_OK, EPOP_OK, STR_12);
			}
			break;
	}
}

void gRoomCore::OnLButtonDown_Room()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();

	int		i;

	if(m_bCharSel)
	{
		if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
		{
			chat->OnLbuttonDown(mouse->m_nPosX, mouse->m_nPosY);
		}

		for(i = 0; i < BSM_SELECT; i++)
		{
			if(m_SelBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				if(m_SelBtn[i].m_eBtnMode == EBM_CLICK)
					return;

				m_nSelChar = i;
			}
		}
		if(m_nSelChar != -1)
		{
			if(m_SelBtn[BSM_SELECT].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			{
				PK_CHARSELECT_ASK		ask;

				ask.classtype = (CLASSTYPE)m_nSelChar;
				strcpy(ask.szID, gPlayerContainer::GetIF()->m_MyPlayer.szID);

				gServer::GetIF()->Send(PL_CHARSELECT_ASK, sizeof ask, &ask);
			}
		}
	}
	else
	{
		if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
		{
			chat->OnLbuttonDown(mouse->m_nPosX, mouse->m_nPosY);
			return;
		}

		ROOM	*room = &gPlayerContainer::GetIF()->m_MyRoom;
		
		// 뒤에 캐릭터정보 배경
		for(i = 0; i < room->nMaxPlayer; i++)
		{
			RECT		rcDest;

			SetRect(&rcDest,
				WAIT_POS_CHARBACK_X,
				WAIT_POS_CHARBACK_Y,
				WAIT_POS_CHARBACK_X + WAIT_SIZE_CHARBACK_W,
				WAIT_POS_CHARBACK_Y + WAIT_SIZE_CHARBACK_H );
			OffsetRect(&rcDest,
				(i % 4) * (WAIT_TERM_CHARBACK_X + WAIT_SIZE_CHARBACK_W), (i / 4) * (WAIT_TERM_CHARBACK_Y + WAIT_SIZE_CHARBACK_H));

			if(strlen(room->szRoomMaxPlayer[i]) > 0)
			{
				if(gUtil::PointInRect(mouse->m_nPosX, mouse->m_nPosY, rcDest))
				{
					if( strcmp(gPlayerContainer::GetIF()->m_MyPlayer.szID, room->szRoomMaxPlayer[i]) == 0 
						&& m_nSelUser == i)
					{
						m_bCharSel = true;
						m_nSelChar = gPlayerContainer::GetIF()->m_MyPlayer.classtype;
					}
					m_nSelUser = i;
					break;
				}
			}
		}
	}
}

void gRoomCore::OnMouseMove_Room()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();


	int		i;

	if(m_bCharSel)
	{
		if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
		{
			chat->OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);
		}

		for(i = 0; i < BSM_SELECT; i++)
		{
			if(m_SelBtn[i].m_eBtnMode != EBM_CLICK)
			{
				if(!m_SelBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
					m_SelBtn[i].m_eBtnMode = EBM_NONE;
				else
					m_SelBtn[i].m_eBtnMode = EBM_HOVER;
			}
		}
		for(i = BSM_SELECT; i < BSM_END; i++)
		{
			if(!m_SelBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_SelBtn[i].m_eBtnMode = EBM_NONE;
			else
				m_SelBtn[i].m_eBtnMode = EBM_HOVER;
		}
	}
	else
	{
		if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
		{
			chat->OnMouseMove(mouse->m_nPosX, mouse->m_nPosY);
			return;
		}

		for(i = 0; i < BWM_END; i++)
		{
			if(!m_WaitBtn[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
				m_WaitBtn[i].m_eBtnMode = EBM_NONE;
			else
				m_WaitBtn[i].m_eBtnMode = EBM_HOVER;

		}
	}
}

void gRoomCore::OnLButtonUp_Room()
{
	gMouse		*mouse	= gMouse::GetIF();
	gChat		*chat	= gChat::GetIF();

	if(chat->PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		chat->OnLbuttonUp(mouse->m_nPosX, mouse->m_nPosY);
		return;
	}
}

void gRoomCore::pk_roomrefresh_rep(PK_ROOMREFRESH_REP *rep)
{
	gPlayerContainer::GetIF()->SetMyRoom(&rep->room);
	gPlayerContainer::GetIF()->SetPlayerList(rep->playerlist);
}

void gRoomCore::OnRButtonDown_Room()
{
	gMouse		*mouse = gMouse::GetIF();

	m_bCharSel = false;
	m_nSelChar = -1;
}