#include "gGameCore.h"

//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------

static gGameCore s_GameCore;

gGameCore *gGameCore::GetIF()
{
	return &s_GameCore;
}

gGameCore::gGameCore()
{

}

gGameCore::~gGameCore()
{

}

bool gGameCore::SetUp()
{
	return true;
}

void gGameCore::MainLoop()
{

}

void gGameCore::Draw()
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