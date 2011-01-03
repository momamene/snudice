#include "Mouse.h"
#include "MainWin.h"
#include "PopUp.h"
#include "LoginCore.h"
#include "BattleNetCore.h"
#include "SubmitCore.h"
#include "RoomCore.h"
#include "GameCore.h"
#include "PlaySoundCore.h"

#define MOUSEIMG			".\\Data\\Interface\\mouse.img"
#define MOUSESIZEW			25
#define MOUSESIZEH			25

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
	if(!m_ImgMouse.Load(MOUSEIMG))
		return false;

	m_modeMouse = MM_DEFAULT1;
	m_bShow = true;		// true는 setup하기위해서. m_bShow != bShow 비교떄메
	SetShow(false);
	return true;
}

// 이넘의 mainloop 에서는 추후에 마우스가 깜빡인다던지 그럴때 활용
void gMouse::MainLoop()
{
	Draw();
}

void gMouse::Draw()
{
	RECT	rcDest, rcSour;

	SetRect(&rcDest,
		0, 0, MOUSESIZEW, MOUSESIZEH);
	rcSour = rcDest;
	OffsetRect(&rcDest,
		m_nPosX, m_nPosY);
	OffsetRect(&rcSour,
		0, m_modeMouse * MOUSESIZEH);

	m_ImgMouse.Draw(rcDest, rcSour, false);
}

void gMouse::OnLButtonDown()
{
	gPlaySoundCore::GetIF()->PlayEffectSound(EFFECT_FILE_8);

	m_modeMouse = MM_DEFAULT2;

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
	m_modeMouse = MM_DEFAULT1;

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
	gPlaySoundCore::GetIF()->PlayEffectSound(EFFECT_FILE_9);

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
	m_ImgMouse.Release();
}

void gMouse::SetShow(bool show)
{
	if(m_bShow != show)
	{
		ShowCursor(show);
		m_bShow = show;
	}
}

bool gMouse::Restore()
{
	if(!m_ImgMouse.Restore())
		return false;

	return true;
}