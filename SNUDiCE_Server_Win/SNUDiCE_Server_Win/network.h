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
#define BUFFERSIZE				2048

#define PK_HEADER_SIZE			4

#define SNUDICE_VERSION			"0.5002"

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
	PL_CHANNELCHANGE_REP,

	PL_ROOMMAKER_ASK,
	PL_ROOMMAKER_REP,

	PL_ROOMLIST_ASK,
	PL_ROOMLIST_REP,

	PL_ROOMJOIN_ASK,
	PL_ROOMJOIN_REP,

	PL_ROOMREFRESH_REP,

	PL_CHARSELECT_ASK,
	PL_GAMEREADY_ASK,
	PL_GAMESTART_ASK,
	PL_GAMESTART_REP,

	PL_SUBMIT_ASK,
	PL_SUBMIT_REP,

	PL_SUBMITREADY_ASK,
	PL_SUBMITREADY_REP,

	PL_MAINGAMESTART_REP,

	PL_MOVESTART_ASK,
	PL_MOVESTART_REP,
	PL_MOVEEND_ASK,

	PL_BUSMOVECHOOSE_REP,
	PL_BUSMOVESELECT_ASK,
	PL_BUSMOVESTART_REP,
	PL_BUSMOVEEND_ASK,

	PL_GAMEPLAYERINFO_REP,

	PL_POPINFO_REP,			// Ŭ���̾�Ʈ�� ��ǳ��ó�� ���� ����� ��

	PL_GAMEEND_REP,

	PL_NEXTTURN_REP,

	PL_ITEMUSE_ASK,
	PL_ITEMUSE_REP,

	PL_WARPSTART_ASK,		// �Ѹ� ����.
	PL_WARPSTART_REP,
	PL_WARPEND_ASK,

	PL_WARPLISTSTART_REP,	// ���� ������ ������ų��
	PL_WARPLISTEND_ASK,

};

enum eCOREMODE
{
	ECM_NONLOGIN,			// login ���ѻ���

	ECM_LOGIN,

	ECM_BATTLENET,			// LOGIN �ϸ� �� ���

	ECM_ROOMMAKE,
	ECM_ROOMJOIN,
	ECM_ROOM,

	ECM_SUBMIT,				// ������û

	ECM_GAME,				// ���ΰ���
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

enum CLASSTYPE
{
	CLASS_NONE = -1,		// ���þȵȰ�
	// ���
	CLASS_LITERAL,			// �ι�
	CLASS_SOCIAL,			// ��ȸ
	CLASS_MANAGE,			// �濵
	CLASS_LAW,				// ��
	CLASS_LIFE,				// ��Ȱ����
	CLASS_TEACH,			// �����
	CLASS_FREE,				// ��������

	// ����
	CLASS_ENGINE,			// ��
	CLASS_NATURE,			// �ڿ�
	CLASS_DOCTOR,			// �ǻ�
	CLASS_ANIMAL,			// ���ǻ�
	CLASS_DRUG,				// ��
	CLASS_NURSE,			// ��ȣ
	CLASS_FARM,				// ��

	// ����
	CLASS_MUSIC,			// ��
	CLASS_ART,				// ��

	CLASS_END,

};

#define CHARNAMELENGTH		16
#define CHARCOLLEGENAME		16
#define MAXCHARNUM			16		// ĳ���� ����

struct CHARINFO
{
	char		szName[CHARNAMELENGTH];
	char		szCollege[CHARCOLLEGENAME];
	bool		bMale;
	// �н���
	int			nLang;
	int			nMath;
	int			nArt;
	// ü��
	int			nStamina;
	// �̵���
	int			nDice4;
	int			nDice6;
};

struct PLAYER
{
	char		szID[IDLENGTH];
	eCOREMODE	coreWhere;
	int			nCoreFlag;
	SOCKET		sock;

