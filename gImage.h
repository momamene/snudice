//------------------------------------------------------------------------------------
//	gImage Class
//
//	2010. 07. 16	CoderK
//
//	�̹����� �ٷ�� Ŭ����
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

	bool		Load(char *szFileName);							// img ���ϸ� �о���
	void		Draw(int nX, int nY);							// ����� ������ gMainWin�� ����ۿ�
	
	void		Draw(RECT rcDest, RECT rcSour);
	
	void		Release();
};
