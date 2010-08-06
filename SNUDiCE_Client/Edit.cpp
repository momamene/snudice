#include "Edit.h"
#include "Util.h"
#include "MainWin.h"

static EDITTYPE s_eType;

static UINT_PTR CALLBACK EditHook( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );

gEdit::gEdit()
{
	m_hEdit = NULL;
}

gEdit::~gEdit()
{

}
	
	
bool gEdit::isFocus()
{
	return GetFocus() == m_hEdit;
}

void gEdit::SetFocusOn()
{
	SetFocus(m_hEdit);
}

bool gEdit::SetUp(RECT rcPos, char *img, int strsize, EDITTYPE type)
{
	if(!m_ImgEdit.Load(img))
		return false;

	DWORD	dwFlag = EDIT_STYLE;

	if(type == EDIT_PASSWORD)
		dwFlag |= ES_PASSWORD;

	m_hEdit = CreateWindow("edit", NULL, dwFlag,
			1000, 0,
			m_ImgEdit.m_nWidth, m_ImgEdit.m_nHeight / 2,
			gMainWin::GetIF()->m_hWnd, (HMENU)NULL, gMainWin::GetIF()->m_hInst, NULL);

//	SetWindowLong(m_hEdit, GWL_WNDPROC, (LONG)EditHook);

	s_eType		= type;
	m_rcPos		= rcPos;

	m_szEdit	= new char[strsize];
	m_nStrSize	= strsize;

	return true;
}

void gEdit::Release()
{
	m_ImgEdit.Release();

	if(m_szEdit)
		delete [] m_szEdit;

}

void gEdit::Draw()
{
	RECT	rcSour;

	SetRect(&rcSour,
			0, 0, m_ImgEdit.m_nWidth, m_ImgEdit.m_nHeight / 2);

	if(!isFocus())
		OffsetRect(&rcSour, 0, m_ImgEdit.m_nHeight / 2);

	m_ImgEdit.Draw(m_rcPos, rcSour, false);
	GetWindowText(m_hEdit, m_szEdit, m_nStrSize);

	gUtil::BeginText();
		gUtil::Text(m_rcPos.left + 5, m_rcPos.top + 4, m_szEdit);
	gUtil::EndText();
}

bool gEdit::isPointInEdit(int nX, int nY)
{
	return gUtil::PointInRect(nX, nY, m_rcPos);
}

UINT_PTR CALLBACK EditHook( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch(message)
	{

	}

	return FALSE;
}