/**
* @file game_server.cpp
*
* @author Hourui (liquidmonkey)
*/

#include "GameServer.hpp"
#include "ServiceManager.hpp"
#include "ServiceUserManager.hpp"
#include "logger.hpp"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace main
{
////////////////////////////////////////////////////////////////////////////////////////////////////
bool 
GameServer::OnStart(void)
{
	m_io_service.start();
	m_dispatch_service.start(1);

	m_game_server.init(5000, &m_io_service, &m_dispatch_service);
	m_game_server.start("0.0.0.0", 8001);

	HOOK_SERVICE<SRT::ServiceUserManager>();


	Clog::info("Server Starting ...");

	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void 
GameServer::OnStop(void)
{
	m_game_server.stop();

	m_io_service.stop();
	m_dispatch_service.stop();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}//namespace main
////////////////////////////////////////////////////////////////////////////////////////////////////
}//namespace Utility 
