//------------------------------------------------------------------------------------
//	gChat Class
//
//	2010. 08. 15	CoderK
//
//	채팅창
//------------------------------------------------------------------------------------
#pragma once
#include "MainWin.h"
#include "networkconst.h"
#include "Image.h"
#include "ImgButton.h"
#include "Edit.h"
#include "Util.h"

#define MSGSTACKSIZE		100

#define CHAT_FILE_BACK		".\\Data\\Interface\\chat_back.img"
#define CHAT_SIZE_W			400
#define CHAT_SIZE_H			120
#define CHAT_POS_X			(WNDSIZEW - CHAT_SIZE_W)
#define CHAT_POS_Y			(WNDSIZEH - CHAT_SIZE_H)
#define SHOW_MAXMSG			5		// 채팅창에 보여주는 메시지 갯수

#define CHAT_FILE_MSG		".\\Data\\Interface\\chatmsg.img"			// msg edit
#define CHAT_SIZE_MSGW		380
#define CHAT_SIZE_MSGH		20
#define CHAT_POS_MSGX		(CHAT_POS_X + (CHAT_SIZE_W - CHAT_SIZE_MSGW) / 2)
#define CHAT_POS_MSGY		(WNDSIZEH - 25)


class gChat
{
public:
	static gChat	*GetIF();

	gChat(void);
	virtual ~gChat(void);

public:
	gImage		m_ImgBack;
	gEdit		m_Edit;
	bool		m_bShow;

	// message stack
	int			m_nCur;
	char		m_szID[MSGSTACKSIZE][IDLENGTH];
	char		m_szMsg[MSGSTACKSIZE][MSGLENGTH];

public:
	bool		SetUp();
	void		Release();
	void		Draw();
	void		AddStr(char* szID, char* szMsg);
	void		MsgClear();					// 메시지 입력 창 클리어
	void		SendMsg();
	void		pk_message_rep(PK_MESSAGE_REP* rep);

private:
	void		DrawMsg();
};
