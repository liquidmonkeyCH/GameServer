/**
* @file Server.hpp
*
* @author Hourui (liquidmonkey)
**/

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <mutex>
#include <condition_variable>
#include <string>
#include <vector>

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////
namespace main
{
////////////////////////////////////////////////////////////////////////////////
class Server
{
public:
	Server(void) = default;
	~Server(void) = default;
	using param_list = std::vector<std::string>;
public:
	bool Start(bool bDaemon, const char* szServerName,int nParam,char* pParams[]);
	void Run(void);
	void Stop(void);
	size_t getParamCount(void);
	const char* getParam(size_t n);
	const char* getName(void);
protected:
	virtual bool OnStart(void) = 0;
	virtual void OnStop(void) = 0;
private:
	void daemon(void);
	void setsignal(void);
private:
	std::string				m_kName;
	param_list				m_kParamList;
	bool					m_running;
	std::mutex				m_mutex;
	std::condition_variable	m_cv;
};
////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
} //namespace Utility
#endif //__SERVICE_HPP__