	// ���Ӱ��� ����
	CLASSTYPE	classtype;
	bool		bReady;
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


typedef struct
{
	CHANNEL			channel;

} PK_CHANNELREFRESH_REP;

enum CH_CHANGE_ERROR
{
	ECE_SUCCESS,
	ECE_CHANNELISOVER,
};

struct PK_CHANNELCHANGE_ASK
{
	char			szID[IDLENGTH];
	int				nChannel;
};

struct PK_CHANNELCHANGE_REP
{
	CH_CHANGE_ERROR	error;
	CHANNEL			channel;

};

#define MAXROOMFORPAGE		8								// �� �������� ǥ�õ� �� �ִ� �� ����
#define MAXROOM				40								// ���� �� �ִ� �� ����
#define MAXROOMNAME			32
#define MAXROOMPASS			16
#define ROOMMAXPLAYER		8
#define MAXPAGE				(MAXROOM / MAXROOMFORPAGE)

struct ROOM
{
	bool	isGaming;										// ������
	bool	isPass;
	char	szRoomName[MAXROOMNAME];
	char	szRoomPass[MAXROOMPASS];
	int		nMaxPlayer;
	int		nNowPlayer;
	int		nMakerIndex;									// ������index
	char	szRoomMaxPlayer[ROOMMAXPLAYER][IDLENGTH];		// �⺻������ 0��°�� ����
};

struct PK_ROOMMAKER_ASK
{
	char		szID[IDLENGTH];
	ROOM		room;
};

enum ERROR_ROOMMAKE
{
	ERM_USINGNAME,		// ���̸� �ߺ�
	ERM_SUCCESS,
};

struct PK_ROOMMAKER_REP
{
	ERROR_ROOMMAKE	result;
	ROOM		room;
	PLAYER		playerlist[ROOMMAXPLAYER];
};

struct PK_ROOMLIST_ASK
{
	char		szID[IDLENGTH];
	int			nPage;
};

struct PK_ROOMLIST_REP
{
	int			nPage;
	ROOM		roomlist[MAXROOMFORPAGE];
};

struct PK_ROOMJOIN_ASK
{
	char		szID[IDLENGTH];
	int			nPage;					// ������
	int			nIdx;					// ���������� ���°��
	char		szPass[MAXROOMPASS];
};

enum ERROR_ROOMJOIN
{
	ERJ_SUCCESS,
	ERJ_PASSWRONG,
	ERJ_FULL,
	ERJ_PLAYING,
	ERJ_NOROOM,
};

struct PK_ROOMJOIN_REP
{
	ERROR_ROOMJOIN		result;
	ROOM				joinroom;
	PLAYER				playerlist[ROOMMAXPLAYER];
};

struct PK_ROOMREFRESH_REP
{
	ROOM				room;
	PLAYER				playerlist[ROOMMAXPLAYER];
};

struct PK_CHARSELECT_ASK
{
	char				szID[IDLENGTH];
	CLASSTYPE			classtype;
};

typedef struct
{
	char				szID[IDLENGTH];
	bool				bReady;

} PK_GAMEREADY_ASK, PK_GAMESTART_ASK;

enum ERRORGAMESTART
{
	EGS_NOREADY,			// ������ �غ� �ȵ�..(������ ĳ���� ���� x)
	EGS_NOREADYUSER,		// �������� �غ� �ȵ�.
	EGS_ONEUSER,			// ������ ���� �Ѹ��̶� ���� �Ұ�.(�Ѹ����� ���� ���� �Ұ�)
	EGS_SUCCESS,
};

#define AVAILSEAT		255
#define CLASSNUM		18
#define CLASSSEAT		3
#define NOSEAT			99

struct PK_GAMESTART_REP
{
	ERRORGAMESTART		result;
	BYTE				subject[CLASSNUM][CLASSSEAT];
};

// ���� ��û
struct PK_SUBMIT_ASK
{
	char			szID[IDLENGTH];
	BYTE			nSubjectIdx;			// ��û�� ���� index
	bool			bSubmit;				// true�� ��û, false�� ���
};

struct PK_SUBMIT_REP
{
	BYTE			subject[CLASSNUM][CLASSSEAT];
};

struct PK_SUBMITREADY_ASK
{
	char			szID[IDLENGTH];
};

enum ESUBMITERROR
{
	ESUB_LESSCLASS,					// ���������� 6�� �Ʒ���.
	ESUB_SUCCESS,
};

struct PK_SUBMITREADY_REP
{
	ESUBMITERROR	result;
};

#define MAXSUBJECT				6	// �ѻ���� �������մ� �����
#define MAXITEMNUM				4	// �ѻ���� �������� �� �ִ� ������ ��

struct GAMEPLAYER
{
	char		szID[IDLENGTH];
	// ��������
	CLASSTYPE	ctype;

	BYTE		nLang;
	BYTE		nMath;
	BYTE		nArt;
	BYTE		nStamina, nMaxStamina;
	BYTE		nDice4, nDice6;

	float		fGrade[MAXSUBJECT];
	float		fAvGrade;
	BYTE		bySubIdx[MAXSUBJECT];
	int			nRank;

	int			nItem[MAXITEMNUM];		// ������ -1

