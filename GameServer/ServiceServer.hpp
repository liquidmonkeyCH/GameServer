#pragma once
/**
* @file ServiceServer.hpp
*
* @author Hourui (liquidmonkey)
**/

#ifndef __SERVICE_ENGINE_HPP__
#define __SERVICE_ENGINE_HPP__

#include "ServiceManager.hpp"
#include "net_io_service_iocp.hpp"
#include "msg_controler_planA.hpp"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////
class ServiceServer : public Service
{
public:
	DECLARE_SERVICE_ID(ServiceServer)
	void LoadFromDatabase(void);
public:
	net::io_service_iface* get_io_service(void);
	msg::planA::controler* get_controler(void);
private:
	net::io_service_iocp	m_io_service;
	msg::planA::controler	m_controler;
};
////////////////////////////////////////////////////////////////////////////////
} //namespace Utility
#endif //__SERVICE_HPP__