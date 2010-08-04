#pragma once
#define MAXSAVOR_N 100

class Savor
{
public:
	int count;
	TILE bmpKindSavor[MAXSAVOR_N];
public:
	Savor(void);
	~Savor(void);
	void Save();
	void Load();
};

class SavorPREV
{
public:
	int count;
	TILEPREV bmpKindSavor[MAXSAVOR_N];
};
