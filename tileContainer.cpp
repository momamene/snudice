#include "tileContainer.h"
#include "TILE.h"
#include "gGameCore.h"
#include "const.h"
#include "gMainWin.h"
#include "gUtil.h"
#include "gMouse.h"
#include "gPlayerManager.h"

static tileContainer s_tileContainer; // 2

tileContainer *tileContainer::GetIF() // 3
{
	return &s_tileContainer;
}

// 1. Setup Line


void tileContainer::Setup()
{
	gGameCore *ggameCore = gGameCore::GetIF();
	
	POINT temp;
	for(int i = 0 ; i < LINEX ; i++){
		for (int j = 0 ; j < LINEY ; j++){
			tileMap[i*LINEY+j].init(i,j);
		}
	}
	gimage[0].Load(".\\Data\\Map\\food.img");
	gimage[1].Load(".\\Data\\Map\\card.img");
	gimage[2].Load(".\\Data\\Map\\nokdu.img");
	gimage[3].Load(".\\Data\\Map\\bus.img");
	gimage[4].Load(".\\Data\\Map\\maingate.img");
	gimage[5].Load(".\\Data\\Map\\mountain.img");
	gimage[6].Load(".\\Data\\Map\\lang.img");
	gimage[7].Load(".\\Data\\Map\\math.img");
	gimage[8].Load(".\\Data\\Map\\art.img");
	
	m_wallpaper.Load(TITLE_IMG_TITLE);

	m_xSpacePos=-1;
	m_ySpacePos=-1;
	m_Next_xSpacePos = -1;
	m_Next_ySpacePos = -1;
	m_subjectN=0;


	Load();
	posSpacor();
	temp.x = m_xSpacePos;
	temp.y = m_ySpacePos;
	temp = conToAbs(temp);
	ggameCore->PutScreenPos(temp.x- WNDSIZEW/2 + HALFX,temp.y- WNDSIZEH/2 + HALFY);

}

void tileContainer::LoadFileToBKS()
{
	int i;
	//for(i = 0 ; i < LINEX*LINEY ; i++)
	//	memset(&tileMap[i],0,sizeof(TILE));
	
	hFile=CreateFile("load.xy",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile!=INVALID_HANDLE_VALUE) {
		ReadFile(hFile,&count,sizeof(int),&dw,NULL);
	//	for(i = 0 ; i < count ; i++)
	//		ReadFile(hFile,&bmpKindSavor[i],sizeof(TILE)*count,&dw,NULL);
		for(i = 0 ; i < count ; i++){
			memset(&bmpKindSavor[i],0,sizeof(TILE));
			ReadFile(hFile,&bmpKindSavor[i],sizeof(TILE),&dw,NULL);
		}
	}
	CloseHandle(hFile);
}


int tileContainer::flagToRow (int index){
	for(int i = 0 ; i < m_subjectN ; i++){
		if(m_subject[i]==index) return i;
	}
	return -1;
}

int tileContainer::rowToFirstTile(int row){
	for(int i = 0 ; i < LINEX*LINEY ; i++){
		if(tileMap[i].tileType==TY_CLASS&&tileMap[i].flag2==m_subject[row]) return i;
	}
	return -1;
}

int tileContainer::flagToFirstTile(int index){
	int row = flagToRow(index);
	return rowToFirstTile(row); // 실은 더 쉬운 방법이 있지만; (이게 뭐하는 짓이냐 당췌. firsttile이 flag를 가지고 있는데.
	return -1;
}


void tileContainer::LoadBKSToTM()
{
	gMainWin *gmainWin = gMainWin::GetIF();
	int i;
	m_xInitSpacePos=-1;
	m_yInitSpacePos=-1;

	int localcount = 0;
	for(i = 0 ; i < MAXSAVOR_N ; i++)
		memset(&tileMap[i],0,sizeof(TILE));
	for(i = 0 ; i < LINEX ; i++) {
		for (int j = 0 ; j < LINEY ; j++) {
			//if(localcount >= count) return;
			if(i == bmpKindSavor[localcount].ptPos.x && j == bmpKindSavor[localcount].ptPos.y){
				tileMap[i*LINEY+j] = bmpKindSavor[localcount];
				localcount++;
				if(tileMap[i*LINEY+j].tileType==TY_MAINGATE){
					m_xInitSpacePos = i;
					m_yInitSpacePos = j;
				}
				if(tileMap[i*LINEY+j].tileType==TY_CLASS){
					//m_subject[m_subjectN]=tileMap;
					
					if(flagToRow(tileMap[i*LINEY+j].flag2)==-1){
						m_subject[m_subjectN]=tileMap[i*LINEY+j].flag2;
						m_subjectN++;
					}

				}
			}
			else tileMap[i*LINEY+j].init(i,j);
		}
	}
	if(m_xInitSpacePos==-1&&m_yInitSpacePos==-1){
		MessageBox(gmainWin->m_hWnd, "Tile Info Error : There is no MainGate", "Error", MB_OK);
	}
}

