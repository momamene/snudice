#include "gChar.h"
#include "const.h"

//------------------------------------------------------------------------------------
//	Constructor	/	Destructor
//------------------------------------------------------------------------------------

gChar::gChar()
{

}

gChar::~gChar()
{

}

bool gChar::SetUp(CHARDATA data, char *szIllu)
{
	m_Data = data;
	if(FAILED(m_ImgIllu.Load(szIllu))) return false;

	return true;
}

void gChar::Draw()
{

}

void gChar::DrawIllu(RECT rcScr)
{
	RECT	rcImg = {0, 0, IMGILLUSTW, IMGILLUSTH};
	m_ImgIllu.Draw(rcScr, rcImg);
}

void gChar::Release()
{
	m_ImgIllu.Release();
}