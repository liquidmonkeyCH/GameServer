// game_server.cpp : Defines the entry point for the console application.
//

#include "GameServer.hpp"
#include "Singleton.hpp"
#include "logger.hpp"

using namespace Utility;

class test
{
public:
	static int* instance(void)
	{
		static int num;
		return &num;
	}
};

int main(int argc, char* argv[])
{
	logger klogger(logger::log_level::debug);
	Clog::active_logger(&klogger);

	Clog::info("%p", test::instance());

#ifndef _WIN32
	int pid = fork();
	if (pid != 0)
	{
		// parent exit
		exit(-1);
	}
	// create a new session
#endif // !_WIN32

	Clog::info("%p", test::instance());
	/*
	CSingleton<main::GameServer>* server = CSingleton<main::GameServer>::GetInstance();

	if (!server->Start(true, "game_server",argc,argv))
		return 0;

	server->Run();
	*/
	system("pause");
    return 0;
}

