//------------------------------------------------------------------------------------
//	gImgButton Class
//
//	2010. 08. 04	CoderK
//
//	�̹��� ��ư�� �ٷ�� Ŭ����
//	Imageó�� Release ���� �� ��
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
	gImage		m_Img;						// ��ư�� �Է¹޴� �̹�����, ���� �Ǵ� ���η� 3���� �̹����� ����
											// ������� �Ϲ�, ���콺 �÷��� ���� ��, Ŭ������ ��
	RECT		m_rcPos;					// ��ư�� ��ġ�� ����
	bool		m_bVertical;				// ���η� 3���� ���η� 3����
	eBUTTONMODE	m_eBtnMode;
	bool		m_bShow;

	bool		SetUp(char *szImgName, bool vertical, RECT rcPos);
	bool		Restore();

	void		Draw();

	bool		PointInButton(int nX, int nY);

	void		Release();
};

