//------------------------------------------------------------------------------------
//	gPopUp Class
//
//	2010. 08. 02	CoderK
//
//	popup창 띄우자
//------------------------------------------------------------------------------------
#pragma once
#include "Image.h"
#include "ImgButton.h"
#include "Core.h"

enum BTNCLK				// popup창에서 어떤 버튼이 클릭되었나
{
	ECLK_OK,			// 확인
	ECLK_CANCEL,		// 취소			버튼 생성시 확인, 취소 2개
	ECLK_END,
};

enum ePOPTYPE			// 팝업창 타입
{
	EPOP_RECONNECT = 0,
	EPOP_DISCONNECT = 1,
	EPOP_EXIT = 1,
	EPOP_ROOMBACK,	//방나가고돌아오기수정
	EPOP_OK,			// 걍 OK 눌러서 메시지 확인하는 팝업
};


class gPopUp : Core
{
public:
	gPopUp();
	virtual ~gPopUp();

	static gPopUp	*GetIF();
public:
	BTNCLK		m_eBtnClk;
	ePOPTYPE	m_ePop;

	gImage*		m_Img;					// popup에 띄울 이미지

	gImage		m_ImgPopup;				// popup창 배경 이미지
	gImgButton	m_ImgBtn[ECLK_END];

	bool		m_bPopup;				// popup됬냐

	char		m_szLine1[128];			// popup창에 띄울 메시지 - 1번째 줄
	int			m_nLine1X;
	char		m_szLine2[128];			// popup창에 띄울 메시지 - 2번째 줄
	int			m_nLine2X;

	bool		m_bReturn;				// popup창 후에 버튼 클릭(키보드로도 가능)했냐

public:

	bool		SetPopUp(BTNCLK btn, ePOPTYPE pop, char *szLine1 = NULL, char *szLine2 = NULL);		// popup창 띄우기 전에 정보 셋팅
	bool		SetImgPopUp(BTNCLK btn, ePOPTYPE pop, gImage *img, char *szLine1 = NULL, char *szLine2 = NULL);
	bool		isPopUp();

	void		DoEnter();
	void		DoEsc();

	// overriding
	bool		SetUp();
	void		MainLoop();
	void		Draw();
	void		Release();

	bool		Restore();
	
	void		OnLButtonDown();
	void		OnLButtonUp();
	void		OnMouseMove();
	void		OnRButtonDown();
	//	end overriding

private:
	void		TextPosX();						// comment의 x 좌표 계산(popup창 중앙에 정렬하기 위함)
	void		Ok();
	void		Cancel();
};
