#include "UserBasicInfo.hpp"

//#include "ServiceManager.hpp"
//#include "ServiceUserManager.hpp"
//#include "User/MessageHandler_User.hpp"
//#include "GameServer.hpp"
//#include "DbCacheChannel.h"


namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
CUserBasicInfo::CUserBasicInfo(CUser* pUser):
	m_pUser(pUser)
{
	Clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CUserBasicInfo::~CUserBasicInfo(void)
{
	Clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
CUserBasicInfo::Clear(void)
{
	m_siCode = 0;	
	memset(m_szName,0,sizeof(char)*(NICK_NAME_LEN+2));
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
CUserBasicInfo::Initialize(Protocol_UserBasicInfo& kInfo)
{	
	m_siCode = kInfo.m_siUserCode;
	strncpy(m_szName,kInfo.m_szName,NICK_NAME_LEN);
	m_szName[NICK_NAME_LEN] = 0x0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
CUserBasicInfo::SendUpdate(void)
{
	if(!m_bUpdate)
		return;
	/*		
	MS_GD_SAVE_USER_BASIC_INFO sMS_GD_SAVE_USER_BASIC_INFO;
	sMS_GD_SAVE_USER_BASIC_INFO.m_uiMessageId = MS_GD_SAVE_USER_BASIC_INFO::GetID();
	sMS_GD_SAVE_USER_BASIC_INFO.m_uiLen = sizeof(MS_GD_SAVE_USER_BASIC_INFO);
	
	sMS_GD_SAVE_USER_BASIC_INFO.m_kInfo.m_siUserCode = m_siCode;	
	strncpy(sMS_GD_SAVE_USER_BASIC_INFO.m_kInfo.m_szName,m_szName,NICK_NAME_LEN);
	sMS_GD_SAVE_USER_BASIC_INFO.m_kInfo.m_szName[NICK_NAME_LEN] = 0x0;	
	
	g_pServer->getDbCacheChannel()->SendPacket(&sMS_GD_SAVE_USER_BASIC_INFO,sMS_GD_SAVE_USER_BASIC_INFO.m_uiLen);
	*/
	m_bUpdate = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
CUserBasicInfo::SendInfo(void)
{	
	/*
	MS_GC_USER_BASIC_INFO sMS_GC_USER_BASIC_INFO;
	sMS_GC_USER_BASIC_INFO.m_siUserCode = m_siCode;
	sMS_GC_USER_BASIC_INFO.m_szName = m_szName;
	
	MS_GAME_PROTOCOL kProtocol;
	sMS_GC_USER_BASIC_INFO.Pack(kProtocol);
	if(m_pUser->m_pGameSession)
		m_pUser->m_pGameSession->SendPacket(&kProtocol,kProtocol.m_uiLen);
	*/		
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}