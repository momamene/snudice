#include "Map.h"
#include "MainWin.h" // ��ġ ���� ���� �޽��ϴ�.
#include "SubjectContainer.h"
#include "Chat.h"
#include "SubmitCore.h"
#include "PlayerContainer.h"
#include "UIGame.h"
#include "GameCore.h"

#define TILENUM					9

#define MAPFILE					".\\Data\\map.xy"

#define MAPFILEIMG				".\\Data\\Map\\mapbg.img"
#define BACKMAPX				2255
#define BACKMAPY				1639

#define TILE_FOOD_IMG			".\\Data\\Map\\food.img"
#define TILE_CARD_IMG			".\\Data\\Map\\card.img"
#define TILE_NOKDU_IMG			".\\Data\\Map\\nokdu.img"
#define TILE_BUS_IMG			".\\Data\\Map\\bus.img"
#define TILE_MAINGATE_IMG		".\\Data\\Map\\maingate.img"
#define TILE_MOUNTAIN_IMG		".\\Data\\Map\\mountain.img"
#define TILE_LANG_IMG			".\\Data\\Map\\lang.img"
#define TILE_MATH_IMG			".\\Data\\Map\\math.img"
#define TILE_ART_IMG			".\\Data\\Map\\art.img"
//#define TILE_TITLE_IMG		".\\Data\\Map\\title.img"

#define TILE_SMALLTILE			".\\Data\\Map\\smallmapchip.img"

#define BUSGLOWTICK				600


#define	CURSORSMALL_FILE		".\\Data\\Interface\\map_cursor_small.img"
#define CURSORSMALL_SIZE_W		8
#define CURSORSMALL_SIZE_H		7

#define	CURSORBIG_FILE			".\\Data\\Interface\\map_cursor_big.img"
#define CURSORBIG_SIZE_W		12
#define CURSORBIG_SIZE_H		11

void gTile::init(int xo,int yo)
{
	tileType	= TY_NONE;
	ptPos.x		= xo;
	ptPos.y		= yo;
	prevTile.x	= -1;
	prevTile.y	= -1;
	nextTile.x	= -1;
	nextTile.y	= -1;
	flag1		= 0;
	flag2		= 0;
	memset(college, 0, sizeof(college));
	memset(building, 0, sizeof(building));
	memset(subject, 0, sizeof(subject));
}

static gMap s_tileContainer; // 2

gMap *gMap::GetIF() // 3
{
	return &s_tileContainer;
}


// 1. Setup Line

bool gMap::Setup()
{
	if(!m_ImgMapBG.Load(MAPFILEIMG))
		return false;

	for(int i = 0 ; i < LINEX ; i++)
	{
		for (int j = 0 ; j < LINEY ; j++)
		{
			tileMap[i * LINEY + j].init(i, j);
		}
	}

	if(!m_ImgTile[0].Load(TILE_FOOD_IMG))
		return false;

	if(!m_ImgTile[1].Load(TILE_CARD_IMG))
		return false;

	if(!m_ImgTile[2].Load(TILE_NOKDU_IMG))
		return false;

	if(!m_ImgTile[3].Load(TILE_BUS_IMG))
		return false;

	if(!m_ImgTile[4].Load(TILE_MAINGATE_IMG))
		return false;

	if(!m_ImgTile[5].Load(TILE_MOUNTAIN_IMG))
		return false;

	if(!m_ImgTile[6].Load(TILE_LANG_IMG))
		return false;

	if(!m_ImgTile[7].Load(TILE_MATH_IMG))
		return false;

	if(!m_ImgTile[8].Load(TILE_ART_IMG))
		return false;

//	if(!m_ImgTileBack.Load(TILE_TITLE_IMG))
//		return false;

	if(!m_ImgSmallTile.Load(TILE_SMALLTILE))
		return false;
	
	m_xSpacePos			= -1;
	m_ySpacePos			= -1;
	m_Next_xSpacePos	= -1;
	m_Next_ySpacePos	= -1;
	m_nAbsDrawlineX		= 0;
	m_nAbsDrawlineY		= 0;

	Load();
	
	posSetter(m_xInitSpacePos, m_yInitSpacePos);


	// map cursor
	if(!m_ImgCurSmall.Load(CURSORSMALL_FILE))
		return false;
	if(!m_ImgCurBig.Load(CURSORBIG_FILE))
		return false;

	return true;
}

