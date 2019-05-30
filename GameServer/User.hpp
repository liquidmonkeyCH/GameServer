#ifndef __USER_HPP__
#define __USER_HPP__

//#include "Obj.h"
#include "UserBasicInfo.hpp"
//#include "UserCard.h"

namespace Utility {
	namespace net {
		class game_session;
	}
}

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class CPlayer;
////////////////////////////////////////////////////////////////////////////////////////////////////
class CUser
{
public:
	friend class ServiceUserManager;
	friend class CUserBasicInfo;
	//friend class CUserCard;
public:
	CUser(void);
	~CUser(void);		
	
	void Clear(void);
	void Offline(bool bDetach = false);	
		
public:	
	sint64	GetCode(void){return m_UserBasicInfo.GetCode();}
	const char* GetName(void){return m_UserBasicInfo.GetName();}	
		
public:
	Utility::net::game_session* 	m_pCardSession;
	CPlayer*		m_pPlayer;	
	
	CUserBasicInfo	m_UserBasicInfo;
	//CUserCard		m_UserCard;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // __OBJECT_HPP__