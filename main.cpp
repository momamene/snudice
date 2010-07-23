#include <windows.h>
#include "gMainWin.h"
//#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	if(FAILED(gMainWin::GetIF()->SetUp(hInstance, lpszCmdParam, nCmdShow)))
		return 0;
/*
	char buf[64];
	//wsprintf(buf, "%d", 123.4f);
	sprintf(buf, "%.1f", 123.4f);
	OutputDebugString(buf);
*/
	int	retValue;
	retValue = gMainWin::GetIF()->Run();
	gMainWin::GetIF()->Release();

	return retValue;
}