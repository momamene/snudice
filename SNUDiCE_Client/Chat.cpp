#include "Chat.h"
#include "PlayerContainer.h"
#include "Server.h"
#include "Util.h"
#include "Mouse.h"

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
	MsgStackClear();

	SetRect(&m_rcPos,
			CHAT_POS_X,
			CHAT_POS_Y,
			CHAT_POS_X + CHAT_SIZE_W,
			CHAT_POS_Y + CHAT_SIZE_H);

	if(!m_ImgBack.Load(CHAT_FILE_BACK))
		return false;

	if(!m_scroll.SetUp(CHAT_SCROLL_X, CHAT_SCROLL_Y, CHAT_SCROLL_HEIGHT, CHAT_FILE_SCROLL, false))
		return false;

	RECT	rcPos;

	SetRect(&rcPos,
			CHAT_POS_MSGX,
			CHAT_POS_MSGY,
			CHAT_POS_MSGX + CHAT_SIZE_MSGW,
			CHAT_POS_MSGY + CHAT_SIZE_MSGH);

	if(!m_Edit.SetUp(rcPos, NULL, MSGLENGTH, EDIT_AVAILSPACESTRING))
		return false;

	return true;

}

void gChat::Release()
{
	m_Edit.Release();
	m_ImgBack.Release();
	m_scroll.Release();
}

void gChat::Draw()
{
	if(!m_bShow)
		return;

	m_ImgBack.Draw(CHAT_POS_X, CHAT_POS_Y);
	m_Edit.Draw();
	DrawMsg();

	if(m_scroll.m_bActive)
		m_scroll.Draw();

}

void gChat::DrawMsg()
{
	int		index = m_nShowCur;
	int		i;
	bool    overend=0;

	if(!m_bShow)
		return;

	if(m_nSize == 0)
		return;

	char	szTemp[256];

	if(m_nSize < SHOW_MAXMSG)
	{
		gUtil::BeginText();
		for(i = SHOW_MAXMSG - m_nSize; i < SHOW_MAXMSG; i++)
		{
			if(m_szID[index][0] != 0 && !overend)
			{
				//wsprintf(szTemp, "[%s] %s", m_szID[index], m_szMsg[index--]);
				// 왜 위의 넘으로 한번에 하면, 맨 처음에 제대로 안 나오는지 모르겠음 ;

				wsprintf(szTemp, "[%s] ", m_szID[index]);
				strcat(szTemp, m_szMsg[index--]);
				gUtil::Text(CHAT_MSG_X, CHAT_POS_Y + 70 - CHAT_INTERVALY * (i - (SHOW_MAXMSG - m_nSize)), szTemp);
			}
			else
				index--;

			if(index < 0)
				index += MSGSTACKSIZE;

			if(index==m_nCur) overend=1;
		}
		gUtil::EndText();
		return;
	}
	
	gUtil::BeginText();
	for(i = 0; i < SHOW_MAXMSG; i++)
	{
		if(m_szID[index][0] != 0 && !overend)
		{
			//wsprintf(szTemp, "[%s] %s", m_szID[index], m_szMsg[index--]);
			// 왜 위의 넘으로 한번에 하면, 맨 처음에 제대로 안 나오는지 모르겠음 ;

			wsprintf(szTemp, "[%s] ", m_szID[index]);
			strcat(szTemp, m_szMsg[index--]);
			gUtil::Text(CHAT_MSG_X, CHAT_POS_Y + 70 - CHAT_INTERVALY * i, szTemp);
		}
		else
			index--;

		if(index < 0)
			index += MSGSTACKSIZE;

		if(index==m_nCur) overend=1;

	}
	gUtil::EndText();
}

void gChat::AddStr(char* szID, char* szMsg)
{
	m_nCur++;

	if(m_nCur >= MSGSTACKSIZE)
		m_nCur -= MSGSTACKSIZE;

	m_nShowCur = m_nCur;
	strcpy(m_szID[m_nCur], szID);
	strcpy(m_szMsg[m_nCur], szMsg);

	m_nSize++;

	if(m_nSize >= MSGSTACKSIZE)
	{
		m_nSize		= MSGSTACKSIZE;
		m_nStart++;

		if(m_nStart >= MSGSTACKSIZE)
			m_nStart -= MSGSTACKSIZE;
	}
	int a=(m_nShowCur-m_nStart);
	a=(m_nShowCur<m_nStart) ? a+MSGSTACKSIZE : a; 

	m_scroll.ChangeCursor(a, m_nShowCur==m_nCur ? a:m_nSize);
}

void gChat::MsgClear()
{
	m_Edit.Clear();
}