void gMap::Clear()
{
	posSetter(m_xInitSpacePos, m_yInitSpacePos);
}


void gMap::LoadFileToBKS()
{
	int		i;
		
	hFile = CreateFile(MAPFILE, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		ReadFile(hFile, &count, sizeof(int), &dw, NULL);
		for(i = 0 ; i < count ; i++){
			memset(&bmpKindSavor[i], 0, sizeof(gTile));
			ReadFile(hFile, &bmpKindSavor[i], sizeof(gTile), &dw, NULL);
		}
	}
	CloseHandle(hFile);
}

void gMap::LoadBKSToTM()
{
	gMainWin *gmainWin = gMainWin::GetIF(); // temp
	gSubjectContainer *gSC = gSubjectContainer::GetIF();
	int i;
	m_xInitSpacePos	= -1;
	m_yInitSpacePos	= -1;

	int localcount = 0;
	for(i = 0 ; i < MAXSAVOR_N ; i++)
		memset(&tileMap[i],0,sizeof(gTile));
	for(i = 0 ; i < LINEX ; i++)
	{
		for (int j = 0 ; j < LINEY ; j++)
		{
			if(i == bmpKindSavor[localcount].ptPos.x && j == bmpKindSavor[localcount].ptPos.y)
			{
				tileMap[i*LINEY+j] = bmpKindSavor[localcount];
				localcount++;
				if(tileMap[i*LINEY+j].tileType==TY_MAINGATE)
				{
					m_xInitSpacePos = i;
					m_yInitSpacePos = j;
				}
				else if (tileMap[i*LINEY+j].tileType==TY_CLASS)
				{
					gSC->putSubject(tileMap[i*LINEY+j],i*LINEY+j);
				}
				
			}
			else tileMap[i*LINEY+j].init(i,j);
		}
	}
	if(m_xInitSpacePos == -1 && m_yInitSpacePos == -1)
	{
		OutputDebugString("Tile Info Error : There is no MainGate\n");
		MessageBox(gmainWin->m_hWnd, "Tile Info Error : There is no MainGate", "Error", MB_OK);
		// temp
	}
}

void gMap::Load()
{
	LoadFileToBKS();
	LoadBKSToTM();
}

// 1. Setup Line End


// 2. Draw Line Start

void gMap::DrawHexagonOne(int x0, int y0, int i, int j, int n, int playerIdx, bool boolo, int type)
{
//	gGameCore *gameCore = gGameCore::GetIF();
	gPlayerContainer	*pc = gPlayerContainer::GetIF();
	
	int		k;
	RECT	a;
	RECT	b;

	k = tileMap[i*LINEY+j].tileType;

	if(k == TY_NONE)
		return;
	
	if(i%2 == 0)
	{
		a.left	= WIDEX * i/2;
		a.top	= FULLY * j;
	}
	else
	{
		a.left	= LEFTX + MIDDLEX + WIDEX * (i - 1) / 2;
		a.top	= HALFY + FULLY * j;
	}
	if(n == 1)
	{
		/*
		a.left -= gameCore->m_xPos;
		a.top -= gameCore->m_yPos;
		*/
		// sangwoo temp
		a.left	-= m_nAbsDrawlineX;
		a.top	-= m_nAbsDrawlineY;
		//
	}
	
	a.left	/= n;
	a.top	/= n;
	a.left	+= x0;
	a.top	+= y0;
	a.right = a.left + FULLX / n;
	a.bottom = a.top + FULLY / n;
	
	
	if(!type)
		SetRect(&b, 0, 0, FULLX, FULLY);
	else
		SetRect(&b, FULLX, 0, FULLX * 2, FULLY);
	
	if(k == TY_CLASS)
	{
		if(strlen(pc->m_GPlayerList[playerIdx].szID) != 0)
		{
			for(int c = 0; c < MAXSUBJECT; c++)
			{
				if(tileMap[i * LINEY + j].flag2 == pc->m_GPlayerList[playerIdx].bySubIdx[c])
				{
					OffsetRect(&b, FULLX, 0);
					break;
				}
			}
		}
		m_ImgTile[  k + tileMap[i * LINEY + j].flag1  ].Draw(a, b, boolo);
	}
	else
	{
		if(k == TY_BUS && n == 1)
		{
			static int	bustick		= GetTickCount();
			static bool	bGlow		= false;
			if(gGameCore::GetIF()->m_bBusSel)
			{
				if(GetTickCount() - bustick > BUSGLOWTICK)
				{
					bGlow = !bGlow;
					bustick = GetTickCount();
				}

				if(bGlow)
					OffsetRect(&b, FULLX, 0);
			}
		}
		m_ImgTile[k].Draw(a, b, boolo);
	}
}

