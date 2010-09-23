#include "GameCore.h"
#include "PopUp.h"
#include "Util.h"
#include "stringconst.h"
#include "MainWin.h"

static gGameCore s_GameCore;

gGameCore *gGameCore::GetIF()
{
	return &s_GameCore;
}

gGameCore::gGameCore(void)
{
}

gGameCore::~gGameCore(void)
{
}

bool gGameCore::SetUp()
{
	return true;
}

void gGameCore::MainLoop()
{
	Draw();

	// popup Ã¢ Ã³¸®
	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->MainLoop();
		return;
	}

	if(gPopUp::GetIF()->m_bReturn)
	{
		switch(gPopUp::GetIF()->m_ePop)
		{
			case EPOP_DISCONNECT:
				switch(gPopUp::GetIF()->m_eBtnClk)
				{
					case ECLK_OK:
						gMainWin::GetIF()->Exit();
						break;
				}
				break;
		}
		gPopUp::GetIF()->m_bReturn = false;
	}
}

void gGameCore::Draw()
{

}

void gGameCore::Release()
{

}

void gGameCore::OnLButtonDown()
{

}

void gGameCore::OnLButtonUp()
{

}

void gGameCore::OnMouseMove()
{

}

void gGameCore::OnRButtonDown()
{

}

bool gGameCore::PreTransMsg(MSG &msg)
{
	return false;
}