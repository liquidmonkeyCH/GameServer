/**
 * @file GameProtocol_User.hpp
 * 用户资料相关协议
 *
 * @author Hourui (liquidmonkey)
 */

#ifndef __CGP_USER_HPP__
#define __CGP_USER_HPP__

#include "csCommonDefine.hpp"
#include "csCommonStruct.hpp"
#include "csCommonEnum.hpp"

#ifdef WIN32
#pragma warning (disable:4819)
#endif

#pragma pack(1)

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
struct MS_CG_LOGIN : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x00);

	//char	m_Account[ACCOUNT_LEN+2];
	//char	m_Password[PASSWORD_LEN+2];
	//unsigned int m_UniqueId;
};

struct MS_GC_LOGIN : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x00);

	//unsigned int	m_Result;		//eLoginCtrl
	bool m_IsSuccess;	
};
////////////////////////////////////////////////////////////////////////////////////////////////////

struct MS_GC_START_FIGHTT : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x01);

	bool m_IsHost;
};

/*
struct MS_GC_ROUND_CTRL : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x01);

    unsigned int            m_RoundCtrl;
	unsigned int			m_Order;  	//先后顺序:CTRL_ROUND_FIRST,CTRL_ROUND_LATTER
	MSG_ROUNDCTRL_CONTENT   m_content;
};*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*struct MS_CG_OPERATE : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x02);

	unsigned int            m_operation;
	MSG_OPERATION_CONTENT   m_content;
};

struct MS_GC_OPERATE : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x02);

    unsigned int            m_operation;
	MSG_OPERATION_CONTENT   m_content;
};*/

struct MS_CG_TRANSMIT : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x02);

	unsigned int m_Opcode;
	char m_Json[4000];
};

struct MS_GC_TRANSMIT : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x02);

	unsigned int m_Opcode;
    char m_Json[4000];
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/*struct MS_CG_GAMEOVER : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x03);
};

struct MS_GC_GAMEOVER : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x03);
	unsigned int            m_NormalShutdown;
};*/
struct MS_CG_REQUEST_DISCONNECT : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x03);
};

struct MS_GC_REQUEST_DISCONNECT : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x03);
	bool m_bIsNormalDisconnect;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}
#pragma pack()
#endif // __GAME_PROTOCOL_USER_HPP__