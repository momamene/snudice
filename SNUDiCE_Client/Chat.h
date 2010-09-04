//------------------------------------------------------------------------------------
//	gChat Class
//
//	2010. 08. 15	CoderK
//
//	채팅창 for BattleNet
//------------------------------------------------------------------------------------
#pragma once
#include "MainWin.h"
#include "networkconst.h"
#include "Image.h"
#include "ImgButton.h"
#include "Edit.h"
#include "Util.h"
#include "Scrollbar.h"

#define MSGSTACKSIZE		100

#define CHAT_FILE_BACK		".\\Data\\Interface\\chat_back.img"
#define CHAT_SIZE_W			480
#define CHAT_SIZE_H			120
#define CHAT_POS_X			0
#define CHAT_POS_Y			(WNDSIZEH - CHAT_SIZE_H)
#define SHOW_MAXMSG			4		// 채팅창에 보여주는 메시지 갯수

#define CHAT_SIZE_MSGW		330
#define CHAT_SIZE_MSGH		20
#define CHAT_POS_MSGX		(CHAT_POS_X + 20)
#define CHAT_POS_MSGY		(WNDSIZEH - 27)

#define CHAT_INTERVALY		17		// 채팅메시지 y축 간격
#define CHAT_MSG_X			(CHAT_POS_X + 30)		// 채팅창. 내가 메시지 치는 부분 말고

#define CHAT_FILE_SCROLL	".\\Data\\Interface\\scroll_chat.img"
#define CHAT_SCROLL_X		(CHAT_POS_X + 10)
#define CHAT_SCROLL_Y		(CHAT_POS_Y + 10)
#define CHAT_SCROLL_HEIGHT	80

#define CHAT_SCROLL_PER_BTN	4		


class gChat
{
public:
	static gChat	*GetIF();

	gChat(void);
	virtual ~gChat(void);

public:
	RECT		m_rcPos;
	gImage		m_ImgBack;
	gEdit		m_Edit;
	bool		m_bShow;
	gScrollbar	m_scroll;

	// message stack
	int			m_nStart;
	int			m_nCur;			// circular stack.   end
	int			m_nShowCur;
	int			m_nSize;
	char		m_szID[MSGSTACKSIZE][IDLENGTH];
	char		m_szMsg[MSGSTACKSIZE][MSGLENGTH];

public:
	bool		SetUp();
	void		Release();
	void		Draw();
	void		AddStr(char* szID, char* szMsg);
	void		MsgClear();					// 메시지 입력 창 클리어
	void		SendMsg();
	bool		PointInUI(int x, int y);
	
	void		MainLoop();

	void		OnLbuttonDown(int x, int y);
	void		OnLbuttonUp(int x, int y);
	void		OnMouseMove(int x, int y);

	void		pk_message_rep(PK_MESSAGE_REP* rep);
private:
	void		DrawMsg();
};
