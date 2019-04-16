/**
 * @file Service.hpp
 * 服务基类
 * 
 * @author Hourui (liquidmonkey)
 **/
 
#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////
class Service
{
public:
	typedef const char* SERVICE_ID;
public:
	virtual SERVICE_ID GetId(void) = 0;
	virtual void LoadFromDatabase(void) = 0;
};
////////////////////////////////////////////////////////////////////////////////
#define DECLARE_SERVICE_ID(serviceId)	\
	public:								\
		SERVICE_ID GetId(void)			\
		{								\
			return (#serviceId);		\
		}								\
		static SERVICE_ID ID(void)		\
		{								\
			return (#serviceId);		\
		}								\
	private:							\
		serviceId(void);				\
		~serviceId(void);				\
		template<class T> friend struct ServiceManager::refence;
////////////////////////////////////////////////////////////////////////////////
} //namespace Utility
#endif //__SERVICE_HPP__