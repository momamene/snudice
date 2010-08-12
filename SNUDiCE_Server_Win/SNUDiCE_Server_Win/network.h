#pragma once
#include <windows.h>
#pragma comment(lib, "ws2_32.lib") 

#define	WINSOCK_VERSION_2_2		MAKEWORD(2, 2)
#define SERVER_IP				"127.0.0.1"
#define SERVER_PORT				9000
#define BUFFERSIZE				1024

#define PK_HEADER_SIZE		4

#define CHATMSG_LENGTH			64
//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
//	��� ��������
//�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�
enum ePROTOCOL
{
	PL_LOGIN_ASK,
	PL_LOGIN_REP,
	PL_NORMALMSG_ASK,
	PL_NORMALMSG_REP,
};


enum eCOREMODE
{
	ECM_NONLOGIN,			// login ���ѻ���
	ECM_LOGIN,				// ��� �� Ŭ���̾�Ʈ���� �α��� �ϱ� ���� �ʿ��� ���. ��Ʈ��ũ�� �������
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


struct USER
{
	char		szID[16];
	char		szPW[16];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
};

struct PLAYER
{
	char		szID[16];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
	SOCKET		sock;
};

struct PK_LOGIN_ASK
{
	char		szID[16];
	char		szPW[16];
};

enum LOGIN_ERROR
{
	ELE_NOID,			// id ����
	ELE_PWERROR,		// pw ����
	ELE_OVERCONNECT,	// �ߺ�����
	ELE_SUCCESS,		// login ����
};

struct PK_LOGIN_REP
{
	PLAYER			player;
	LOGIN_ERROR		error;
};

typedef struct
{
	char	szID[16];
	char	szMsg[CHATMSG_LENGTH];	

}	PK_NORMALMSG_ASK,	PK_NORMALMSG_REP;
