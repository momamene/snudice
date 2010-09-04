//------------------------------------------------------------------------------------
//	gScrollbar Class
//
//	2010. 09. 04	CoderK
//
//	scroll bar
//	일단은 수직으로만 제공
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
	gImage			m_ImgBack;		// 스크롤바 뒤에 이미지
	gImgButton		m_ImgBtn[SCR_END];

	RECT			m_rcPos;		
	RECT			m_rcPosScroll;	// 스크롤바 영역(위,아래 버튼 제외)
//	int				m_nCursor;		// 바가 어디 있냐.
	
	bool			m_bActive;		// 활성화되어있냐

private:
	int				m_nMouseTemp;

public:
	bool			SetUp(int x, int y, int height, char *szImg, bool up = true);	// up == true  스크롤바가 위에서 시작
	void			Draw();
	void			Release();

	SCROLLBTN		whatIsClicked();
	void			ChangeCursor(int cur, int size);

	void			OnLbuttonDown(int x, int y);
	void			OnLbuttonUp(int x, int y);
	void			OnMouseMove(int x, int y);

};
