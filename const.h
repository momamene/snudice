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
#define TITLE_IMG_TITLE		"title.img"
//	start button
#define TBT_START_IMG		"tstart.img"
#define TBT_START_SIZEW		62			// start button 가로
#define TBT_START_SIZEH		20			// start button 세로
#define TBT_START_VERTICAL	false		// 가로로 3개
#define TBT_START_X			40			// 시작 x
#define TBT_START_Y			350			// 시작 y
//	exit button
#define TBT_EXIT_IMG		"texit.img"
#define TBT_EXIT_SIZEW		62			// EXIT button 가로
#define TBT_EXIT_SIZEH		20			// EXIT button 세로
#define TBT_EXIT_VERTICAL	false		// 가로로 3개
#define TBT_EXIT_X			40			// 시작 x
#define TBT_EXIT_Y			380			// 시작 y
//	Title - charsell
#define CHARSELBGFILE		"charsel.img"
#define CHARIDCARDW			100			// 캐릭터선택모드에서 그리는 캐릭터 학생증카드
#define CHARIDCARDH			60
#define CHAEDATAFILE		"chardat.dat"
#define CHARNUM				16			// 캐릭터 개수
#define IDCARDIMG1			"charselid1.img"
#define IDCARDIMG2			"charselid2.img"
#define IDCARDIMG3			"charselid3.img"
#define IDCARDIMG4			"charselid4.img"
#define IDCARDIMG5			"charselid5.img"
#define IDCARDIMG6			"charselid6.img"
#define IDCARDIMG7			"charselid7.img"
#define IDCARDIMG8			"charselid8.img"
#define IDCARDIMG9			"charselid9.img"
#define IDCARDIMG10			"charselid10.img"
#define IDCARDIMG11			"charselid11.img"
#define IDCARDIMG12			"charselid12.img"
#define IDCARDIMG13			"charselid13.img"
#define IDCARDIMG14			"charselid14.img"
#define IDCARDIMG15			"charselid15.img"
#define IDCARDIMG16			"charselid16.img"
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
#define SELCHARIMGY			50


// CharManager
// Char
#define IMGILLUSTW			500
#define IMGILLUSTH			800
