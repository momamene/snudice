#define MAXSAVOR_N 60

class tileContainer
{
public:
	HANDLE hFile;
	DWORD dw;
	gImage gimage[5];

	int count;
	TILE bmpKindSavor[MAXSAVOR_N];
	TILE tileMap[LINEX*LINEY];
public:
	void Setup();
	void LoadFileToBKS();
	void LoadBKSToTM();
	void Load();
	void GetTileFromIJ();
	void Draw();
};


void tileContainer::Setup(){
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
	memset(tileMap,0,sizeof(tilemap));
	for(int i = 0 ; i < LINEX ; i++) {
		for (int j = 0 ; j < LINEY ; j++) {
			if(localcount >= count) return;
			if(i == bmpKindSavor[localcount].ptPos.x && j == bmpKindSavor[localcount].ptPos.y){
				tileMap[i*LINEX+j] = bmpKindSavor[localcount];
				localcount++;
			}
			else tileMap[i*LINEX+j].init(i,j);
		}
	}
}

void tileContainer::Load(){
	LoadFileToBKS();
	LoadBKSToTM();
}
TILE tileContainer::GetTileFromIJ(int i, int j){
	return tileMap[i*LINEX+j];
}
TILE tileContainer::GetPrevTileFromIJ(int i,int j){
	int x = tileMap[i*LINEX+j]->prevTile.x;
	int y = tileMap[i*LINEX+j]->prevTile.y; // 왜 -> 로 인식한 걸까?
	return GetTileFromIJ(x,y);
}
TILE tileContainer::GetNextTileFromIJ(int i,int j){
	int x = tileMap[i*LINEX+j]->nextTile.x;
	int y = tileMap[i*LINEX+j]->nextTile.y; // 왜 -> 로 인식한 걸까?
	return GetTileFromIJ(x,y);
}

void Draw(){
	for(int i = ttemp1.x ; i < ttemp2.x ; i++) {
		for(int j = ttemp1.y ; j < ttemp2.y ; j++) {
			if(bmpKind[i][j].tileType==TY_NONE) continue;
			
			wsprintf(buf,"%d %d",i,j);
			for (int k = TY_CLASS; k < TY_MAINGATE + 1 ; k++){
				if(bmpKind[i][j].tileType==k) {
					if(i%2==0)	gimage[k-1].Draw(WIDEX*i/2,FULLY*j);
					else		gimage[k-1].Draw(LEFTX+MIDDLEX+WIDEX*(i-1)/2,HALFY+FULLY*j);
				}
			}
		}
	}
}	

