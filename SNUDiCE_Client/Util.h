//------------------------------------------------------------------------------------
//	gUtil Class
//
//	2010. 08. 04	CoderK
//
//	이것저것 도와주는 함수들. no 객체 생성
//	text 출력할 때 무조건 시작할때 begin, 끝나고 end
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
	static void Text(int x, int y, char *str, int lineterm = 20);	//lineterm -> 엔터칠때 얼마나 내려가나
	static void EndText();

	static void DebugMsg(char *msg);

	static bool PointInRect(int x, int y, RECT rc);
	static int	TextLength(char *sz);
};

