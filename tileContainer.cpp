#include "tileContainer.h"
#include "TILE.h"
#include "gGameCore.h"
#include "const.h"
#include "gMainWin.h"
#include "gUtil.h"
#include "gMouse.h"

static tileContainer s_tileContainer; // 2

tileContainer *tileContainer::GetIF() // 3
{
	return &s_tileContainer;
}

// 1. Setup Line


void tileContainer::Setup(){

	for(int i = 0 ; i < LINEX ; i++){
		for (int j = 0 ; j < LINEY ; j++){
			tileMap[i*LINEY+j].init(i,j);
		}
	}
	gimage[0].Load(".\\Data\\Map\\class.img");
	gimage[1].Load(".\\Data\\Map\\item.img");
	gimage[2].Load(".\\Data\\Map\\stamina.img");
	gimage[3].Load(".\\Data\\Map\\bus.img");
	gimage[4].Load(".\\Data\\Map\\maingate.img");
	m_wallpaper.Load(TITLE_IMG_TITLE);

	m_xSpacePos=-1;
	m_ySpacePos=-1;
	m_Next_xSpacePos = -1;
	m_Next_ySpacePos = -1;


	Load();
	posSpacor();
}

void tileContainer::LoadFileToBKS(){
	int i;
	for(i = 0 ; i < LINEX*LINEY ; i++)
		memset(&tileMap[i],0,sizeof(TILE));
	
	hFile=CreateFile("load.xy",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile!=INVALID_HANDLE_VALUE) {
		ReadFile(hFile,&count,sizeof(int),&dw,NULL);
		for(i = 0 ; i < count ; i++)
			ReadFile(hFile,&bmpKindSavor[i],sizeof(TILE)*count,&dw,NULL);
	}
	CloseHandle(hFile);
}

void tileContainer::LoadBKSToTM(){
	gMainWin *gmainWin = gMainWin::GetIF();
	int i;
	m_xInitSpacePos=-1;
	m_yInitSpacePos=-1;

	int localcount = 0;
	for(i = 0 ; i < MAXSAVOR_N ; i++)
		memset(&tileMap[i],0,sizeof(TILE));
	for(i = 0 ; i < LINEX ; i++) {
		for (int j = 0 ; j < LINEY ; j++) {
			if(localcount >= count) return;
			if(i == bmpKindSavor[localcount].ptPos.x && j == bmpKindSavor[localcount].ptPos.y){
				//tileMap[i*LINEY+j].init(i,j);
				//tileMap[i*LINEY+j].tileType=bmpKindSavor[localcount].tileType;
				tileMap[i*LINEY+j] = bmpKindSavor[localcount];
				//memset(tileMap[i*LINEY+j].building,0,sizeof(char)*128);
				//strcpy(tileMap[i*LINEY+j].building,bmpKindSavor[localcount].building);
				localcount++;
				if(tileMap[i*LINEY+j].tileType==TY_MAINGATE){
					m_xInitSpacePos = i;
					m_yInitSpacePos = j;
				}
			}
			else tileMap[i*LINEY+j].init(i,j);
		}
	}
	if(m_xInitSpacePos==-1&&m_yInitSpacePos==-1){
		MessageBox(gmainWin->m_hWnd, "Tile Info Error : There is no MainGate", "Error", MB_OK);
	}
}

void tileContainer::Load(){
	LoadFileToBKS();
	LoadBKSToTM();
}

// Setup Line End

// 2. Draw Line Start

void tileContainer::Draw(){
	int i,j;
	
	int n = 10; // 축소율
	int start_x =0;
	int start_y = 0;
	gGameCore *gameCore = gGameCore::GetIF();
	m_wallpaper.Draw(0,0);
	
	for(i = 0 ; i < LINEX ; i++) { 
		for(j = 0 ; j < LINEY ; j++) {
			if(tileMap[i*LINEY+j].tileType==TY_NONE) continue;	
			if(i%2==0){
				for(int k = 0 ; k < 5 ; k++){				
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(-gameCore->m_xPos+WIDEX*i/2,-gameCore->m_yPos+FULLY*j);
				}
			}
			else{
				for(int k = 0 ; k < 5; k++){
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(-gameCore->m_xPos+LEFTX+MIDDLEX+WIDEX*(i-1)/2,-gameCore->m_yPos+HALFY+FULLY*j);
				}
			}
		}
	}
	// 빈 사각형은 어떻게 띄울 것인가?
	if(gameCore->m_minimapOn==1||gameCore->m_minimapOn==2)
		minimapDraw(start_x,start_y,n);
	DrawSubInfo();
	
}

void tileContainer::minimapDraw(int start_x,int start_y,int n){
	int i,j;
	RECT inner_a, inner_b;
	m_wallpaper.Draw(WNDSIZEW - 240,WNDSIZEH - 180); 
	
	for(i = 0 ; i < LINEX ; i++) { 
		for(j = 0 ; j < LINEY ; j++) {
			if(tileMap[i*LINEY+j].tileType==TY_NONE)continue;	
			if(i%2==0){
				for(int k = 0 ; k < 5 ; k++){
					inner_a.left = WNDSIZEW - 240 + start_x + (WIDEX*i/2)/n;
					inner_a.top = WNDSIZEH - 180 + start_y + (FULLY*j)/n;
					inner_a.right = inner_a.left + FULLX/n;
					inner_a.bottom = inner_a.top + FULLY/n;
					inner_b.left = 0;
					inner_b.top = 0;
					inner_b.right =  gimage[k].m_nWidth;
					inner_b.bottom =  gimage[k].m_nHeight;
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(inner_a,inner_b);
				}
			}
			else{
				for(int k = 0 ; k < 5; k++){
					inner_a.left = WNDSIZEW - 240 + (LEFTX+MIDDLEX+WIDEX*(i-1)/2)/n;
					inner_a.top = WNDSIZEH - 180 + (HALFY+FULLY*j)/n;
					inner_a.right = inner_a.left + FULLX/n;
					inner_a.bottom = inner_a.top + FULLY/n;
					inner_b.left = 0;
					inner_b.top = 0;
					inner_b.right = gimage[k].m_nWidth;
					inner_b.bottom = gimage[k].m_nHeight;
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(inner_a,inner_b);
				}
			}
		}
	}
}


void tileContainer::DrawSubInfo(){
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
void tileContainer::posSpacor() {	// 다음 칸으로 움직이라는 신호.
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
void tileContainer::posMover(int frame){
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

bool tileContainer::isExisted(int i, int j){
	if(i>-1&&j>-1&&i<LINEX&&j<LINEY){
		if(tileMap[i*LINEY+j].tileType!=TY_NONE) return true;
	}
	return false;
}


POINT tileContainer::conToAbs(POINT ij){
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

POINT tileContainer::absToCon() {
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

POINT tileContainer::nextN_Tile(POINT ij, int n) {
	POINT res;
	POINT ij2;
	if(n==0){
		return ij;
	}
	else if(isExisted(ij.x,ij.y)){
		ij2 =tileMap[ij.x*LINEY+ij.y].prevTile;
		res = nextN_Tile(ij2,n-1);
	}
	else {
		res.x = -1;
		res.y = -1;
	}
	return res;
}

// 4. Essential for All Line End