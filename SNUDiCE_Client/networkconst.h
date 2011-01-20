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
#define SERVER_IP				"211.169.219.93"		// �¿�
//#define SERVER_IP				"211.169.219.86"		// ��Ź
//#define SERVER_IP				"211.169.219.87"		// â��
#define SERVER_PORT				9000
#define BUFFERSIZE				2048

#define PK_HEADER_SIZE			4

#define SNUDICE_VERSION			"0.9002"

//#define DEF_SERVER

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

	PL_SUBMITCOUNT_ASK,			// ������û���, �����ð� ������ �ð� �����ٰ� �˷��ִ� �뵵

	PL_MAINGAMESTART_REP,

	PL_MOVESTART_ASK,
	PL_MOVESTART_REP,
	PL_MOVEEND_ASK,

	PL_BUSMOVECHOOSE_REP,
	PL_BUSMOVESELECT_ASK,
	PL_BUSMOVESTART_REP,
	PL_BUSMOVEEND_ASK,

	PL_GAMEPLAYERINFO_REP,

	PL_GAMEEND_REP,

	PL_NEXTTURN_REP,

	PL_ITEMUSE_ASK,
	PL_ITEMUSE_REP,

	PL_ITEMUSESTART_ASK,

	PL_WARPSTART_REP,			// ���� �ϳ�.
	PL_WARPEND_ASK,

	PL_WARPLISTSTART_REP,		// ���� ������ ������ų��
	PL_WARPLISTEND_ASK,

	PL_INFOCHANGE_REP,			// ������ ��� -> ĳ���� ���Ȱ��� ��ġ ��ȭ ǥ��
	PL_INFOCHANGEEND_ASK,

	PL_ROOMBACK_ASK,			// ���ӳ� -> ������
	PL_ROOMBACK_REP,			//

	PL_EXIT_REP,				// ������ �������� ó��

	PL_GOLOGIN_ASK,

	//	PL_WHISPER_ASK,				// Whisper
	PL_FRIENDADD_ASK,			// ģ�� �߰�
	PL_FRIENDDELETE_ASK,		// ģ�� ����
	PL_FRIENDWHISPER_ASK,		// ģ������ �Ӹ�
	PL_FRIENDLIST_ASK,			// ģ�� ��� ����

	PL_ASKCOUPLE_REP,			// Ŀ�õɰ��� ���´�.
	PL_ANSCOUPLE_ASK,			// �亯

	PL_BECOUPLE_REP,			// Ŀ�� �Ǿ��ٴ� ���� ���
	PL_BECOUPLEEND_ASK,			// ���� ��

	PL_MOVESTARTCOUPLE_REP,		// �ֻ��� ���� �̵�. Ŀ�ø��
	PL_MOVEENDCOUPLE_ASK,

	PL_BUSMOVESTARTCOUPLE_REP,	// ����Ÿ�� �̵�. Ŀ�ø��
	PL_BUSMOVEENDCOUPLE_ASK,
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
	char		szPW[33];
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
	int			nCoreFlag;		//�̳� ���ϴ� ���̳�
	SOCKET		sock;

	// ���Ӱ��� ����
	CLASSTYPE	classtype;
	bool		bReady;
};

struct PK_LOGIN_ASK
{
	char		szID[IDLENGTH];
	char		szPW[33];
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
#define ROOMMAXPLAYER		6
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


//�泪�����ƿ������

struct PK_ROOMBACK_ASK
{
	char		szID[IDLENGTH];	
};

struct PK_ROOMBACK_REP
{
	ROOM		room;
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

#define	SUBMITTICK		20000

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

struct PK_SUBMITCOUNT_ASK
{
	char			szID[IDLENGTH];
};

#define MAXSUBJECT				6	// �ѻ���� �������մ� �����
#define MAXITEMNUM				4	// �ѻ���� �������� �� �ִ� ������ ��

struct GAMEPLAYER
{
	char		szID[IDLENGTH];
	// ��������
	CLASSTYPE	ctype;

	int			nLang;
	int			nMath;
	int			nArt;
	int			nStamina, nMaxStamina;
	int			nDice4, nDice6;

	float		fGrade[MAXSUBJECT];
	float		fAvGrade;
	BYTE		bySubIdx[MAXSUBJECT];
	int			nRank;

	int			nItem[MAXITEMNUM];		// ������ -1

