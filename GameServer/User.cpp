#include "User.hpp"

//#include "DbCacheChannel.h"

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
CUser::CUser(void):	
	m_pCardSession(NULL),
	m_pPlayer(NULL),
	m_UserBasicInfo(this)	
{	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CUser::~CUser(void)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
CUser::Clear(void)
{		
	m_pCardSession = NULL;
	m_pPlayer = NULL;	
	
	m_UserBasicInfo.Clear();
	//m_UserCard.Clear();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
CUser::Offline(bool bDetach)
{
/*
	if(bDetach)
	{
		m_UserItem.SendUpdate(true);
		m_UserNotice.SendUpdate();
		m_UserRecord.SendUpdate();
		GetService<ServiceMatchManager>()->OffLine(this);
		
		return;
	}
	
	m_UserScene.SendUpdate(true);
		
	
	m_pPlayer->offline();

	MS_GD_USER_OFFLINE sMS_GD_USER_OFFLINE;
	
	sMS_GD_USER_OFFLINE.m_uiMessageId = MS_GD_USER_OFFLINE::GetID();
	sMS_GD_USER_OFFLINE.m_uiLen = sizeof(MS_GD_USER_OFFLINE);
	
	sMS_GD_USER_OFFLINE.m_siUserCode = m_UserBasicInfo.GetCode();
	sMS_GD_USER_OFFLINE.m_bOnline = false;
	sMS_GD_USER_OFFLINE.m_siTotalOnline = m_UserBasicInfo.TotalOnline();
	sMS_GD_USER_OFFLINE.m_siAllOnline = m_UserBasicInfo.GetAllOnline();
	
	g_pServer->getDbCacheChannel()->SendPacket(&sMS_GD_USER_OFFLINE,sMS_GD_USER_OFFLINE.m_uiLen);
	
*/	
	m_pCardSession = NULL;
	m_pPlayer = NULL;	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}