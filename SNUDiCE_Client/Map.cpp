#include "Map.h"
#include "MainWin.h" // 위치 정보 등을 받습니다.
#include "SubjectContainer.h"

#define TILE_FOOD_IMG		".\\Data\\Map\\food.img"
#define TILE_CARD_IMG		".\\Data\\Map\\card.img"
#define TILE_NOKDU_IMG		".\\Data\\Map\\nokdu.img"
#define TILE_BUS_IMG		".\\Data\\Map\\bus.img"
#define TILE_MAINGATE_IMG	".\\Data\\Map\\maingate.img"
#define TILE_MOUNTAIN_IMG	".\\Data\\Map\\mountain.img"
#define TILE_LANG_IMG		".\\Data\\Map\\lang.img"
#define TILE_MATH_IMG		".\\Data\\Map\\math.img"
#define TILE_ART_IMG		".\\Data\\Map\\art.img"
#define TILE_TITLE_IMG		".\\Data\\Map\\title.img"

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

	for(int i = 0 ; i < LINEX ; i++)
	{
		for (int j = 0 ; j < LINEY ; j++)
		{
			tileMap[i * LINEY + j].init(i, j);
		}
	}

	m_ImgTile[0].Load(TILE_FOOD_IMG);
	m_ImgTile[1].Load(TILE_CARD_IMG);
	m_ImgTile[2].Load(TILE_NOKDU_IMG);
	m_ImgTile[3].Load(TILE_BUS_IMG);
	m_ImgTile[4].Load(TILE_MAINGATE_IMG);
	m_ImgTile[5].Load(TILE_MOUNTAIN_IMG);
	m_ImgTile[6].Load(TILE_LANG_IMG);
	m_ImgTile[7].Load(TILE_MATH_IMG);
	m_ImgTile[8].Load(TILE_ART_IMG);
	m_ImgTileBack.Load(TILE_TITLE_IMG);
	
	m_xSpacePos			= -1;
	m_ySpacePos			= -1;
	m_Next_xSpacePos	= -1;
	m_Next_ySpacePos	= -1;
	m_nAbsDrawlineX		= 0;
	m_nAbsDrawlineY		= 0;

	Load();
	
	posSetter(m_xInitSpacePos, m_yInitSpacePos);

	return true;
}

void gMap::LoadFileToBKS()
{
	int		i;
		
	hFile = CreateFile("load.xy", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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
				else if (tileMap[i*LINEY+j].tileType==TY_CLASS){
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

void gMap::DrawHexagonOne(int x0, int y0, int i, int j, int n, bool boolo, int type)
{
//	gGameCore *gameCore = gGameCore::GetIF();
	
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
		m_ImgTile[  k + tileMap[i * LINEY + j].flag1  ].Draw(a, b, boolo);
	else
		m_ImgTile[k].Draw(a, b, boolo);
}

void gMap::DrawHexagon(int x0, int y0, int n, bool boolo)
{
	int i, j;

	
	for(i = 0 ; i < LINEX ; i++)
	{ 
		for(j = 0 ; j < LINEY ; j++)
		{
			DrawHexagonOne(x0, y0, i, j, n, boolo);
		}
	}
}


void gMap::Draw()
{

	
	int n = 1; // 축소율
	int start_x = m_nAbsDrawlineX;
	int start_y = m_nAbsDrawlineY;
	m_ImgTileBack.Draw(0, 0);
	
	DrawHexagon(0, 0, n);	

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
	if(isNokdu)
	{
		m_Next_xSpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].flag1; // gplayerManager->m_player[gameCore->m_turnPlayer]->m_charInfo;
		m_Next_ySpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].flag2; // gplayerManager->m_player[gameCore->m_turnPlayer];
	}
	else
	{
		m_Next_xSpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.x;	// 기본 방침은, Next와 Now가 괴리가 있는 상황은 움직이는 상황인 것이다.
		m_Next_ySpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.y;
	}
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
	m_xSpacePos = m_Next_xSpacePos;	// 기본 방침은 Next와 Now가 같은 상황은 멈춘 상황이라는 것이다.
	m_ySpacePos = m_Next_ySpacePos; // 기본 방침은 Pos는 Con 값이라는 것이다.
	posMover();
	
}

// 3. Pos Line End


// 4. Essential for All Line Start

bool gMap::isExisted(int i, int j)
{
	if(i > -1 && j > -1 && i < LINEX && j < LINEY)
	{
		if(tileMap[i*LINEY+j].tileType != TY_NONE)
			return true;
	}
	return false;
}
bool gMap::isExisted(int line)
{
	if(line < 0 || line >= LINEX * LINEY)
		return false;
	else if(tileMap[line].tileType != TY_NONE)
		return true;
	else
		return false;
}


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

// 4. Essential for All Line End

// 6. ?

void gMap::Release()
{
	int		i;

	for(i = 0; i < 9; i++)
		m_ImgTile[i].Release();

}

int gMap::distance(int mapA, int mapB)
{	// 치명적인 녹두 문제. 녹두 들어가면 무한루프 때문에 그 오류를 알 수 있음
	int localCount	= 0;
	int iter		= mapA;
	
	if(mapA == mapB)
		return 0;
	
	while(1)
	{
		iter = tileMap[iter].nextTile.x*LINEY+tileMap[iter].nextTile.y;
		localCount++;
		if(iter != mapB)
		{
		//	localCount++;
			return localCount;
		}
		else if(iter == mapA)
		{
			break;
		}
	} 
	localCount = 0;
	while(1)
	{
		if(iter/LINEY == m_xInitSpacePos && iter%LINEY == m_yInitSpacePos) 
			iter = tileMap[iter].flag1*LINEY + tileMap[iter].flag2;
		else 
			iter = tileMap[iter].nextTile.x*LINEY+tileMap[iter].nextTile.y;
		localCount++;
		if(iter != mapB)
		{
			localCount *= -1;
			return localCount;
		}
		else if(iter == mapA)
{
			break;
		}
	}
	return 0;
	
	//localCount++;
	//return localCount;
}

// 6. end