void gMap::DrawHexagon(int x0, int y0, int n, int playerIdx, bool boolo)
{
	int i, j;

	
	for(i = 0 ; i < LINEX ; i++)
	{ 
		for(j = 0 ; j < LINEY ; j++)
		{
			DrawHexagonOne(x0, y0, i, j, n, playerIdx, boolo);
		}
	}
}

#define SMALLFULLX 13
#define SMALLFULLY 10

void gMap::DrawHexagonSubmitOne(int x0, int y0, int i, int j, int n, int classtype, int statetype)
{
	// classtype 0 : ���
	// classtype 1 : ����
	// classtype 2 : ��ü��
	// classtype 3 : nothing.
	// statetype 0 : basic
	// statetype 0,1 : ��������
	// statetype 2 : ����!

	//	gGameCore *gameCore = gGameCore::GetIF();

	int		k;
	RECT	a;
	RECT	b;

	k = tileMap[i*LINEY+j].tileType;

	if(k == TY_NONE)
		return;

	if(i%2 == 0) {
		a.left	= WIDEX * i/2;
		a.top	= FULLY * j;
	}
	else {
		a.left	= LEFTX + MIDDLEX + WIDEX * (i - 1) / 2;
		a.top	= HALFY + FULLY * j;
	}

	a.left	/= n;
	a.top	/= n;
	a.left	+= x0;
	a.top	+= y0;
	a.right = a.left + FULLX / n;
	a.bottom = a.top + FULLY / n;


	if(classtype==3) {
		SetRect(&b,0,0,SMALLFULLX,SMALLFULLY);
	}
	else {
		SetRect(&b,0,(classtype*3+statetype+1)*SMALLFULLY,
			SMALLFULLX,(classtype*3+statetype+2)*SMALLFULLY);
	}

	m_ImgSmallTile.Draw(a,b,false);
}

void gMap::DrawHexagonMinimapOne(int x0, int y0, int i, int j, int n, int classtype, int statetype)
{
	int		k;
	RECT	a;
	RECT	b;

	k = tileMap[i*LINEY+j].tileType;

	if(k == TY_NONE)
		return;

	if(i%2 == 0) {
		a.left	= WIDEX * i/2;
		a.top	= FULLY * j;
	}
	else {
		a.left	= LEFTX + MIDDLEX + WIDEX * (i - 1) / 2;
		a.top	= HALFY + FULLY * j;
	}

	a.left	/= n;
	a.top	/= n;
	a.left	+= x0;
	a.top	+= y0;
	a.right = a.left + FULLX / n;
	a.bottom = a.top + FULLY / n;


	if(classtype==3) {
		SetRect(&b,0,0,SMALLFULLX,SMALLFULLY);
	}
	else {
		SetRect(&b,0,(classtype*3+statetype+1)*SMALLFULLY,
			SMALLFULLX,(classtype*3+statetype+2)*SMALLFULLY);
	}

	m_ImgSmallTile.Draw(a,b);
}

