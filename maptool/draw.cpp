#include "main.h"
//#include <windows.h>

void DDB2DIB(HBITMAP hbit,LPCTSTR Path)
{
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	BITMAP bit;
	BITMAPINFO *pih;
	int PalSize;
	HANDLE hFile;
	DWORD dwWritten,Size;
	HDC hdc;

	// ��ü ȭ�鿡 ���� DC�� ���Ѵ�.
	hdc=GetDC(NULL);

	// ��Ʈ�� �����κ��� ���� ����ü�� �ʱ�ȭ�Ѵ�.
	GetObject(hbit,sizeof(BITMAP),&bit);
	ih.biSize=sizeof(BITMAPINFOHEADER);
	ih.biWidth=bit.bmWidth;
	ih.biHeight=bit.bmHeight;
	ih.biPlanes=1;
	ih.biBitCount=bit.bmPlanes*bit.bmBitsPixel;
	ih.biCompression=BI_RGB;
	ih.biSizeImage=0;
	ih.biXPelsPerMeter=0;
	ih.biYPelsPerMeter=0;
	ih.biClrUsed=0;
	ih.biClrImportant=0;

	// ���� ����ü + �ȷ�Ʈ ũ�⸸ŭ �޸𸮸� �Ҵ��ϰ� �� ���ۿ� 
	// ���� ����ü�� �����Ѵ�.
	PalSize=(ih.biBitCount > 8 ? 0:1 << ih.biBitCount)*sizeof(RGBQUAD);
	pih=(BITMAPINFO *)malloc(ih.biSize+PalSize);
	pih->bmiHeader=ih;

	// ��Ʈ���� ũ�⸦ ���Ѵ�.
	GetDIBits(hdc,hbit,0,bit.bmHeight,NULL,pih,DIB_RGB_COLORS);
	ih=pih->bmiHeader;

	// ��Ʈ�� ũ�Ⱑ �������� �ʾ��� ��� ���۾����� ���� ����Ѵ�.
	if (ih.biSizeImage == 0) {
		ih.biSizeImage=((((ih.biWidth*ih.biBitCount)+31) & ~31) >> 3) * ih.biHeight;
	}

	// ������ �����͸� �б����� �޸� ���Ҵ��Ѵ�.
	Size=ih.biSize+PalSize+ih.biSizeImage;
	pih=(BITMAPINFO *)realloc(pih,Size);

	// ������ �����͸� �о���δ�.
	GetDIBits(hdc,hbit,0,bit.bmHeight,(PBYTE)pih+ih.biSize+PalSize,pih,DIB_RGB_COLORS);

	// ���� ����� �����.
	fh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PalSize;
	fh.bfReserved1=0;
	fh.bfReserved2=0;
	fh.bfSize=Size+sizeof(BITMAPFILEHEADER);
	fh.bfType=0x4d42;

	// ������ �����ϰ� ���� ����� ���� ����ü, �ȷ�Ʈ, ������ �����͸� ����Ѵ�.
	hFile=CreateFile(Path,GENERIC_WRITE,0,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	WriteFile(hFile,&fh,sizeof(fh),&dwWritten,NULL);
	WriteFile(hFile,pih,Size,&dwWritten,NULL);

	free(pih);
	ReleaseDC(NULL,hdc);
	CloseHandle(hFile);
}

void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit,double n) {
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,hBit);

	GetObject(hBit,sizeof(BITMAP),&bit);
	bx=bit.bmWidth;
	by=bit.bmHeight;

	//BitBlt(hdc,x,y,bx,by,MemDC,0,0,SRCCOPY);
	TransparentBlt(hdc,x,y,bx/n,by/n,MemDC,0,0,bx,by,RGB(255,0,0));

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void hahaha(HWND hWnd) {
	int local_xMax=(LINEX/2+LINEX%2)*WIDEX-MIDDLEX; 
	int local_yMax=LINEY*FULLY+HALFY;
	HBITMAP hbit;
	HDC hdc, hMemDC;
	hdc=GetDC(hWnd);
	hbit=CreateCompatibleBitmap(hdc,local_xMax,local_yMax);
	hMemDC=CreateCompatibleDC(hdc);
	SelectObject(hMemDC,hbit);
	SelectObject(hMemDC,GetStockObject(WHITE_PEN));
	Rectangle(hMemDC,0,0,local_xMax,local_yMax);
	char buf[1000];
		
	// painting Start!
	int n = 1;
	for(int i = 0 ; i < LINEX ; i++) {
			for(int j = 0 ; j < LINEY ; j++) { 
				wsprintf(buf,"%d %d",i,j);
				if(bmpKind[i][j].tileType==TY_NONE) continue;
				else if(bmpKind[i][j].tileType==TY_CLASS) {
					if(i%2==0)	DrawBitmap(hMemDC,WIDEX*i/2/n,FULLY*j/n,MyBitmap[0],n);
					else	DrawBitmap(hMemDC,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[0],n);
				}
				else if (bmpKind[i][j].tileType==TY_ITEM) {
					if(i%2==0)	DrawBitmap(hMemDC,WIDEX*i/2/n,FULLY*j/n,MyBitmap[1],n);
					else	DrawBitmap(hMemDC,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[1],n);
				}
				else if (bmpKind[i][j].tileType==TY_STAMINA) {
					if(i%2==0)	DrawBitmap(hMemDC,WIDEX*i/2/n,FULLY*j/n,MyBitmap[2],n);
					else	DrawBitmap(hMemDC,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[2],n);
				}
				else if (bmpKind[i][j].tileType==TY_BUS) {
					if(i%2==0)	DrawBitmap(hMemDC,WIDEX*i/2/n,FULLY*j/n,MyBitmap[3],n);
					else	DrawBitmap(hMemDC,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[3],n);
				}
				else if (bmpKind[i][j].tileType==TY_MAINGATE) {
					if(i%2==0)	DrawBitmap(hMemDC,WIDEX*i/2/n,FULLY*j/n,MyBitmap[4],n);
					else	DrawBitmap(hMemDC,LEFTX/n+MIDDLEX/n+WIDEX*(i-1)/2/n,HALFY/n+FULLY*j/n,MyBitmap[4],n);
				}
				if(i%2==0){
				TextOut(hMemDC,WIDEX*i/2+LEFTX,FULLY*j,buf,strlen(buf));
				TextOut(hMemDC,WIDEX*i/2+LEFTX,FULLY*j+20,bmpKind[i][j].college,strlen(bmpKind[i][j].college));
				TextOut(hMemDC,WIDEX*i/2+LEFTX,FULLY*j+40,bmpKind[i][j].building,strlen(bmpKind[i][j].building));
				TextOut(hMemDC,WIDEX*i/2+LEFTX,FULLY*j+60,bmpKind[i][j].subject,strlen(bmpKind[i][j].subject));
				}
				if(i%2==1){
				TextOut(hMemDC,WIDEX*i/2+LEFTX,FULLY*j+HALFY,buf,strlen(buf));
				TextOut(hMemDC,WIDEX*i/2+LEFTX,FULLY*j+HALFY+20,bmpKind[i][j].college,strlen(bmpKind[i][j].college));
				TextOut(hMemDC,WIDEX*i/2+LEFTX,FULLY*j+HALFY+40,bmpKind[i][j].building,strlen(bmpKind[i][j].building));
				TextOut(hMemDC,WIDEX*i/2+LEFTX,FULLY*j+HALFY+60,bmpKind[i][j].subject,strlen(bmpKind[i][j].subject));
				}
			}

	}
	// painting End!

	DeleteDC(hMemDC);
	ReleaseDC(hWnd,hdc);
	DDB2DIB(hbit,"test.bmp");
	MessageBox(hWnd,"�׸� ������ test.bmp�� �����߽��ϴ�.","�˸�",MB_OK);
	DeleteObject(hbit);

}
