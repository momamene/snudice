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

bool gChar::SetUp(CHARDATA data, char *szIllu, char *szDot)
{
	m_Data = data;
	if(FAILED(m_ImgIllu.Load(szIllu))) return false;
	if(FAILED(m_ImgDot.Load(szDot))) return false;

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

void gChar::DrawDot(RECT rcScr,int dotConX, int dotConY)	// 0~2, 0~3 까지의 숫자만 입력하세요.
{
	int FULLX = 70;
	int FULLY = 130;
	RECT	rcImg = {dotConX*FULLX, dotConY*FULLY, (dotConX+1)*FULLX, (dotConY+1)*FULLY};
	m_ImgDot.Draw(rcScr, rcImg, false);
}

void gChar::Release()
{
	m_ImgIllu.Release();
	m_ImgDot.Release();
}