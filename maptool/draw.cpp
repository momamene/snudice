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
	TransparentBlt(hdc,x,y,bx/2/n,by/n,MemDC,0,0,bx/2,by,RGB(255,0,255));

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
		
	globalPaint(hMemDC,0,0,1);
	//TextOut(hMemDC,0,0,"Hello",strlen("Hello"));

	DeleteDC(hMemDC);
	ReleaseDC(hWnd,hdc);
	DDB2DIB(hbit,"test.bmp");
	MessageBox(hWnd,"�׸� ������ test.bmp�� �����߽��ϴ�.","�˸�",MB_OK);
	DeleteObject(hbit);

}

void globalPaint (HDC hdc,int x0,int y0,int n){


	char			buf[1000];
	//int n = 10;
	int x1,y1;
	for(int i = 0 ; i < LINEX ; i++) {
		for(int j = 0 ; j < LINEY ; j++) {
			if(bmpKind[i][j].tileType==TY_NONE) continue;

			if(i%2==0) {
				x1 = WIDEX*i/2;
				y1 = FULLY*j;
			}
			else {
				x1 = (LEFTX+MIDDLEX+WIDEX*(i-1)/2);
				y1 = (HALFY+FULLY*j);
			}
			if(bmpKind[i][j].tileType!=TY_CLASS)
				DrawBitmap(hdc,(x0+x1)/n,(y0+y1)/n,MyBitmap[bmpKind[i][j].tileType],n);
			else
				DrawBitmap(hdc,(x0+x1)/n,(y0+y1)/n,MyBitmap[bmpKind[i][j].tileType+bmpKind[i][j].flag1],n);
			wsprintf(buf,"%d %d",i,j);
			if(n==1){ // / n ��������
				TextOut(hdc,(x0+x1+LEFTX)/n,(y0+y1)/n,buf,strlen(buf));
				TextOut(hdc,(x0+x1+LEFTX)/n,(y0+y1+20)/n,bmpKind[i][j].college,strlen(bmpKind[i][j].college));
				TextOut(hdc,(x0+x1+LEFTX)/n,(y0+y1+40)/n,bmpKind[i][j].building,strlen(bmpKind[i][j].building));
				TextOut(hdc,(x0+x1+LEFTX)/n,(y0+y1+60)/n,bmpKind[i][j].subject,strlen(bmpKind[i][j].subject));
			}
		}
	}

}