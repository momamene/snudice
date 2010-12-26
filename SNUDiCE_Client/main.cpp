#include "MainWin.h"
#include <windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	gMainWin	*main = gMainWin::GetIF();

	if(strcmp(lpszCmdParam, "RunByUpdater") != 0)
		return -1;

	if(!main->SetUp(hInstance, lpszCmdParam, nCmdShow))
	{
		if(main->m_hWnd == NULL)
			return 0;
		else
		{
			main->Exit();
		}
	}

	int		retValue; 
	retValue = main->Run();
	main->Release();

	return retValue;
}