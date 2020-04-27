#include <iostream>
#include <algorithm>
#include <execution>
#include <iterator>
#include <memory>
#include <future>
#include <random>
namespace {
	template<typename _Ty>
	void inner_product(const std::vector<_Ty>& lhs,const std::vector<_Ty>& rhs){
		 	
	}
	template<typename _calc_type>
	constexpr auto getdis() {
		if constexpr (std::is_same_v<_calc_type, float_t>) {
			return std::uniform_real_distribution<_calc_type>(1.0f, 100.0f);
		}
		else if constexpr (std::is_same_v<_calc_type,int32_t>){
			return std::uniform_int_distribution<_calc_type>(1, 100);
		}
	}
}

int main() {
	/*std::vector<int32_t> vec1{ 1,2,3 };
	std::vector<int32_t> vec2{ 1,2,3 };
	std::vector<int32_t> vec3{ 1,2,3 };

	std::cout << 
		std::transform_reduce(std::execution::par,
			vec1.begin(), vec1.end(), vec2.begin(), 0);
	
	 std::transform(std::execution::par,
	 vec1.begin(), vec1.end(), vec2.begin(),vec3.begin(),
		[](auto&, auto&) {return 1; });

	 copy(vec3.begin(), vec3.end(), std::ostream_iterator<int32_t>
		(std::cout," "));
	                       */

	constexpr int32_t vec_size = 1000'000; 
	constexpr int32_t N_Cores = 4; 
	constexpr int32_t th_range = vec_size / N_Cores; 
	using calc_type = int32_t; 

	std::random_device Rd;
	std::mt19937 MT(77);
	
	auto Dis = getdis<calc_type>();

	std::vector<calc_type> vec0, vec1;

	vec0.reserve(vec_size);
	vec1.reserve(vec_size);

	std::generate_n(std::back_inserter(vec0), vec_size,[&MT,&Dis]
	{return Dis(MT);  });

	std::generate_n(std::back_inserter(vec1), vec_size, [&MT, &Dis]
	{return Dis(MT);  });

	
	//std::vector<std::future<calc_type>> futures;
	std::vector<calc_type> futures;
	calc_type sum = 0;
	futures.reserve(N_Cores);
	
	auto NOW  = std::chrono::system_clock::now(); 

	for (size_t i = 0; i < N_Cores; ++i) {
		
		size_t start = th_range * i;
		size_t last = 0;

		if (i == N_Cores - 1) {
			size_t last = (th_range * (i + 1) ) + 1;
		}
		else
		size_t last = th_range * (i + 1); 
		/*std::cout << "start : " << start << " " << last << " " << 
		std::endl;*/

		sum += std::inner_product(begin(vec0) + start,
			std::begin(vec0) + last, begin(vec1), 0);
		/*futures.push_back(std::async(std::launch::async,
			[&] { return std::inner_product(,begin(vec0)+ start,
				std::end(vec0)-last, begin(vec1), 0);  }));*/
	};

	//std::for_each(begin(futures), end(futures), [&sum]
	//(auto& element) {
	//		std::cout << " ??  ";
	//		/*sum += */
	//		std::cout << "get" << element.get() << " ";  });

	std::chrono::duration<double> TIME((std::chrono::system_clock::now() - NOW));
	std::cout << TIME.count() << std::endl;
	std::cout << sum << std::endl << std::endl; 

	sum = 0; 

	NOW = std::chrono::system_clock::now(); 
	sum = std::inner_product(begin(vec0), end(vec0), begin(vec1), 0);    
	TIME = std::chrono::system_clock::now() - NOW; 
	std::cout << TIME.count() << std::endl;
	std::cout << sum << std::endl << std::endl;
}