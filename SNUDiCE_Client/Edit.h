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
#include <ime.h>					// ime32.lib

enum EDITTYPE
{
	EDIT_NUMBER,					// ����
	EDIT_PASSWORD,					// ���
	EDIT_STRING,					// ���ڿ�(���� ��)
	EDIT_AVAILSPACESTRING,			// ���ڿ�(��������)
};

#define	EDITID_START			100

class gEdit
{
public:
	gEdit();
	virtual ~gEdit();

public:
	EDITTYPE	m_eType;			// -> static���� cpp���� ����. �ֳĸ� �ſ��� �����ؾߵǹǷ�

	int			m_nEditID;
	HWND		m_hEdit;
	RECT		m_rcPos;
	gImage		m_ImgEdit;
	char*		m_szEdit;
	int			m_nStrSize;			// ����Ʈ�ڽ� maximum length

public:
	bool		isKorean();			// �Է¸�尡 �ѱ��̳� �����
	void		Draw();
	bool		isFocus();
	void		SetFocusOn();
	bool		SetUp(RECT rcPos, char *img, int strsize, EDITTYPE type);
	void		Release();
	bool		isPointInEdit(int nX, int nY);
	int			GetszLength();
};