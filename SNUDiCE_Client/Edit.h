//------------------------------------------------------------------------------------
//	gEdit Class
//
//	2010. 08. 05	CoderK
//
//	Window�� Edit Control�� Direct�� �°�
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include "utilconst.h"
#include "Image.h"

enum EDITTYPE
{
	EDIT_NUMBER,					// ����
	EDIT_PASSWORD,					// ���
	EDIT_STRING,					// ���ڿ�(���� ��)
	EDIT_AVAILSPACESTRING,			// ���ڿ�(��������)
};

class gEdit
{
public:
	gEdit();
	virtual ~gEdit();

public:
//	EDITTYPE	m_eType;			// -> static���� cpp���� ����. �ֳĸ� �ſ��� �����ؾߵǹǷ�

	HWND		m_hEdit;
	RECT		m_rcPos;
	gImage		m_ImgEdit;
	int			m_nStrSize;
	char*		m_szEdit;

public:
	void		Draw();
	bool		isFocus();
	void		SetFocusOn();
	bool		SetUp(RECT rcPos, char *img, int strsize, EDITTYPE type);
	void		Release();
	bool		isPointInEdit(int nX, int nY);
};