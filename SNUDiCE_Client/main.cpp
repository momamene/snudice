#include "MainWin.h"
#include <windows.h>
#include <stdio.h>

#using <System.dll>

using namespace System;
using namespace System::Diagnostics;

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

	int		retValue = -1; 
	StackTrace^ st;
	
	__try {
		retValue = main->Run();
	}
	__except(st = gcnew StackTrace( true ), EXCEPTION_EXECUTE_HANDLER) {
		STARTUPINFO si = {sizeof(STARTUPINFO),};
		
		FILE *fp=fopen("Bug.txt","wt");
		String^ stackIndent = "";
		for ( int i = 0; i < st->FrameCount; i++ )
		{

			// Note that at this level, there are five
			// stack frames, one for each method invocation.
			StackFrame^ sf = st->GetFrame( i );
			fprintf(fp,"\n");
			fprintf(fp,"High up the call stack, Method: {%s}\n", sf->GetMethod()->ToString() );
			fprintf(fp,"High up the call stack, Line Number: {%s}\n", sf->GetFileLineNumber().ToString() );
		}
		fclose(fp);
		
		Sleep(1000);
		WinExec("BugReport.exe", SW_SHOWNORMAL);
		//CreateProcess(Path, " c:\\autoexec.bat", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	}
	main->Release();

	return retValue;
}