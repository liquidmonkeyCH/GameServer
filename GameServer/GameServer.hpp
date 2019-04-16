/**
* @file GameServer.hpp
*
* @author Hourui (liquidmonkey)
*/
#ifndef __GAME_SERVER_HPP__
#define __GAME_SERVER_HPP__

#include "Server.hpp"
#include "net_io_service_iocp.hpp"
#include "msg_controler_planA.hpp"
#include "net_game_server.hpp"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace main 
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class GameServer : public Server
{
public:
	GameServer(void) = default;
	~GameServer(void) = default;
public:
	bool OnStart(void);
	void OnStop(void);
private:
	net::io_service_iocp		m_io_service;
	task::dispatcher_balance	m_dispatch_service;

	net::GameServer				m_kGameServer;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}//namespace main
////////////////////////////////////////////////////////////////////////////////////////////////////
}//namespace Utility 
#endif //__NET_SERVER_HPP__#pragma once
