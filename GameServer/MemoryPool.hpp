/**
 * @file MemoryPool.hpp
 * 
 * 小型物件内存管理
 * @author Hourui (liquidmonkey)
 */ 
 
#ifndef __MEMORY_POOL_HPP__
#define __MEMORY_POOL_HPP__

#include <assert.h>
#include <limits>
#include <climits>
#include <vector>

namespace Utility
{
////////////////////////////////////////////////////////////////////////////////////////////////////
template<size_t N>
struct _Chunk_Base
{
#ifndef NDEBUG
	typedef typename std::conditional<N == 0,unsigned long long,
			typename std::conditional<N < SCHAR_MAX, unsigned char,
			typename std::conditional<N < SHRT_MAX, unsigned short,
			typename std::conditional<N < LONG_MAX, unsigned long,
			unsigned long long>::type>::type>::type>::type size_type;
	const static size_type size_mask = static_cast<size_type>(1) << (std::numeric_limits<size_type>::digits-1);
	
	static void _set(size_type& _first,size_type _offset[])
	{
		assert(_first < N);
		assert(!(_offset[_first] & size_mask));
		size_type tmp = _first;
		_first = _offset[_first]?(_offset[_first] == size_mask-1?0:_offset[_first]):_first+1;
		assert(_first <= N);
		_offset[tmp] = size_mask;
	}
	
	static void _reset(std::ptrdiff_t _pos,size_type& _first,size_type _offset[])
	{
		assert(_offset[_pos] & size_mask);
		
		_offset[_pos] = _first?_first:size_mask-1;
		_first = static_cast<size_type>(_pos);
		
		assert(_first < N);
	}
#else
	typedef typename std::conditional<N == 0,unsigned long long,
			typename std::conditional<N < UCHAR_MAX,unsigned char,
			typename std::conditional<N < USHRT_MAX, unsigned short,
			typename std::conditional<N < ULONG_MAX, unsigned long,
			unsigned long long>::type>::type>::type>::type size_type;
			
	static void _set(size_type& _first,size_type _offset[])
	{
		 _first = _offset[_first]?(_offset[_first]==std::numeric_limits<size_type>::max()?0:_offset[_first]):(_first+1);
	}
	
	static void _reset(std::ptrdiff_t _pos,size_type& _first,size_type _offset[])
	{
		_offset[_pos] = _first?_first:std::numeric_limits<size_type>::max();
		_first = static_cast<size_type>(_pos);
	}
#endif
	static_assert(N <= LLONG_MAX, "size too large!");
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
class _Chunk_Release_Model;
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N = 0>
class CMemoryPool : private _Chunk_Base<N>
{
private:
	typedef _Chunk_Base<N> Base;
	typedef typename Base::size_type size_type;
	friend class _Chunk_Release_Model<T, N>;
	
	T				_data[N];
	size_type		_offset[N];
	size_type		_first,_left;
	
	void _free(T* p);
public:	
	CMemoryPool(void);
	~CMemoryPool(void);
	
	CMemoryPool(const CMemoryPool&) = delete;
	CMemoryPool& operator=(const CMemoryPool&) = delete;
	
	std::ptrdiff_t npos(T* p);
	
	T*	malloc(void);
	bool free(T* p);
	
	void clear(void);
};

template<class T>
class CMemoryPool<T,0> : private _Chunk_Base<0>
{
private:
	typedef _Chunk_Base<0> Base;
	typedef typename Base::size_type size_type;
	friend class _Chunk_Release_Model<T, 0>;
	
	T*				_data;
	size_type*		_offset;
	size_type		_first,_left,_size;
public:	
	CMemoryPool(void);
	~CMemoryPool(void);
	
	CMemoryPool(const CMemoryPool&) = delete;
	CMemoryPool<T,0>& operator=(const CMemoryPool&) = delete;
	
	std::ptrdiff_t npos(T* p);
	
	void init(size_t size);
	
	T*	malloc(void);
	bool free(T* p);
	
	void clear(void);	
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
class _Chunk_Release_Model
{
protected:
	typedef CMemoryPool<T,N> Chunk;
	typedef std::vector<Chunk*> Chunks;
	typedef typename Chunks::iterator Ckiter;
	typedef typename Chunks::reverse_iterator RCiter;
	
	Chunks	_Chunks;
	size_t	_allocChunk;
	size_t	_deallocChunk;
	
	_Chunk_Release_Model(void);
	~_Chunk_Release_Model(void);
	
	_Chunk_Release_Model(const _Chunk_Release_Model&) = delete;
	_Chunk_Release_Model& operator=(const _Chunk_Release_Model&) = delete;
	
	_Chunk_Release_Model(const _Chunk_Release_Model&&) = delete;
	_Chunk_Release_Model& operator=(const _Chunk_Release_Model&&) = delete;
	
	size_t _forward(size_t n,size_t i,size_t total){ n=n+i; return n>=total?n-total:n; }
	size_t _backward(size_t n,size_t i,size_t total){ return n>=i?n-i:total+n-i; }

	std::ptrdiff_t _npos(T* p,size_t& n);
	
	size_t _chunk_size(size_t n) { return _Chunks[n]->_left; } 
public:	
	void clear(void);
	T* malloc(void);
};

template<class T,size_t N>
struct _MRM_hold : public _Chunk_Release_Model<T,N>
{
	typedef _Chunk_Release_Model<T,N> Base;
	
	std::ptrdiff_t npos(T* p) { size_t i;std::ptrdiff_t pos = _npos(p,i); return pos<0?-1:pos+i*N; }
	void free(T* p);	
};

template<class T,size_t N>
struct _MRM_auto1 : public _Chunk_Release_Model<T,N>
{
	typedef _Chunk_Release_Model<T,N> Base;
	
	void free(T* p);
};
////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t Grow=120,template<class,size_t> class Release = _MRM_auto1>
struct CMemoryPoolEx : public Release<T,Grow>
{
	static_assert(Grow,"Grow can not be 0!");
	
	CMemoryPoolEx(void){}
	~CMemoryPoolEx(void){}
	
	CMemoryPoolEx(const CMemoryPoolEx&) = delete;
	CMemoryPoolEx& operator=(const CMemoryPoolEx&) = delete;
	
	CMemoryPoolEx(const CMemoryPoolEx&&) = delete;
	CMemoryPoolEx& operator=(const CMemoryPoolEx&&) = delete;
};
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "MemoryPool.inl"
////////////////////////////////////////////////////////////////////////////////////////////////////	
}//namespace Utility
#endif //__MEMORY_POOL_HPP__