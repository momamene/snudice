//------------------------------------------------------------------------------------
//	gUIGame Class
//
//	2010. 09. 24	CoderK
//
//	���Ӹ���� �������̽�
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Image.h"
#include "ImgButton.h"
#include "ScrollBar.h"
#include "Timer.h"

enum UIIMAGE
{
	UIIMG_MAININFO,
	UIIMG_BAROUTLINE,
	UIIMG_BARGUAGE,

	UIIMG_SUBINFO,			// ������, ������Ȳ ��ư
	UIIMG_SUBWND,			// �������

	UIIMG_MINIMAP,			// ���ϴ�
	UIIMG_MINIMAPCURSOR,

	UIIMG_MAPTOOLTIP,

	UIIMG_FACEOUTLINE,		// ������ ���, Ÿ�� ������ ��

	UIIMG_COUPLEOUTLINE,	// Ŀ�� ����
	UIIMG_LOVE,				// ��Ʈ ������

	UIIMG_TURNOUTLINE,
	UIIMG_CROWN,

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

	UIBTN_END,
};

enum UITYPE
{
	UIT_MAININFO,
	UIT_SUBINFO,		// ������, ������Ȳ ��ư
	UIT_SUBWND,			// �������
	UIT_MINIMAPBACK,
	UIT_MINIMAP,		// �̴ϸ�.. back����
	UIT_ITEM,
	UIT_MENU,
	UIT_DICE,
	UIT_END,
};

// �޴�â ������ ����� �ֳ�.
enum UIMODE
{
	UIM_NONE,
	UIM_ITEM,					// ������ī��
	UIM_TARGETSELECT,			// ������ �� ��� ����
	UIM_TARGETSELECT_MULTI,		// ��� ������ ��, �������� ��
	UIM_PLACESELECT,			// �̵� ��� ����
	UIM_SUGANG,					// �������
	UIM_ITEMUSEINFO,			// ������ ��� ����
	UIM_INFOCHANGE,				// ��ġ ���� ����
	UIM_BECOUPLE,				// Ŀ�õǾ��ٴ� ����
};

// ������ ���, ĳ���� �� ��ư
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
	// �������
	int			m_nSubSel;					// ������� ���� �����ֳ�

	// ������ - target, place select ��, ���õ� ������ ���� ���ܵα�
	bool		m_bItemUsed;
	int			m_nItemID;
	TARGETBTN	m_target[ROOMMAXPLAYER];
	int			m_nTargetNum;				// Ÿ�� ����
	bool		m_bTargetByMove;			// Move ��忡�� Ÿ��, ī�� ��� �������� �̿��� �� ����, infochange ��
	char		m_szTarget[IDLENGTH];
	TARGETBTN	m_itemuser;					// itemuse_rep, ���� ���� ��� ��, ������ ����� ��.
	int			m_nCardIdx;					// itemuse_rep, ī���ε���
	CHANGEINFO	m_info[ROOMMAXPLAYER];		// infochange_rep

	bool		m_bPopInfo;					// ��ǳ�� ����

	gTimer		m_timer;					// ī�� ��� ����, info

	bool		m_bCouple;					// true�� Ŀ�õǴ°�, false�� ���� ��


private:
	RECT		m_rcBarDest, m_rcBarSour;
	int			m_rankIdx[ROOMMAXPLAYER];	// ��ŷ�ε���

public:
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

	void		SetTargetButton(int nPos, int charmax);		// ������ ���, ĳ���� �� ��, charmax �� ��ġ�� ĳ���� ��
	void		DrawTargetButton();

	void		SetTargetButton_UseInfo();					// ������ ��� ���� ������ ��, TARGET_ALL, TARGET_ALLEXCEPTME ����.
	void		SetTargetButton_InfoChange();				// infochange_rep

	void		Draw_InfoChange();
};
