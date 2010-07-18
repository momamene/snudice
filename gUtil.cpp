#include "gUtil.h"
#include "gMainWin.h"
#include <windows.h>
#include <stdio.h>

HDC		s_hdc;

void gUtil::BeginText()
{
	gMainWin::GetIF()->m_lpDDBack->GetDC(&s_hdc);
	SetBkMode(s_hdc, TRANSPARENT);
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
	gMainWin::GetIF()->m_lpDDBack->ReleaseDC(s_hdc);
}