//------------------------------------------------------------------------------------
//	gSubmitCore Class
//
//	2010. 09. 23	CoderK
//
//	수강신청
//------------------------------------------------------------------------------------
#pragma once
#include "networkconst.h"
#include "Image.h"
#include "ImgButton.h"
#include "Core.h"

enum SUBBTN
{
	BSUB_READY,
	BSUB_CHANGE,

	BSUB_END,
};

class gSubmitCore : Core
{
public:
	static gSubmitCore	*GetIF();

	gSubmitCore(void);
	~gSubmitCore(void);

public:
	gImage			m_ImgBack;
	gImage			m_ImgIconPlayer;
	gImage			m_ImgMiniMap;
	gImgButton		m_BtnClass[CLASSNUM];
	int				m_nSelected;				// 마우스 hover된 과목
	gImgButton		m_BtnSub[BSUB_END];
	bool			m_bReady;
	bool			m_bChange;

	BYTE			m_subject[CLASSNUM][CLASSSEAT];

public:
	void			pk_submit_rep(PK_SUBMIT_REP *rep);
	void			pk_submitready_rep(PK_SUBMITREADY_REP *rep);
	void			pk_maingametart_rep(PK_MAINGAMESTART_REP *rep);

	void			SetSubject(BYTE *subj);

	bool			SetUp();
	void			MainLoop();
	void			Draw();
	void			Release();
	
	void			OnLButtonDown();
	void			OnLButtonUp();
	void			OnMouseMove();
	void			OnRButtonDown();
};
