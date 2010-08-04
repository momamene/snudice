

class hSeries {
public:
	HWND hCombo;	
	HWND hEdit[12];
	HWND hButton[2];

	void hEditChanger(TILE t);
	void caseProcessor (int caseo,int hiParam);
	XY bfAI(XY befConPoint,XY nowPoint);
};
