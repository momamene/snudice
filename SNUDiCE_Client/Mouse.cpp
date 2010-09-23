#include "Mouse.h"
#include "MainWin.h"
#include "PopUp.h"
#include "LoginCore.h"
#include "BattleNetCore.h"
#include "SubmitCore.h"
#include "RoomCore.h"
#include "GameCore.h"

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

// 이넘의 mainloop 에서는 추후에 마우스가 깜빡인다던지 그럴때 활용
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
		case ECM_BATTLENET:
			gBattleNetCore::GetIF()->OnLButtonDown();
			break;
		case ECM_ROOMMAKE: case ECM_ROOMJOIN: case ECM_ROOM:
			gRoomCore::GetIF()->OnLButtonDown();
			break;
		case ECM_SUBMIT:
			gSubmitCore::GetIF()->OnLButtonDown();
			break;
		case ECM_GAME:
			gGameCore::GetIF()->OnLButtonDown();
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

	switch(gMainWin::GetIF()->m_eCoreMode)
	{
		case ECM_LOGIN:
			gLoginCore::GetIF()->OnLButtonUp();
			break;
		case ECM_BATTLENET:
			gBattleNetCore::GetIF()->OnLButtonUp();
			break;
		case ECM_ROOMMAKE: case ECM_ROOMJOIN: case ECM_ROOM:
			gRoomCore::GetIF()->OnLButtonUp();
			break;
		case ECM_SUBMIT:
			gSubmitCore::GetIF()->OnLButtonUp();
			break;
		case ECM_GAME:
			gGameCore::GetIF()->OnLButtonUp();
			break;
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
		case ECM_BATTLENET:
			gBattleNetCore::GetIF()->OnMouseMove();
			break;
		case ECM_ROOMMAKE: case ECM_ROOMJOIN: case ECM_ROOM:
			gRoomCore::GetIF()->OnMouseMove();
			break;
		case ECM_SUBMIT:
			gSubmitCore::GetIF()->OnMouseMove();
			break;
		case ECM_GAME:
			gGameCore::GetIF()->OnMouseMove();
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

	switch(gMainWin::GetIF()->m_eCoreMode)
	{
		case ECM_LOGIN:
			gLoginCore::GetIF()->OnRButtonDown();
			break;
		case ECM_BATTLENET:
			gBattleNetCore::GetIF()->OnRButtonDown();
			break;
		case ECM_ROOMMAKE: case ECM_ROOMJOIN: case ECM_ROOM:
			gRoomCore::GetIF()->OnRButtonDown();
			break;
		case ECM_SUBMIT:
			gSubmitCore::GetIF()->OnRButtonDown();
			break;
		case ECM_GAME:
			gGameCore::GetIF()->OnRButtonDown();
			break;
	}
}

void gMouse::Release()
{

}