//------------------------------------------------------------------------------------
//	gScrollbar Class
//
//	2010. 09. 04	CoderK
//
//	scroll bar
//	�ϴ��� �������θ� ����
//------------------------------------------------------------------------------------
#pragma once
#include "Image.h"
#include "ImgButton.h"

enum SCROLLBTN
{
	SCR_UP,
	SCR_DOWN,
	SCR_BAR,
	SCR_END,
};

#define SCROLL_SIZE_BACK_W		10
#define SCROLL_SIZE_BAR_W		16
#define SCROLL_SIZE_BAR_H		17
#define SCROLL_SIZE_UPDOWN_W	8
#define SCROLL_SIZE_UPDOWN_H	7

#define SCROLL_FILE_BAR			".\\Data\\Interface\\scroll_btnbar.img"
#define SCROLL_FILE_UP			".\\Data\\Interface\\scroll_btnup.img"
#define SCROLL_FILE_DOWN		".\\Data\\Interface\\scroll_btndown.img"

class gScrollbar
{
public:
	gScrollbar(void);
	~gScrollbar(void);

public:
	gImage			m_ImgBack;		// ��ũ�ѹ� �ڿ� �̹���
	gImgButton		m_ImgBtn[SCR_END];

	RECT			m_rcPos;		
	RECT			m_rcPosScroll;	// ��ũ�ѹ� ����(��,�Ʒ� ��ư ����)
//	int				m_nCursor;		// �ٰ� ��� �ֳ�.
	
	bool			m_bActive;		// Ȱ��ȭ�Ǿ��ֳ�

private:
	int				m_nMouseTemp;

public:
	bool			SetUp(int x, int y, int height, char *szImg, bool up = true);	// up == true  ��ũ�ѹٰ� ������ ����
	void			Draw();
	void			Release();

	SCROLLBTN		whatIsClicked();
	void			ChangeCursor(int cur, int size);

	void			OnLbuttonDown(int x, int y);
	void			OnLbuttonUp(int x, int y);
	void			OnMouseMove(int x, int y);

};