void tileContainer::Load()
{
	LoadFileToBKS();
	LoadBKSToTM();
}

// Setup Line End

// 2. Draw Line Start

void tileContainer::DrawSubmit(){

	int i;
	gGameCore *gameCore = gGameCore::GetIF();
	gPlayerManager *gplayerManager = gPlayerManager::GetIF();
	int l_selectSubject;
		RECT tempRC;
		int tile;
	gUtil::BeginText();	
	for (i = 0 ; i < m_subjectN ; i++){
		tile = rowToFirstTile(i);
		if(tile>=0)
			gUtil::Text(0,i*20,tileMap[tile].subject);
		else
			gUtil::Text(0,i*20,"you are simang");
	}
	
	l_selectSubject=gameCore->m_selectSubject;
	if(l_selectSubject>=0){
		tile = flagToFirstTile(l_selectSubject);
		//if(isExisted(tile)){
			gUtil::Text(320,0,tileMap[tile].college);
			gUtil::Text(320,20,tileMap[tile].building);
			gUtil::Text(320,40,tileMap[tile].subject);
		//}
		
	}
	
	for(i = 0 ; i < gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.m_subjectN ; i++) {
		
		tile=flagToFirstTile(gplayerManager->m_player[gameCore->m_turnPlayer].m_subjectGrader.m_subject[i]);
		//if(isExisted(tile))
			gUtil::Text(160,i*20,tileMap[tile].subject);
	}


	gUtil::EndText();

	tempRC.left = 480;
	tempRC.top = 0;
	tempRC.right = 640;
	tempRC.bottom = 480;	
	gplayerManager->m_player[gameCore->m_turnPlayer].m_charInfo.DrawIllu(tempRC); // 여기서 지금 막혓음 problem10 (푼거 아님?)
		
}

void tileContainer::DrawHexagon(int x0,int y0,int n){
	gGameCore *gameCore = gGameCore::GetIF();

	int i, j;
	// Draw local 변수
	int k;
	RECT a;
	RECT b;

	//int x1,y1;
	//
	
	for(i = 0 ; i < LINEX ; i++) { 
		for(j = 0 ; j < LINEY ; j++) {
			k = tileMap[i*LINEY+j].tileType;
			if(k==TY_NONE) continue;
			
			if(i%2==0){
				a.left = WIDEX*i/2;
				a.top = FULLY*j;
			}
			else{
				a.left = LEFTX + MIDDLEX + WIDEX*(i-1)/2;
				a.top = HALFY + FULLY*j;
			}
			if(n==1){
				a.left -= gameCore->m_xPos;
				a.top -= gameCore->m_yPos;
			}
			a.left /= n;
			a.top /= n;

			a.left += x0;
			a.top += y0;
			a.right = a.left + FULLX/n;
			a.bottom = a.top + FULLY/n;
			
			/*
			b.left = 0;
			b.top = 0;
			b.right = FULLX;
			b.bottom = FULLY;
			*/
			SetRect(&b,0,0,FULLX,FULLY);

			if(k==TY_CLASS) gimage[k+tileMap[i*LINEY+j].flag1].Draw(a,b);
			else gimage[k].Draw(a,b, false);
			
			
		}
	}
}

void tileContainer::Draw()
{
	int i,j;


	
	int n = 10; // 축소율
	int start_x =0;
	int start_y = 0;
	
	gGameCore *gameCore = gGameCore::GetIF();


	m_wallpaper.Draw(0,0);

	if(gameCore->m_gMode==EGM_SUBMIT){
		DrawSubmit();
		return;
	}
	else{	
		DrawHexagon(0,0,1);
	

		// 빈 사각형은 어떻게 띄울 것인가?
		if(gameCore->m_minimapOn==1||gameCore->m_minimapOn==2)
			DrawHexagon( WNDSIZEW - 240 , WNDSIZEH - 180 , n );
			//minimapDraw(start_x,start_y,n);
		DrawSubInfo();
	}
	
}

void tileContainer::DrawSubInfo()
{
	gGameCore *ggameCore = gGameCore::GetIF();
	gUtil::BeginText();	
	
	POINT Abs;
	POINT Con2;
	Con2 = absToCon();
	if (isExisted(Con2.x,Con2.y)){
		Abs = conToAbs(Con2);
		gUtil::Text(Abs.x-(ggameCore->m_xPos),Abs.y-(ggameCore->m_yPos)+FULLY,tileMap[Con2.x*LINEY+Con2.y].college);
		gUtil::Text(Abs.x-(ggameCore->m_xPos),Abs.y-(ggameCore->m_yPos)+FULLY+20,tileMap[Con2.x*LINEY+Con2.y].building);
		gUtil::Text(Abs.x-(ggameCore->m_xPos),Abs.y-(ggameCore->m_yPos)+FULLY+40,tileMap[Con2.x*LINEY+Con2.y].subject);
	}
	
	
	
	gUtil::EndText();
}