void gMap::DrawMinimap(int x0, int y0, int n)
{
	gSubmitCore *gSC = gSubmitCore::GetIF();

	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	int nMyInRoomIndex = gPC->GetMyPIndex();
	int nSubjectIndexInTempTile;		// �� Ÿ���� ������ subjectIndex;
	bool bTemp;
	static int tick = GetTickCount(), state=0;
	static int state2 = 2;

	for(int i = 0 ; i < LINEX ; i++)
	{ 
		for(int j = 0 ; j < LINEY ; j++)
		{
			if(tileMap[i*LINEY+j].tileType==TY_NONE) 
				continue;
			else if(tileMap[i*LINEY+j].tileType!=TY_CLASS) 
				DrawHexagonMinimapOne(x0, y0, i, j, n, 3, 0);
			else {
				nSubjectIndexInTempTile = tileMap[i*LINEY+j].flag2;

				bTemp = false;
				for(int k = 0 ; k < CLASSSEAT ; k++) {
					if(gSC->m_subject[nSubjectIndexInTempTile][k] == nMyInRoomIndex) bTemp = true;
				}

				if(bTemp) {
					DrawHexagonMinimapOne(x0, y0, i, j, n, tileMap[i*LINEY+j].flag1, 2);
				}
				else
					DrawHexagonMinimapOne(x0, y0, i, j, n, tileMap[i*LINEY+j].flag1, 0);
			}
		}
	}
	DrawMiniMapCursor(n, x0, y0);
}

void gMap::DrawSubmit(int x0, int y0, int n, int subjectIndex, int frameOn) // frameOn = false �� �⺻ setting
{
	gSubmitCore *gSC = gSubmitCore::GetIF();	// ���õ� list
	//	list 2 : gSC->m_subject �� �������.
	//  list 1 : ������ ����̰�, ������ ������... �̷��� tileMap�� �ְ���...

	gPlayerContainer *gPC = gPlayerContainer::GetIF();
	int nMyInRoomIndex = gPC->GetMyPIndex();
	int nSubjectIndexInTempTile;		// �� Ÿ���� ������ subjectIndex;
	bool bTemp;
	static int tick = GetTickCount(), state=0;
	static int state2 = 2;

	for(int i = 0 ; i < LINEX ; i++)
	{ 
		for(int j = 0 ; j < LINEY ; j++)
		{
			if(tileMap[i*LINEY+j].tileType==TY_NONE) 
				continue;
			else if(tileMap[i*LINEY+j].tileType!=TY_CLASS) 
				DrawHexagonSubmitOne(x0, y0, i, j, n, 3, 0);
			else {
				nSubjectIndexInTempTile = tileMap[i*LINEY+j].flag2;

				bTemp = false;
				for(int k = 0 ; k < CLASSSEAT ; k++) {
					if(gSC->m_subject[nSubjectIndexInTempTile][k] == nMyInRoomIndex) bTemp = true;
				}

				if(bTemp) {
					if(subjectIndex == nSubjectIndexInTempTile) {
						if(GetTickCount() - tick > 300) { //Sung Managed Here!
							state2 = 3 - state2;
							tick = GetTickCount();
						}
						DrawHexagonSubmitOne(x0, y0, i, j, n, tileMap[i*LINEY+j].flag1, state2);
					}
					else 
						DrawHexagonSubmitOne(x0, y0, i, j, n, tileMap[i*LINEY+j].flag1, 2);
				}
				else if (subjectIndex >= 0 && subjectIndex == nSubjectIndexInTempTile) {
					if(GetTickCount() - tick > 300) {
						state = 1 - state;     //Modified
						tick = GetTickCount(); //By Sung
					}
					DrawHexagonSubmitOne(x0, y0, i, j, n, tileMap[i*LINEY+j].flag1, state);
				}
				else
					DrawHexagonSubmitOne(x0, y0, i, j, n, tileMap[i*LINEY+j].flag1, 0);
			}
		}
	}
}

void gMap::Edge()
{
	if(m_nAbsDrawlineX < 0)
		m_nAbsDrawlineX = 0;
	if(m_nAbsDrawlineY < 0)
		m_nAbsDrawlineY = 0;
	if(m_nAbsDrawlineX > BACKMAPX - WNDSIZEW) 
		m_nAbsDrawlineX = BACKMAPX - WNDSIZEW;
	if(m_nAbsDrawlineY > BACKMAPY - WNDSIZEH) 
		m_nAbsDrawlineY = BACKMAPY - WNDSIZEH;
}

void gMap::Draw()
{
	int n = 1; // �����
//	int start_x = m_nAbsDrawlineX;
//	int start_y = m_nAbsDrawlineY;
//	m_ImgTileBack.Draw(0, 0);

	RECT	rcDest, rcSour;

//	float	fRateX, fRateY;
//	fRateX = m_ImgMapBG.m_nWidth / WNDSIZEW;
//	fRateY = m_ImgMapBG.m_nHeight / WNDSIZEH;

	SetRect(&rcDest,
		0, 0, WNDSIZEW, WNDSIZEH);
	rcSour = rcDest;

	Edge();

	OffsetRect(&rcSour,
		m_nAbsDrawlineX, m_nAbsDrawlineY);

	m_ImgMapBG.Draw(rcDest, rcSour, false);
	
	DrawHexagon(0, 0, n, gPlayerContainer::GetIF()->GetMyGPIndex());

}

