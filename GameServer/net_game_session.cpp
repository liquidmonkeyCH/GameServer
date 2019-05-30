/**
* @file net_game_session.cpp
*
* @author Hourui (liquidmonkey)
*/

#include "net_game_session.hpp"
#include "logger.hpp"

#include "ServiceManager.hpp"
#include "ServiceUserManager.hpp"
#include "MessageHandler_User.hpp"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
namespace net
{
////////////////////////////////////////////////////////////////////////////////////////////////////
game_session::game_session(void):m_bReg(false)
{
	Clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void game_session::Clear(void)
{
	m_uiState = eNone;

	m_bLog = false;

	m_bNewCreate = false;

	m_pUser = NULL;

	memset(m_szAccount, 0, SRT::ACCOUNT_LEN + 2);

	m_siBattleCode = 0;
	m_uiUserCode = 0;
	m_uiOrder = 0;
	m_bLogin = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void game_session::on_connect(void)
{
	m_socket_impl.set_no_delay(true);
	m_socket_impl.set_keep_alive(true, 1000, 1000, 15);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void game_session::on_close(net::session_iface::reason)
{
	Clog::info("CardServer,Client to GateServer Connector is Close!,client ip=%s", m_socket->get_host().c_str());

	SRT::ServiceUserManager* pService = Utility::GetService<SRT::ServiceUserManager>();
	uchar8 ucBattleStatus = pService->GetBattleStatus(this);
	// 非正常结束
	if (ucBattleStatus != 2)
	{
		game_session* pRival = pService->GetBattleRivalSession(this);
		if (pRival)
		{
			SRT::MS_GC_REQUEST_DISCONNECT kgc;
			kgc.m_uiMessageId = SRT::MS_GC_REQUEST_DISCONNECT::GetID();
			kgc.m_uiLen = sizeof(SRT::MS_GC_REQUEST_DISCONNECT);
			kgc.m_bIsNormalDisconnect = false;

			pRival->send((const char*)&kgc, kgc.m_uiLen);

			pRival->close(net::session_iface::reason::cs_service_stop);
		}
	}

	pService->ClearBattle(this);

	pService->ClearLoginUser(this->m_uiUserCode);

	Clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}// namespace net
////////////////////////////////////////////////////////////////////////////////////////////////////
}//namespace Utility 