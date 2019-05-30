/**
 * @file MessageHandler_User.hpp
 * User模块协议处理函数声明文件
 *
 * @author Hourui (liquidmonkey)
 */
 
#ifndef __MESSAGE_HANDLER_USER_HPP__
#define __MESSAGE_HANDLER_USER_HPP__

#include "cgpUser.hpp"
#include "msg_controler_planA.hpp"

namespace SRT
{
namespace CMessageHandlerCollection
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/*
uint32 CG_LOGIN_CLIENT_Handler(void*, void*, void*);
uint32 CG_ROUND_CTRL_Handler(void*, void*, void*);
uint32 CG_OPERATE_Handler(void*, void*, void*);
uint32 CG_GAMEOVER_Handler(void*, void*, void*);
*/

int CG_LOGIN_Handler(Utility::task::object_iface* obj, const char* msg, void* ptr);
int CG_TRANSMIT_Handler(Utility::task::object_iface* obj, const char* msg, void* ptr);
int CG_REQUEST_DISCONNECT_Handler(Utility::task::object_iface* obj, const char* msg, void* ptr);

////////////////////////////////////////////////////////////////////////////////////////////////////	
} // namespace CMessageHandlerCollection
} // namespace SRT

#endif //__MESSAGE_HANDLER_USER_HPP__