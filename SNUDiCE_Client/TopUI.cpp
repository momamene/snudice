#include "TopUI.h"
#include "Util.h"
#include "MainWin.h"
#include "PlayerContainer.h"
#include "RoomCore.h"
#include "Server.h"
#include "Chat.h"

static gTopUI s_TopUI;

gTopUI *gTopUI::GetIF()
{
	return &s_TopUI;
}

gTopUI::gTopUI(void)
{
}

gTopUI::~gTopUI(void)
{
}


bool gTopUI::SetUp()
{
	if(!m_ImgBack.Load(TOP_FILE_BACK))
		return false;

	SetRect(&m_rcPos,
			TOP_POS_BACK_X,
			TOP_POS_BACK_Y,
			TOP_POS_BACK_X + TOP_POS_BACK_W,
			TOP_POS_BACK_Y + TOP_POS_BACK_H);

	RECT	rcDest, rcSour, rcTemp;
	SetRect(&rcSour, 0, 0, TOP_BTN_SIZEW, TOP_BTN_SIZEH);
	SetRect(&rcDest,
		TOP_BTN_POS_X,
		TOP_BTN_POS_Y,
		TOP_BTN_POS_X + TOP_BTN_SIZEW,
		TOP_BTN_POS_Y + TOP_BTN_SIZEH );

	rcTemp = rcDest;
	OffsetRect(&rcTemp, - (TOP_END - TOP_BACK) * TOP_BTN_TERM_X, 0);
	if(!m_Btn[TOP_BACK].SetUp(TOP_BTN_BACK_FILE, false, rcDest))
		return false;
	
	return true;
}

void gTopUI::Draw()
{
	m_ImgBack.Draw(m_rcPos.left, m_rcPos.top);

	int		i;

	for(i = 0; i < TOP_END; i++)
		m_Btn[i].Draw();
}

void gTopUI::Release()
{
	m_ImgBack.Release();

	int		i;
	
	for(i = 0; i < TOP_END; i++)
		m_Btn[i].Release();
}

bool gTopUI::Restore()
{
	if(!m_ImgBack.Restore())
		return false;

	int		i;

	for(i = 0; i < TOP_END; i++)
		if(!m_Btn[i].Restore())
			return false;

	return true;
}

void gTopUI::OnLButtonDown(int x, int y)
{
	if(m_Btn[TOP_BACK].PointInButton(x, y))
	{
		OnLButtonDown_Back();
		return;
	}
}

void gTopUI::OnLButtonDown_Back()
{
	gPlayerContainer	*pc = gPlayerContainer::GetIF();
	gChat				*chat = gChat::GetIF();

	switch(gMainWin::GetIF()->m_eCoreMode)
	{
	case ECM_BATTLENET:
		{
			PK_GOLOGIN_ASK		ask;

			strcpy(ask.szID, pc->m_MyPlayer.szID);
			gServer::GetIF()->Send(PL_GOLOGIN_ASK, sizeof(ask), &ask);

			chat->MsgStackClear();
			gMainWin::GetIF()->m_eCoreMode = ECM_LOGIN;
		}
		break;
	case ECM_ROOMMAKE:
		{
			gRoomCore::GetIF()->Cancel_Make();
		}
		break;
	case ECM_ROOMJOIN:
		{
			gRoomCore::GetIF()->m_bEnteringPass = false;
			gRoomCore::GetIF()->m_nSelected = -1;
			gRoomCore::GetIF()->m_EditPassEnter.Clear();
			SetFocus(gMainWin::GetIF()->m_hWnd);
		}
	case ECM_ROOM:
		{
			PK_CHANNELCHANGE_ASK	ask;

			ask.nChannel = pc->m_MyChannel.nChannelNum;
			strcpy(ask.szID, pc->m_MyPlayer.szID);

			gServer::GetIF()->Send(PL_CHANNELCHANGE_ASK, sizeof(ask), &ask);
			chat->MsgStackClear();
			gMainWin::GetIF()->m_eCoreMode = ECM_BATTLENET;
		}
		break;
	}
	return;
}

void gTopUI::OnMouseMove(int x, int y)
{
	int		i;

	for(i = 0; i < TOP_END; i++)
	{
		if(m_Btn[i].PointInButton(x, y))
			m_Btn[i].m_eBtnMode = EBM_HOVER;
		else
			m_Btn[i].m_eBtnMode = EBM_NONE;
	}
}

bool gTopUI::PointInUI(int x, int y)
{
	if(gUtil::PointInRect(x, y, m_rcPos))
		return true;

	return false;
}