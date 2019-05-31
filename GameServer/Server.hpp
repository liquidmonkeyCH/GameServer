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
private:
	class controler
	{
	public:
		controler(void) = default;
		~controler(void) = default;
		void run(void);
		void stop(void);
	private:
		std::mutex m_mutex;
		std::condition_variable	m_cv;
	};
public:
	Server(void) = default;
	~Server(void) = default;
	using param_list = std::vector<std::string>;
	friend void on_signal(int n);
public:
	bool Start(bool bDaemon, const char* szServerName,int nParam,char* pParams[]);
	void Run(void);
protected:
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
};
////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////
} //namespace Utility
#endif //__SERVICE_HPP__
