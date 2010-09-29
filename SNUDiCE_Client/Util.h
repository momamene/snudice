//------------------------------------------------------------------------------------
//	gUtil Class
//
//	2010. 08. 04	CoderK
//
//	�̰����� �����ִ� �Լ���. no ��ü ����
//	text ����� �� ������ �����Ҷ� begin, ������ end
//------------------------------------------------------------------------------------
#pragma once
#include <windows.h>

class gUtil  
{
public:
	// text
	static void SetFont(char *font);
	static void SetSize(int size);
	static void SetDefaultFont();
	static void SetColor();
	static void BeginText();
	static void Text(int x, int y, char *str, int lineterm = 20);	//lineterm -> ����ĥ�� �󸶳� ��������
	static void EndText();

	static void DebugMsg(char *msg);

	static bool PointInRect(int x, int y, RECT rc);
	static int	TextLength(char *sz);
};

