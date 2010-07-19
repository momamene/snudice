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

//	Title
#define TITLE_IMG_TITLE		".\\Data\\Title\\title.img"
//	start button
#define TBT_START_IMG		".\\Data\\Title\\tstart.img"
#define TBT_START_SIZEW		62			// start button 가로
#define TBT_START_SIZEH		20			// start button 세로
#define TBT_START_VERTICAL	false		// 가로로 3개
#define TBT_START_X			40			// 시작 x
#define TBT_START_Y			350			// 시작 y
//	exit button
#define TBT_EXIT_IMG		".\\Data\\Title\\texit.img"
#define TBT_EXIT_SIZEW		62			// EXIT button 가로
#define TBT_EXIT_SIZEH		20			// EXIT button 세로
#define TBT_EXIT_VERTICAL	false		// 가로로 3개
#define TBT_EXIT_X			40			// 시작 x
#define TBT_EXIT_Y			380			// 시작 y
//	Title - charsell
#define CHARSELBGFILE		".\\Data\\Title\\charselbg.img"
#define CHARIDCARDW			100			// 캐릭터선택모드에서 그리는 캐릭터 학생증카드
#define CHARIDCARDH			60
#define CHAEDATAFILE		"chardat.dat"
#define CHARNUM				16			// 캐릭터 개수
#define IDCARDIMG1			".\\Data\\Title\\charselid1.img"
#define IDCARDIMG2			".\\Data\\Title\\charselid2.img"
#define IDCARDIMG3			".\\Data\\Title\\charselid3.img"
#define IDCARDIMG4			".\\Data\\Title\\charselid4.img"
#define IDCARDIMG5			".\\Data\\Title\\charselid5.img"
#define IDCARDIMG6			".\\Data\\Title\\charselid6.img"
#define IDCARDIMG7			".\\Data\\Title\\charselid7.img"
#define IDCARDIMG8			".\\Data\\Title\\charselid8.img"
#define IDCARDIMG9			".\\Data\\Title\\charselid9.img"
#define IDCARDIMG10			".\\Data\\Title\\charselid10.img"
#define IDCARDIMG11			".\\Data\\Title\\charselid11.img"
#define IDCARDIMG12			".\\Data\\Title\\charselid12.img"
#define IDCARDIMG13			".\\Data\\Title\\charselid13.img"
#define IDCARDIMG14			".\\Data\\Title\\charselid14.img"
#define IDCARDIMG15			".\\Data\\Title\\charselid15.img"
#define IDCARDIMG16			".\\Data\\Title\\charselid16.img"
#define IDCARDX1			50
#define IDCARDY1			50
#define IDCARDX2			50 + 120
#define IDCARDY2			50
#define IDCARDX3			50 + 240		
#define IDCARDY3			50
#define IDCARDX4			50
#define IDCARDY4			50 + 70
#define IDCARDX5			50 + 120			
#define IDCARDY5			50 + 70
#define IDCARDX6			50 + 240
#define IDCARDY6			50 + 70
#define IDCARDX7			50
#define IDCARDY7			50 + 140
#define IDCARDX8			50 + 120			
#define IDCARDY8			50 + 140
#define IDCARDX9			50 + 240
#define IDCARDY9			50 + 140
#define IDCARDX10			50			
#define IDCARDY10			50 + 210
#define IDCARDX11			50 + 120			
#define IDCARDY11			50 + 210
#define IDCARDX12			50 + 240	
#define IDCARDY12			50 + 210
#define IDCARDX13			50
#define IDCARDY13			50 + 280
#define IDCARDX14			50 + 120
#define IDCARDY14			50 + 280
#define IDCARDX15			50 + 240			
#define IDCARDY15			50 + 280
#define IDCARDX16			50
#define IDCARDY16			50 + 350
#define SELCHARIMGW			400
#define SELCHARIMGH			240
#define SELCHARIMGX			430
#define SELCHARIMGY			30
#define CHARINFOX			420
#define CHARINFOY			270

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


#define	IF_POS_SCARDW		484
#define IF_POS_SCARDH		287
