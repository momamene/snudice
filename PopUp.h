//------------------------------------------------------------------------------------
//	gPlayer Class
//
//	2010. 08. 02	CoderK
//
//	popupâ �����
//------------------------------------------------------------------------------------
#pragma once
#include "Image.h"
#include "ImgButton.h"
#include "Core.h"

enum BTNCLK				// popupâ���� � ��ư�� Ŭ���Ǿ���
{
	ECLK_OK,			// Ȯ��
	ECLK_CANCEL,		// ���			��ư ������ Ȯ��, ��� 2��
	ECLK_END,
};


class gPopUp : Core
{
public:
	gPopUp();
	virtual ~gPopUp();

	static gPopUp	*GetIF();
public:
	BTNCLK		m_eBtnClk;

	gImage*		m_Img;					// popup�� ��� �̹���

	gImage		m_ImgPopup;				// popupâ ��� �̹���
	gImgButton	m_ImgBtn[ECLK_END];

	bool		m_bPopup;				// popup���

	char		m_szLine1[128];			// popupâ�� ��� �޽��� - 1��° ��
	int			m_nLine1X;
	char		m_szLine2[128];			// popupâ�� ��� �޽��� - 2��° ��
	int			m_nLine2X;

	bool		m_bReturn;				// popupâ �Ŀ� ��ư Ŭ��(Ű����ε� ����)�߳�

public:

	bool		SetPopUp(BTNCLK btn, char *szLine1 = NULL, char *szLine2 = NULL);		// popupâ ���� ���� ���� ����
	bool		SetImgPopUp(BTNCLK btn, gImage *img, char *szLine1 = NULL, char *szLine2 = NULL);
	bool		isPopUp();

	// overriding
	bool		SetUp();
	bool		MainLoop();
	void		Draw();
	void		Release();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	//	end overriding

private:
	void		TextPosX();						// comment�� x ��ǥ ���(popupâ �߾ӿ� �����ϱ� ����)
	void		Ok();
	void		Cancel();
};
