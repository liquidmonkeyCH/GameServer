#ifndef __USER_BASIC_HPP__
#define __USER_BASIC_HPP__

#include "csCommonStruct.hpp"

//#include "User.hpp"

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class CUser;
//class CGameSession;
//class ServiceUserManager;
////////////////////////////////////////////////////////////////////////////////////////////////////
class CUserBasicInfo
{
public:
	//friend class ServiceUserManager;	
public:
	CUserBasicInfo(CUser* pUser);
	~CUserBasicInfo(void);
	
	void Initialize(Protocol_UserBasicInfo& kInfo);
	void Clear(void);
	
	void SendInfo(void);
	void SendUpdate(void);			
	
// 基本信息
public:
	sint64 GetCode(void) { return m_siCode; }
	const char* GetName(void) { return m_szName; }
private:		
	void changeName(const char* szName){ ::memcpy(m_szName,szName,NICK_NAME_LEN);m_szName[NICK_NAME_LEN] = 0x0;  m_bUpdate = true;}
private:
	bool	m_bUpdate;	
	
	// 基本信息
	sint64	m_siCode;					// 唯一编号
	char	m_szName[NICK_NAME_LEN+2];	// 名称
	
	CUser*	m_pUser;
};
////////////////////////////////////////////////////////////////////////////////////////////////////	
}

#endif // __USER_BASIC_HPP__