//------------------------------------------------------------------------------------
//	coreconst.h
//
//	2010. 08. 04	CoderK	
//
//	core��� ���� define
//------------------------------------------------------------------------------------
#pragma once

enum eCOREMODE
{
	ECM_TITLE,				// Ÿ��Ʋ
	ECM_PSEL,				// �÷��̾� ����
	ECM_CSEL,				// ĳ���� ����
	ECM_SUBMIT,				// ������û
	ECM_GAME,				// ����
};

// ECM_TITLE
#define TITLE_FILE_BACK			".\\Data\\Title\\title.img"

// start
#define TITLE_FILE_STARTBTN		".\\Data\\Title\\tstart.img"
#define TITLE_SIZE_STARTBTNW	62
#define TITLE_SIZE_STARTBTNH	20
#define TITLE_VERT_STARTBTN		false
#define TITLE_POS_STARTBTNX		40
#define TITLE_POS_STARTBTNY		350

// exit
#define TITLE_FILE_EXITBTN		".\\Data\\Title\\texit.img"
#define TITLE_SIZE_EXITBTNW		62
#define TITLE_SIZE_EXITBTNH		20
#define TITLE_VERT_EXITBTN		false
#define TITLE_POS_EXITBTNX		40
#define TITLE_POS_EXITBTNY		380