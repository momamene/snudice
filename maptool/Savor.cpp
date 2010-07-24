#include "main.h"

Savor::Savor(void)
{
	count = 0;
}

Savor::~Savor(void)
{
}

void Savor::Save(){
	for(int i = 0 ; i < LINEX ; i++) {
		for(int j = 0 ; j < LINEY ; j++) {
			if(count >= MAXSAVOR_N) return;
			else if(bmpKind[i][j].tileType == TY_NONE) continue;
			else {
			bmpKindSavor[count] = bmpKind[i][j];
			count++;
			}
		}
	}
}

void Savor::Load(){
	int localcount = 0;
	for(int i = 0 ; i < LINEX ; i++) {
		for (int j = 0 ; j < LINEY ; j++) {
			//if(localcount >= count) return;
			if(i == bmpKindSavor[localcount].ptPos.x && j == bmpKindSavor[localcount].ptPos.y){
				bmpKind[i][j] = bmpKindSavor[localcount];
				localcount++;
			}
			else bmpKind[i][j].init(i,j);
		}
	}
}
