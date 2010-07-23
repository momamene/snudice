// 이것들은 왜 global이 안되나.
HINSTANCE g_hInst;

//bool boolBmpKind[LINEX][LINEY];
TILE bmpKind[LINEX][LINEY];
TILE bmpKind2[LINEX][LINEY];

XY nowConPoint; // 이건 현재 좌표의 변환 자표 (이거 뭔가 이상한데 둘을 합쳐야지)
XY nowPoint; // 이건 현재 좌표

