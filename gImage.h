//------------------------------------------------------------------------------------
//	gImage Class
//
//	2010. 07. 16	CoderK
//
//	이미지를 다루는 클래스
//------------------------------------------------------------------------------------
//		Img file format
/*	
		DWORD				dwDataSize;
		int					nWidth;
		int					nHeight;
		DWORD				dwPitch;
		RGBQUAD				rgb[256];
		BYTE*				pData;
*/
#pragma once
#include <windows.h>
#include <ddraw.h>

class gImage  
{
public:
	gImage();
	virtual ~gImage();
public:
	LPDIRECTDRAWSURFACE		m_lpDDSur;

	int			m_nWidth;
	int			m_nHeight;

	bool		Load(char *szFileName);							// img 파일만 읽어짐
	void		Draw(int nX, int nY);							// 출력은 무조건 gMainWin의 백버퍼에
	
	void		Draw(RECT rcDest, RECT rcSour);
	
	void		Release();
};
