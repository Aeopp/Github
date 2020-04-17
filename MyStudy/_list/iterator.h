#pragma once
template<typename Ty>
class iterator
{
	using iterator_category;
	using value_type = typename Ty::value_type;
	using difference_type = typename Ty::difference_type;
	using pointer = typename Ty::pointer;
	using reference = typename Ty::reference;

	using container_type = Ty; 
	using conty = Ty;
	
	iterator(conty& _cont, typename conty::iterator _where)
		: container(&_cont), iter(_where){};
	iterator& operator=(const typename conty::value_type& val)
	{
		
	}

private:
	conty* container;
	typename conty::iterator iter; 
};

