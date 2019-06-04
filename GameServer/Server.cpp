/**
* @file Server.cpp
*
* @author Hourui (liquidmonkey)
**/

#include "Server.hpp"
#include "Singleton.hpp"
#include <iostream>
#include <signal.h>
#include "logger.hpp"
#include <stdio.h>
#include <stdlib.h>

#ifndef _WIN32
#include <unistd.h>
#endif

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////
namespace main
{
////////////////////////////////////////////////////////////////////////////////
void 
Server::controler::run(void)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_cv.wait(lock);
}
////////////////////////////////////////////////////////////////////////////////
void
Server::controler::stop(void)
{
	m_cv.notify_all();
}
////////////////////////////////////////////////////////////////////////////////
Server::controler*
Server::get_controler(void)
{
	static controler m_controler;
	return &m_controler;
}
////////////////////////////////////////////////////////////////////////////////
bool 
Server::Start(const char* szServerName, int nParam, char* pParams[])
{
	bool bDaemon = false;
	for (int i = 0; i < nParam; ++i)
	{
		if (strcmp(pParams[i], "-d") == 0 || strcmp(pParams[i], "-daemon") == 0)
			bDaemon = true;

		m_kParamList.push_back(pParams[i]);
	}

	if (bDaemon)
		daemon();

	setsignal();
	m_kName = szServerName;

	return OnStart();
}
////////////////////////////////////////////////////////////////////////////////
void
Server::Run(void)
{
	Clog::info("%s start!", m_kName.c_str());
	get_controler()->run();
	OnStop();
}
////////////////////////////////////////////////////////////////////////////////
void
Server::daemon(void)
{
#ifndef _WIN32
	int pid = fork();
	if (pid != 0)
	{
		// parent exit
		_exit(-1);
	}
	// create a new session
	setsid();

	fclose(stdin);
	fclose(stdout);
	fclose(stderr);
#endif // !_WIN32
}
////////////////////////////////////////////////////////////////////////////////
void on_signal(int n)
{
	if (n == SIGINT || n == SIGTERM)
	{
		Server::get_controler()->stop();
		return;
	}
}
////////////////////////////////////////////////////////////////////////////////
void
Server::setsignal(void)
{
#ifndef _WIN32
	signal(SIGHUP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
	act.sa_handler = on_signal;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
#else
	signal(SIGINT, on_signal);
	signal(SIGTERM, on_signal);
#endif // !_WIN32
}
////////////////////////////////////////////////////////////////////////////////
size_t
Server::getParamCount(void)
{
	return m_kParamList.size();
}
////////////////////////////////////////////////////////////////////////////////
const char*
Server::getParam(size_t n)
{
	if (n >= m_kParamList.size())
		return nullptr;

	return m_kParamList[n].c_str();
}
////////////////////////////////////////////////////////////////////////////////
const char*
Server::getName(void)
{
	return m_kName.c_str();
}
////////////////////////////////////////////////////////////////////////////////
}// namespace main
////////////////////////////////////////////////////////////////////////////////
} //namespace Utility
