#include "Server.h"

int main()
{
	int		nRet;

	gServer *sv = gServer::GetIF();

	if(!sv->SetUp())
		return -1;

	sv->Run();
	sv->Release();

	return 0;
}