void gMap::DrawMap()
{
	DrawHexagon(235, 105, 6, gUIGame::GetIF()->m_nCharSelected, true);
	DrawMapCursor(6, 235, 105);
}

// 2. Draw Line End


// 3. pos Line Start
// posSpacor() - start, posMovor() - On, posStoper() - End

void gMap::posSetter(int xSpacePos, int ySpacePos)
{
	m_xSpacePos = xSpacePos;
	m_ySpacePos = ySpacePos;
	posMover();
}

void gMap::posSpacor(bool isNokdu)
{
	if(isNokdu && m_xSpacePos == m_xInitSpacePos && m_ySpacePos == m_yInitSpacePos)
	{
		m_Next_xSpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].flag1; // gplayerManager->m_player[gameCore->m_turnPlayer]->m_charInfo;
		m_Next_ySpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].flag2; // gplayerManager->m_player[gameCore->m_turnPlayer];
	}
	else
	{
		m_Next_xSpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.x;	// �⺻ ��ħ��, Next�� Now�� ������ �ִ� ��Ȳ�� �����̴� ��Ȳ�� ���̴�.
		m_Next_ySpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.y;
	}
	posMover();
}

void gMap::posSpacor(int xNextSpacePos, int yNextSpacePos)
{
	m_Next_xSpacePos = xNextSpacePos;
	m_Next_ySpacePos = yNextSpacePos;
	posMover();
}

void gMap::posMover ()
{
	POINT a;

	a.x	= m_xSpacePos;
	a.y	= m_ySpacePos;
	a	= conToAbs(a);
	m_nAbsDrawlineX = a.x - WNDSIZEW/2 + HALFX;
	m_nAbsDrawlineY = a.y - WNDSIZEH/2 + HALFY;
}

void gMap::posMover(int frame,int frameN)
{
	POINT b, a;
	b.x = m_Next_xSpacePos;
	b.y = m_Next_ySpacePos;
	a.x = m_xSpacePos;
	a.y = m_ySpacePos;
	b = conToAbs(b);
	a = conToAbs(a);
	b.x = b.x - WNDSIZEW/2 + HALFX;
	b.y = b.y - WNDSIZEH/2 + HALFY;
	a.x = a.x - WNDSIZEW/2 + HALFX;
	a.y = a.y - WNDSIZEH/2 + HALFY;

	m_nAbsDrawlineX = a.x + frame * (b.x - a.x) / frameN;
	m_nAbsDrawlineY = a.y + frame * (b.y - a.y) / frameN;
}


void gMap::posStoper()
{
	m_xSpacePos = m_Next_xSpacePos;	// �⺻ ��ħ�� Next�� Now�� ���� ��Ȳ�� ���� ��Ȳ�̶�� ���̴�.
	m_ySpacePos = m_Next_ySpacePos; // �⺻ ��ħ�� Pos�� Con ���̶�� ���̴�.
	posMover();
	
}

// 3. Pos Line End


// 4. Essential for All Line Start

POINT gMap::conToAbs(POINT ij)
{
	POINT res;
	if(ij.x % 2 == 0)
	{
		res.x = WIDEX * (ij.x / 2);
		res.y = FULLY * ij.y;
	}
	else{
		res.x = LEFTX + MIDDLEX + WIDEX * (ij.x - 1) / 2;
		res.y = HALFY + FULLY *ij.y;
	}
	return res;
}


