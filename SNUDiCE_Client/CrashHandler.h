#pragma once

#include <windows.h>
#include <vector>
using namespace std;

class CCrashHandler
{
	FILE*			m_pFile;
	char			m_szPath[200];
	
protected:
	static CCrashHandler*		m_pThis;
public:
	void ReportErrMsg(char* szErrMsg);
	void ReportCrash();
	void Report(char* szErrMsg);
	
	static LONG ExceptionCallBack(EXCEPTION_POINTERS *pExPtrs);
	static void ExitGame(char* szErrMsg);
	void Release();
	BOOL Init();
	CCrashHandler();
	virtual ~CCrashHandler();

	static inline CCrashHandler* GetThis()		{ return m_pThis; }
	static inline void Create()					{ new CCrashHandler(); }

};

inline CCrashHandler* _CrashHandler()
{
	return CCrashHandler::GetThis();
}
