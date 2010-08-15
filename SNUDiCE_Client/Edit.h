//------------------------------------------------------------------------------------
//	gEdit Class
//
//	2010. 08. 05	CoderK
//
//	Window용 Edit Control을 Direct에 맞게
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include "utilconst.h"
#include "Image.h"
#include <ime.h>					// ime32.lib

enum EDITTYPE
{
	EDIT_NUMBER,					// 숫자
	EDIT_PASSWORD,					// 비번
	EDIT_STRING,					// 문자열(띄어쓰기 노)
	EDIT_AVAILSPACESTRING,			// 문자열(띄어쓰기포함)
};

#define	EDITID_START			100

class gEdit
{
public:
	gEdit();
	virtual ~gEdit();

public:
	EDITTYPE	m_eType;			// -> static으로 cpp에서 관리. 왜냐면 훅에서 접근해야되므로

	int			m_nEditID;
	HWND		m_hEdit;
	RECT		m_rcPos;
	gImage		m_ImgEdit;
	char*		m_szEdit;
	int			m_nStrSize;			// 에디트박스 maximum length

public:
	bool		isKorean();			// 입력모드가 한글이냐 영어냐
	void		Draw();
	bool		isFocus();
	void		SetFocusOn();
	bool		SetUp(RECT rcPos, char *img, int strsize, EDITTYPE type);
	void		Release();
	bool		isPointInEdit(int nX, int nY);
	int			GetszLength();
};