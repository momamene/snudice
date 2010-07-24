#pragma once
#define MAXSAVOR_N 70

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

