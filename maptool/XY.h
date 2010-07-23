
#define LEFTX 25
#define MIDDLEX 52
#define FULLX 102
#define WIDEX 152
#define HALFY 40
#define FULLY 80

#define LINEX 30
#define LINEY 20

class XY {
public:
	int x;
	int y;
	XY absToCon ();
	void put (int xo, int yo);
	void XY::putCon(int xo, int yo);
};
