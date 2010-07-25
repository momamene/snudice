#include "main.h"

int prev_next;
int minimap;
/*
bool hSeries::bfAIbool (XY bCP,XY nCP) {
	if(nCP.x)%2==
}
*/

XY hSeries::bfAI (XY bCP,XY nCP) {
	if(nCP.x<0||nCP.y<0||nCP.x>LINEX||nCP.y>LINEY){
		return bCP;
	}
	else if(bCP.x<0||bCP.y<0) {
		//bCP.x = nCP.x;
		//bCP.y = nCP.y;
		return nCP;
	}
	else if( 
		( // 이것 좀 어떻게 고치자. 불리안 함수를 따로 만들던지
			(nCP.x)%2==0&&
			((abs(bCP.x-nCP.x)==1&&abs(bCP.y-nCP.y)<=1)||(abs(bCP.y-nCP.y)==1&&abs(bCP.x-nCP.x)<=1))&&
			!((bCP.y-nCP.y)==1&&(bCP.x!=nCP.x))
		)
		|| 
		(	
			(nCP.x)%2==1&&
			((abs(bCP.x-nCP.x)==1&&abs(bCP.y-nCP.y)<=1)||(abs(bCP.y-nCP.y)==1&&abs(bCP.x-nCP.x)<=1))&&
			!((bCP.y-nCP.y)==-1&&(bCP.x!=nCP.x))
		)
		// 미칠듯한 막장 코딩 아 이거 누가 만든거야.
	  )
	{	
		//befPoint.x = nowTILE.ptPos.x;
		//befPoint.y = nowTILE.ptPos.y;
		if(bmpKind[nCP.x][nCP.y].prevTile.x==-1){
			bmpKind[bCP.x][bCP.y].nextTile = bmpKind[nCP.x][nCP.y].ptPos;
			bmpKind[nCP.x][nCP.y].prevTile = bmpKind[bCP.x][bCP.y].ptPos;
		}
		return nCP;
		//bCP.x = nCP.x;
		//bCP.y = nCP.y;
	}
	else {
		return nCP;
	}
	return bCP;
}

