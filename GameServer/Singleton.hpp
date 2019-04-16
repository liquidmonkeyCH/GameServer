/**
 * @file Singleton.hpp
 * 
 * 单例
 * @author Hourui (liquidmonkey)
 */ 
 
#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class CSingleton : public T
{
	CSingleton(void){}
	~CSingleton(void){}

	
	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;
	CSingleton(const CSingleton&&) = delete;
	CSingleton& operator=(const CSingleton&&) = delete;
public:
	static CSingleton* GetInstance(void)
	{
		static CSingleton _data;
		return &_data;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////
}
#endif //__SINGLETON_HPP__