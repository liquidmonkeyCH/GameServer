/**
 * @file UniqueCode.hpp
 * 唯一码生成器
 * 
 * @author Hourui (liquidmonkey)
 **/
 
#ifndef __UNIQUE_CODE_HPP__
#define __UNIQUE_CODE_HPP__

#include "TypesDn.h"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class CUniqueCode
{
public:
	CUniqueCode(uint16 uiKey);
	~CUniqueCode(void);
	
	sint64 CreateCode(void);
private:
	time_t		m_tmDate;
	uint32		m_uiIndex;
	uint16		m_uiKey;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif // __MEMORY_STREAM_HPP__