/**
 * @file ServiceManager.hpp
 * 服务管理
 * 
 * @author hourui (liquidmonkey)
 **/

#ifndef __SERVICE_MANAGER_HPP__
#define __SERVICE_MANAGER_HPP__

#include "logger.hpp"
#include "Service.hpp"
#include "ServiceException.hpp"

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
class ServiceManager
{
public:
	template<class T>
	struct refence 
	{
		refence(void):_data(nullptr){}
		~refence(void){ clear(); }
		
		void clear(void){ delete _data;_data=nullptr; }
		void init(void){ T* t=new T;t->LoadFromDatabase();_data=t; }
		
		T*	_data;
	};
private:	
	template<class T>
	static refence<T>* _refence(void)
	{
		static refence<T> res;
		return &res;
	}
public:
	template<class T>
	static T* GetService(void)
	{
		refence<T>* res = _refence<T>();
		if(!res->_data)
			throw ServiceManagerException(ServiceManagerException::NOT_FOUND);
			
		return res->_data;
	}
	
	template<class T>
	static void Attach(void)
	{
		refence<T>* res = _refence<T>();
		if(res->_data)
			throw ServiceManagerException(ServiceManagerException::DUPLICATE_ATTACH);
			
		res->init();
	}
	
	template<class T>
	static void Detach(void)
	{
		refence<T>* res = _refence<T>();
		if(!res->_data)
			throw ServiceManagerException(ServiceManagerException::DUPLICATE_DETACH);
			
		res->clear();
	}	
};

template<typename T>
T* GetService(void)throw()
{
	T* pkPointer = nullptr;

	try
	{
		pkPointer =
			ServiceManager::GetService<T>();
	}
	catch(ServiceManagerException& e)
	{
		CLog::error("%s(%s)",e.what(),T::ID());
	}

	return pkPointer;
}

template<typename T>
void
HOOK_SERVICE(void)
{
	try
	{
		ServiceManager::Attach<T>();
	}
	catch (ServiceManagerException& e)
	{
		CLog::error("%s(%s)", e.what(), T::ID());
		throw(e);
	}
}

template<typename T>
void
DE_HOOK_SERVICE(void)
{
	try
	{
		ServiceManager::Detach<T>();
	}
	catch (ServiceManagerException& e)
	{
		CLog::error("%s(%s)", e.what(), T::ID());
		throw(e);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace SRT
#endif // __SERVICE_MANAGER_HPP__