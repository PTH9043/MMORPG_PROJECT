#include "ServerDefines.h"
#include "CServerApp.h"
#include "AMySqlDriver.h"

int main()
{
	//SHPTR<AMySqlDriver> spDriver = CreateInitNative<AMySqlDriver>("tcp://127.0.0.1:3306", "root", "Qkrxogus0652!");

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Server::CServerApp* Server = CreateAndRegisterApp<Server::CServerApp>();
	Server->Start();
	std::cout << "End Server\n";
}