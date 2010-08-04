#include "Server.h"

int main(int argc, char *argv[])
{
	int		nRet;

	gServer *sv = gServer::GetIF();

	if(!sv->SetUp(argc, argv))
		return -1;

	sv->Run();
	sv->Release();

	return 0;
}