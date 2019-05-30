/**
 * @file SharedDefines.hpp
 * 共享预定义
 *
 * @author Hourui (liquidmonkey)
 */

#ifndef __CS_COMMON_ENUM_HPP__
#define __CS_COMMON_ENUM_HPP__

namespace SRT
{
////////////////////////////////////////////////////////////////////////////////////////////////////
/***************************************常量定义*****************************************************/
////////////////////////////////////////////////////////////////////////////////////////////////////
enum eLoginCtrl
{
	CTRL_LOGIN_SUCC,				// 成功
	CTRL_LOGIN_START,				// 开始游戏
	CTRL_LOGIN_MD5NOTMATCH,			// MD5验证失败
	CTRL_LOGIN_NEEDCREATEUSER,		// 需要创建角色
	CTRL_LOGIN_WRONGPASSWD,			// 密码错误
	CTRL_LOGIN_USERFREEZE,			// 角色被冻结
	CTRL_LOGIN_ACCOUNTFREEZE,		// 帐号被冻结
};

enum eRoundCtrl
{
	CTRL_ROUND_INIT = 200,
	CTRL_ROUND_FIRST,//先开始回合
	CTRL_ROUND_LATTER,
	CTRL_ROUND_START,//双方登陆成功，回合开始
	CTRL_ROUND_WAIT,//后者等待
	CTRL_ROUND_PLAYING,//游戏中
	CTRL_ROUND_SWITCH_COUNT_DOWN,
	CTRL_ROUND_SWITCH,//通知切换回合
	CTRL_GIVE_UP,//投降
	CTRL_NETWORK_SERVER_BREAK,
	CTRL_NETWORK_SELF_BREAK,//己方网络中断
	CTRL_NETWORK_OTHER_BREAK,//对方网络中断
	CTRL_GAME_OVER  //游戏结束
};

enum eUIOperation
{
	OPERATION_INIT = 400,

	OPERATION_USECARD_APPEARANCE,//出牌，角色上场
	OPERATION_USECARD_ENCHANT,	//出牌，给角色HP加强化
	OPERATION_USECARD_ATTACK_UNIT,//出牌，用技能卡攻击对方角色或建筑
	OPERATION_USECARD_ATTACK_COUNTRY,//出牌，用技能卡攻击对方城堡

	OPERATION_USEUNIT_ATTACK_UNIT,	//拖动角色，攻击对方角色
	OPERATION_USEUNIT_ATTACK_BUILDING,//拖动角色，攻击对方建筑
	OPERATION_USEUNIT_ATTACK_COUNTRY,//拖动角色，攻击对方城堡
	OPERATION_USEUNIT_ATTACK_SUMMON,//拖动角色，攻击对方建筑
	OPERATION_USEUNIT_ATTACK_TRENCHES,//角色上场后，需要指定攻击目标的战吼

	OPERATION_USECOUNTRY_ATTACK_UNIT,//使用城堡技能攻击角色
	OPERATION_USECOUNTRY_ATTACK_BUILDING,//使用城堡技能攻击建筑
	OPERATION_USECOUNTRY_ATTACK_SUMMON,//使用城堡技能攻击召唤兽
	OPERATION_USECOUNTRY_ATTACK_COUNTRY,//使用城堡技能攻击城堡

	OPERATION_BUILDING_AUTOATTACK,//建筑自动攻击，暂时没用到

	OPERATION_ERROR
};

enum eSceneStack
{
	SCENE_INIT = 500,
	SCENE_TITLE,
	SCENE_LOADING,
	SCENE_MAIN,
	SCENE_RESULT
};

enum eObjLayer
{
	LAYER_BASE = 1,
	LAYER_COUNTRY,
	LAYER_UNIT,
	LAYER_SPINE,
	LAYER_CARD,
	LAYER_ANI,
	LAYER_OTHERMENU,
	LAYER_SELFMENU,
	LAYER_INFO_CARD,
	LAYER_TEMP_HIGH,
	LAYER_RESULT
};

enum eGameResult
{
	RESULT_WIN = 0,//胜利
	RESULT_LOSE,//失败
	RESULT_DRAWN//打平
};

enum SharedDefines
{
	IP_LEN															= 15,
	ACCOUNT_LEN														= 32,		// 用户ID长度
	PASSWORD_LEN													= 16,
	NICK_NAME_LEN													= 20, 		// 角色昵称长度
	NICK_NAME_CREATE_LEN											= 12,
	MD5_STR_LEN														= 32,		// MD5字串长度	
	SECOND_PER_DAY													= 24*3600,	// 一天的秒数
	TIME_ZONE_SECOND												= 8*3600,	// 时区时间差
	
	MAX_SCENE_UNIT_COUNT											= 9,		// 场上战斗单位最大数量
	MAX_BATTLE_ROUND_TIME											= 60,		// 场上战斗一回合的最长时间
	MAX_SKILL_COUNT_ONECARD											= 5,		// 一张卡片或活动单位最大技能数量
};
////////////////////////////////////////////////////////////////////////////////////////////////////
enum ErrorCode
{
	eSuccess														= 0,		// 成功
};
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
}//namespace SRT

#endif //__SHARED_DEFINES_HPP__