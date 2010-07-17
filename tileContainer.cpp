#include "tileContainer.h"
#include "TILE.h"
#include "gGameCore.h"
#include "const.h"

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
	int localcount = 0;
	memset(tileMap,0,sizeof(tileMap));
	for(int i = 0 ; i < LINEX ; i++) {
		for (int j = 0 ; j < LINEY ; j++) {
			if(localcount >= count) return;
			if(i == bmpKindSavor[localcount].ptPos.x && j == bmpKindSavor[localcount].ptPos.y){
				tileMap[i*LINEY+j] = bmpKindSavor[localcount];
				localcount++;
			}
			else tileMap[i*LINEY+j].init(i,j);
		}
	}
}

void tileContainer::Load(){
	LoadFileToBKS();
	LoadBKSToTM();
}
/*
TILE tileContainer::GetTileFromIJ(int i, int j){
	return tileMap[i*LINEY+j];
}
TILE tileContainer::GetPrevTileFromIJ(int i,int j){
	int x = tileMap[i*LINEY+j].prevTile.x;
	int y = tileMap[i*LINEY+j].prevTile.y; // 왜 -> 로 인식한 걸까?
	return GetTileFromIJ(x,y);
}
TILE tileContainer::GetNextTileFromIJ(int i,int j){
	int x = tileMap[i*LINEY+j].nextTile.x;
	int y = tileMap[i*LINEY+j].nextTile.y; 
	return GetTileFromIJ(x,y);
}
*/
void tileContainer::Draw(){
	gGameCore *gameCore = gGameCore::GetIF();
	m_wallpaper.Draw(0,0);
	for(int i = 0 ; i < LINEX ; i++) { 
		for(int j = 0 ; j < LINEY ; j++) {
				if(tileMap[i*LINEY+j].tileType==TY_NONE)continue;	
				if(i%2==0){
					for(int k = 0 ; k < 5 ; k++)
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(-gameCore->m_xPos+WIDEX*i/2,-gameCore->m_yPos+FULLY*j);
					//if(tileMap[i*LINEY+j].tileType==TY_ITEM) gimage[1].Draw(WIDEX*i/2,FULLY*j);
					//if(tileMap[i*LINEY+j].tileType==TY_STAMINA) gimage[2].Draw(WIDEX*i/2,FULLY*j);
					//if(tileMap[i*LINEY+j].tileType==TY_BUS) gimage[3].Draw(WIDEX*i/2,FULLY*j);
					//if(tileMap[i*LINEY+j].tileType==TY_MAINGATE) gimage[4].Draw(WIDEX*i/2,FULLY*j);
				}
				else{
					for(int k = 0 ; k < 5; k++)
					if(tileMap[i*LINEY+j].tileType==TY_CLASS+k) gimage[k].Draw(-gameCore->m_xPos+LEFTX+MIDDLEX+WIDEX*(i-1)/2,-gameCore->m_yPos+HALFY+FULLY*j);
					//if(tileMap[i*LINEY+j].tileType==TY_ITEM) gimage[1].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
					//if(tileMap[i*LINEY+j].tileType==TY_STAMINA) gimage[2].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
					//if(tileMap[i*LINEY+j].tileType==TY_BUS) gimage[3].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
					//if(tileMap[i*LINEY+j].tileType==TY_MAINGATE) gimage[4].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
				}
		}
	}
	
	
}	

