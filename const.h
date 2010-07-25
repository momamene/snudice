//------------------------------------------------------------------------------------
//	const.h 18
//------------------------------------------------------------------------------------
#pragma once
#define BIT			32
#define	WNDSIZEW	640
#define WNDSIZEH	480
#define GAMENAME	"SNU Dice"
#define WNDSTYLE	(WS_CAPTION | WS_SYSMENU)

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

#define MAXPLAYER			4			// 최대 플레이어 수

//	Title

//	prev, next btn
#define TITLE_IMG_PREV			".\\Data\\Title\\prev.img"
#define TITLE_IMG_NEXT			".\\Data\\Title\\next.img"
#define TITLE_POS_PREVW			40
#define TITLE_POS_PREVH			40
#define TITLE_POS_PREVX			WNDSIZEW - 100
#define TITLE_POS_PREVY			WNDSIZEH - 50
#define TITLE_POS_NEXTW			40
#define TITLE_POS_NEXTH			40
#define TITLE_POS_NEXTX			WNDSIZEW - 50
#define TITLE_POS_NEXTY			WNDSIZEH - 50


#define TITLE_IMG_TITLE			".\\Data\\Title\\title.img"
//	start button
#define TBT_START_IMG			".\\Data\\Title\\tstart.img"
#define TBT_START_SIZEW			62			// start button 가로
#define TBT_START_SIZEH			20			// start button 세로
#define TBT_START_VERTICAL		false		// 가로로 3개
#define TBT_START_X				40			// 시작 x
#define TBT_START_Y				350			// 시작 y
//	exit button
#define TBT_EXIT_IMG			".\\Data\\Title\\texit.img"
#define TBT_EXIT_SIZEW			62			// EXIT button 가로
#define TBT_EXIT_SIZEH			20			// EXIT button 세로
#define TBT_EXIT_VERTICAL		false		// 가로로 3개
#define TBT_EXIT_X				40			// 시작 x
#define TBT_EXIT_Y				380			// 시작 y
//	Title - playersel
#define PSEL_IMG_BACK			".\\Data\\Title\\playersel_back.img"
#define PSEL_IMG_MODE			".\\Data\\Title\\playersel_mode.img"
#define PSEL_POS_MODEW			417
#define PSEL_POS_MODEH			60
#define PSEL_POS_NPW			120			// 1p 2p .. 가로
#define PSEL_POS_NPH			60			// 1p 2p .. 세로
#define PSEL_IMG_1P				".\\Data\\Title\\playersel_1p.img"
#define PSEL_POS_1PX			50
#define PSEL_POS_1PY			120
#define PSEL_POS_1MODEX			180
#define PSEL_IMG_2P				".\\Data\\Title\\playersel_2p.img"
#define PSEL_POS_2PX			50
#define PSEL_POS_2PY			200
#define PSEL_POS_2MODEX			180
#define PSEL_IMG_3P				".\\Data\\Title\\playersel_3p.img"
#define PSEL_POS_3PX			50
#define PSEL_POS_3PY			280
#define PSEL_POS_3MODEX			180
#define PSEL_IMG_4P				".\\Data\\Title\\playersel_4p.img"
#define PSEL_POS_4PX			50
#define PSEL_POS_4PY			360
#define PSEL_POS_4MODEX			180
#define PSEL_IMG_CHECK			".\\Data\\Title\\check.img"
#define PSEL_POS_CHECKW			70
#define PSEL_POS_CHECKH			70
#define PSEL_POS_CHECKHELPX(i)	( (PSEL_POS_MODEW / 3) * (i - 1) + (PSEL_POS_CHECKW / 2) )		// 사람,컴,안해 모드에 따라 check 출력좌표 돠줌
#define PSEL_POS_CHECKHELPY(i)	( i - 20 )

