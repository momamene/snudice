#include "CrashHandler.h"
#include <stdio.h>

#define SIZE_TEMP				0x200

static char s_szCompiledDate[] = __DATE__;
static char s_szCompiledTime[] = __TIME__;

static int						s_nNumAddress = 0;
static DWORD					s_pAddress[30];
static EXCEPTION_POINTERS		s_sExPtrs;
//static BYTE						s_pStackMemory[SIZE_TEMP];
static BYTE*					s_pStackMemory;

// 중복 호출 방지
static bool						s_bGetMemory	= false;
static bool						s_bShowed		= false;


CCrashHandler*	CCrashHandler::m_pThis = NULL;


CCrashHandler::CCrashHandler()
{
	if( m_pThis == NULL )
	{
		m_pThis = this;
	}

}

CCrashHandler::~CCrashHandler()
{

}

BOOL CCrashHandler::Init()
{
	GetCurrentDirectory(200, m_szPath);
	sprintf(m_szPath, "%s\\EventLog", m_szPath);
	return TRUE;
}

void CCrashHandler::Release()
{

}

void CCrashHandler::ExitGame(char* szErrMsg)
{
	if( !s_bShowed )
	{
		s_bShowed = true;
		_CrashHandler()->Report(szErrMsg);
	}

}

static	DWORD		s_dwCode;
static	DWORD		s_dwStack;
static	DWORD*		s_pStack;

// 버그리포트를 남기는 함수
LONG CCrashHandler::ExceptionCallBack(EXCEPTION_POINTERS *pExPtrs)
{
	if( !s_bGetMemory )
	{
		s_bGetMemory	= true;

		s_dwCode		= pExPtrs->ContextRecord->Eip;
		s_dwStack		= pExPtrs->ContextRecord->Ebp;
		s_pStack		= (DWORD*)s_dwStack;

		// Error Infomaition & Register Memory Infomaition 
		s_sExPtrs = *pExPtrs;

		// Stack Memory Information
		s_pStackMemory = new BYTE[SIZE_TEMP];
		memcpy(s_pStackMemory, (BYTE*)pExPtrs->ContextRecord->Esp, SIZE_TEMP);

		// Call Stack Information
		s_pAddress[s_nNumAddress] = s_dwCode;
		++s_nNumAddress;

		// Search Callstack Info
		while( s_pStack && (unsigned long)s_pStack != 0xffffffff && s_dwCode && s_nNumAddress < 30 )
		{
			if( (DWORD)s_pStack > 0x80000000 )
			{
				break;
			}
			s_dwStack	= *s_pStack;
			s_pStack	+= 1;
			s_dwCode	= *s_pStack;

			s_pStack	= (DWORD*)s_dwStack;

			s_pAddress[s_nNumAddress] = s_dwCode;
			++s_nNumAddress;
		}
	}
	CCrashHandler::ExitGame(NULL);

	return EXCEPTION_EXECUTE_HANDLER;
}


//────────────────────────────────────
//	Name :	
//	Desc :	
//────────────────────────────────────
void CCrashHandler::Report(char* szErrMsg)
{
	m_pFile = fopen("bug.txt", "wt");


	ReportErrMsg(szErrMsg);
	ReportCrash();

	fclose(m_pFile);

	char szExe[MAX_PATH];
	sprintf(szExe, "bugReport.exe"); 
	Sleep(500);
	WinExec(szExe, SW_SHOWNORMAL);
 
}

void CCrashHandler::ReportCrash()
{
	int i;

	if( !s_nNumAddress )
	{
		return;
	}

	// Error Infomaition 
	fprintf(m_pFile, "[ Error Infomaition ] \n");
	fprintf(m_pFile, "Error Code : %X \n", s_sExPtrs.ExceptionRecord->ExceptionCode);
	fprintf(m_pFile, "\n");

	// Call Stack Information
	fprintf(m_pFile, "[ Call Stack Information ] \n");
	for(i = 0; i < s_nNumAddress; ++i)
	{
		fprintf(m_pFile, "0001 : 0x%08x \n", s_pAddress[i]);
	}
	fprintf(m_pFile, "\n");

	// Register Memory Infomaition 
	fprintf(m_pFile, "[ Register Memory Infomaition ] \n");
	fprintf(m_pFile, "EAX : 0x%08X \n", s_sExPtrs.ContextRecord->Eax);
	fprintf(m_pFile, "EBX : 0x%08X \n", s_sExPtrs.ContextRecord->Ebx);
	fprintf(m_pFile, "ECX : 0x%08X \n", s_sExPtrs.ContextRecord->Ecx);
	fprintf(m_pFile, "EDX : 0x%08X \n", s_sExPtrs.ContextRecord->Edx);
	fprintf(m_pFile, "ESI : 0x%08X \n", s_sExPtrs.ContextRecord->Esi);
	fprintf(m_pFile, "EDI : 0x%08X \n", s_sExPtrs.ContextRecord->Edi);
	fprintf(m_pFile, "EIP : 0x%08X \n", s_sExPtrs.ContextRecord->Eip);
	fprintf(m_pFile, "ESP : 0x%08X \n", s_sExPtrs.ContextRecord->Esp);
	fprintf(m_pFile, "EBP : 0x%08X \n", s_sExPtrs.ContextRecord->Ebp);
	fprintf(m_pFile, "Flg : 0x%08X \n", s_sExPtrs.ContextRecord->EFlags);
	fprintf(m_pFile, "CS  : 0x%08X \n", s_sExPtrs.ContextRecord->SegCs);
	fprintf(m_pFile, "DS  : 0x%08X \n", s_sExPtrs.ContextRecord->SegDs);
	fprintf(m_pFile, "SS  : 0x%08X \n", s_sExPtrs.ContextRecord->SegSs);
	fprintf(m_pFile, "ES  : 0x%08X \n", s_sExPtrs.ContextRecord->SegEs);
	fprintf(m_pFile, "FS  : 0x%08X \n", s_sExPtrs.ContextRecord->SegFs);
	fprintf(m_pFile, "GS  : 0x%08X \n", s_sExPtrs.ContextRecord->SegGs);
	fprintf(m_pFile, "\n");

	// Stack Memory Information
	fprintf(m_pFile, "[ Stack Memory Infomaition ]");
	DWORD	dwSp = s_sExPtrs.ContextRecord->Esp;
	for(i = 0; i < SIZE_TEMP; ++i)
	{
		if( (i % 16) == 0 )
		{
			fprintf(m_pFile, "\n");
			fprintf(m_pFile, "0x%08X\t", dwSp + i);
		}
		
		if( ((i + 1) % 4) == 0)
			fprintf( m_pFile, "%02X    ", s_pStackMemory[i]);
		else
			fprintf(m_pFile, "%02X ", s_pStackMemory[i]);
		
	}
	fprintf(m_pFile, "\n");
	fprintf(m_pFile, "\n");

}

void CCrashHandler::ReportErrMsg(char *szErrMsg)
{
	if( szErrMsg )
	{
		fprintf(m_pFile, "\n");
		fprintf(m_pFile, "[ Error Message ] \n");
		fprintf(m_pFile, szErrMsg);
		fprintf(m_pFile, "\n");
	}
	fprintf(m_pFile, "\n");
}
