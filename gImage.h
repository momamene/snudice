//------------------------------------------------------------------------------------
//	gImage Class
//
//	2010. 07. 16	CoderK				
//
//	�̹����� �ٷ�� Ŭ����
//	2010. 07. 20
//	�� 256 �ȷ�Ʈ �� �� �־�߸� ����� �д��� ����. ImgConverter�� �ֽŲ� �� ��.
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

	bool		Load(char *szFileName);									// img ���ϸ� �о���
	void		Draw(int nX = 0, int nY = 0);							// ����� ������ gMainWin�� ����ۿ�
	void		Draw(RECT rcDest, RECT rcSour, bool stretch = true);	// bool ������ Ȯ�����, Ŭ�������� ����
	
	void		Release();
};
