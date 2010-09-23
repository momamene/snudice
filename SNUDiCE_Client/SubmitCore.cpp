#include "SubmitCore.h"

#define SUB_FILE_BACK			".\\Data\\Submit\\sub_back.img"

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
}

void gSubmitCore::MainLoop()
{
	Draw();
}

void gSubmitCore::Draw()
{
	m_ImgBack.Draw();
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

}

void gSubmitCore::OnRButtonDown()
{

}