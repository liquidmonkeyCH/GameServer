// GameServer.cpp : Defines the entry point for the console application.
//

#include "GameServer.hpp"
#include "Singleton.hpp"

using namespace Utility;

int main(int argc, char* argv[])
{
	main::Server* server = CSingleton<main::GameServer>::GetInstance();

	if (!server->Start(true, "GameServer",argc,argv))
		return 0;

	server->Run();

    return 0;
}

