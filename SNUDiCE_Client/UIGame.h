//------------------------------------------------------------------------------------
//	gUIGame Class
//
//	2010. 09. 24	CoderK
//
//	게임모드의 인터페이스
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Image.h"
#include "ImgButton.h"
#include "ScrollBar.h"
#include "Timer.h"

//#define UI_ICON_DRAW

enum UIIMAGE
{
	UIIMG_MAININFO,
	UIIMG_BAROUTLINE,
	UIIMG_BARGUAGE,

	UIIMG_SUBINFO,			// 아이템, 수강현황 버튼
	UIIMG_SUBWND,			// 수강편람

	UIIMG_MINIMAP,			// 우하단
	UIIMG_MINIMAPCURSOR,

	UIIMG_MAPTOOLTIP,

	UIIMG_FACEOUTLINE,		// 아이템 사용, 타겟 선택할 시

	UIIMG_COUPLEOUTLINE,	// 커플 액자
	UIIMG_LOVE,				// 하트 게이지

	UIIMG_TURNOUTLINE,
	UIIMG_CROWN,

	UIIMG_NUMBER,
	UIIMG_ICON,

	UIIMG_USERBOX,

	UIIMG_YOURTURN,
	UIIMG_TIMER,

	UIIMG_RESULT,

	UIIMG_MAPBACK,
	UIIMG_MAPBG,
	UIIMG_MAPPLAYER,
	UIIMG_MAPPLAYEROUT,
	UIIMG_MAPPLAYERBAR,		// 체력바
	UIIMG_MAPLOVE,

	UIIMG_GUAGEBARBACK,		// 이동할때 주사위 게이지 바
	UIIMG_GUAGEBAR,

	UIIMG_GETITEM,

	UIIMG_MENUBACK,

	UIIMG_END,
};

enum UIBTN
{
	UIBTN_ITEMCARD,

	UIBTN_SUBJECT,
	UIBTN_SUBPREV,
	UIBTN_SUBNEXT,

	UIBTN_MENU,

	UIBTN_DICE,

	UIBTN_MAPBTN,

	UIBTN_OPTION,
	UIBTN_OUT,
	UIBTN_EXIT,

	UIBTN_END,
};

enum UITYPE
{
	UIT_MAININFO,
	UIT_SUBINFO,		// 아이템, 수강현황 버튼
	UIT_SUBWND,			// 수강편람
	UIT_MINIMAPBACK,
	UIT_MINIMAP,		// 미니맵.. back말고
	UIT_ITEM,
	UIT_MENU,			// 메뉴 버튼
	UIT_DICE,
	UIT_MAPBTN,
	UIT_MAP,
	UIT_MENUBACK,		// 메뉴 모드
	UIT_OPTION,			// 환경설정
	UIT_END,
};

// 메뉴창 같은거 띄워져 있나.
enum UIMODE
{
	UIM_NONE,
	UIM_ITEM,					// 아이템카드
	UIM_TARGETSELECT,			// 아이템 쓸 대상 선택
	UIM_TARGETSELECT_MULTI,		// 대상 선택한 후, 여러명일 때
	UIM_PLACESELECT,			// 이동 장소 선택
	UIM_SUGANG,					// 수강편람
	UIM_DICEGUAGE,				// 주사위 게이지
	UIM_MENU,					// 메뉴 == 환경설정
	UIM_OPTION,
	UIM_MAP,
};

enum DRAWMODE
{
	DM_NONE,
	DM_ITEMUSEINFO,				// 아이템 사용 정보
	DM_INFOCHANGE,				// 수치 변경 정보
	DM_BECOUPLE,				// 커플되었다는 정보
	DM_RESULT,
};

// 아이템 사용, 캐릭터 얼굴 버튼
struct TARGETBTN
{
	gImage		*img;
	int			idx;
	RECT		rcPos;
};

class gUIGame
{
public:
	static gUIGame *GetIF();

