#include "Scrollbar.h"
#include "Util.h"

gScrollbar::gScrollbar(void)
{
}

gScrollbar::~gScrollbar(void)
{
}


bool gScrollbar::SetUp(int x, int y, int height, char *szImg, bool up)
{
	SetRect(&m_rcPos,
		x, y, x + SCROLL_SIZE_BACK_W, y + height);

	if(!m_ImgBack.Load(szImg))
		return false;

	RECT	rcPos;

	SetRect(&rcPos,
			x + (SCROLL_SIZE_BACK_W - SCROLL_SIZE_UPDOWN_W) / 2,
			y,
			x + (SCROLL_SIZE_BACK_W - SCROLL_SIZE_UPDOWN_W) / 2 + SCROLL_SIZE_UPDOWN_W,
			y + SCROLL_SIZE_UPDOWN_H );

	if(!m_ImgBtn[SCR_UP].SetUp(SCROLL_FILE_UP, false, rcPos))
		return false;

	SetRect(&rcPos,
			x + (SCROLL_SIZE_BACK_W - SCROLL_SIZE_UPDOWN_W) / 2,
			y + height - SCROLL_SIZE_UPDOWN_H,
			x + (SCROLL_SIZE_BACK_W - SCROLL_SIZE_UPDOWN_W) / 2 + SCROLL_SIZE_UPDOWN_W,
			y + height);

	if(!m_ImgBtn[SCR_DOWN].SetUp(SCROLL_FILE_DOWN, false, rcPos))
		return false;

	SetRect(&m_rcPosScroll,
			x,
			y + SCROLL_SIZE_UPDOWN_H,
			x + SCROLL_SIZE_BACK_W,
			y + height - SCROLL_SIZE_UPDOWN_H);

	if(up)
	{
		SetRect(&rcPos,
			x - (SCROLL_SIZE_BAR_W - SCROLL_SIZE_BACK_W) / 2,
			m_rcPosScroll.top,
			x - (SCROLL_SIZE_BAR_W - SCROLL_SIZE_BACK_W) / 2 + SCROLL_SIZE_BAR_W,
			m_rcPosScroll.top + SCROLL_SIZE_BAR_H);
	}
	else
	{
		SetRect(&rcPos,
			x - (SCROLL_SIZE_BAR_W - SCROLL_SIZE_BACK_W) / 2,
			m_rcPosScroll.bottom - SCROLL_SIZE_BAR_H,
			x - (SCROLL_SIZE_BAR_W - SCROLL_SIZE_BACK_W) / 2 + SCROLL_SIZE_BAR_W,
			m_rcPosScroll.bottom);
	}

	if(!m_ImgBtn[SCR_BAR].SetUp(SCROLL_FILE_BAR, false, rcPos))
		return false;

	m_bActive = true;

	return true;
}

void gScrollbar::Draw()
{
	m_ImgBack.Draw(m_rcPos.left, m_rcPos.top);

	int			i;

	for(i = 0; i < SCR_END; i++)
		m_ImgBtn[i].Draw();

}

void gScrollbar::Release()
{
	m_ImgBack.Release();

	int		i;

	for(i = 0; i < SCR_END; i++)
		m_ImgBtn[i].Release();

}

void gScrollbar::OnLbuttonDown(int x, int y)
{
	if(m_ImgBtn[SCR_UP].PointInButton(x, y))
	{
		m_ImgBtn[SCR_UP].m_eBtnMode = EBM_CLICK;
	}
	else if(m_ImgBtn[SCR_DOWN].PointInButton(x, y))
	{
		m_ImgBtn[SCR_DOWN].m_eBtnMode = EBM_CLICK;
	}
	else if(m_ImgBtn[SCR_BAR].PointInButton(x, y))
	{
		m_ImgBtn[SCR_BAR].m_eBtnMode = EBM_CLICK;
		m_nMouseTemp = y;
	}
}

