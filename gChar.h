//------------------------------------------------------------------------------------
//	gChar Class
//
//	2010. 07. 17	CoderK
//
//	ĳ���� 
//------------------------------------------------------------------------------------
#pragma once
#include "gImage.h"

// chardat.dat ���Ͽ��� �޴� ����Ÿ
enum eSEX
{
	ESEX_MALE,
	ESEX_FEMALE,
};

struct CHARDATA
{
	char	szColleage[32];
	char	szName[32];
	eSEX	eSex;
	int		nLang;
	int		nMath;
	int		nArt;
	int		nStamina;
	int		nMove;
	char	szComment[256];
	// illu imgfile
};

class gChar  
{
public:
	gChar();
	virtual ~gChar();
public:
	gImage		m_ImgIllu;
	CHARDATA	m_Data;

	bool		SetUp(CHARDATA data, char *szIllu);
	void		Draw();
	void		DrawIllu(RECT rcScr);

	void		Release();
};

