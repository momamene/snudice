//------------------------------------------------------------------------------------
//	networkconst.h
//
//	2010. 08. 04	CoderK	
//
//	network ���� define �� �������� �� ��Ŷ ����ü
//	ws2_32.lib �߰��ؾ� ��
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>

#define WM_SOCKET				WM_USER + 1

#define	WINSOCK_VERSION_2_2		MAKEWORD(2, 2)
#define SERVER_IP				"211.169.219.71"
#define SERVER_PORT				9000
#define BUFFERSIZE				1024

#define PK_HEADER_SIZE			4

//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	��� ��������
//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
enum ePROTOCOL
{
	PL_LOGIN_ASK,
	PL_LOGIN_REP,
	PL_MESSAGE_ASK,
	PL_MESSAGE_REP,

	PL_CHANNELREFRESH_REP,

	PL_CHANNELCHANGE_ASK,
};


enum eCOREMODE
{
	ECM_NONLOGIN,			// login ���ѻ���
	ECM_LOGIN,
	ECM_BATTLENET,			// LOGIN �ϸ� �� ���
	
	
	ECM_TITLE,				// Ÿ��Ʋ
	ECM_PSEL,				// �÷��̾� ����
	ECM_CSEL,				// ĳ���� ����
	ECM_SUBMIT,				// ������û
	ECM_GAME,				// ����
};

struct PK_DEFAULT
{
	WORD	dwSize;
	WORD	dwProtocol;
	char	strPacket[BUFFERSIZE];
};

#define MSGLENGTH				128			// ä���Ҷ� �޽��� ��������
#define IDLENGTH				16			// ID ���� ����
#define CHANNELUSERMAX			10			// �� ä�ο� �ִ� ��� �� �ִ�
#define CHANNELMAX				6			// ä�� ����

struct USER
{
	char		szID[IDLENGTH];
	char		szPW[IDLENGTH];
};

struct PLAYER
{
	char		szID[IDLENGTH];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
	SOCKET		sock;
};

struct PK_LOGIN_ASK
{
	char		szID[IDLENGTH];
	char		szPW[IDLENGTH];
};

enum LOGIN_ERROR
{
	ELE_NOID,			// id ����
	ELE_PWERROR,		// pw ����
	ELE_OVERCONNECT,	// �ߺ�����
	ELE_USEROVER,		// ���� ���� �ο� �ʰ�
	ELE_SUCCESS,		// login ����
};

struct CHANNEL
{
	int				nChannelNum;
	int				nUserNum;
	char			szUserInCh[CHANNELUSERMAX][IDLENGTH];		// ä�ο� �ִ� ���� ID ��
};

struct PK_LOGIN_REP
{
	PLAYER			player;
	LOGIN_ERROR		error;
	CHANNEL			channel;
};

typedef struct
{
	char	szID[IDLENGTH];
	char	szMsg[MSGLENGTH];

} PK_MESSAGE_ASK, PK_MESSAGE_REP;

struct PK_CHANNELCHANGE_ASK
{
	char			szID[IDLENGTH];
	int				nChannel;
};

typedef struct
{
	CHANNEL			channel;

} PK_CHANNELREFRESH_REP;