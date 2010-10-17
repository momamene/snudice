#include "ImgButton.h"

gImgButton::gImgButton()
{

}

gImgButton::~gImgButton()
{

}

bool gImgButton::SetUp(char *szImgName, bool vertical, RECT rcPos)
{
	if(!m_Img.Load(szImgName))
		return false;

	m_bVertical	= vertical;
	m_rcPos		= rcPos;
	m_bShow		= true;
	
	return true;
}

void gImgButton::Draw()
{
	if(m_bShow)
	{
		RECT	rcPrt;

		if(m_bVertical)
		{
			SetRect(&rcPrt, 0, 0, m_Img.m_nWidth, m_Img.m_nHeight / 3);
			OffsetRect(&rcPrt, 0, m_Img.m_nHeight * m_eBtnMode / 3);
		}
		else
		{
			SetRect(&rcPrt, 0, 0, m_Img.m_nWidth / 3, m_Img.m_nHeight);
			OffsetRect(&rcPrt, m_Img.m_nWidth* m_eBtnMode / 3, 0);
		}
		m_Img.Draw(m_rcPos, rcPrt);
	}
}

bool gImgButton::PointInButton(int nX, int nY)
{
	if(m_bShow)
	{
		if(m_rcPos.left < nX && nX < m_rcPos.right
			&& m_rcPos.top < nY && nY < m_rcPos.bottom)
			return true;
	}
	return false;
}

void gImgButton::Release()
{
	m_Img.Release();
}

bool gImgButton::Restore()
{
	return m_Img.Restore();
}