//	GameCore - charsel
#define CHARDATAFILE			".\\chardat.dat"
#define CHARNUM					16			// 캐릭터 개수
#define CSEL_IMG_BACK			".\\Data\\CharSelect\\charselbg.img"
#define CSEL_POS_IDCARDW		77
#define CSEL_POS_IDCARDH		45
//
//	ㅁ ㅁ ㅁ ㅁ
//    ㅁ ㅁ ㅁ
//	언어계열
#define CSEL_IMG_IDIMG1			".\\Data\\CharSelect\\human.img"		// 인문대
#define CSEL_POS_IDCARDX1		40
#define CSEL_POS_IDCARDY1		80
#define CSEL_IMG_IDIMG2			".\\Data\\CharSelect\\society.img"		// 사회대
#define CSEL_POS_IDCARDX2		40 + 90
#define CSEL_POS_IDCARDY2		80
#define CSEL_IMG_IDIMG3			".\\Data\\CharSelect\\venture.img"		// 경영대
#define CSEL_POS_IDCARDX3		40 + 90 * 2
#define CSEL_POS_IDCARDY3		80
#define CSEL_IMG_IDIMG4			".\\Data\\CharSelect\\law.img"			// 법대
#define CSEL_POS_IDCARDX4		40 + 90 * 3
#define CSEL_POS_IDCARDY4		80
#define CSEL_IMG_IDIMG5			".\\Data\\CharSelect\\live.img"			// 생활과학대
#define CSEL_POS_IDCARDX5		70
#define CSEL_POS_IDCARDY5		80 + 60
#define CSEL_IMG_IDIMG6			".\\Data\\CharSelect\\teach.img"		// 사범대
#define CSEL_POS_IDCARDX6		70 + 100
#define CSEL_POS_IDCARDY6		80 + 60
#define CSEL_IMG_IDIMG7			".\\Data\\CharSelect\\free.img"			// 자유전공
#define CSEL_POS_IDCARDX7		70 + 100 * 2
#define CSEL_POS_IDCARDY7		80 + 60
//	수리계열
#define CSEL_IMG_IDIMG8			".\\Data\\CharSelect\\engine.img"		// 공대
#define CSEL_POS_IDCARDX8		40
#define CSEL_POS_IDCARDY8		230
#define CSEL_IMG_IDIMG9			".\\Data\\CharSelect\\nature.img"		// 자연대
#define CSEL_POS_IDCARDX9		40 + 90
#define CSEL_POS_IDCARDY9		230
#define CSEL_IMG_IDIMG10		".\\Data\\CharSelect\\doctor.img"		// 의대
#define CSEL_POS_IDCARDX10		40 + 90 * 2
#define CSEL_POS_IDCARDY10		230
#define CSEL_IMG_IDIMG11		".\\Data\\CharSelect\\animal.img"		// 수의대
#define CSEL_POS_IDCARDX11		40 + 90 * 3
#define CSEL_POS_IDCARDY11		230
#define CSEL_IMG_IDIMG12		".\\Data\\CharSelect\\parm.img"			// 약대
#define CSEL_POS_IDCARDX12		70
#define CSEL_POS_IDCARDY12		230 + 60
#define CSEL_IMG_IDIMG13		".\\Data\\CharSelect\\nurse.img"		// 간호대
#define CSEL_POS_IDCARDX13		70 + 100
#define CSEL_POS_IDCARDY13		230 + 60
#define CSEL_IMG_IDIMG14		".\\Data\\CharSelect\\farm.img"			// 농대
#define CSEL_POS_IDCARDX14		70 + 100 * 2
#define CSEL_POS_IDCARDY14		230 + 60
//	예술계열
#define CSEL_IMG_IDIMG15		".\\Data\\CharSelect\\music.img"		// 음대
#define CSEL_POS_IDCARDX15		100
#define CSEL_POS_IDCARDY15		380
#define CSEL_IMG_IDIMG16		".\\Data\\CharSelect\\art.img"			// 미대
#define CSEL_POS_IDCARDX16		220
#define CSEL_POS_IDCARDY16		380
//	캐릭터일러표시
#define CSEL_POS_ILLUW			120
#define CSEL_POS_ILLUH			180
#define CSEL_POS_ILLUX			450
#define CSEL_POS_ILLUY			60
//	캐릭터정보표시
#define CSEL_POS_CHARINFOX		420
#define CSEL_POS_CHARINFOY		270
//	누구턴이냐
#define CSEL_IMG_PLAYER			".\\Data\\CharSelect\\player.img"
#define CSEL_POS_PLAYERW		90
#define CSEL_POS_PLAYERH		25
#define CSEL_POS_PLAYERX		480
#define CSEL_POS_PLAYERY		15

// CharManager
// Char
#define IMGILLUSTW			500
#define IMGILLUSTH			800

// gMouse.h - sangwoo
#define MINMOVE				20

// Interface
#define IF_IMG_MENUBACK		".\\Data\\Interface\\menu_back.img"
#define	IF_POS_MENUBACKX	20
#define IF_POS_MENUBACKY	0
#define IF_POS_MENUBTNW		49		//수강, 아이템, 시스템
#define IF_POS_MENUBTNH		49
#define IF_IMG_SUGANG		".\\Data\\Interface\\menu_btn_sugang.img"
#define IF_POS_SUGANGX		IF_POS_MENUBACKX + 276
#define IF_POS_SUGANGY		IF_POS_MENUBACKY + 19
#define IF_IMG_ITEM			".\\Data\\Interface\\menu_btn_item.img"
#define IF_POS_ITEMX		IF_POS_MENUBACKX + 331
#define IF_POS_ITEMY		IF_POS_MENUBACKY + 5
#define IF_IMG_SYSTEM		".\\Data\\Interface\\menu_btn_system.img"
#define IF_POS_SYSTEMX		IF_POS_MENUBACKX + 387
#define	IF_POS_SYSTEMY		IF_POS_MENUBACKY + 9


#define	IF_POS_SCARDW		484		// scard, menu_sysback, menu_itemback, menu_sugangback...
#define IF_POS_SCARDH		287
#define IF_IMG_ITEMBACK		".\\Data\\Interface\\menu_item_back.img"
#define IF_IMG_SUGANGBACK	".\\Data\\Interface\\menu_sugang_back.img"
#define IF_IMG_SYSBACK		".\\Data\\Interface\\menu_system_back.img"
#define IF_POS_BACKX		((WNDSIZEW - IF_POS_SCARDW) / 2)
#define IF_POS_BACKY		((WNDSIZEH - IF_POS_SCARDH) / 2)