	int			nLove;					// ������.			Ŀ�� �ƴϸ� - 1
	char		szCouple[IDLENGTH];		// Ŀ�� ���̵�		Ŀ�� �ƴϸ� memset 0

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

typedef struct
{
	int			nDist;
	BYTE		Dice4_1;
	BYTE		Dice4_2;
	BYTE		Dice6_1;
	BYTE		Dice6_2;
}
PK_MOVESTART_REP, PK_MOVESTARTCOUPLE_REP;

typedef struct
{
	char		szID[IDLENGTH];
	int			nDestPos;			// ���� ��ǥ
}
PK_MOVEEND_ASK,  PK_MOVEENDCOUPLE_ASK;

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

typedef struct			// ��� �ֵ����� �̵����Ѷ� ��� �ѷ���
{
	int			nDist;
}
PK_BUSMOVESTART_REP, PK_BUSMOVESTARTCOUPLE_REP;

typedef struct			// ��� �ֵ����� �޾Ƽ� �� ������, nextturn
{
	char		szID[IDLENGTH];
	int			nDestPos;
}
PK_BUSMOVEEND_ASK, PK_BUSMOVEENDCOUPLE_ASK;

struct PK_GAMEPLAYERINFO_REP
{
	GAMEPLAYER	list[ROOMMAXPLAYER];
};

struct CHANGEINFO
{
	char		szID[IDLENGTH];
	int			nLang;
	int			nMath;
	int			nArt;
	int			nStamina;
	int			nGrade;				// ���뵵. ������ �ƴ�
	int			nLove;
};

struct PK_GAMEEND_REP
{
	char		szID[IDLENGTH];		// �̱��
};

#ifdef DEF_SERVER
#define ITEMNUM		29 +1			// 
#else
#define ITEMNUM		29
#endif

enum ITEMTARGET
{
	TARGET_ME,				// ��
	TARGET_ALL,				// �� ���� ��� ����
	TARGET_ALLEXCEPTME,		// �� ���� ��� ����
	TARGET_OTHER,			// �ٸ� ���� �ϳ�
	TARGET_MEOTHER,			// ���� ���
	TARGET_OTHERSEX,		// �̼�
	TARGET_MYCOUPLE,		// �� ����
	TARGET_OTHERCOUPLE,		// �ٸ� Ŀ��
	TARGET_ALLCOUPLE,		// ��� Ŀ��
	TARGET_ALLSINGLE,		// ��� �̱�

};

enum ITEMTYPE
{
	ITEM_STAT,
	ITEM_STAMINA,
	ITEM_MOVESELECT,		// ���� ������ ĭ���� �̵�
	ITEM_MOVEPLACE,			// ��ũ��Ʈ�� ������ ��ҷ� �̵�
	ITEM_NOCLASS,			// �ް�. ����� ���� ������ ��ȿȭ
	ITEM_TOGETHERCLASS,		// ��밡 �� ������ ��ĥ ��, ���� ���뵵 +
	ITEM_LOVE,				// ������
	ITEM_DASH,				// �������� �뽬
	ITEM_POWERDASH,			// �����Ұ� �뽬
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
	int			nMulti;			// ITEM_STAT		*
	int			nExistTurn;		// ���� ��
	int			nPos;			// ITEM_MOVEPLACE
	int			nLove;			// ������
};

struct PK_ITEMUSE_ASK
{
	char		szID[IDLENGTH];			// �����
	char		szTarget[IDLENGTH];		// ���
	int			nItemID;
	int			nStartPos;				// move�� ��
	int			nDestPos;				// move�� ��
};

struct PK_ITEMUSE_REP
{
	char		szUser[IDLENGTH];		// �����
	char		szTarget[IDLENGTH];		// ���
	int			nItemID;
};

struct PK_ITEMUSESTART_ASK
{
	char		szID[IDLENGTH];
};


struct PK_WARPSTART_REP
{
	char		szID[IDLENGTH];  // �����̴� ��.
	int			nDest;    // ���� ��ǥ
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
	char		szID[IDLENGTH];
	int			nDestPos[ROOMMAXPLAYER];		// �ش���� ���� ���� -1�� ä���� ����
};

struct PK_INFOCHANGE_REP
{
	CHANGEINFO	info[ROOMMAXPLAYER];			// �ش� ���� �� memset(info , 0)
};

struct PK_INFOCHANGEEND_ASK
{
	char		szID[IDLENGTH];
};

struct PK_GOLOGIN_ASK
{
	char		szID[IDLENGTH];
};

struct PK_EXIT_REP
{
	char		szID[IDLENGTH];
	int			flag;							// ���� ��� �� //���������� �״� �־�� �� ������ ����.
};

/*//WHISPER ����
struct PK_WHISPER_ASK
{
char		szToID[IDLENGTH];
char		szFromID[IDLENGTH];
char		szComment[MSGLENGTH];
};
*/
typedef struct
{
	char		szMyID[IDLENGTH];
	char		szFriendID[IDLENGTH];
} PK_FRIENDADD_ASK, PK_FRIENDDELETE_ASK;

struct PK_FRIENDWHISPER_ASK
{
	char		szMyID[IDLENGTH];
	char		szComment[MSGLENGTH];
};

struct PK_FRIENDLIST_ASK
{
	char		szMyID[IDLENGTH];
};


// couple
struct PK_ASKCOUPLE_REP
{
	char		szCouple[IDLENGTH];				// ���� Ŀ�õ� ���� id
};

struct PK_ANSCOUPLE_ASK
{
	bool		bYes;
};

struct PK_BECOUPLE_REP
{
	char		szMale[IDLENGTH];
	char		szFeMale[IDLENGTH];
	bool		bCouple;						// true�� Ŀ��, false�� ����
};

struct PK_BECOUPLEEND_ASK
{
	char		szID[IDLENGTH];
};

#define COUPLE_DEBUFFTURN      5
#define COUPLE_MINUS_STAT      -5