// 2. Draw Line End

// 3. pos Line Start

// posSpacor() - start, posMovor() - On, posStoper() - End
void tileContainer::posSpacor() 
{	// 다음 칸으로 움직이라는 신호.
	gGameCore *gameCore = gGameCore::GetIF();


	if(m_xSpacePos==-1&&m_xSpacePos==-1){
		m_xSpacePos=m_xInitSpacePos;
		m_ySpacePos=m_yInitSpacePos;
		m_Next_xSpacePos = m_xSpacePos;
		m_Next_ySpacePos = m_ySpacePos;
	}
	else{
		if(isExisted(m_xSpacePos,m_ySpacePos)){
			m_Next_xSpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.x;	// 기본 방침은, Next와 Now가 괴리가 있는 상황은 움직이는 상황인 것이다.
			m_Next_ySpacePos = tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.y;
			
			if(isExisted(m_Next_xSpacePos,m_Next_ySpacePos)){

			}
			else{
				// error 처리 해야 하는데 생략
			}
			
		}
	}
}
void tileContainer::posMover(int frame)
{
	gGameCore *ggameCore = gGameCore::GetIF();
	POINT b, a;
	b.x = m_Next_xSpacePos;
	b.y = m_Next_ySpacePos;
	//b = conToAbs(b);
	a.x = m_xSpacePos;
	a.y = m_ySpacePos;
	//a = conToAbs(a);
	b = conToAbs(b);
	a = conToAbs(a);
	b.x = b.x - WNDSIZEW/2 + HALFX;
	b.y = b.y - WNDSIZEH/2 + HALFY;
	a.x = a.x - WNDSIZEW/2 + HALFX;
	a.y = a.y - WNDSIZEH/2 + HALFY;

	ggameCore->PutScreenPos(a.x + frame*(b.x-a.x)/MAXFRAMECOUNT,a.y + frame*(b.y-a.y)/MAXFRAMECOUNT);
	//ggameCore->PutScreenPos(b.x,b.y);

}
void tileContainer::posStoper(){
	m_xSpacePos = m_Next_xSpacePos;	// 기본 방침은 Next와 Now가 같은 상황은 멈춘 상황이라는 것이다.
	m_ySpacePos = m_Next_ySpacePos; // 기본 방침은 Pos는 Con 값이라는 것이다.
}

// 3. Pos Line End

// 4. Essential for All Line Start

bool tileContainer::isExisted(int i, int j)
{
	if(i>-1&&j>-1&&i<LINEX&&j<LINEY){
		if(tileMap[i*LINEY+j].tileType!=TY_NONE) return true;
	}
	return false;
}
bool tileContainer::isExisted(int line)
{
	if(line<0||line>=LINEX*LINEY) return false;
	else if(tileMap[line].tileType!=TY_NONE) return true;
	else return false;
}


POINT tileContainer::conToAbs(POINT ij)
{
	POINT res;
	if(ij.x%2==0){
		res.x = WIDEX*(ij.x/2);
		res.y = FULLY*ij.y;
	}
	else{
		res.x = LEFTX+MIDDLEX+WIDEX*(ij.x-1)/2;
		res.y = HALFY+FULLY*ij.y;
	}
	return res;
}

POINT tileContainer::absToCon() 
{
	gGameCore *ggameCore = gGameCore::GetIF();
	gMouse *gmouse = gMouse::GetIF();
	
	POINT res;
	
	int n,m;
	int xo,yo;
	n = (ggameCore->m_xPos + gmouse->m_nPosX) / WIDEX;
	n = n*2;
	m = (ggameCore->m_yPos + gmouse->m_nPosY) / FULLY;
	xo = (ggameCore->m_xPos + gmouse->m_nPosX) % WIDEX;
	yo = (ggameCore->m_yPos + gmouse->m_nPosY) % FULLY;
	

	if(-1 * HALFY * xo + HALFY * LEFTX > LEFTX * yo) { n--; m--; } 
	else if(HALFY * xo + HALFY * LEFTX <= LEFTX * yo ) { n--; }
	else if(yo < HALFY && HALFY * xo + ( HALFY * LEFTX - HALFY * FULLX ) > LEFTX * yo ) { n++; m--; }
	else if(yo >= HALFY && - HALFY * xo + ( HALFY * LEFTX + HALFY * FULLX ) <= LEFTX*yo ) { n++; }
	res.x = n;
	res.y = m;
	return res;
	
}
