/**
 * @file MemoryPool.inl
 * 
 * 小型物件内存管理
 * @author Hourui (liquidmonkey)
 */ 
 
///////////////////////////////////////////////////////////////////////////////////////////////////
//********************************* CMemoryPool **************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
CMemoryPool<T,N>::CMemoryPool(void):
	_first(0),_left(N)
{
	memset(_offset,0,sizeof(size_type)*N);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
CMemoryPool<T,N>::~CMemoryPool(void)
{
	clear();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
void CMemoryPool<T,N>::clear(void)
{
	_first = 0;
	_left = N;
	
	memset(_offset,0,sizeof(size_type)*N);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
std::ptrdiff_t CMemoryPool<T,N>::npos(T* p)
{
	if(p < _data || p >= _data+N) return -1;
	
	return p-_data;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
T* CMemoryPool<T,N>::malloc(void)
{
	if (!_left) 
		return nullptr;
		
	T* p = _data + _first;
	Base::_set(_first,_offset);
	--_left;
	return p;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
bool CMemoryPool<T,N>::free(T* p)
{
	std::ptrdiff_t _pos = npos(p);
	if(_pos < 0) 
		return false;
	
	Base::_reset(_pos,_first,_offset);
	
	++_left;
	
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline
CMemoryPool<T,0>::CMemoryPool(void):
	_data(nullptr),_offset(nullptr),_first(0),_left(0),_size(0)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline
CMemoryPool<T,0>::~CMemoryPool(void)
{
	delete[] _data;
	delete[] _offset;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline
void CMemoryPool<T,0>::clear(void)
{
	_first = 0;
	_left = _size;
	
	memset(_offset,0,sizeof(size_type)*_size);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline
void CMemoryPool<T,0>::init(size_t size)
{
	_data = new T[size];
	_offset = new size_type[size];
	_left = size;
	_size = size;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline
std::ptrdiff_t CMemoryPool<T,0>::npos(T* p)
{
	if(!_data || p < _data || p >= _data+_size) return -1;
	
	return p-_data;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline
T* CMemoryPool<T,0>::malloc(void)
{
	if (!_left) return nullptr;
	T* p = _data + _first;
	Base::_set(_first,_offset);
	--_left;
	return p;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
inline
bool CMemoryPool<T,0>::free(T* p)
{
	std::ptrdiff_t _pos = npos(p);
	if(_pos < 0) 
		return false;
	
	Base::_reset(_pos,_first,_offset);
	
	++_left;
	
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//********************************* CMemoryPoolEx ************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N> 
_Chunk_Release_Model<T,N>::_Chunk_Release_Model(void):
	_allocChunk(0),
	_deallocChunk(0)
{
	_Chunks.push_back(new Chunk);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N> 
_Chunk_Release_Model<T,N>::~_Chunk_Release_Model(void)
{
	for(auto it=_Chunks.begin(); it!=_Chunks.end(); ++it)
	{
		delete *it;
		*it = nullptr;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N> 
void _Chunk_Release_Model<T,N>::clear(void)
{
	for(auto it=_Chunks.begin(); it!=_Chunks.end(); ++it)
		it->clear();
	
	_allocChunk = 0;
	_deallocChunk = 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
std::ptrdiff_t _Chunk_Release_Model<T,N>::_npos(T* p,size_t& n)
{	
	n = _deallocChunk;
	std::ptrdiff_t pos = _Chunks[n]->npos(p);
	if(pos>=0)
		return pos;

	size_t total = _Chunks.size();
	for(size_t i=1;i<=total/2;++i)
	{
		n = _forward(_deallocChunk,i,total);
		pos = _Chunks[n]->npos(p);
		if(pos>=0)
			return pos;
			
		size_t m = n;
		n = _backward(_deallocChunk,i,total);
		if(m==n) break;

		pos = _Chunks[n]->npos(p);
		if(pos>=0)
			return pos;
	}

	return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
T* _Chunk_Release_Model<T,N>::malloc(void)
{
	if(!_Chunks[_allocChunk]->_left)
	{
		_allocChunk = _Chunks.size();
		for(size_t i=0; i<_allocChunk; ++i)
		{
			if(!_Chunks[i]->_left) continue;
			
			_allocChunk = i;
			return _Chunks[i]->malloc();
		}
		
		_Chunks.push_back(new Chunk);
	}
	
	return _Chunks[_allocChunk]->malloc();
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
void _MRM_hold<T,N>::free(T* p)
{
	size_t n;
	if(Base::_npos(p,n)<0)
		return;
		
	assert(Base::_Chunks[n]->free(p));
	Base::_deallocChunk = n;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
template<class T,size_t N>
void _MRM_auto1<T,N>::free(T* p)
{
	size_t n;
	if(Base::_npos(p,n)<0)
		return;
		
	assert(Base::_Chunks[n]->free(p));
	Base::_deallocChunk = n;
	
	if(Base::_chunk_size(n) < N)
		return;
		
	n = Base::_Chunks.size()-1;
	if(n == Base::_deallocChunk)
		return;
		
	if(Base::_chunk_size(n) >= N)
	{
		delete Base::_Chunks[n];
		Base::_Chunks.pop_back();
		if(Base::_allocChunk == n)
			Base::_allocChunk = 0;
		--n;
	}

	typename Base::Chunk* pChunk = Base::_Chunks[n];
	Base::_Chunks[n] = Base::_Chunks[Base::_deallocChunk];
	Base::_Chunks[Base::_deallocChunk] = pChunk;
	
	if(Base::_allocChunk == n)
		Base::_allocChunk = Base::_deallocChunk;
}
///////////////////////////////////////////////////////////////////////////////////////////////////