POINT gMap::absToCon(POINT ij) 
{

	POINT res;
	
	int n,m;
	int xo,yo;
	n = (ij.x) / WIDEX;
	n = n * 2;
	m = (ij.y) / FULLY;
	xo = (ij.x) % WIDEX;
	yo = (ij.y) % FULLY;
	
	
	if(-1 * HALFY * xo + HALFY * LEFTX > LEFTX * yo)
	{
		n--;
		m--;
	} 
	else if(HALFY * xo + HALFY * LEFTX <= LEFTX * yo )
	{
		n--;
	}
	else if(yo < HALFY && HALFY * xo + ( HALFY * LEFTX - HALFY * FULLX ) > LEFTX * yo )
	{
		n++; m--;
	}
	else if(yo >= HALFY && - HALFY * xo + ( HALFY * LEFTX + HALFY * FULLX ) <= LEFTX*yo )
	{
		n++;
	}
	res.x = n;
	res.y = m;

	return res;
}

int gMap::viewabsToCon(POINT ij)
{
	ij.x += m_nAbsDrawlineX;
	ij.y += m_nAbsDrawlineY;

	POINT	ptCon = absToCon(ij);
	int		con = ptCon.x * LINEY + ptCon.y;

	return con;
}

POINT gMap::ConToViewabs(int nPos)
{
	POINT	pt;

	pt.x = nPos/LINEY;
	pt.y = nPos%LINEY;
	pt = conToAbs(pt);
	pt.x -= m_nAbsDrawlineX;
	pt.y -= m_nAbsDrawlineY;

	return pt;
}

// 4. Essential for All Line End

// 6. ?

void gMap::MainLoop()
{

}

void gMap::Release()
{
	int		i;

	for(i = 0; i < TILENUM; i++)
		m_ImgTile[i].Release();

//	m_ImgTileBack.Release();

	m_ImgSmallTile.Release();
	m_ImgMapBG.Release();
}

bool gMap::Restore()
{
	int		i;

	for(i = 0; i < TILENUM; i++)
		if(!m_ImgTile[i].Restore())
			return false;

	if(!m_ImgSmallTile.Restore())
		return false;

	if(!m_ImgMapBG.Restore())
		return false;

	return true;
}

int gMap::PositionFor_gPC()
{
	if(m_xSpacePos < m_Next_xSpacePos) return 3;
	else if(m_xSpacePos > m_Next_xSpacePos) return 1;
	else if(m_ySpacePos < m_Next_ySpacePos) return 0;
	else if(m_ySpacePos > m_Next_ySpacePos) return 2;
	else return 0;
}

int gMap::Destination(int mapA, int spacor)
{
	int iter = mapA;
	while(spacor!=0){
		if(spacor>0) {
			iter = tileMap[iter].nextTile.x*LINEY + tileMap[iter].nextTile.y;
			spacor--;
		}
		else if(spacor<0) {
			if(iter/LINEY == m_xInitSpacePos && iter%LINEY == m_yInitSpacePos) 
				iter = tileMap[iter].flag1 * LINEY + tileMap[iter].flag2;
			else 
				iter = tileMap[iter].nextTile.x*LINEY + tileMap[iter].nextTile.y;
			spacor++;
		}
	}
	return iter;
}

float gMap::GetPosRateX()
{
	return (float)m_nAbsDrawlineX / BACKMAPX;
}

float gMap::GetPosRateY()
{
	return (float)m_nAbsDrawlineY / BACKMAPY;
}

void gMap::SetPosByRateX(float ratex)
{
	m_nAbsDrawlineX = int(BACKMAPX * ratex);
}

void gMap::SetPosByRateY(float ratey)
{
	m_nAbsDrawlineY = int(BACKMAPY * ratey);
}

void gMap::DrawMapCursor(int nSizeRate, int posX, int posY)
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	int		i;

	int		x, y;
	RECT	rcDest, rcSour;
	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(gPC->m_GPlayerList[i].szID) == 0)
			continue;

