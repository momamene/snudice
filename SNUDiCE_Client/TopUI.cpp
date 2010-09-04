#include "TopUI.h"

static gTopUI s_TopUI;

gTopUI *gTopUI::GetIF()
{
	return &s_TopUI;
}

gTopUI::gTopUI(void)
{
}

gTopUI::~gTopUI(void)
{
}


bool gTopUI::SetUp()
{
	if(!m_ImgBack.Load(TOP_FILE_BACK))
		return false;

	SetRect(&m_rcPos,
			TOP_POS_BACK_X,
			TOP_POS_BACK_Y,
			TOP_POS_BACK_X + TOP_POS_BACK_W,
			TOP_POS_BACK_Y + TOP_POS_BACK_H);

	return true;
}

void gTopUI::Draw()
{
	m_ImgBack.Draw(m_rcPos.left, m_rcPos.top);
}

void gTopUI::Release()
{
	m_ImgBack.Release();
}