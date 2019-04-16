/**
* @file Server.cpp
*
* @author Hourui (liquidmonkey)
**/

#include "Server.hpp"
#include <iostream>
#include <signal.h>

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////
namespace main
{
////////////////////////////////////////////////////////////////////////////////
bool 
Server::Start(bool bDaemon, const char* szServerName, int nParam, char* pParams[])
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_running)
		return false;

	if (bDaemon)
		daemon();

	setsignal();

	m_running = true;
	m_kName = szServerName;

	for (int i = 0; i < nParam; ++i)
		m_kParamList.push_back(pParams[i]);

	return OnStart();
}
////////////////////////////////////////////////////////////////////////////////
void
Server::Run(void)
{
#ifdef _WIN32
	std::string str;
	do {
		std::cin >> str;
		if (str.compare("exit") == 0)
			break;
	} while (true);
	Stop();
#endif // _WIN32	
	std::unique_lock<std::mutex> lock(m_mutex);
	m_cv.wait(lock);
}
////////////////////////////////////////////////////////////////////////////////
void
Server::Stop(void)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (!m_running)
		return;

	OnStop();

	m_running = false;
	m_cv.notify_all();
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
