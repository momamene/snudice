#include "Edit.h"
#include "Util.h"
#include "MainWin.h"

#define EDIT_STYLE				(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT)

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
	static int	id = EDITID_START;

	if(img)
	{
		if(!m_ImgEdit.Load(img))
			return false;

		m_bImg = true;
	}
	else
		m_bImg = false;

	m_nEditID = id;

	DWORD	dwFlag = EDIT_STYLE;

	if(type == EDIT_PASSWORD)
		dwFlag |= ES_PASSWORD;

	m_hEdit = CreateWindow("edit", NULL, dwFlag,
			-100, -100,
			640, 20,
			gMainWin::GetIF()->m_hWnd, (HMENU)id++, gMainWin::GetIF()->m_hInst, NULL);
	
//	SetWindowLong(m_hEdit, GWL_WNDPROC, (LONG)EditHook);

	m_eType		= type;
	m_rcPos		= rcPos;
	
	m_szEdit	= new char[strsize + 1];
	memset(m_szEdit, 0, sizeof(m_szEdit));
	m_nStrSize	= strsize + 1;

	SendMessage(m_hEdit, EM_LIMITTEXT, (WPARAM)strsize, 0);

	return true;
}

void gEdit::Release()
{
	if(m_bImg)
		m_ImgEdit.Release();

	if(m_szEdit)
		delete [] m_szEdit;
}

void gEdit::Draw()
{
	int		t = (DWORD)GetTickCount();

	if(m_bImg)
	{
		RECT	rcSour;

		SetRect(&rcSour,
				0, 0, m_ImgEdit.m_nWidth, m_ImgEdit.m_nHeight / 2);

		if(!isFocus())
			OffsetRect(&rcSour, 0, m_ImgEdit.m_nHeight / 2);

		m_ImgEdit.Draw(m_rcPos, rcSour, false);
	}

	GetWindowText(m_hEdit, m_szEdit, m_nStrSize);

	char	szTemp[256];
	char	PrintTemp[256]={0,};
	if(m_eType == EDIT_PASSWORD)
	{
		int		i;

		strcpy(szTemp, m_szEdit);
		for(i = 0; i < (int)strlen(m_szEdit); i++)
		{
			m_szEdit[i] = '*';
		}
	}

	int m_CurPoint=(WORD)SendMessage(m_hEdit,EM_GETSEL,0,0);
	if(isFocus())
	{
		strncpy(PrintTemp,m_szEdit,m_CurPoint);
		if( t %1000 <= 500)
			strcat(PrintTemp,"|");
		else
			strcat(PrintTemp," ");

		strcat(PrintTemp,m_szEdit+m_CurPoint);
	}
	else strcpy(PrintTemp,m_szEdit);

	gUtil::BeginText();
		gUtil::Text(m_rcPos.left + 5, m_rcPos.top + 4, PrintTemp);
	gUtil::EndText();

	if(m_eType == EDIT_PASSWORD)
		strcpy(m_szEdit, szTemp);
}

bool gEdit::isPointInEdit(int nX, int nY)
{
	return gUtil::PointInRect(nX, nY, m_rcPos);
}


bool gEdit::isKorean()
{
	HIMC	data;

	data = ImmGetContext(m_hEdit);

	int		Korean;
	Korean = ImmGetOpenStatus(data);
	
	ImmReleaseContext(m_hEdit, data);

	if(Korean)
		return true;
	else
		return false;
}

int	gEdit::GetszLength()
{
	return strlen(m_szEdit);
}

void gEdit::Clear()
{
	strcpy(m_szEdit, "");
	SendMessage(m_hEdit, WM_SETTEXT, (WPARAM)m_szEdit, 0);
}

bool gEdit::Restore()
{
	if(m_bImg)
		if(!m_ImgEdit.Restore())
			return false;

	return true;
}