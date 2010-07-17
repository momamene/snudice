#include <windows.h>
#include "gMainWin.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	if(FAILED(gMainWin::GetIF()->SetUp(hInstance, lpszCmdParam, nCmdShow)))
		return 0;
	
	int	retValue;
	retValue = gMainWin::GetIF()->Run();
	gMainWin::GetIF()->Release();
	
	return retValue;
}