//		if(strcmp(gPC->m_GPlayerList[i].szID, gPC->m_MyGamePlayer.szID) == 0)
		if(i == gUIGame::GetIF()->m_nCharSelected)
			continue;

		y = gPC->m_GPlayerList[i].nPos % LINEY;
		x = gPC->m_GPlayerList[i].nPos / LINEY;

		if(x % 2 == 0)
		{
			rcDest.left		= WIDEX * x / 2;
			rcDest.top		= FULLY * y;
		}
		else
		{
			rcDest.left		= LEFTX + MIDDLEX + WIDEX * (x - 1) / 2;
			rcDest.top		= HALFY + FULLY * y;
		}

		rcDest.left	/= nSizeRate;
		rcDest.top	/= nSizeRate;

		rcDest.right	= rcDest.left + CURSORBIG_SIZE_W;
		rcDest.bottom	= rcDest.top + CURSORBIG_SIZE_H;

		OffsetRect(&rcDest, posX + 3, posY - 6);

		SetRect(&rcSour,
			0, 0, CURSORBIG_SIZE_W, CURSORBIG_SIZE_H);

		m_ImgCurBig.Draw(rcDest, rcSour, false);
	}

	y = gPC->m_GPlayerList[gUIGame::GetIF()->m_nCharSelected].nPos % LINEY;
	x = gPC->m_GPlayerList[gUIGame::GetIF()->m_nCharSelected].nPos / LINEY;

	if(x % 2 == 0)
	{
		rcDest.left		= WIDEX * x / 2;
		rcDest.top		= FULLY * y;
	}
	else
	{
		rcDest.left		= LEFTX + MIDDLEX + WIDEX * (x - 1) / 2;
		rcDest.top		= HALFY + FULLY * y;
	}

	rcDest.left	/= nSizeRate;
	rcDest.top	/= nSizeRate;

	rcDest.right	= rcDest.left + CURSORBIG_SIZE_W;
	rcDest.bottom	= rcDest.top + CURSORBIG_SIZE_H;

	OffsetRect(&rcDest, posX + 3, posY - 6);

	SetRect(&rcSour,
		0, 0, CURSORBIG_SIZE_W, CURSORBIG_SIZE_H);
	OffsetRect(&rcSour, CURSORBIG_SIZE_W, 0);

	m_ImgCurBig.Draw(rcDest, rcSour, false);
}

void gMap::DrawMiniMapCursor(int nSizeRate, int posX, int posY)
{
	gPlayerContainer	*gPC = gPlayerContainer::GetIF();

	int		i;

	int		x, y;
	RECT	rcDest, rcSour;
	for(i = 0; i < ROOMMAXPLAYER; i++)
	{
		if(strlen(gPC->m_GPlayerList[i].szID) == 0)
			continue;

		if(strcmp(gPC->m_GPlayerList[i].szID, gPC->m_MyGamePlayer.szID) == 0)
			continue;

		y = gPC->m_GPlayerList[i].nPos % LINEY;
		x = gPC->m_GPlayerList[i].nPos / LINEY;

		if(x % 2 == 0)
		{
			rcDest.left		= WIDEX * x / 2;
			rcDest.top		= FULLY * y;
		}
		else
		{
			rcDest.left		= LEFTX + MIDDLEX + WIDEX * (x - 1) / 2;
			rcDest.top		= HALFY + FULLY * y;
		}

		rcDest.left	/= nSizeRate;
		rcDest.top	/= nSizeRate;

		rcDest.right	= rcDest.left + CURSORSMALL_SIZE_W;
		rcDest.bottom	= rcDest.top + CURSORSMALL_SIZE_H;

		OffsetRect(&rcDest, posX - 1, posY - 4);

		SetRect(&rcSour,
			0, 0, CURSORSMALL_SIZE_W, CURSORSMALL_SIZE_H);

		m_ImgCurSmall.Draw(rcDest, rcSour, false);
	}

	y = gPC->m_MyGamePlayer.nPos % LINEY;
	x = gPC->m_MyGamePlayer.nPos / LINEY;

	if(x % 2 == 0)
	{
		rcDest.left		= WIDEX * x / 2;
		rcDest.top		= FULLY * y;
	}
	else
	{
		rcDest.left		= LEFTX + MIDDLEX + WIDEX * (x - 1) / 2;
		rcDest.top		= HALFY + FULLY * y;
	}

	rcDest.left	/= nSizeRate;
	rcDest.top	/= nSizeRate;

	rcDest.right	= rcDest.left + CURSORSMALL_SIZE_W;
	rcDest.bottom	= rcDest.top + CURSORSMALL_SIZE_H;

	OffsetRect(&rcDest, posX - 1, posY - 4);

	SetRect(&rcSour,
		0, 0, CURSORSMALL_SIZE_W, CURSORSMALL_SIZE_H);
	OffsetRect(&rcSour, CURSORSMALL_SIZE_W, 0);

	m_ImgCurSmall.Draw(rcDest, rcSour, false);
}