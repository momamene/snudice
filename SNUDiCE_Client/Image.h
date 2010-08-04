//------------------------------------------------------------------------------------
//	gImage Class
//
//	2010. 08. 04	CoderK				
//
//	이미지를 다루는 클래스
//	ImgConverter 써서 변환된 img 파일을 다룬다.
//	Release()로 자원 해제해 주는 것 잊지 말 것.
//------------------------------------------------------------------------------------
//		Img file format
/*	
		int					nPallete;
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

	bool		Load(char *szFileName);									// img 파일만 읽어짐
	void		Draw(int nX = 0, int nY = 0);							// 출력은 무조건 gMainWin의 백버퍼에
	void		Draw(RECT rcDest, RECT rcSour, bool stretch = true);	// bool 값으로 확대축소. true면 클리핑 안됨.

	void		Release();
};
