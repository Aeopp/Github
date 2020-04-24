#include <cstddef>
#include <queue>
#include <stdexcept>
#include <memory> 
using namespace std; 
template<typename _Ty>
class objectpool
{
	objectpool(uint64_t chunksize = defaultsize); 
	objectpool(const objectpool<_Ty>& src) = delete;
	objectpool&operator=(const objectpool<_Ty>& src) = delete;
	objectpool(objectpool<_Ty>&&) noexcept = default;
	objectpool&operator=(objectpool<_Ty>&&) noexcept = default;
	
	using object = shared_ptr<_Ty>; 
	object acquire_object();
private:
	queue<unique_ptr<_Ty>> freelist;
	size_t chunk_size;
	static inline const size_t default_size = 10; 
	
	void allocate_chunk(); 
};

template<typename _Ty>
objectpool<_Ty>::objectpool(uint64_t chunksize)
{
	if (chunksize == 0) {
		throw invalid_argument("사이즈가 유효하지 않다");
	}
	this->chunk_size = chunksize; 
	allocate_chunk(); 
}

template<typename _Ty>
typename objectpool<_Ty>::object objectpool<_Ty>::acquire_object()
{
	if (freelist.empty()) allocate_chunk();

	auto obj = move(freelist.front());
	freelist.pop();

	object smart_object = (obj.release(), [this](_Ty* t) {
		freelist.push(unique_ptr<_Ty>(t));		});

	return smart_object;
};


template<typename _Ty>
void objectpool<_Ty>::allocate_chunk()
{
	for (uint64_t i = 0; i < this->chunk_size; ++i) {
		freelist.emplace(std::make_unique<T>());
	}; 
}
