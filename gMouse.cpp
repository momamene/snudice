#include "gMouse.h"
#include "gMainWin.h"
#include "gTitleCore.h"
#include "gGameCore.h"

//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------

static gMouse s_Mouse;

gMouse *gMouse::GetIF()
{
	return &s_Mouse;
}

gMouse::gMouse()
{

}

gMouse::~gMouse()
{

}

bool gMouse::SetUp()
{
	return true;
}

void gMouse::MainLoop()
{

}

void gMouse::Draw()
{

}

//------------------------------------------------------------------------------------
//	mouse Ã³¸®
//------------------------------------------------------------------------------------
void gMouse::OnLButtonDown()
{
	switch(gMainWin::GetIF()->m_eCoreMode)
	{
		case EMC_TITLE:
			gTitleCore::GetIF()->OnLButtonDown();
			break;
	}
}

void gMouse::OnLButtonUp()
{
	switch(gMainWin::GetIF()->m_eCoreMode)
	{
	case EMC_TITLE:
		gTitleCore::GetIF()->OnLButtonUp();
		break;
	}
}

void gMouse::OnMouseMove()
{
	switch(gMainWin::GetIF()->m_eCoreMode)
	{
	case EMC_TITLE:
		gTitleCore::GetIF()->OnMouseMove();
		break;
	case EMC_GAME:
		gGameCore::GetIF()->OnMouseMove();
		break;
	}
}

void gMouse::OnRButtonDown()
{
	switch(gMainWin::GetIF()->m_eCoreMode)
	{
	case EMC_TITLE:
		gTitleCore::GetIF()->OnRButtonDown();
		break;
	}
}