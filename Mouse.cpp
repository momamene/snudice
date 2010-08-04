#include "Mouse.h"
#include "MainWin.h"

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

bool gMouse::MainLoop()
{
	return true;
}

void gMouse::Draw()
{

}

void gMouse::OnLButtonDown()
{

}

void gMouse::OnLButtonUp()
{

}

void gMouse::OnMouseMove()
{

}

void gMouse::OnRButtonDown()
{

}

void gMouse::Release()
{

}