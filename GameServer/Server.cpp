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
bool 
Server::Start(bool bDaemon, const char* szServerName, int nParam, char* pParams[])
{
	if (bDaemon)
		daemon();

	setsignal();
	m_kName = szServerName;

	for (int i = 0; i < nParam; ++i)
		m_kParamList.push_back(pParams[i]);

	return OnStart();
}
////////////////////////////////////////////////////////////////////////////////
void
Server::Run(void)
{
	Clog::info("Server start!");	
	CSingleton<Server::controler>::GetInstance()->run();
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
		exit(-1);
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
	if (n == SIGINT)
	{
		CSingleton<Server::controler>::GetInstance()->stop();
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
	sigaction(SIGTERM, &act, NULL);
#else
	signal(SIGINT, on_signal);
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
