#include <windows.h>
#include "MainWin.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	gMainWin	*main = gMainWin::GetIF();

	if(!main->SetUp(hInstance, lpszCmdParam, nCmdShow))
	{
		if(main->m_hWnd == NULL)
			return 0;
		else
		{
			main->Exit();
			return 0;
		}
	}

	int		retValue; 
	retValue = main->Run();
	main->Release();

	return retValue;
}