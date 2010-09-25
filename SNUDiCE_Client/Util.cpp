#include <stdio.h>
#include "utilconst.h"
#include "Util.h"
#include "MainWin.h"

HDC		s_hdc;
HFONT	s_font;
HFONT	s_ofont;
int		s_nSize			= UTIL_DEFAULT_FONTSIZE;
char	s_szFont[32]	= UTIL_DEFAULT_FONT;

void gUtil::BeginText()
{
	gMainWin::GetIF()->m_lpDDBack->GetDC(&s_hdc);
	SetBkMode(s_hdc, TRANSPARENT);
	s_font = CreateFont(s_nSize, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0,
			VARIABLE_PITCH | FF_ROMAN, s_szFont);
	s_ofont = (HFONT)SelectObject(s_hdc, s_font);
}

void gUtil::Text(int x, int y, char *str, int lineterm)
{
	if(s_hdc == NULL) return;

	int		len = strlen(str);
	char	szBuf[256];
	int		k = 0;
	int		line = 0;

	for(int i = 0; i < len; i++)
	{
		if(str[i] != '_')
		{
			szBuf[k++] = str[i];
		}
		else
		{
			szBuf[k] = NULL;
			TextOut(s_hdc, x, y + lineterm * line, szBuf, strlen(szBuf));
			k = 0;
			line++;
		}
	}
	szBuf[k] = '\0';
	TextOut(s_hdc, x, y + lineterm * line, szBuf, strlen(szBuf));
}

void gUtil::EndText()
{
	SelectObject(s_hdc, s_ofont);
	DeleteObject(s_font);
	gMainWin::GetIF()->m_lpDDBack->ReleaseDC(s_hdc);
}

void gUtil::SetFont(char *font)
{
	strcpy(s_szFont, font);
}

void gUtil::SetSize(int size)
{
	s_nSize = size;
}

void gUtil::SetColor()
{

}

bool gUtil::PointInRect(int x, int y, RECT rc)
{
	if(rc.left <= x && x <= rc.right
		&& rc.top <= y && y <= rc.bottom)
		return true;
	else
		return false;
}

void gUtil::DebugMsg(char *msg)
{
	OutputDebugString(msg);
}

void gUtil::SetDefaultFont()
{
	s_nSize = UTIL_DEFAULT_FONTSIZE;
	strcpy(s_szFont, UTIL_DEFAULT_FONT);
}