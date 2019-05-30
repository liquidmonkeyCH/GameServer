#include "ServiceManager.hpp"
#include "ServiceUserManager.hpp"

/*
#include "ServiceLogManager.hpp"
#include "ServiceLuaSupport.hpp"
#include "LuaFunction.hpp"
*/

#include "GameServer.hpp"
#include "net_game_session.hpp"

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
ServiceUserManager::ServiceUserManager(void) :
	m_kUniqueCode(1)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
ServiceUserManager::~ServiceUserManager(void)
{
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
	ServiceUserManager::LoadFromDatabase(void)
{
	/*
	m_kUserTable.Init(g_pServer->getGameEpollService()->getMaxSession());
	chat_reg();

	memset(m_kStarArrayTable,0,sizeof(StarArray_Config*)*MAX_HERO_ATTR);

	// 读取配置
	TSTRING kFilePath = CSystem::getCurrentDirectory() + "/data/StarArray_conf.csv";

	CFileLoader kFileLoader(kFilePath);
	StrSpliter<1024> kStrSpliter("");
	StrSpliter<1024> kStrSpliter2("");

	if(kFileLoader.Next() < 6)
	{
	g_pServer->getLog()->logLn(CLog::LL_0,"[Error] StarArray_conf open failure!");
	throw ServiceManagerException(ServiceManagerException::INIT_ERROR);
	}

	while(kFileLoader.Next() >= 6)
	{
	uchar8 uiAttr = (uchar8)atoi(kFileLoader.getData(0)) - 1;

	if(uiAttr >= MAX_HERO_ATTR || m_kStarArrayTable[uiAttr] != NULL)
	{
	g_pServer->getLog()->logLn(CLog::LL_0,"[Error] StarArray_conf Attr duplicate,Attr=%d,line=%d",uiAttr,kFileLoader.GetCurrentRow());
	throw ServiceManagerException(ServiceManagerException::INIT_ERROR);
	}

	StarArray_Config* pConf = new StarArray_Config;
	m_kStarArrayTable[uiAttr] = pConf;

	pConf->m_uiAttr = uiAttr;
	pConf->m_uiGrow = (uchar8)atoi(kFileLoader.getData(2));
	// sam add open level
	pConf->m_uiOpenLevel = (uchar8)atoi(kFileLoader.getData(6));
	pConf->m_uiAffectAttr = (uchar8)atoi(kFileLoader.getData(7))-1;
	if(pConf->m_uiAffectAttr >= MAX_HERO_ATTR)
	{
	g_pServer->getLog()->logLn(CLog::LL_0,"[Error] StarArray_conf affect attr err,Attr=%d,line=%d",pConf->m_uiAffectAttr,kFileLoader.GetCurrentRow());
	throw ServiceManagerException(ServiceManagerException::INIT_ERROR);
	}
	if(pConf->m_uiGrow != 0)
	continue;


	kStrSpliter.reset(kFileLoader.getData(3),"|");

	for(uchar8 i=0; i<kStrSpliter.size(); ++i)
	{
	uiAttr = (uchar8)atoi(kStrSpliter.getData(i)) - 1;
	if(uiAttr >= MAX_HERO_ATTR)
	break;

	pConf->m_uiNeedAttr.push_back(uiAttr);
	}

	kStrSpliter.reset(kFileLoader.getData(4),"|");
	kStrSpliter2.reset(kFileLoader.getData(5),"|");

	if(kStrSpliter.size() != kStrSpliter2.size())
	{
	g_pServer->getLog()->logLn(CLog::LL_0,"[Error] StarArray_conf Levelsize != AttrSize,line=%d",kFileLoader.GetCurrentRow());
	throw ServiceManagerException(ServiceManagerException::INIT_ERROR);
	}

	for(uchar8 i=0; i<kStrSpliter.size(); ++i)
	{
	uiAttr = (uchar8)atoi(kStrSpliter.getData(i));
	if(uiAttr == 0)
	break;

	pConf->m_kNeedLevel[uiAttr] = atoi(kStrSpliter2.getData(i));
	}
	}

	//load energy信息
	LUA_BEGIN
	LuaFunction<luaf_res,5> Information(L,"Energy","Information");
	luaf_res res = Information();
	m_Energy_Info.m_siMAX_ENERGY = res.get<F32>(0);
	m_Energy_Info.m_siCONSUME_ENERGY = res.get<F32>(1);
	m_Energy_Info.m_siINCREACE_DELAY = res.get<sint32>(2)*60;
	m_Energy_Info.m_siINCREACE_NUM = res.get<sint32>(3);
	m_Energy_Info.m_siGiveValue = res.get<sint32>(4);
	LuaFunction<luaf_res,2> Sober(L,"Sober","Information");
	res = Sober();
	SOBER_ONLINE = res.get<sint32>(0);
	SOBER_OFFLINE = res.get<sint32>(1);
	LUA_END
	*/
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CPlayer*
	ServiceUserManager::GetPlayer(const char* szAccount)
{
	std::lock_guard<std::mutex> lock(m_kPlayerMonitor);

	PLAYER_ACCOUNT_MAP::iterator it = m_kPlayerAccountTable.find(szAccount);

	if (it != m_kPlayerAccountTable.end())
		return it->second;

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
sint64
ServiceUserManager::GetUserCode(const char* szAccount)
{
synchronized sync(&m_kPlayerMonitor);

PLAYER_ACCOUNT_MAP::iterator it=m_kPlayerAccountTable.find(szAccount);
if(it != m_kPlayerAccountTable.end())
return it->second->GetUserCode();
return 0;
}
*/
////////////////////////////////////////////////////////////////////////////////////////////////////
CUser*
	ServiceUserManager::GetUser(sint64 siUserCode)
{
	std::lock_guard<std::mutex> lock(m_kUserMonitor);

	USER_ID_MAP::iterator it = m_kUserIdTable.find(siUserCode);

	if (it != m_kUserIdTable.end())
		return it->second;

	return NULL;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CUser*
	ServiceUserManager::createUser(CPlayer* pPlayer)
{
	std::lock_guard<std::mutex> lock(m_kUserMonitor);

	if (m_kLoadingTable.find(pPlayer->m_siUserCode) != m_kLoadingTable.end())
		return NULL;

	if (m_kUserIdTable.find(pPlayer->m_siUserCode) != m_kUserIdTable.end())
		return NULL;

	m_kLoadingTable.insert(pPlayer->m_siUserCode);

	CUser* pUser = m_kUserTable.malloc();

	pUser->m_pPlayer = pPlayer;

	return pUser;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
int
	ServiceUserManager::Verify(net::game_session* pCardSession)
{
	/*
	CPlayer* pPlayer = NULL;
	{
	synchronized sync(&m_kPlayerMonitor);

	PLAYER_ACCOUNT_MAP::iterator it=m_kPlayerAccountTable.find(pCardSession->m_szAccount);
	if(it == m_kPlayerAccountTable.end())
	{
	pCardSession->m_bNewCreate = true;
	pCardSession->m_uiState = CCardSession::eCreateUser;
	return MS_GC_LOGIN_CLIENT::eNeedCreateUser;
	}

	pPlayer = it->second;
	}

	CUser* pUser = GetUser(pPlayer->m_siUserCode);

	if(pUser)	// 用户已登录且资料完整
	{
	}
	else
	{
	pUser = createUser(pPlayer);

	if(!pUser)
	{
	// 有其他用户正在登陆此帐号
	pCardSession->doClose(CSession::CS_SERVICE_STOP);
	return MS_GC_LOGIN_CLIENT::eSuccess;
	}

	// 绑定用户及Session
	pUser->m_pCardSession = pCardSession;
	pCardSession->m_pUser = pUser;

	// 获取用户信息
	pCardSession->m_uiState = CCardSession::eLoading;
	}

	*/
	//return MS_GC_LOGIN_CLIENT::eSuccess;
	return 1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
CPlayer*
	ServiceUserManager::Attach(Protocol_UserBasicInfo& kInfo)
{
	CPlayer* pPlayer = m_kPlayerPool.malloc();

	pPlayer->m_siUserCode = kInfo.m_siUserCode;
	memcpy(pPlayer->m_szAccount, kInfo.m_szAccount, ACCOUNT_LEN);
	pPlayer->m_szAccount[ACCOUNT_LEN + 2] = 0x0;
	memcpy(pPlayer->m_szName, kInfo.m_szName, NICK_NAME_LEN);
	pPlayer->m_szName[NICK_NAME_LEN + 2] = 0x0;

	std::lock_guard<std::mutex> lock(m_kPlayerMonitor);

	m_kPlayerIdTable[pPlayer->m_siUserCode] = pPlayer;
	m_kPlayerAccountTable[pPlayer->m_szAccount] = pPlayer;

	return pPlayer;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
	ServiceUserManager::Attach(CUser* pUser)
{
	std::lock_guard<std::mutex> lock(m_kUserMonitor);

	m_kLoadingTable.erase(pUser->m_pPlayer->m_siUserCode);

	m_kUserIdTable[pUser->m_pPlayer->m_siUserCode] = pUser;

	//size_t uiOnline = m_kUserIdTable.size();	
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void
	ServiceUserManager::Detach(CUser* pUser)
{
	std::lock_guard<std::mutex> lock(m_kUserMonitor);

	m_kUserIdTable.erase(pUser->m_pPlayer->m_siUserCode);
	m_kLoadingTable.erase(pUser->m_pPlayer->m_siUserCode);

	pUser->Clear();

	m_kUserTable.free(pUser);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
sint64
	ServiceUserManager::GetUniqueCode(void)
{
	return m_kUniqueCode.CreateCode();
}
////////////////////////////////////////////////////////////////////////////////////////////////////
// tmp login
////////////////////////////////////////////////////////////////////////////////////////////////////
bool ServiceUserManager::AddLoginUser(uint32 uiUserCode, net::game_session* pSession)
{
	LoginPlayer* pFreeUser = SearchFreeUser();

	LoginPlayer* pLoginUser = new LoginPlayer;
	//strncpy(pLoginUser->m_szAccount,pszAcount,ACCOUNT_LEN);
	//pLoginUser->m_szAccount[ACCOUNT_LEN] = 0x0;		
	pLoginUser->m_uiUserCode = uiUserCode;
	pLoginUser->m_pSession = pSession;

	m_vecLoginUser.push_back(pLoginUser);

	/*if(m_vecLoginUser.size() >= 2)
	{
	Battle* pBattle = new Battle;
	pBattle->m_BattleCode = GetUniqueCode();
	pBattle->m_pAttackPlayer = m_vecLoginUser[0];
	pBattle->m_pDefendPlayer = m_vecLoginUser[1];
	pBattle->m_ucStatus = 1;
	m_mapBattle[pBattle->m_BattleCode] = pBattle;

	if(pBattle->m_pAttackPlayer->m_pSession)
	pBattle->m_pAttackPlayer->m_pSession->m_siBattleCode = pBattle->m_BattleCode;
	if(pBattle->m_pDefendPlayer->m_pSession)
	pBattle->m_pDefendPlayer->m_pSession->m_siBattleCode = pBattle->m_BattleCode;
	}
	return m_vecLoginUser.size();
	*/


	if (pFreeUser)
	{
		Battle* pBattle = new Battle;
		pBattle->m_BattleCode = GetUniqueCode();
		pBattle->m_pAttackPlayer = pFreeUser;
		pBattle->m_pDefendPlayer = pLoginUser;
		pBattle->m_ucStatus = 1;
		m_mapBattle[pBattle->m_BattleCode] = pBattle;

		if (pBattle->m_pAttackPlayer->m_pSession)
		{
			pBattle->m_pAttackPlayer->m_pSession->m_siBattleCode = pBattle->m_BattleCode;
			pBattle->m_pAttackPlayer->m_pSession->m_uiOrder = 1;
		}
		if (pBattle->m_pDefendPlayer->m_pSession)
		{
			pBattle->m_pDefendPlayer->m_pSession->m_siBattleCode = pBattle->m_BattleCode;
			pBattle->m_pDefendPlayer->m_pSession->m_uiOrder = 2;
		}
		return true;
	}

	return false;
}
LoginPlayer* ServiceUserManager::SearchFreeUser(void)
{
	LoginPlayer* pPlayer = NULL;

	std::vector<LoginPlayer*>::iterator it2;
	for (it2 = m_vecLoginUser.begin(); it2 != m_vecLoginUser.end(); it2++)
	{
		pPlayer = *it2;
		if (pPlayer->m_pSession &&  pPlayer->m_pSession->m_siBattleCode == 0)
			return pPlayer;
	}
	return NULL;
}
bool
	ServiceUserManager::IsCanLogin(uint32 uiUserCode, net::game_session* pSession)
{
	LoginPlayer* pLoginUser = NULL;
	//vector<LoginPlayer*>		m_vecLoginUser;
	std::vector<LoginPlayer*>::iterator it;
	for (it = m_vecLoginUser.begin(); it != m_vecLoginUser.end(); it++)
	{
		pLoginUser = *it;
		if (uiUserCode == pLoginUser->m_uiUserCode)
			return false;
	}

	//if(m_vecLoginUser.size() >= 2)
	//return false;

	return true;
}
net::game_session*
	ServiceUserManager::GetBattleRivalSession(net::game_session* pSession)
{
	Battle* pBattle = NULL;
	sint64 siBattleCode = pSession->m_siBattleCode;
	std::map<sint64, Battle*>::iterator it;
	it = m_mapBattle.find(siBattleCode);
	if (it == m_mapBattle.end())
		return NULL;

	pBattle = it->second;

	if (pBattle->m_pAttackPlayer->m_pSession == pSession)
		return pBattle->m_pDefendPlayer->m_pSession;
	else if (pBattle->m_pDefendPlayer->m_pSession == pSession)
		return pBattle->m_pAttackPlayer->m_pSession;
	else
		return NULL;
}
uchar8
	ServiceUserManager::GetBattleStatus(net::game_session* pSession)
{
	Battle* pBattle = NULL;
	sint64 siBattleCode = pSession->m_siBattleCode;
	std::map<sint64, Battle*>::iterator it;
	it = m_mapBattle.find(siBattleCode);
	if (it == m_mapBattle.end())
		return 0;

	pBattle = it->second;

	return pBattle->m_ucStatus;
}
void
	ServiceUserManager::SetBattleStatus(net::game_session* pSession, uchar8 uiStatus)
{
	if (!pSession)
		return;

	Battle* pBattle = NULL;
	std::map<sint64, Battle*>::iterator it;
	it = m_mapBattle.find(pSession->m_siBattleCode);
	if (it == m_mapBattle.end())
		return;

	pBattle = it->second;

	pBattle->m_ucStatus = uiStatus;
}

void
	ServiceUserManager::ClearBattle(net::game_session* pSession)
{
	//vector<LoginPlayer*>		m_vecLoginUser;
	//map<sint64,Battle*>			m_mapBattle;	

	Battle* pBattle = NULL;
	sint64 siBattleCode = pSession->m_siBattleCode;
	std::map<sint64, Battle*>::iterator it;
	it = m_mapBattle.find(siBattleCode);
	if (it == m_mapBattle.end())
		return;

	pBattle = it->second;

	LoginPlayer* pLoginPlayer = NULL;
	for (uchar8 i = 0; i<2; i++)
	{
		if (i == 0)
			pLoginPlayer = pBattle->m_pAttackPlayer;
		else
			pLoginPlayer = pBattle->m_pDefendPlayer;

		ClearLoginUser(pLoginPlayer->m_uiUserCode);
	}

	pBattle->Clear();
	delete pBattle;
	m_mapBattle.erase(it);
}
/*
void
ServiceUserManager::ClearLoginUser(LoginPlayer* pLoginPlayer)
{
if(pLoginPlayer == NULL)
return;

vector<LoginPlayer*>::iterator it2;
for(it2=m_vecLoginUser.begin();it2!=m_vecLoginUser.end();it2++)
{
if(*it2 == pLoginPlayer)
{
(*it2)->Clear();
delete pLoginPlayer;
m_vecLoginUser.erase(it2);
break;
}
}
}*/
void
	ServiceUserManager::ClearLoginUser(uint32 uiUserCode)
{
	LoginPlayer* pLoginPlayer = NULL;
	std::vector<LoginPlayer*>::iterator it2;
	for (it2 = m_vecLoginUser.begin(); it2 != m_vecLoginUser.end(); it2++)
	{
		pLoginPlayer = *it2;
		if ((*it2)->m_uiUserCode == uiUserCode)
		{
			(*it2)->Clear();
			delete pLoginPlayer;
			m_vecLoginUser.erase(it2);
			break;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}
