//#include "main.h"
#include "XY.h"

XY XY::absToCon () {
	XY res;



	int n,m;
	int xo,yo;
	n = x/WIDEX;
	n = n*2;
	m = y/FULLY;
	xo = x%WIDEX;
	yo = y%FULLY;
	
	// ������ Ÿ�缺�� ���� �ٽ� ���캸��
	// ��� ��ǥ ���� (258,80) -> (?,?)
	// Ȥ�� (25,52,80) -> (?,?,?)
	if(-1 * HALFY * xo + HALFY * LEFTX > LEFTX * yo) { n--; m--; } 
	else if(HALFY * xo + HALFY * LEFTX <= LEFTX * yo ) { n--; }
	else if(yo < HALFY && HALFY * xo + ( HALFY * LEFTX - HALFY * FULLX ) > LEFTX * yo ) { n++; m--; }
	else if(yo >= HALFY && - HALFY * xo + ( HALFY * LEFTX + HALFY * FULLX ) <= LEFTX*yo ) { n++; }
	res.x = n;
	res.y = m;
	return res;
}
void XY::put(int xo, int yo) {
	x = xo;
	y = yo;
}
void XY::putCon(int xo,int yo) {
	
	XY temp, temp2;
	temp2.x = xo;
	temp2.y = yo;
	temp = temp2.absToCon();
	if(temp.x>=0&&temp.y>=0&&temp.x<LINEX&&temp.y<LINEY){	// ġ������ ����.
		x = temp.x;
		y = temp.y;
	}
}
