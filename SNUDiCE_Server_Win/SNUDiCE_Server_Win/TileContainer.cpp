#include "MainWin.h"
#include "TileContainer.h"
#include "SubjectContainer.h"

static gTileContainer s_tileContainer; // 2

gTileContainer *gTileContainer::GetIF() // 3
{
	return &s_tileContainer;
}

bool gTileContainer::Setup()
{
	for(int i = 0 ; i < LINEX ; i++) {
		for (int j = 0 ; j < LINEY ; j++) {
			m_tileMap[i*LINEY+j].init(i,j);
		}
	}


	Load();

	// sangwoo temp
	/*
	char buf[128];
	OutputDebugString("Test in TileContainer\n");
	int a = distance(5*LINEY+14,5*LINEY+15);
	wsprintf(buf,"%d\n",a);
	OutputDebugString(buf);

	a = distance(5*LINEY+14,5*LINEY+14);
	wsprintf(buf,"%d\n",a);
	OutputDebugString(buf);

	a = distance(5*LINEY+14,6*LINEY+14);
	wsprintf(buf,"%d\n",a);
	OutputDebugString(buf);

	a = distance(5*LINEY+14,4*LINEY+15);
	wsprintf(buf,"%d\n",a);
	OutputDebugString(buf);

	a = distance(4*LINEY+15,5*LINEY+15);
	wsprintf(buf,"%d\n",a);
	OutputDebugString(buf);

	a = destination(5*LINEY+14,6);
	wsprintf(buf,"%d %d\n",a/LINEY,a%LINEY);
	OutputDebugString(buf);

	a = destination(5*LINEY+14,7);
	wsprintf(buf,"%d %d\n",a/LINEY,a%LINEY);
	OutputDebugString(buf);
	*/
	// end



	return true;
}

//////////////////////////////////////////////////////////////////////////
/// Load Function
//////////////////////////////////////////////////////////////////////////

void gTileContainer::Load()
{
	LoadFileToBKS();
	LoadBKSToTM();
}

void gTileContainer::LoadFileToBKS()
{
	gMainWin *mw = gMainWin::GetIF();

	int i;
	HANDLE	hFile;
	DWORD	dw;

	hFile=CreateFile("load.xy",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hFile!=INVALID_HANDLE_VALUE) {
		ReadFile(hFile,&m_TileNum,sizeof(int),&dw,NULL);
		for(i = 0 ; i < m_TileNum ; i++){
			memset(&m_bmpKindSavor[i],0,sizeof(TILE));
			ReadFile(hFile,&m_bmpKindSavor[i],sizeof(TILE),&dw,NULL);
		}
	}
	else {
		MessageBox(mw->m_hWnd, "Tile Info Error : There is no MainGate", "Error", MB_OK);
	}
	CloseHandle(hFile);
}




void gTileContainer::LoadBKSToTM()
{
	gMainWin *gmainWin = gMainWin::GetIF();
	gSubjectContainer *gSC = gSubjectContainer::GetIF();
	int i;
	m_xInitSpacePos=-1;
	m_yInitSpacePos=-1;

	int localcount = 0;
	for(i = 0 ; i < MAXSAVOR_N ; i++)
		memset(&m_tileMap[i],0,sizeof(TILE));
	for(i = 0 ; i < LINEX ; i++) {
		for (int j = 0 ; j < LINEY ; j++) {
			if(i == m_bmpKindSavor[localcount].ptPos.x && j == m_bmpKindSavor[localcount].ptPos.y){
				m_tileMap[i*LINEY+j] = m_bmpKindSavor[localcount];
				localcount++;
				if(m_tileMap[i*LINEY+j].tileType==TY_MAINGATE){
					m_xInitSpacePos = i;
					m_yInitSpacePos = j;
				}
				else if (m_tileMap[i*LINEY+j].tileType==TY_CLASS){
					gSC->putSubject(m_tileMap[i*LINEY+j],i*LINEY+j);
					//if(m_tileMap[i*LINEY+j].flag2 < MAXSUBJECT_N &&
					//	m_subject[m_tileMap[i*LINEY+j].flag2] = -1)
					//	m_subject[m_tileMap[i*LINEY+j].flag2] = i*LINEY+j;
				}
			}
			else m_tileMap[i*LINEY+j].init(i,j);
		}
	}
	if(m_xInitSpacePos==-1&&m_yInitSpacePos==-1){
		MessageBox(gmainWin->m_hWnd, "Tile Info Error : There is no MainGate", "Error", MB_OK);
	}
}

int gTileContainer::distance(int mapA, int mapB)
{	// 치명적인 녹두 문제. 녹두 들어가면 무한루프 때문에 그 오류를 알 수 있음
	int localCount	= 0;
	int iter		= mapA;

	if(mapA == mapB)
		return 0;

	while(1)
	{
		iter = m_tileMap[iter].nextTile.x*LINEY+m_tileMap[iter].nextTile.y;
		localCount++;
		if(iter == mapB)
		{
			//	localCount++;
			return localCount;
		}
		else if(iter == mapA || localCount > 100)	// 논리적으로 온당하지 않은 부당한 
			// sangwoo temp. localCount > 100 이렇게 하는 건 막장이지 임마.
		{
			break;
		}
	} 
	localCount = 0;
	iter = mapA;
	while(1)
	{
		if(iter/LINEY == m_xInitSpacePos && iter%LINEY == m_yInitSpacePos) 
			iter = m_tileMap[iter].flag1*LINEY + m_tileMap[iter].flag2;
		else 
			iter = m_tileMap[iter].nextTile.x*LINEY+m_tileMap[iter].nextTile.y;
		localCount++;
		if(iter == mapB)
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
}

int gTileContainer::destination(int mapA,int spacor) // Find mapB
{
	int iter = mapA;
	while(spacor!=0){
		if(spacor>0) {
			iter = m_tileMap[iter].nextTile.x*LINEY+m_tileMap[iter].nextTile.y;
			spacor--;
		}
		else if(spacor<0) {
			if(iter/LINEY == m_xInitSpacePos && iter%LINEY == m_yInitSpacePos) 
				iter = m_tileMap[iter].flag1 * LINEY + m_tileMap[iter].flag2;
			else 
				iter = m_tileMap[iter].nextTile.x*LINEY+m_tileMap[iter].nextTile.y;
			spacor++;
		}
	}
	return iter;
}