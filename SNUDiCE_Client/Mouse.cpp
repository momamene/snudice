#include "Mouse.h"
#include "MainWin.h"
#include "PopUp.h"
#include "LoginCore.h"

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

// �̳��� mainloop ������ ���Ŀ� ���콺�� �����δٴ��� �׷��� Ȱ��
void gMouse::MainLoop()
{

}

void gMouse::Draw()
{

}

void gMouse::OnLButtonDown()
{
	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->OnLButtonDown();
		return;	
	}

	switch(gMainWin::GetIF()->m_eCoreMode)
	{
		case ECM_LOGIN:
			gLoginCore::GetIF()->OnLButtonDown();
			break;
		case ECM_PSEL:
			break;
		case ECM_CSEL:
			break;
		case ECM_SUBMIT:
			break;
		case ECM_GAME:
			break;
	}

}

void gMouse::OnLButtonUp()
{
	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->OnLButtonUp();
		return;	
	}
}

void gMouse::OnMouseMove()
{
	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->OnMouseMove();
		return;	
	}

	switch(gMainWin::GetIF()->m_eCoreMode)
	{
	case ECM_LOGIN:
		gLoginCore::GetIF()->OnMouseMove();
		break;
	case ECM_PSEL:
		break;
	case ECM_CSEL:
		break;
	case ECM_SUBMIT:
		break;
	case ECM_GAME:
		break;
	}
}

void gMouse::OnRButtonDown()
{
	if(gPopUp::GetIF()->isPopUp())
	{
		gPopUp::GetIF()->OnRButtonDown();
		return;	
	}
}

void gMouse::Release()
{

}