void gChat::SendMsg()
{
	if(strlen(m_Edit.m_szEdit) == 0)
		return;

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

void gChat::OnLbuttonDown(int x, int y)
{
//	if(gUtil::PointInRect(x, y, m_scroll.m_rcPos))
		m_scroll.OnLbuttonDown(x, y);
}

void gChat::OnLbuttonUp(int x, int y)
{
//	if(gUtil::PointInRect(x, y, m_scroll.m_rcPos))
		m_scroll.OnLbuttonUp(x, y);
}

void gChat::OnMouseMove(int x, int y)
{
//	if(gUtil::PointInRect(x, y, m_scroll.m_rcPos))
		m_scroll.OnMouseMove(x, y);
}

bool gChat::PointInUI(int x, int y)
{
	if(gUtil::PointInRect(x, y, m_rcPos))
		return true;

	return false;
}

void gChat::MainLoop()
{
	int a;
	gMouse	*mouse = gMouse::GetIF();
	static int tick = GetTickCount();

	if(PointInUI(mouse->m_nPosX, mouse->m_nPosY))
	{
		switch(m_scroll.whatIsClicked())
		{
			case SCR_DOWN:
				if(GetTickCount() - tick > 500)
				{
					if(CHAT_SCROLL_PER_BTN > m_nSize)
						return;
					else
					{
						a=(m_nCur-m_nShowCur);
						if(a<0) a+=MSGSTACKSIZE;
						//m_nCur과 m_nShowCur 사이의 공간을 a에 임시로 저장하여 공간이 CHAT_SCROLL_PER_BTN(4) 이상 있는지 확인
						//공간이 확보되어 있을 경우 4 추가
						if(a >= CHAT_SCROLL_PER_BTN) {
							m_nShowCur += CHAT_SCROLL_PER_BTN;
							m_nShowCur %= MSGSTACKSIZE;
						}
						//아닐경우 ShowCur는 Cur로 간다.
						else m_nShowCur=m_nCur;

						a=(m_nShowCur-m_nStart);
						if(a<=0) a+=MSGSTACKSIZE;
					}
					tick = GetTickCount();
					//ShowCur과 Cur이 같아지는 경우 끝까지 내려간 것이므로 (a,a)를 줘서 스크롤바를 끝까지 내려가게 표시한다.
					m_scroll.ChangeCursor(a, m_nShowCur==m_nCur ? a:m_nSize);
				}
				break;
			case SCR_UP:
				if(GetTickCount() - tick > 500)
				{
					if(CHAT_SCROLL_PER_BTN > m_nSize)
						return;
					else
					{
						a=(m_nShowCur-m_nStart);
						if(a<0) a+=MSGSTACKSIZE;
						//ShowCur과 Start사이의 공간을 계산, Start는 msg가 들어가는 곳이 아니다!
						//따라서 Cur의 경우가 약간 다르다. 차이점은 if문에서 부등하고 빠진 것을 볼 수 있을 것이다.
						if(a > CHAT_SCROLL_PER_BTN) {
							m_nShowCur -= CHAT_SCROLL_PER_BTN;
							if(m_nShowCur<0) m_nShowCur+=MSGSTACKSIZE;
						}
					}
					tick = GetTickCount();

					a=(m_nShowCur-m_nStart);
					if(a<0) a+=MSGSTACKSIZE;

					//표시해야 할 문자열의 개수가 CHAT_SCROLL_PER_BTN보다 작으면,
					//예를 들면 ShowCur가 Start+2의 위치에 있을 경우.

					//빈칸을 표시하게 되는데, 그게 싫어서 아예 Start+4보다 ShowCur가 작아지는 것을 막았다.
					if(a<CHAT_SCROLL_PER_BTN) {
						m_nShowCur = (m_nStart+CHAT_SCROLL_PER_BTN)%MSGSTACKSIZE;
						a=CHAT_SCROLL_PER_BTN;
					}
					//a가 CHAT_SCROLL_PER_BTN일 경우 끝까지 올라간 것이라고 간주한다.
					m_scroll.ChangeCursor(a>CHAT_SCROLL_PER_BTN ? a:0 , m_nSize);
				}
				break;
			case SCR_BAR:
				{
					int		nScrollSize = m_scroll.m_rcPosScroll.bottom - m_scroll.m_rcPosScroll.top;
					int		nCur = m_scroll.m_ImgBtn[SCR_BAR].m_rcPos.top + SCROLL_SIZE_BAR_H - m_scroll.m_rcPosScroll.top;

					if(nCur == nScrollSize)
					{
						m_nShowCur = m_nCur;
						return;
					}

					float	fTemp = (float)nCur / nScrollSize;

					m_nShowCur = (m_nStart + (int)(m_nSize * fTemp)-1)%MSGSTACKSIZE;
					
					if((int)(m_nSize * fTemp) <= CHAT_SCROLL_PER_BTN+1) {
						m_nShowCur=(m_nStart+CHAT_SCROLL_PER_BTN)%MSGSTACKSIZE;
						return;
					}
				}
				break;
		}
	}
	if(m_scroll.m_ImgBtn[SCR_UP].m_eBtnMode != EBM_CLICK
		&& m_scroll.m_ImgBtn[SCR_DOWN].m_eBtnMode != EBM_CLICK)
		tick = 501;
}

void gChat::MsgStackClear()
{
	m_nCur		= 0;//SHOW_MAXMSG - 1;
	m_nSize		= 0;
	m_nShowCur	= m_nCur;
	m_nStart	= m_nCur;

	memset(m_szID, 0, MSGSTACKSIZE * IDLENGTH );
	memset(m_szMsg, 0, MSGSTACKSIZE * MSGLENGTH );
}

bool gChat::Restore()
{
	if(!m_ImgBack.Restore())
		return false;
	if(!m_Edit.Restore())
		return false;
	if(!m_scroll.Restore())
		return false;

	return true;
}