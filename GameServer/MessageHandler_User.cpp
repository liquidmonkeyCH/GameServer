/**
 * @file CG_GET_PAY_Handler.cpp
 * 处理客户端更新充值请求
 *
 * @author Hourui (liquidmonkey)
 */
#include "MessageHandler_User.hpp"
#include "ServiceManager.hpp"
#include "ServiceUserManager.hpp"

//#include "ServiceVipManager.hpp"
//#include "ServiceItemManager.hpp"
//#include "ServiceLuaSupport.hpp"
//#include "LuaFunction.hpp"
//#include "User.hpp"

using namespace Utility;

namespace SRT
{
namespace CMessageHandlerCollection
{
////////////////////////////////////////////////////////////////////////////////////////////////////
int CG_LOGIN_Handler(task::object_iface* obj, const char* msg, void* ptr)
{
	net::game_session* pCardSession = dynamic_cast<net::game_session*>(obj);
	MS_CG_LOGIN* pMS_CG_LOGIN = (MS_CG_LOGIN*)msg;
	
	FUNCTION_LOG(pCardSession->get_fd());
	
	uint32 siUserCode = pCardSession->get_fd()+1000;
	
	Clog::info("uiUserCode=[%d]request login",siUserCode);		
	
	MS_GC_LOGIN kgc;
	kgc.m_uiMessageId = MS_GC_LOGIN::GetID();
	kgc.m_uiLen = sizeof(MS_GC_LOGIN);	
	
	// 已经登陆
	if(pCardSession->m_bLogin)
	{
		kgc.m_IsSuccess = false;		
		pCardSession->send((const char*)&kgc,kgc.m_uiLen);			
		return 0;		
	}

	// check if user can login?
	if(!GetService<ServiceUserManager>()->IsCanLogin(siUserCode,pCardSession))
	{
		kgc.m_IsSuccess = false;		
		pCardSession->send((const char*)&kgc,kgc.m_uiLen);
		return 0;
	}		
	
	pCardSession->m_uiUserCode = siUserCode;	
	pCardSession->m_bLogin = true;	
	// pCardSession->m_uiUserCode = pMS_CG_LOGIN->m_UniqueId;		
	
	
	bool bMatch = GetService<ServiceUserManager>()->AddLoginUser(pCardSession->m_uiUserCode,pCardSession);			

	// 回复登陆信息	
	kgc.m_IsSuccess = true;	
	pCardSession->send((const char*)&kgc,kgc.m_uiLen);
		
	if(bMatch)
	{
		// 回合开始  给自己发
		MS_GC_START_FIGHTT kgcRound;
		kgcRound.m_uiMessageId = MS_GC_START_FIGHTT::GetID();
		kgcRound.m_uiLen = sizeof(MS_GC_START_FIGHTT);
		
		kgcRound.m_IsHost = (pCardSession->m_uiOrder == 1)?true:false;
		pCardSession->send((const char*)&kgcRound,kgcRound.m_uiLen);

		// 回合开始  给对手发
		net::game_session* pRivalCardSession = GetService<ServiceUserManager>()->GetBattleRivalSession(pCardSession);
		if(pRivalCardSession)
		{
			kgcRound.m_IsHost = (pRivalCardSession->m_uiOrder == 1)?true:false;
			pRivalCardSession->send((const char*)&kgcRound,kgcRound.m_uiLen);
		}
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int CG_TRANSMIT_Handler(task::object_iface* obj, const char* msg, void* ptr)
{
	net::game_session* pCardSession = dynamic_cast<net::game_session*>(obj);
	MS_CG_TRANSMIT* pMS_CG_TRANSMIT = (MS_CG_TRANSMIT*)msg;
	
	FUNCTION_LOG(pCardSession->get_fd());
	
	if(pCardSession->m_siBattleCode <= 0)
	{
		Clog::info("uiUserCode=[%d] isnot battle status!", pCardSession->m_uiUserCode);
		return 1;
	}
		
	MS_GC_TRANSMIT kgc;
	kgc.m_uiMessageId = MS_GC_TRANSMIT::GetID();
	kgc.m_uiLen = sizeof(MS_GC_TRANSMIT);
	
	kgc.m_Opcode = pMS_CG_TRANSMIT->m_Opcode;
	memcpy(kgc.m_Json,pMS_CG_TRANSMIT->m_Json,4000);
	
	net::game_session* pRivalCardSession = GetService<ServiceUserManager>()->GetBattleRivalSession(pCardSession);
	if(pRivalCardSession)
		pRivalCardSession->send((const char*)&kgc,kgc.m_uiLen);
	
	return 0;	
}
int CG_REQUEST_DISCONNECT_Handler(task::object_iface* obj, const char* msg, void* ptr)
{
	net::game_session* pCardSession = dynamic_cast<net::game_session*>(obj);
	MS_CG_REQUEST_DISCONNECT* pMS_CG_REQUEST_DISCONNECT = (MS_CG_REQUEST_DISCONNECT*)msg;
	
	FUNCTION_LOG(pCardSession->get_fd());
	
	MS_GC_REQUEST_DISCONNECT kgc;
	kgc.m_uiMessageId = MS_GC_REQUEST_DISCONNECT::GetID();
	kgc.m_uiLen = sizeof(MS_GC_REQUEST_DISCONNECT);
	
	kgc.m_bIsNormalDisconnect = 1;
	
	net::game_session* pRivalCardSession = GetService<ServiceUserManager>()->GetBattleRivalSession(pCardSession);
	if(pRivalCardSession)
		pRivalCardSession->send((const char*)&kgc,kgc.m_uiLen);
		
	// 设置游戏正常结束
	GetService<ServiceUserManager>()->SetBattleStatus(pCardSession,2);	
		
	pCardSession->close(net::session_iface::reason::cs_service_stop);
	if(pRivalCardSession)
		pRivalCardSession->close(net::session_iface::reason::cs_service_stop);
	
	return 0;	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}//CMessageHandlerCollection
}//SRT