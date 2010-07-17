#include "tileContainer.h"
#include "TILE.h"

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

void tileContainer::Draw(){
//	int k;
	//gimage[0].Draw(0,0);
	//gimage[1].Draw(LEFTX+MIDDLEX,HALFY);
	//gimage[2].Draw(0,FULLY);
	//gimage[4].Draw(1,1);
	//gimage[0].Draw(3,4);
	
	//char buf[10];
	for(int i = 0 ; i < LINEX ; i++) { // 현재 오류입니다. 왜일까? (25,2)에서는 오류. 이것은 설마 맵툴 비동기화?
		for(int j = 0 ; j < LINEY ; j++) {
			//k = tileMap[i*LINEX+j].tileType;

			//if(k==TY_NONE) continue;
			
			//wsprintf(buf,"%d %d",i,j);
			//for (int k = TY_CLASS; k < TY_MAINGATE + 1 ; k++){
			//	if(tileMap[i*LINEX+j].tileType==k) {
				if(tileMap[i*LINEY+j].tileType==TY_NONE)continue;	
				if(i%2==0){
					if(tileMap[i*LINEY+j].tileType==TY_CLASS) gimage[0].Draw(WIDEX*i/2,FULLY*j);
					if(tileMap[i*LINEY+j].tileType==TY_ITEM) gimage[1].Draw(WIDEX*i/2,FULLY*j);
					if(tileMap[i*LINEY+j].tileType==TY_STAMINA) gimage[2].Draw(WIDEX*i/2,FULLY*j);
					if(tileMap[i*LINEY+j].tileType==TY_BUS) gimage[3].Draw(WIDEX*i/2,FULLY*j);
					if(tileMap[i*LINEY+j].tileType==TY_MAINGATE) gimage[4].Draw(WIDEX*i/2,FULLY*j);
				}
				else{
					if(tileMap[i*LINEY+j].tileType==TY_CLASS) gimage[0].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
					if(tileMap[i*LINEY+j].tileType==TY_ITEM) gimage[1].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
					if(tileMap[i*LINEY+j].tileType==TY_STAMINA) gimage[2].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
					if(tileMap[i*LINEY+j].tileType==TY_BUS) gimage[3].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
					if(tileMap[i*LINEY+j].tileType==TY_MAINGATE) gimage[4].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
				}
			//		else		gimage[k-1].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
			//	}
			//}
		}
	}
	
	
}	

