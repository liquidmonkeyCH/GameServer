#ifndef __CS_COMMONDEFINE_HPP__
#define __CS_COMMONDEFINE_HPP__

#include "csCommonEnum.hpp"
#include "csCommonStruct.hpp"
#include "logger.hpp"

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
#define FUNCTION_LOG(__siId)	\
	Clog::info("[%u][%lu] %s", __siId,::GetCurrentThreadId(),__FUNCTION__);

//#define SDO_LOG(__szFormat, ...)	 					g_pServer->getLog()->logLn(CLog::LL_1,__szFormat,##__VA_ARGS__);
////////////////////////////////////////////////////////////////////////////////////////////////////
enum ProtocolType
{
	Protocol_Game_Client		= 0x01,
};
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ProtocolClass
{
	Protocol_Class_User			= 0x01,
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}

// 		DECLARE_PROTOCOL_ID(		0x0A,		0x0F,		 0x0C) = 0x0A0F0C
#define DECLARE_PROTOCOL_ID(ProtocolType,ProtocolClass,ProtocolId)		\
public:																	\
	static uint32 GetID(void)											\
	{																	\
		return (ProtocolType << 16| ProtocolClass << 8 | ProtocolId);	\
	}																	\
	static uint32 GetType(void)											\
	{																	\
		return ProtocolType;											\
	}																	\
	uint32 getMessageId(void)											\
	{																	\
		return (ProtocolType << 16 | ProtocolClass << 8 | ProtocolId);	\
	}
	
#define REGISTER_MESSAGE(__szName)													\
	pMessage = new CMessage();														\
	if(pMessage == NULL){															\
		CDispatchService::setErrorCode(CDispatchService::DSR_NULL);					\
		return;																		\
	}																				\
	static_assert(sizeof(MS_##__szName)<=MAX_PACKET_LEN,"MS_"#__szName" TOO LARGE!");	\
	pMessage->m_sMessageName    = #__szName; 										\
	pMessage->m_uiMessageType   = MS_##__szName::GetType();							\
	pMessage->m_uiMessageId     = MS_##__szName::GetID();							\
	pMessage->m_pMessageHandler = CMessageHandlerCollection::__szName##_Handler;	\
	CMessageHandlerFactory::addMessage(pMessage);
	
#define REGISTER_MESSAGE_EX(__szName)												\
	pMessage = new CMessage();														\
	if(pMessage == NULL){															\
	CDispatchService::setErrorCode(CDispatchService::DSR_NULL);						\
	return;																			\
	}																				\
	static_assert(sizeof(MS_##__szName)<=MAX_PACKET_LEN,"MS_"#__szName" TOO LARGE!");	\
	pMessage->m_sMessageName    = #__szName; 										\
	pMessage->m_uiMessageType   = MS_##__szName::GetType();							\
	pMessage->m_uiMessageId     = MS_##__szName::GetID();							\
	pMessage->m_pMessageHandler = CMessageHandlerCollection::__szName##_Handler_Ex;	\
	CMessageHandlerFactory::addMessage(pMessage);


#endif // __PROTOCOL_HPP__