void hSeries::hEditChanger (TILE t) {
	char str[128];
	wsprintf(str,"%d",t.ptPos.x);				
	SetWindowText(hEdit[0],str);
	wsprintf(str,"%d",t.ptPos.y);				
	SetWindowText(hEdit[1],str);
	wsprintf(str,"%d",t.prevTile.x);				
	SetWindowText(hEdit[2],str);
	wsprintf(str,"%d",t.prevTile.y);				
	SetWindowText(hEdit[3],str);
	wsprintf(str,"%d",t.nextTile.x);				
	SetWindowText(hEdit[4],str);
	wsprintf(str,"%d",t.nextTile.y);				
	SetWindowText(hEdit[5],str);
	wsprintf(str,"%d",t.flag1);				
	SetWindowText(hEdit[6],str);
	wsprintf(str,"%d",t.flag2);				
	SetWindowText(hEdit[7],str);
	wsprintf(str,"%d",t.flag3);				
	SetWindowText(hEdit[11],str);
	SetWindowText(hEdit[8],t.college);
	SetWindowText(hEdit[9],t.building);
	SetWindowText(hEdit[10],t.subject);
	//changed2=1;
}
void hSeries::caseProcessor (int caseo,int hiParam) {
	ETILETYPE i;
	TCHAR str[128];
	switch(caseo){
		case 100: // Combolist
			//SetWindowText(hWnd,TEXT("H"));
			switch(hiParam) {
			case CBN_SELCHANGE:
				i=(ETILETYPE)SendMessage(hCombo,CB_GETCURSEL,0,0);
				if (mode==1) {
					if(i!=TY_CLASS)
						tempBmpKind.tileType = i;
					else
						tempBmpKind.tileType = i;
				}
				else if (mode==2) {
					if(i!=TY_CLASS)
						bmpKind[nowConPoint.x][nowConPoint.y].tileType=i;
					else
						bmpKind[nowConPoint.x][nowConPoint.y].tileType=i;
				}

	
			}
		case 101:// combobutton
			mode=1;
			hEditChanger(tempBmpKind);
			InvalidateRect(hC2,NULL,TRUE);
			break;
		case 102: // combobutton
			mode=2;
			hEditChanger(bmpKind[nowConPoint.x][nowConPoint.y]);
			InvalidateRect(hC2,NULL,TRUE);
			break;
		case 110:
			break;
		case 111:
			break;
		case 112:
			if(mode==1){ // 이게 왜 안먹히지????? problem
				GetWindowText(H.hEdit[2],str,128);
				tempBmpKind.prevTile.x=atoi(str);
			}
			else if(mode==2){	
				GetWindowText(H.hEdit[2],str,128);
				bmpKind[nowConPoint.x][nowConPoint.y].prevTile.x=atoi(str);
			}
			break;
	case 113:
			if(mode==1){
			}
			else if(mode==2){	
				GetWindowText(H.hEdit[3],str,128);
				bmpKind[nowConPoint.x][nowConPoint.y].prevTile.y=atoi(str);
			}
			break;
	case 114:
			if(mode==1){
			}
			else if(mode==2){	
				GetWindowText(H.hEdit[4],str,128);
				bmpKind[nowConPoint.x][nowConPoint.y].nextTile.x=atoi(str);
			}
			break;
	case 115:
			if(mode==1){
			}
			else if(mode==2){	
				GetWindowText(H.hEdit[5],str,128);
				bmpKind[nowConPoint.x][nowConPoint.y].nextTile.y=atoi(str);
			}
			break;
	case 116:
		if(mode==1){
		}
		else if(mode==2){	
			GetWindowText(H.hEdit[6],str,128);
			bmpKind[nowConPoint.x][nowConPoint.y].flag1=atoi(str);
		}
		break;
	case 117:
		if(mode==1){
		}
		else if(mode==2){	
			GetWindowText(H.hEdit[7],str,128);
			bmpKind[nowConPoint.x][nowConPoint.y].flag2=atoi(str);
		}
		break;
	case 121:
		if(mode==1){
		}
		else if(mode==2){	
			GetWindowText(H.hEdit[11],str,128);
			bmpKind[nowConPoint.x][nowConPoint.y].flag3=atoi(str);
		}
		break;

	case 118:
		switch(hiParam){
		case EN_CHANGE:
			if(mode==1){
			}
			else if(mode==2){
				GetWindowText(H.hEdit[8],str,128);
				strcpy(bmpKind[nowConPoint.x][nowConPoint.y].college,str);
			}
			break;
		}
		break;
	case 119:
		switch(hiParam){
		case EN_CHANGE:
			if(mode==1){
			}
			else if(mode==2){
				GetWindowText(H.hEdit[9],str,128);
				strcpy(bmpKind[nowConPoint.x][nowConPoint.y].building,str);
			}
			break;
		}
		break;
	case 120:
		switch(hiParam){
		case EN_CHANGE:
			if(mode==1){
			}
			else if(mode==2){
				GetWindowText(H.hEdit[10],str,128);
				strcpy(bmpKind[nowConPoint.x][nowConPoint.y].subject,str);
			}
			break;
		}
		break;
	case 130:
		if(SendMessage(hButton[0],BM_GETCHECK,0,0)==BST_UNCHECKED) {
			SendMessage(hButton[0],BM_SETCHECK,BST_CHECKED,0);
			prev_next=1;
		}
		else {
			SendMessage(hButton[0],BM_SETCHECK,BST_UNCHECKED,0);
			prev_next=0;
		}
		break;
	case 131:
		if(SendMessage(hButton[1],BM_GETCHECK,0,0)==BST_UNCHECKED) {
			SendMessage(hButton[1],BM_SETCHECK,BST_CHECKED,0);
			minimap=1;
		}
		else {
			SendMessage(hButton[1],BM_SETCHECK,BST_UNCHECKED,0);
			minimap=0;
		}	
		break;
	}
	InvalidateRect(hC1,NULL,TRUE);
}
