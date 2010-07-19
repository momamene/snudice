#include "tileContainer.h"
#include "TILE.h"
#include "gGameCore.h"
#include "const.h"
#include "gMainWin.h"

static tileContainer s_tileContainer; // 2

tileContainer *tileContainer::GetIF() // 3
{
	return &s_tileContainer;
}

void tileContainer::Setup(){

	for(int i = 0 ; i < LINEX ; i++){
		for (int j = 0 ; j < LINEY ; j++){
			tileMap[i*LINEY+j].init(i,j);
		}
	}
	gimage[0].Load("class.img");
	gimage[1].Load("item.img");
	gimage[2].Load("stamina.img");
	gimage[3].Load("bus.img");
	gimage[4].Load("maingate.img");
	m_wallpaper.Load(TITLE_IMG_TITLE);

	m_xSpacePos=-1;
	m_ySpacePos=-1;


	Load();
}

void tileContainer::LoadFileToBKS(){
	memset(tileMap,0,sizeof(bmpKindSavor));
	hFile=CreateFile("load.xy",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile!=INVALID_HANDLE_VALUE) {
		ReadFile(hFile,&count,sizeof(int),&dw,NULL);
		ReadFile(hFile,&bmpKindSavor,sizeof(TILE)*count,&dw,NULL);
	}
}

void tileContainer::LoadBKSToTM(){
	gMainWin *gmainWin = gMainWin::GetIF();

	m_xInitSpacePos=-1;
	m_yInitSpacePos=-1;

	int localcount = 0;
	memset(tileMap,0,sizeof(tileMap));
	for(int i = 0 ; i < LINEX ; i++) {
		for (int j = 0 ; j < LINEY ; j++) {
			if(localcount >= count) return;
			if(i == bmpKindSavor[localcount].ptPos.x && j == bmpKindSavor[localcount].ptPos.y){
				tileMap[i*LINEY+j] = bmpKindSavor[localcount];
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

void tileContainer::minimapDraw(int start_x,int start_y,int n){
	int i,j;
	RECT inner_a, inner_b;
	for(i = 0 ; i < LINEX ; i++) { 
		for(j = 0 ; j < LINEY ; j++) {
			if(tileMap[i*LINEY+j].tileType==TY_NONE)continue;	
			if(i%2==0){
				for(int k = 0 ; k < 5 ; k++){
					inner_a.left = start_x + (WIDEX*i/2)/n;
					inner_a.top = start_y + (FULLY*j)/n;
					inner_a.right = inner_a.left+FULLX/n;
					inner_a.bottom = inner_a.top+FULLY/n;
					inner_b.left = 0;
					inner_b.top = 0;
					inner_b.right = gimage[k].m_nWidth;
					inner_b.bottom = gimage[k].m_nHeight;
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(inner_a,inner_b);
				}
			}
			else{
				for(int k = 0 ; k < 5; k++){
					inner_a.left = start_x + (LEFTX+MIDDLEX+WIDEX*(i-1)/2)/n;
					inner_a.top = start_y + (HALFY+FULLY*j)/n;
					inner_a.right = inner_a.left+FULLX/n;
					inner_a.bottom = inner_a.top+FULLY/n;
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

void tileContainer::Draw(){
	int i,j;
	
	int n = 10; // 축소율
	int start_x =0;
	int start_y = 0;
	gGameCore *gameCore = gGameCore::GetIF();
	m_wallpaper.Draw(0,0);
	for(i = 0 ; i < LINEX ; i++) { 
		for(j = 0 ; j < LINEY ; j++) {
				if(tileMap[i*LINEY+j].tileType==TY_NONE)continue;	
				if(i%2==0){
					for(int k = 0 ; k < 5 ; k++)
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(-gameCore->m_xPos+WIDEX*i/2,-gameCore->m_yPos+FULLY*j);
				}
				else{
					for(int k = 0 ; k < 5; k++)
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(-gameCore->m_xPos+LEFTX+MIDDLEX+WIDEX*(i-1)/2,-gameCore->m_yPos+HALFY+FULLY*j);
				}
		}
	}
	//m_wallpaper.Draw() 
	//빈 사각형은 어떻게 띄울 것인가?
	if(gameCore->m_minimapOn==1||gameCore->m_minimapOn==2)
		minimapDraw(start_x,start_y,n);

}

bool tileContainer::isExisted(int i, int j){
	if(i>-1&&j>-1&&i<LINEX&&j<LINEY){
		if(tileMap[i*LINEY+j].tileType!=TY_NONE) return true;
	}
	return false;
}

void tileContainer::viewSpacor(){
	gGameCore *gameCore = gGameCore::GetIF();
	int a,b;
	if(m_xSpacePos%2==0){
		a = WIDEX*m_xSpacePos/2 - WNDSIZEW/2;
		b = FULLY*m_ySpacePos - WNDSIZEH/2;
	}
	else {
		a = LEFTX+MIDDLEX+WIDEX*(m_xSpacePos-1)/2 - WNDSIZEW/2;
		b = HALFY+FULLY*m_ySpacePos - WNDSIZEH/2;
	}
	gameCore->m_xPos = a; // 첫번째 문제는 6,15가 아니라 abs(6,15)
	gameCore->m_yPos = b;
	
}

void tileContainer::posSpacor() {
	//TILE temp;
	int nextX,nextY;
	if(m_xSpacePos==-1&&m_xSpacePos==-1){
		m_xSpacePos=m_xInitSpacePos;
		m_ySpacePos=m_yInitSpacePos;
		viewSpacor();
	}
	else{
		if(isExisted(m_xSpacePos,m_ySpacePos)){
			nextX = tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.x;
			nextY = tileMap[m_xSpacePos*LINEY+m_ySpacePos].nextTile.y;
			if(isExisted(nextX,nextY)){
				m_xSpacePos=nextX;
				m_ySpacePos=nextY;
				viewSpacor();
			}
		}
	}
}
