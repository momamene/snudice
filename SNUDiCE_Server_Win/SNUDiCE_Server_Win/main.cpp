#include "MainWin.h"
#include <windows.h>



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	gMainWin	*main = gMainWin::GetIF();
	int			retValue;
	
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

	if(!main->MakeListenThread())
		return -1;

	retValue = main->Run();
	main->Release();
	return retValue;
}