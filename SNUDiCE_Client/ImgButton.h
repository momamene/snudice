//------------------------------------------------------------------------------------
//	gImgButton Class
//
//	2010. 08. 04	CoderK
//
//	이미지 버튼을 다루는 클래스
//	Image처럼 Release 잊지 말 것
//------------------------------------------------------------------------------------
#pragma once
#include "Image.h"

enum eBUTTONMODE
{
	EBM_NONE,
	EBM_HOVER,
	EBM_CLICK,
};

class gImgButton  
{
public:
	gImgButton();
	virtual ~gImgButton();

public:
	gImage		m_Img;						// 버튼에 입력받는 이미지는, 가로 또는 세로로 3개의 이미지의 연속
											// 순서대로 일반, 마우스 올려져 있을 때, 클릭했을 때
	RECT		m_rcPos;					// 버튼이 위치한 영역
	bool		m_bVertical;				// 가로로 3개냐 세로로 3개냐
	eBUTTONMODE	m_eBtnMode;
	bool		m_bShow;

	bool		SetUp(char *szImgName, bool vertical, RECT rcPos);
	bool		Restore();

	void		Draw();

	bool		PointInButton(int nX, int nY);

	void		Release();
};

