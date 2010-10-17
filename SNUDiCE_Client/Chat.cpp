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
				// �� ���� ������ �ѹ��� �ϸ�, �� ó���� ����� �� �������� �𸣰��� ;

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
			// �� ���� ������ �ѹ��� �ϸ�, �� ó���� ����� �� �������� �𸣰��� ;

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
						//m_nCur�� m_nShowCur ������ ������ a�� �ӽ÷� �����Ͽ� ������ CHAT_SCROLL_PER_BTN(4) �̻� �ִ��� Ȯ��
						//������ Ȯ���Ǿ� ���� ��� 4 �߰�
						if(a >= CHAT_SCROLL_PER_BTN) {
							m_nShowCur += CHAT_SCROLL_PER_BTN;
							m_nShowCur %= MSGSTACKSIZE;
						}
						//�ƴҰ�� ShowCur�� Cur�� ����.
						else m_nShowCur=m_nCur;

						a=(m_nShowCur-m_nStart);
						if(a<=0) a+=MSGSTACKSIZE;
					}
					tick = GetTickCount();
					//ShowCur�� Cur�� �������� ��� ������ ������ ���̹Ƿ� (a,a)�� �༭ ��ũ�ѹٸ� ������ �������� ǥ���Ѵ�.
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
						//ShowCur�� Start������ ������ ���, Start�� msg�� ���� ���� �ƴϴ�!
						//���� Cur�� ��찡 �ణ �ٸ���. �������� if������ �ε��ϰ� ���� ���� �� �� ���� ���̴�.
						if(a > CHAT_SCROLL_PER_BTN) {
							m_nShowCur -= CHAT_SCROLL_PER_BTN;
							if(m_nShowCur<0) m_nShowCur+=MSGSTACKSIZE;
						}
					}
					tick = GetTickCount();

					a=(m_nShowCur-m_nStart);
					if(a<0) a+=MSGSTACKSIZE;

					//ǥ���ؾ� �� ���ڿ��� ������ CHAT_SCROLL_PER_BTN���� ������,
					//���� ��� ShowCur�� Start+2�� ��ġ�� ���� ���.

					//��ĭ�� ǥ���ϰ� �Ǵµ�, �װ� �Ⱦ �ƿ� Start+4���� ShowCur�� �۾����� ���� ���Ҵ�.
					if(a<CHAT_SCROLL_PER_BTN) {
						m_nShowCur = (m_nStart+CHAT_SCROLL_PER_BTN)%MSGSTACKSIZE;
						a=CHAT_SCROLL_PER_BTN;
					}
					//a�� CHAT_SCROLL_PER_BTN�� ��� ������ �ö� ���̶�� �����Ѵ�.
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