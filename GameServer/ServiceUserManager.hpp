#ifndef __SERVICE_USER_MANAGER_HPP__
#define __SERVICE_USER_MANAGER_HPP__

#include "ServiceManager.hpp"
#include "User.hpp"
#include "net_game_session.hpp"

#include "MemoryPool.hpp"
//#include "Utility.hpp"
#include "UniqueCode.hpp"

#include <mutex>

using namespace Utility;

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class CPlayer
{
private:
	friend class ServiceUserManager;
	friend class CUser;
	friend class CUserBasicInfo;

public:
	sint64 GetUserCode(void) { return m_siUserCode; }
	const char* GetName(void) { return m_szName; }
	const char* GetAccount(void) { return m_szAccount; }

private:
	sint64		m_siUserCode;
	char 		m_szName[NICK_NAME_LEN + 2];
	char		m_szAccount[ACCOUNT_LEN + 2];
};
////////////////////////////////////////////////////////////////////////////////////////////////////

struct LoginPlayer
{
	//char			m_szAccount[ACCOUNT_LEN+2];
	uint32			m_uiUserCode;
	net::game_session*	m_pSession;

	void Clear(void)
	{
		//memset(m_szAccount,0,sizeof(m_szAccount));
		m_uiUserCode = 0;
		m_pSession = NULL;
	}
};

struct Battle
{
	sint64			m_BattleCode;
	LoginPlayer*	m_pAttackPlayer;
	LoginPlayer*	m_pDefendPlayer;
	uchar8			m_ucStatus;		// 0:initial 1:battle start  2:normal end

	void Clear(void)
	{
		m_BattleCode = 0;
		m_pAttackPlayer = NULL;
		m_pDefendPlayer = NULL;
		m_ucStatus = 0;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
class ServiceUserManager : public Service
{
public:
	struct helpless
	{
		bool operator()(const char* const &L, const char* const &R) const
		{
			return strcmp(L, R) < 0;
		}
	};

	typedef std::map<sint64, CPlayer*> PLAYER_ID_MAP;
	typedef std::map<const char*, CPlayer*, helpless> PLAYER_ACCOUNT_MAP;

	typedef std::map<sint64, CUser*>	USER_ID_MAP;
	typedef std::set<sint64> LOADING_MAP;


	DECLARE_SERVICE_ID(ServiceUserManager);
public:
	void LoadFromDatabase(void);
	CPlayer* Attach(Protocol_UserBasicInfo& kInfo);
public:
	// find function
	CPlayer* GetPlayer(sint64 siUserCode);						// 查找离线用户
	CPlayer* GetPlayer(const char* szAccount);					// 查找离线用户

	CUser* GetUser(sint64 siUserCode);							// 查找在线用户

																// login function
	int Verify(net::game_session* pCardSession);
	//sint64 GetUserCode(const char* szAccount);
	sint64 GetUniqueCode(void);

	void Attach(CUser* pUser);					// 将用户加入在线管理
	void Detach(CUser* pUser);					// 从在线管理中移除用户并归还内存


private:
	CUser* createUser(CPlayer* pPlayer);
private:
	std::mutex 					m_kUserMonitor;
	std::mutex 					m_kPlayerMonitor;

	CMemoryPoolEx<CPlayer, 100>	m_kPlayerPool;
	PLAYER_ID_MAP				m_kPlayerIdTable;
	PLAYER_ACCOUNT_MAP			m_kPlayerAccountTable;


	CMemoryPoolEx<CUser, 100>	m_kUserTable;
	USER_ID_MAP					m_kUserIdTable;
	LOADING_MAP					m_kLoadingTable;

	CUniqueCode					m_kUniqueCode;
public:
	std::vector<LoginPlayer*>		m_vecLoginUser;
	std::map<sint64, Battle*>			m_mapBattle;

	// return login num;
	//sint32						AddLoginUser(uint32 uiUserCode,net::game_session* pSession);
	// return is start battle?
	bool						AddLoginUser(uint32 uiUserCode, net::game_session* pSession);
	bool						IsCanLogin(uint32 uiUserCode, net::game_session* pSession);
	net::game_session*		 		GetBattleRivalSession(net::game_session* pSession);
	uchar8				 		GetBattleStatus(net::game_session* pSession);
	void						SetBattleStatus(net::game_session* pSession, uchar8 uiStatus);

	//void						ClearLoginUser(LoginPlayer* pLoginUser);
	void						ClearBattle(net::game_session* pSession);
	void						ClearLoginUser(uint32 uiUserCode);

	LoginPlayer*				SearchFreeUser(void);
};
////////////////////////////////////////////////////////////////////////////////////////////////////	
}

#endif // __SERVICE_USER_MANAGER_HPP__
