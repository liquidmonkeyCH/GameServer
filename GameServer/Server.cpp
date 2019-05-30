/**
* @file Server.cpp
*
* @author Hourui (liquidmonkey)
**/

#include "Server.hpp"
#include <iostream>
#include <signal.h>
#include "logger.hpp"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////
namespace main
{
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
#ifdef _WIN32
	std::string str;
	do {
		std::cin >> str;
		if (str.compare("exit") == 0)
			break;
	} while (true);
	Stop();
#endif // _WIN32	
}
////////////////////////////////////////////////////////////////////////////////
void
Server::Stop(void)
{
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
void
Server::setsignal(void)
{
#ifndef _WIN32
	signal(SIGHUP, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	sigaction act;
	sigemptyset(&act.sa_mask);
	atc.sa_flags = SA_NODEFER | SA_ONSTACK | SA_RESETHAND;
	sigaction(SIGTERM, &act, NULL);
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
