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

