#include "const.h"
#include "gImage.h"
#include "gMainWin.h"

//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------
gImage::gImage()
{

}

gImage::~gImage()
{

}


bool gImage::Load(char *szFileName)
{
	HANDLE		hFile;
	DWORD		dwDataSize;
	DWORD		dwRead;
	DWORD		dwPitch;
	RGBQUAD		rgb[256];
	BYTE*		pData;
	char		szError[256];

	// Read Img File
	hFile = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
//		wsprintf(szError, "gImage : %s open failed", szFileName);
//		MessageBox(gMainWin::GetIF()->m_hWnd, szError, "Error", MB_OK);
		CloseHandle(hFile);
		return false;
	}

	ReadFile(hFile, &dwDataSize, sizeof(dwDataSize), &dwRead, NULL);
	ReadFile(hFile, &m_nWidth, sizeof(m_nWidth), &dwRead, NULL);
	ReadFile(hFile, &m_nHeight, sizeof(m_nHeight), &dwRead, NULL);
	ReadFile(hFile, &dwPitch, sizeof(dwPitch), &dwRead, NULL);
	ReadFile(hFile, rgb, sizeof(RGBQUAD) * 256, &dwRead, NULL);
	pData = new BYTE[dwDataSize];
	ReadFile(hFile, pData, dwDataSize, &dwRead, NULL);
	CloseHandle(hFile);

	DDSURFACEDESC		ddsd;
	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize			= sizeof(DDSURFACEDESC);
	ddsd.dwFlags		= DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	ddsd.ddsCaps.dwCaps	= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth		= m_nWidth;
	ddsd.dwHeight		= m_nHeight;

	LPDIRECTDRAW	dd = gMainWin::GetIF()->m_lpDD;
	if(FAILED(dd->CreateSurface(&ddsd, &m_lpDDSur, NULL)))
	{
//		wsprintf(szError, "gImage : %s surface failed", szFileName);
//		MessageBox(gMainWin::GetIF()->m_hWnd, szError, "Error", MB_OK);
		return false;
	}

	DWORD*			pAddr;
	int				i, j;
	DWORD			dwDest, dwSour;
	COLORREF		color;

	memset(&ddsd, 0, sizeof(DDSURFACEDESC));
	ddsd.dwSize	= sizeof(DDSURFACEDESC);
	
	m_lpDDSur->Lock(NULL, &ddsd, DDLOCK_SURFACEMEMORYPTR | DDLOCK_WAIT, NULL);
	pAddr = (DWORD*)ddsd.lpSurface;
	
	for(i = 0; i < m_nHeight; i++)
	{
		for(j = 0; j < m_nWidth; j++)
		{
			dwDest = i * (ddsd.lPitch >> 2) + j;
			dwSour = i * dwPitch + j;
			
			color = RGB(rgb [ pData[dwSour] ].rgbBlue, rgb[ pData[dwSour] ].rgbGreen, rgb[ pData[dwSour] ].rgbRed);
			
			memcpy(&pAddr[dwDest], &color, 4);
		}
	}
	m_lpDDSur->Unlock(NULL);
	
	delete [] pData;
	
	DDCOLORKEY		colorkey;
	
	colorkey.dwColorSpaceHighValue	= 0x00ff00ff;
	colorkey.dwColorSpaceLowValue	= 0x00ff00ff;		// colorkey == RGB(255, 0, 255);
	
	m_lpDDSur->SetColorKey(DDCKEY_SRCBLT, &colorkey);

	return true;
}

void gImage::Draw(int nX, int nY)
{
	RECT	rcDest = {nX, nY, nX + m_nWidth, nY + m_nHeight};
	RECT	rcSour = {0, 0, m_nWidth, m_nHeight};

	gMainWin::GetIF()->m_lpDDBack->Blt(&rcDest, m_lpDDSur, &rcSour, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
}

void gImage::Draw(RECT rcDest, RECT rcSour)
{
	gMainWin::GetIF()->m_lpDDBack->Blt(&rcDest, m_lpDDSur, &rcSour, DDBLT_WAIT | DDBLT_KEYSRC, NULL);
}

void gImage::Release()
{
	SAFE_RELEASE(m_lpDDSur);
}