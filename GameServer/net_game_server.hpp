/**
* @file net_game_server.hpp
*
* @author Hourui (liquidmonkey)
*/
#ifndef __NET_GAME_SERVER_HPP__
#define __NET_GAME_SERVER_HPP__

#include "net_game_session.hpp"
#include "net_server.hpp"
#include "msg_controler_planA.hpp"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace net
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class GameServer : public net::server_wrap<Gamesession, msg::planA::controler>
{
public:
	GameServer(void) = default;
	~GameServer(void) = default;
public:
	void on_start(void);
	void on_stop(void);
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}//namespace Utility 
#endif //__NET_SERVER_HPP__#pragma once
