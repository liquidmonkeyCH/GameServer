#ifndef __CGP_USER_H__
#define __CGP_USER_H__

#include "csCommonDefine.h"
#include "csCommonStruct.h"
#include "csCommonEnum.h"

#ifdef WIN32
#pragma warning (disable:4819)
#endif

#pragma pack(1)

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////

struct MS_HEADER
{
	unsigned int m_uiLen;
	unsigned int m_uiMessageId;
};

struct MS_CG_LOGIN : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x00);
};

struct MS_GC_LOGIN : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x00);

	bool m_IsSuccess;
};

struct MS_GC_START_FIGHTT : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x01);

	bool m_IsHost;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
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
struct MS_CG_REQUEST_DISCONNECT : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x03);
};

struct MS_GC_REQUEST_DISCONNECT : public MS_HEADER
{
	DECLARE_PROTOCOL_ID(Protocol_Game_Client,Protocol_Class_User,0x03);
	bool m_bIsNormalDisconnect;
};
}

#pragma pack()
#endif // __GAME_PROTOCOL_USER_H__