// game_server.cpp : Defines the entry point for the console application.
//

#include "GameServer.hpp"
#include "Singleton.hpp"
#include "logger.hpp"

using namespace Utility;

int main(int argc, char* argv[])
{
	logger klogger(logger::log_level::debug);
	Clog::active_logger(&klogger);

	CSingleton<main::GameServer>* server = CSingleton<main::GameServer>::GetInstance();

	if (!server->Start(true, "game_server",argc,argv))
		return 0;

	server->Run();
#ifdef _WIN32
	system("pause");
#endif
    return 0;
}

