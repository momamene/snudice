//------------------------------------------------------------------------------------
//	gInterface Class
//
//	2010. 07. 20	CoderK
//
//	���� ����� �������̽� ó��
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
	ETIP_LANG,			// ���
	ETIP_MATH,			// ����
	ETIP_ART,			// ����
	ETIP_DRINK,			// ���
	ETIP_ITEM,			// ī��
	ETIP_FOOD,			// �Ĵ�
	ETIP_BUS,			// ����
	ETIP_MAINGATE,		// ����
	ETIP_MOUNTAIN,		// ���ǻ�
};

struct TOOLTIP
{
	int				nIndex;				// ���� �ε���
	char			*szSubject;
	char			*szColleage;
	char			*szBuilding;
	gPlayer			*pPlayer[3];		// 3 == ��������
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
	bool		m_bMenu;				// menu â �����ֳ�
	
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

