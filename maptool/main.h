#include <windows.h>

#include "resource.h"

// class
#include "XY.h"
#include "TILE.h"
#include "hSeries.h"
#include "Savor.h"

#pragma comment (lib,"Msimg32.lib") // 이것은 DrawBitmap을 위해서 필요함

// draw.h
// public : 
void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit,double n=1.0); 
void hahaha(HWND hWnd); 
// private : 
void DDB2DIB(HBITMAP hbit,LPCTSTR Path);

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ChildLeftProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ChildRightProc(HWND,UINT,WPARAM,LPARAM);
BOOL CALLBACK AboutDlgProc(HWND hDlg,UINT iMessage,WPARAM wParam,LPARAM lParam);

extern int mode;
extern TILE tempBmpKind;
extern bool boolBmpKind[LINEX][LINEY];
extern TILE bmpKind[LINEX][LINEY];
extern XY nowConPoint;
extern HWND hWndMain, hC1, hC2;
extern hSeries H;

// hSeries.cpp
extern int prev_next;
extern int minimap;

//debug hSeries prev-next
extern int eramoregetta;

// Childs.h
extern TILE bmpKind[LINEX][LINEY];

// left.h
extern HBITMAP MyBitmap[5];
//extern int yPos,xPos;
//extern int yMax,xMax;
//extern int xInc,yInc;