/**
* @file net_game_session.hpp
*
* @author Hourui (liquidmonkey)
*/
#ifndef __NET_GAME_SESSION_HPP__
#define __NET_GAME_SESSION_HPP__

#include "net_session.hpp"
#include "mem_rotative_buffer.hpp"

#include "csCommonDefine.hpp"
#include "User.hpp"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace net
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class game_session : public net::session_wrap<net::socket_type::tcp, mem::rotative_buffer>
{
public:
	enum
	{
		eNone,
		eCreateUser,
		eLoading,
		eAttach,
		eLogin,
		eFight,
		eGM,
	};

	game_session();

	void on_close(net::session_iface::reason);
	void on_connect(void);
	void Clear(void);

public:
	bool	m_bReg;

	uchar8	m_uiState;
	bool	m_bNewCreate;
	SRT::CUser*	m_pUser;
	bool	m_bLog;
	char	m_szAccount[SRT::ACCOUNT_LEN + 2];

	uint32	m_uiUserCode;
	sint64	m_siBattleCode;
	uint32	m_uiOrder;
	bool	m_bLogin;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}// namespace net
////////////////////////////////////////////////////////////////////////////////////////////////////
}//namespace Utility 
#endif //__NET_SERVER_HPP__