//------------------------------------------------------------------------------------
//	gImage Class
//
//	2010. 07. 16	CoderK				
//
//	이미지를 다루는 클래스
//	2010. 07. 20
//	꼭 256 팔레트 다 차 있어야만 제대로 읽던거 수정. ImgConverter도 최신꺼 쓸 것.
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

	bool		Load(char *szFileName);							// img 파일만 읽어짐
	void		Draw(int nX, int nY);							// 출력은 무조건 gMainWin의 백버퍼에
	
	void		Draw(RECT rcDest, RECT rcSour);
	
	void		Release();
};