void gScrollbar::OnLbuttonUp(int x, int y)
{
	if(m_ImgBtn[SCR_UP].PointInButton(x, y))
	{
		m_ImgBtn[SCR_UP].m_eBtnMode = EBM_NONE;
	}
	else if(m_ImgBtn[SCR_DOWN].PointInButton(x, y))
	{
		m_ImgBtn[SCR_DOWN].m_eBtnMode = EBM_NONE;
	}
	else if(m_ImgBtn[SCR_BAR].PointInButton(x, y))
	{
		m_ImgBtn[SCR_BAR].m_eBtnMode = EBM_NONE;
	}

}

void gScrollbar::OnMouseMove(int x, int y)
{
	int			i;

	if(gUtil::PointInRect(x, y, m_rcPos))
	{
		if(GetKeyState(VK_LBUTTON) < 0)
		{
			if(m_ImgBtn[SCR_BAR].m_eBtnMode == EBM_CLICK)
			{
				OffsetRect(&m_ImgBtn[SCR_BAR].m_rcPos, 0, y - m_nMouseTemp);
				m_nMouseTemp = y;
				
				if(m_ImgBtn[SCR_BAR].m_rcPos.top < m_rcPosScroll.top)
				{
					m_ImgBtn[SCR_BAR].m_rcPos.top		= m_rcPosScroll.top;
					m_ImgBtn[SCR_BAR].m_rcPos.bottom	= m_ImgBtn[SCR_BAR].m_rcPos.top + SCROLL_SIZE_BAR_H;
				}
				if(m_ImgBtn[SCR_BAR].m_rcPos.bottom > m_rcPosScroll.bottom)
				{
					m_ImgBtn[SCR_BAR].m_rcPos.bottom	= m_rcPosScroll.bottom;
					m_ImgBtn[SCR_BAR].m_rcPos.top		= m_ImgBtn[SCR_BAR].m_rcPos.bottom - SCROLL_SIZE_BAR_H;
				}
			}
			return;
		}
	}
	for(i = 0; i < SCR_END; i++)
	{
		if(m_ImgBtn[i].PointInButton(x, y))
			m_ImgBtn[i].m_eBtnMode = EBM_HOVER;
		else
			m_ImgBtn[i].m_eBtnMode = EBM_NONE;
	}
}

SCROLLBTN gScrollbar::whatIsClicked()
{
	if(m_ImgBtn[SCR_UP].m_eBtnMode == EBM_CLICK)
		return SCR_UP;
	else if(m_ImgBtn[SCR_DOWN].m_eBtnMode == EBM_CLICK)
		return SCR_DOWN;
	else if(m_ImgBtn[SCR_BAR].m_eBtnMode == EBM_CLICK)
		return SCR_BAR;

	return SCR_END;
}

void gScrollbar::ChangeCursor(int cur, int size)
{
	if(cur == 0)
	{
		m_ImgBtn[SCR_BAR].m_rcPos.top = m_rcPosScroll.top;
		m_ImgBtn[SCR_BAR].m_rcPos.bottom = m_ImgBtn[SCR_BAR].m_rcPos.top + SCROLL_SIZE_BAR_H;
		return;
	}
	if(cur == size)
	{
		m_ImgBtn[SCR_BAR].m_rcPos.top = m_rcPosScroll.bottom - SCROLL_SIZE_BAR_H;
		m_ImgBtn[SCR_BAR].m_rcPos.bottom = m_rcPosScroll.bottom;
		return;
	}

	int		scrollSize	= m_rcPosScroll.bottom - m_rcPosScroll.top - SCROLL_SIZE_BAR_H;

	float	temp = (float)cur / size;
	float	newCur = m_rcPosScroll.top + scrollSize * temp;

	if(newCur + SCROLL_SIZE_BAR_H > m_rcPosScroll.bottom)
		newCur = m_rcPosScroll.bottom - SCROLL_SIZE_BAR_H;

	m_ImgBtn[SCR_BAR].m_rcPos.top = (int)newCur;
	m_ImgBtn[SCR_BAR].m_rcPos.bottom = m_ImgBtn[SCR_BAR].m_rcPos.top + SCROLL_SIZE_BAR_H;
}