	gUIGame(void);
	~gUIGame(void);

public:
	gImage		m_ImgUI[UIIMG_END];
	gImgButton	m_BtnUI[UIBTN_END];
	RECT		m_rcPos[UIT_END];

	UIMODE		m_uimode;
	DRAWMODE	m_drawmode;
	// 수강편람
	int			m_nSubSel;					// 수강편람 누구 보고있나

	// 아이템 - target, place select 시, 선택된 아이템 정보 남겨두기
	bool		m_bItemUsed;
	int			m_nItemID;
	TARGETBTN	m_target[ROOMMAXPLAYER];
	int			m_nTargetNum;				// 타겟 갯수
	bool		m_bTargetByMove;			// Move 모드에서 타겟, 카드 사용 정보에서 이용자 및 대상들, infochange 얼굴
	char		m_szTarget[IDLENGTH];
	TARGETBTN	m_itemuser;					// itemuse_rep, 에서 정보 띄울 떄, 아이템 사용한 넘.
	int			m_nCardIdx;					// itemuse_rep, 카드인덱스
	CHANGEINFO	m_info[ROOMMAXPLAYER];		// infochange_rep

	bool		m_bPopInfo;					// 말풍선 인포

	gTimer		m_timer;					// 카드 사용 정보, info

	bool		m_bCouple;					// 내가 커플이냐
	bool		m_bBeCouple;				// true면 커플되는거, false면 깨는 거

	// your turn
	bool		m_bShowYourTurn;
	int			m_nYourTurnTimer;

	// time count 5,4,3,2,1
	bool		m_bShowTimeCount;
	bool		m_bDrawedTimeCount;

	// map
	int			m_nCharSelected;

	char		m_szStatusMsg[128];

	// 게임 끝났을 때, 다 0으로 정보가 와서, 담아두기 위한것.
	GAMEPLAYER	m_gpTemp[ROOMMAXPLAYER];
	bool		m_bResetGPListInResult;

	// for diceguage bar
	bool		m_bGuageByMouse;			// 마우스로 주사위 굴리는거냐
private:
	RECT		m_rcBarDest, m_rcBarSour;
	int			m_rankIdx[ROOMMAXPLAYER];	// 랭킹인덱스

	// for diceguage bar
	float		m_fSpeed_DiceGuageBar;
	float		m_fPosX_DiceGuageBar;
	int			m_nTimer_DiceGuageBar;

	bool		m_bSendRoomBack;			// gTimer 에러땜시

	// item 얻었을 때, 말풍선
	bool		m_bDrawGetItem;
	int			m_nTimerGetItem;

private:
	void		DrawMapToolTip();
	void		DrawShowAlways();			// 항상 출력
	void		DrawUIMapMode();			// UIM_MAP

public:
	void		pk_getitem_rep(PK_GETITEM_REP* rep);
	void		pk_itemuse_rep(PK_ITEMUSE_REP* rep);
	void		pk_infochange_rep(PK_INFOCHANGE_REP *rep);
	void		pk_becouple_rep(PK_BECOUPLE_REP *rep);
	void		SetbCouple(bool mode); //added

	bool		IsUIRange(int x, int y);

	void		SetRankList();

	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	bool		Restore();
	
	bool		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();

	void		SetTargetButton(int nPos, int charmax);		// 아이템 사용, 캐릭터 고를 때, charmax 는 겹치는 캐릭터 수
	void		DrawTargetButton();

	void		SetTargetButton_UseInfo();					// 아이템 사용 정보 보여줄 때, TARGET_ALL, TARGET_ALLEXCEPTME 때만.
	void		SetTargetButton_InfoChange();				// infochange_rep

	void		Draw_InfoChange();
	void		Draw_GetItem(int x, int y);

	void		DrawTimerImage(int n);

	void		Clear();

	void		GameEnd();

	void		SetDiceGuageMode();
	void		BeforeSendMoveAsk();		// SendMoveAsk 보내기 전에 셋팅
	void		SendMoveAskByNC();			// 주사위 게이지 모드 중에 클라이언트 비활성 되었을 시 메시지 보냄
};