	WORD		nPos;
};

struct PK_MAINGAMESTART_REP
{
	GAMEPLAYER	list[ROOMMAXPLAYER];
	int			nTurn;						// ���� ��
};

// ���� ����

struct PK_MOVESTART_ASK
{
	char		szID[IDLENGTH];
	int			nCurPos;			// ��� ��ǥ
};

struct PK_MOVESTART_REP
{
	int			nDist;
	BYTE		Dice4_1;
	BYTE		Dice4_2;
	BYTE		Dice6_1;
	BYTE		Dice6_2;
};

struct PK_MOVEEND_ASK
{
	char		szID[IDLENGTH];
	int			nDestPos;			// ���� ��ǥ
};

struct PK_NEXTTURN_REP
{
	int			nNowTurn;			// ���� ��
	int			nNextTurn;			// ���� ��
};

struct PK_BUSMOVECHOOSE_REP			// �̵��� ĭ�� ������. �̵��� �� ���� ��� ������ �����ִ� ��Ŷ(�ش� �÷��̾)
{
	int			nNowTurn;
};

struct PK_BUSMOVESELECT_ASK
{
	char		szID[IDLENGTH];
	int			nPos;
};

struct PK_BUSMOVESTART_REP			// ��� �ֵ����� �̵����Ѷ� ��� �ѷ���
{
	int			nDist;
};

struct PK_BUSMOVEEND_ASK			// ��� �ֵ����� �޾Ƽ� �� ������, nextturn
{
	char		szID[IDLENGTH];
	int			nDestPos;
};

struct PK_GAMEPLAYERINFO_REP
{
	GAMEPLAYER	list[ROOMMAXPLAYER];
};

struct PK_POPINFO_REP
{
	char		szID[IDLENGTH];
	int			nLang;
	int			nMath;
	int			nArt;
	int			nStamina;
	int			nGrade;				// ���뵵. ������ �ƴ�
};

struct PK_GAMEEND_REP
{
	char		szID[IDLENGTH];		// �̱��
};

#define ITEMNUM		20

enum ITEMTARGET
{
	TARGET_ME,				// ��
	TARGET_ALL,				// �� ���� ��� ����
	TARGET_ALLEXCEPTME,		// �� ���� ��� ����
	TARGET_OTHER,			// �ٸ� ���� �ϳ�
	TARGET_MEOTHER,			// ���� ���
};

enum ITEMTYPE
{
	ITEM_STAT,
	ITEM_STAMINA,
	ITEM_MOVESELECT,		// ���� ������ ĭ���� �̵�
	ITEM_MOVEPLACE,			// ��ũ��Ʈ�� ������ ��ҷ� �̵�
	ITEM_NOCLASS,			// �ް�. ����� ���� ������ ��ȿȭ
	ITEM_TOGETHERCLASS,		// ��밡 �� ������ ��ĥ ��, ���� ���뵵 +
};

struct ITEMCARD
{
	ITEMTYPE	type;
	ITEMTARGET	target;
	int			nLang;			// ITEM_STAT
	int			nMath;			//
	int			nArt;			//
	int			nMove;			// �� ���� �Ⱦ��ž�
	int			nStamina;		// ITEM_STAMINA
	int			nMulti;			// ITEM_STAT
	int			nExistTurn;		// ���� ��
	int			nPos;			// ITEM_MOVEPLACE
};

struct PK_ITEMUSE_ASK
{
	char  szID[IDLENGTH];   // �����
	char  szTarget[IDLENGTH];  // ���
	int   nItemID;
	int   nPos;     // move�� �� �߰�
};

enum ITEMREPRESULT
{
	ITEMUSE_SUCCESS,
	ITEMUSE_MOVESELECT,
	ITEMUSE_ERROR,
};

struct PK_ITEMUSE_REP
{
	ITEMREPRESULT	result;
};


struct PK_WARPSTART_ASK
{
	char		szID[IDLENGTH];
	int			nCurPos;			// ��� ��ǥ
};

struct PK_WARPSTART_REP
{
	int			nDist;
};

struct PK_WARPEND_ASK
{
	char		szID[IDLENGTH];
	int			nDestPos;			// ���� ��ǥ
};

struct PK_WARPLISTSTART_REP
{
	int			nDestPos[ROOMMAXPLAYER];		// �ش���� ���� ���� -1�� ä����.
};

struct PK_WARPLISTEND_ASK
{
	int			nDestPos[ROOMMAXPLAYER];		// �ش���� ���� ���� -1�� ä���� ����
};

