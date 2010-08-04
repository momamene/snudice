//------------------------------------------------------------------------------------
//	gInterface Class
//
//	2010. 07. 20	CoderK
//
//	게임 모드의 인터페이스 처리
//------------------------------------------------------------------------------------
#pragma once
#include "gCoreIF.h"
#include "gImage.h"
#include "gImgButton.h"
#include "gPlayer.h"

enum eMENU_BTN
{
	EBTN_SUGANG,
	EBTN_ITEMCARD,
	EBTN_SYSTEM,
	EBTN_END
};

enum eMENUMODE
{
	EMM_SUGANG,
	EMM_ITEMCARD,
	EMM_SYSTEM,
	EMM_END
};

enum eTOOLTIPTYPE
{
	ETIP_LANG,			// 언어
	ETIP_MATH,			// 수리
	ETIP_ART,			// 예술
	ETIP_DRINK,			// 녹두
	ETIP_ITEM,			// 카드
	ETIP_FOOD,			// 식당
	ETIP_BUS,			// 버스
	ETIP_MAINGATE,		// 정문
	ETIP_MOUNTAIN,		// 관악산
};

struct TOOLTIP
{
	int				nIndex;				// 수업 인덱스
	char			*szSubject;
	char			*szColleage;
	char			*szBuilding;
	gPlayer			*pPlayer[3];		// 3 == 수강정원
	int				nX;
	int				nY;
	eTOOLTIPTYPE	type;

};

class gInterface : public gCoreIF
{
public:
	static gInterface	*GetIF();

	gInterface();
	virtual ~gInterface();
public:
	gImage		m_ImgMenuback;
	gImgButton	m_BtnMenu[EBTN_END];
	gImage		m_ImgMenu[EMM_END];
	bool		m_bMenu;				// menu 창 열려있냐
	
	//tooltip
	gImage		m_ImgTooltipBack;
	gImage		m_ImgActive;
	TOOLTIP		m_tooltip;
	bool		m_bTooltip;

	eMENUMODE	m_eMenuMode;

	bool		isMenu();
	void		ClearTooltip();

	bool		SetUp();
	void		MainLoop();
	void		Draw();

	void		Release();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
private:
	void		DrawWindow(int mode);
	void		DrawTooltip();
};

