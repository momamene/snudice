#include "MainWin.h"
#include <windows.h>
#include <stdio.h>
#include "CrashHandler.h"

//#define DEBUGMODE

#define NOUSE_CRASHHANDLER

#ifdef DEBUGMODE
#using <System.dll>

using namespace System;
using namespace System::Diagnostics;
#endif

#ifndef DEBUGMODE
BOOL GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len, DWORD &section, DWORD &offset)
{
	MEMORY_BASIC_INFORMATION mbi;
	if(!VirtualQuery(addr, &mbi, sizeof(mbi))) return FALSE;
	
	DWORD hMod = (DWORD)mbi.AllocationBase;
	if(!GetModuleFileName((HMODULE)hMod, szModule, len)) return FALSE;

	PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;
	PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHdr);
	DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address

	for(DWORD i = 0; i < pNtHdr->FileHeader.NumberOfSections; i++, pSection++) {

		DWORD sectionStart = pSection->VirtualAddress;
		DWORD sectionEnd = sectionStart + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

		if((rva >= sectionStart) && (rva <= sectionEnd)) {
			section = i + 1;
			offset = rva - sectionStart;

			return TRUE;
		}
	}
	return FALSE;

}

LONG WINAPI UnhandledExceptionFilter2(PEXCEPTION_POINTERS pExceptionInfo)
{
	PEXCEPTION_RECORD pExceptionRecord = pExceptionInfo->ExceptionRecord;

	FILE *fp=fopen("bug.txt","wt");
	fprintf(fp,"Exception code : %08X\n", pExceptionRecord->ExceptionCode);

	PVOID addr = pExceptionRecord->ExceptionAddress;
	TCHAR szModule[MAX_PATH]={0,};
	DWORD len = MAX_PATH;
	DWORD section = 0;
	DWORD offset = 0;
	MEMORY_BASIC_INFORMATION mbi;

	if(!VirtualQuery(addr, &mbi, sizeof(mbi))) return FALSE;
	DWORD hMod = (DWORD)mbi.AllocationBase;

	//if(!GetModuleFileName((HMODULE)hMod, szModule, len)) return FALSE;

	PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;
	PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);
	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION(pNtHdr);
	DWORD rva = (DWORD)addr ? hMod : 0;

	for(DWORD i = 0; i < pNtHdr->FileHeader.NumberOfSections; i++, pSection++) {

		DWORD sectionStart = pSection->VirtualAddress;
		DWORD sectionEnd = sectionStart + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

		if((rva >= sectionStart) && (rva <= sectionEnd)) {

			section = i + 1;
			offset = (rva) ? sectionStart:offset;

			break;
		}
	}

	fprintf(fp,"Fault Address : %08X %02X:%08X\n%s\n\n", pExceptionRecord->ExceptionAddress, section, offset, szModule);

	PCONTEXT pCtx = pExceptionInfo->ContextRecord;
	DWORD pc = pCtx->Eip;
	PDWORD pFrame, pPrevFrame;

	pFrame = (PDWORD)pCtx->Ebp;


	do {
		TCHAR szModule[MAX_PATH]={0,};
		DWORD section = 0, offset = 0;

		GetLogicalAddress((PVOID)pc, szModule, sizeof(szModule), section, offset);

		fprintf(fp,"%08X %08X %04X:%08X\n%s\n\n", pc, pFrame, section, offset, szModule);

		pc = pFrame[1];
		pPrevFrame = pFrame;
		pFrame = (PDWORD)pFrame[0];

		if((DWORD)pFrame & 3) break;
		if(pFrame <= pPrevFrame) break;
		if(IsBadWritePtr(pFrame, sizeof(PVOID) * 2)) break;

	} while(TRUE);
	fclose(fp);

	Sleep(1000);
	WinExec("BugReport.exe", SW_SHOWNORMAL);
	return TRUE;
}
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	gMainWin	*main = gMainWin::GetIF();

	
	//if(strcmp(lpszCmdParam, "RunByUpdater") != 0)
	//	return -1;

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

#ifdef NOUSE_CRASHHANDLER
	retValue = main->Run();
#else
	#ifndef DEBUGMODE
	//	LPTOP_LEVEL_EXCEPTION_FILTER lpPreviousFilter = NULL;
	//	lpPreviousFilter = SetUnhandledExceptionFilter(UnhandledExceptionFilter2);
	#endif


	#ifdef DEBUGMODE
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
	#endif


	#ifndef DEBUGMODE
		_CrashHandler()->Create();
		_CrashHandler()->Init();
		__try {
			retValue = main->Run();
		}
		__except(_CrashHandler()->ExceptionCallBack(GetExceptionInformation())) {
			return -1;
		}
	//	SetUnhandledExceptionFilter(lpPreviousFilter);
	#endif
#endif

	main->Release();
	return retValue;
}