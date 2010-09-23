#include "SubmitCore.h"
#include "Mouse.h"
#include "SubjectContainer.h"
#include "Util.h"

#define SUB_FILE_BACK				".\\Data\\Submit\\sub_back.img"

#define SUB_BTN_FILE_SELECT			".\\Data\\Submit\\sub_btn_select.img"
#define SUB_BTN_SIZE_SELECT_W		314
#define SUB_BTN_SIZE_SELECT_H		24
#define SUB_BTN_POS_SELECT_X		18
#define SUB_BTN_POS_SELECT_Y		83
#define SUB_BTN_TERM_SELECT_Y		20

#define SUB_TERM_SUBNAME_X			5
#define SUB_TERM_SUBNAME_Y			6
#define SUB_TERM_COLLEGE_X			105
#define SUB_TERM_COLLEGE_Y			6

static gSubmitCore s_SubmitCore;

gSubmitCore *gSubmitCore::GetIF()
{
	return &s_SubmitCore;
}

gSubmitCore::gSubmitCore(void)
{
}

gSubmitCore::~gSubmitCore(void)
{
}

bool gSubmitCore::SetUp()
{
	if(!m_ImgBack.Load(SUB_FILE_BACK))
		return false;

	int		i;

	RECT	rcDest;

	SetRect(&rcDest,
			SUB_BTN_POS_SELECT_X,
			SUB_BTN_POS_SELECT_Y,
			SUB_BTN_POS_SELECT_X + SUB_BTN_SIZE_SELECT_W,
			SUB_BTN_POS_SELECT_Y + SUB_BTN_SIZE_SELECT_H );

	for(i = 0; i < CLASSNUM; i++)
	{
		if(!m_BtnClass[i].SetUp(SUB_BTN_FILE_SELECT, false, rcDest))
			return false;

		OffsetRect(&rcDest, 0, SUB_BTN_TERM_SELECT_Y);
	}

	m_nSelected = -1;
}

void gSubmitCore::MainLoop()
{
	Draw();
}

void gSubmitCore::Draw()
{
	m_ImgBack.Draw();

	int		i;

	for(i = 0; i < CLASSNUM; i++)
		m_BtnClass[i].Draw();

	gUtil::BeginText();
		for(i = 0; i < CLASSNUM; i++)
		{
			gUtil::Text(m_BtnClass[i].m_rcPos.left + SUB_TERM_SUBNAME_X, m_BtnClass[i].m_rcPos.top + SUB_TERM_SUBNAME_Y,
				gSubjectContainer::GetIF()->m_subject[i].subject);

			gUtil::Text(m_BtnClass[i].m_rcPos.left + SUB_TERM_COLLEGE_X, m_BtnClass[i].m_rcPos.top + SUB_TERM_COLLEGE_Y,
				gSubjectContainer::GetIF()->m_subject[i].college);
		}
	gUtil::EndText();
}

void gSubmitCore::Release()
{
	m_ImgBack.Release();
}

void gSubmitCore::OnLButtonDown()
{

}

void gSubmitCore::OnLButtonUp()
{

}

void gSubmitCore::OnMouseMove()
{
	gMouse		*mouse = gMouse::GetIF();

	int			i;

	for(i = 0; i < CLASSNUM; i++)
	{
		if(!m_BtnClass[i].PointInButton(mouse->m_nPosX, mouse->m_nPosY))
			m_BtnClass[i].m_eBtnMode = EBM_NONE;
		else
		{
			m_BtnClass[i].m_eBtnMode = EBM_HOVER;
			m_nSelected		= i;
		}
	}

}

void gSubmitCore::OnRButtonDown()
{

}