/**
 * @file StructsDn.hpp
 * 共享结构定义
 *
 * @author Hourui (liquidmonkey)
 */

#ifndef __CS_COMMON_STRUCT_HPP__
#define __CS_COMMON_STRUCT_HPP__

#include "TypesDn.h"
#include "csCommonEnum.hpp"
//#include "SharedDefines.hpp"

#pragma pack(1)

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
struct MS_HEADER { // 
	uint32 m_uiLen;
	uint32 m_uiMessageId;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
struct Protocol_UserBasicInfo		// 通讯用User基础信息
{
	sint64 	m_siUserCode;
	char	m_szName[NICK_NAME_LEN+2];
	char	m_szAccount[ACCOUNT_LEN+2];			
};

//协议相关数据
struct MSG_ROUNDCTRL_CONTENT
{
	unsigned int 	m_randomSize;
	int 			m_randomFlag[16];
	int 			m_selfHeroHP;
	int 			m_otherHeroHP;
};

struct MSG_OPERATION_CONTENT
{
    int cardIndex;//卡牌索引
    int cardID;//卡牌id
    int unitIndex;//角色索引
    int targetIndex;//目标角色索引
    int result;//游戏结果
    int randomSize;//随机攻击vector的大小
    int randomFlag[16];//随机数组
    int specialType;//特殊战吼类型，需要指定目标的战吼。
    int selfHeroHP;//己方英雄HP
    int otherHeroHP;//对方英雄HP
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}
#pragma pack()
#endif //__STRUCTS_DN_HPP__