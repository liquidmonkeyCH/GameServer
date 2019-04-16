/**
* @file ServiceException.hpp
*
* @author hourui (liquidmonkey)
**/

#ifndef __SERVICE_EXCEPTION_HPP__
#define __SERVICE_EXCEPTION_HPP__

#include <exception>

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////	
class ServiceManagerException : public std::exception
{
public:
	enum STATE {
		NOT_FOUND,
		DUPLICATE_ATTACH,
		DUPLICATE_DETACH,
	};

public:
	ServiceManagerException(STATE eState):m_eState(eState){}

	const char* what(void) const throw();

private:
	STATE m_eState;
};

inline const char*
	ServiceManagerException::what(void) const throw()
{
	switch (m_eState)
	{
	case NOT_FOUND:
		return "Specified Service not found!";
	case DUPLICATE_ATTACH:
		return "Service already existed!";
	case DUPLICATE_DETACH:
		return "Service duplicate detach!";
	default:
		return "Unknown";
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////
} //namespace SRT
#endif // __SERVICE_EXCEPTION_HPP__