#include "Chat.h"
#include "PlayerContainer.h"
#include "Server.h"

static gChat s_Chat;

gChat *gChat::GetIF()
{
	return &s_Chat;
}

gChat::gChat(void)
{
}

gChat::~gChat(void)
{
}

bool gChat::SetUp()
{
	memset(this, 0, sizeof(gChat));

	if(!m_ImgBack.Load(CHAT_FILE_BACK))
		return false;

	RECT	rcPos;

	SetRect(&rcPos,
			CHAT_POS_MSGX,
			CHAT_POS_MSGY,
			CHAT_POS_MSGX + CHAT_SIZE_MSGW,
			CHAT_POS_MSGY + CHAT_SIZE_MSGH);

	if(!m_Edit.SetUp(rcPos, CHAT_FILE_MSG, MSGLENGTH, EDIT_STRING))
		return false;

	m_nCur	= 4;

	return true;

}

void gChat::Release()
{
	m_Edit.Release();
	m_ImgBack.Release();
}

void gChat::Draw()
{
	if(!m_bShow)
		return;

	m_ImgBack.Draw(CHAT_POS_X, CHAT_POS_Y);
	m_Edit.Draw();
	DrawMsg();
}

void gChat::DrawMsg()
{
	int		index = m_nCur;
	int		i;

	if(!m_bShow)
		return;

	gUtil::BeginText();
	for(i = 0; i < SHOW_MAXMSG; i++)
	{
		gUtil::Text(CHAT_POS_X + 10, CHAT_POS_Y + 80 - 17 * i, m_szID[index]);
		gUtil::Text(CHAT_POS_X + 100, CHAT_POS_Y + 80 - 17 * i, m_szMsg[index--]);
		if(index < 0)
			index += MSGSTACKSIZE;

	}
	gUtil::EndText();
}

void gChat::AddStr(char* szID, char* szMsg)
{
	m_nCur++;

	if(m_nCur >= MSGSTACKSIZE)
		m_nCur -= MSGSTACKSIZE;

	strcpy(m_szID[m_nCur], szID);
	strcpy(m_szMsg[m_nCur], szMsg);
}

void gChat::MsgClear()
{
	strcpy(m_Edit.m_szEdit, "");
	SendMessage(m_Edit.m_hEdit, WM_SETTEXT, (WPARAM)m_Edit.m_szEdit, 0);
}

void gChat::SendMsg()
{
	PK_MESSAGE_ASK		ask;

	PLAYER*		myplayer;

	myplayer = &gPlayerContainer::GetIF()->m_MyPlayer;

	strcpy(ask.szID, myplayer->szID);
	strcpy(ask.szMsg, m_Edit.m_szEdit);

	gServer::GetIF()->Send(PL_MESSAGE_ASK, sizeof(ask), &ask);

	MsgClear();
}

void gChat::pk_message_rep(PK_MESSAGE_REP* rep)
{
	AddStr(rep->szID, rep->szMsg);
}