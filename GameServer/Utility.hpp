/**
 * @file Utility.hpp
 * Utiliy Functions & Class
 *
 * @author Hourui (liquidmonkey)
 */
#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

#include <stdio.h>
#include <time.h>
#include <string>
#include <string.h>
#include <random>

namespace Utility
{
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
T* IFNULL(T* pIn,T* pDefault)
{
	if(pIn == NULL)
		return pDefault;
	
	return pIn;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
inline int rand(void)
{
	static time_t m_nSeed = time(NULL);

	m_nSeed = m_nSeed * 214013L + 2531011L;

	return static_cast<int>((m_nSeed >> 16) & 0x7FFFFFFF);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
/*inline std::default_random_engine& _RandEngine(void)
{
	static std::default_random_engine generator(time(NULL));
	return generator;
}*/
///////////////////////////////////////////////////////////////////////////////////////////////////
struct DateTime{
	unsigned short	m_uiYear;
	unsigned char	m_uiMonth;
	unsigned char	m_uiDay;
	unsigned char	m_uiHour;
	unsigned char	m_uiMin;
	unsigned char	m_uiSec;
	unsigned char	m_uiWeek;

	inline time_t  getTime(void)
	{
		struct   tm   tt;
		tt.tm_year=m_uiYear - 1900 ; 
		tt.tm_mon=m_uiMonth - 1 ; 
		tt.tm_mday=m_uiDay;
		tt.tm_hour=m_uiHour;
		tt.tm_min=m_uiMin;
		tt.tm_sec=m_uiSec;
		tt.tm_isdst=1;
		return   mktime(&tt);
	}
	/*
	inline void setCurTime(void)
	{
		struct  tm  tt;
		time_t t=time(NULL);
		localtime_r(&t,&tt);
		m_uiYear=tt.tm_year + 1900 ; 
		m_uiMonth=tt.tm_mon + 1 ; 
		m_uiDay=tt.tm_mday;
		m_uiHour=tt.tm_hour;
		m_uiMin=tt.tm_min;
		m_uiSec=tt.tm_sec;
		m_uiWeek=tt.tm_wday;
	}

	inline void setTodayZeroTime(void)
	{
		clear();
		struct  tm  tt;
		time_t t=time(NULL);
		localtime_r(&t,&tt);
		m_uiYear=tt.tm_year + 1900 ; 
		m_uiMonth=tt.tm_mon + 1 ; 
		m_uiDay=tt.tm_mday;
		m_uiHour=0;
		m_uiMin=0;
		m_uiSec=0;
		m_uiWeek=tt.tm_wday;
	}

	inline void setTime(time_t t)
	{
		struct  tm  tt;
		localtime_r(&t,&tt);
		m_uiYear=tt.tm_year + 1900 ; 
		m_uiMonth=tt.tm_mon + 1 ; 
		m_uiDay=tt.tm_mday;
		m_uiHour=tt.tm_hour;
		m_uiMin=tt.tm_min;
		m_uiSec=tt.tm_sec;
		m_uiWeek=tt.tm_wday;
	}
	*/
	inline std::string strtime(void)
	{
		char buf[20];
		sprintf(buf,"%04d-%02d-%02d %02d:%02d:%02d",
			m_uiYear,
			m_uiMonth,
			m_uiDay,
			m_uiHour,
			m_uiMin,
			m_uiSec);
	   return buf;
	}
	
	inline char* strtime(char* szBuffer,const char* szFormat = NULL)
	{
		if(!szBuffer)
			return NULL;
			
		sprintf(szBuffer,szFormat?szFormat:"%04d-%02d-%02d %02d:%02d:%02d",
			m_uiYear,
			m_uiMonth,
			m_uiDay,
			m_uiHour,
			m_uiMin,
			m_uiSec);
			
		return szBuffer;
	}

	inline void clear()
	{
		m_uiYear=0;
		m_uiMonth=0;
		m_uiDay=0;
		m_uiHour=0;
		m_uiMin=0;
		m_uiSec=0;
		m_uiWeek=0;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////
inline
time_t localday(void)
{
	time_t t=time(NULL);
	return (t+8*3600)/(24*3600);	
}
///////////////////////////////////////////////////////////////////////////////////////////////////
struct strless
{
	bool operator()(const char* const &L,const char* const &R) const
	{
		return strcmp(L,R) < 0;
	}
};

struct wstrless
{
	bool operator()(const wchar_t* const &L,const wchar_t* const &R) const
	{
		return wcscmp(L,R) < 0;
	}
};

struct timevaless
{
	bool operator()(const timeval &L,const timeval &R) const
	{
		if(L.tv_sec > R.tv_sec)
			return false;
		else if(L.tv_sec < R.tv_sec)
			return true;
		else
			return L.tv_usec/1000 < R.tv_usec/1000;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////
inline
const char* BinToStr(char* szBuffer,const void* pData,size_t size)
{
	if(!size)
	{
		strncpy(szBuffer,"0x0",3);
		szBuffer[3] = 0x0;
		return szBuffer;
	}
	
	memset(szBuffer,0,2*size+3);
	unsigned char* p = (unsigned char*)pData;
	strncpy(szBuffer,"0x",2);
	for(size_t i=0; i<size; ++i)
		sprintf(szBuffer,"%s%02X",szBuffer,p[i]);
	
	return szBuffer;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
template<size_t size>
class CBin2Str
{
public:
	CBin2Str(const void* p){ BinToStr(m_kData,p,size); }
	const char* str(void) { return m_kData; }
private:
	char m_kData[size*2+3];
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
CBin2Str<sizeof(T)> Bin2Str(const T& kData)
{
	return CBin2Str<sizeof(T)>(&kData);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif
