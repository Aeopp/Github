#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <atomic>
#include <numeric>
#include <iterator>


// C++ 17 병렬 프로그래밍 참고 페이지
//http://occamsrazr.net/tt/326
//http://occamsrazr.net/tt/325
//https://copynull.tistory.com/232
/*
for_each_n par
sample: 
transform_reduce 
inclusive_scan과 exclusive_scan // inclusive 는 i번째 요소를 부분합에 누적합에 포함시킨다
// exclusive 는 그렇지 않다
transform_inclusive_scan과 transform_exclusive_scan
*/
// 트랜스폼 리듀스....
// #1 use threads...
// #2 use atomic...
// #3 use future
// #4 use async
// #5 for_each 실행정책 par, par_unseq,seq
using namespace std;
namespace
{
	namespace thread_
	{
		void inner_product(const std::vector<float_t>& lhs,
			const std::vector<float_t>& rhs, const int32_t first,
			const int32_t end, double_t&  Dest_Sums,mutex& Lock) {
			
			float_t local_sum = 1;
			
			for (int32_t i = first; i < end; ++i) 
				local_sum += (lhs[i] * rhs[i]);
			{
				// std::scoped_lock Lock(Lock);
				 // Lock.lock();
				atomic<double_t> _atomic = local_sum; 
				Dest_Sums += _atomic;
				 // Lock.unlock();
			}
		}
	}
	namespace atomic_ {
		void inner_product(const std::vector<int>& lhs,
			const std::vector<int>& rhs, const int32_t first,
			const int32_t end, atomic<int>& Dest_Sums) {

			int local_sum = 0;

			for (int32_t i = first; i < end; ++i) {
				local_sum += (lhs[i] * rhs[i]);
			}
			{
			//	atomic<float_t> a_sum = local_sum;
				Dest_Sums += local_sum;
			}
		}
	}
	namespace future_ {
		
	}
	namespace async_{

	}
}


int main() {
	constexpr uint32_t vec_size = 1'000'000ul; 
	constexpr uint32_t N_Cores = 4ul;
	constexpr uint32_t th_calc_size = vec_size / N_Cores;

	random_device rand_device;
	mt19937 MT(rand_device());
	uniform_int_distribution<int> Dis(0, 100);

	vector<int> vec_lhs;
	vec_lhs.reserve(vec_size);
	auto lhs_inserter =back_inserter(vec_lhs);

	vector<int> vec_rhs;
	vec_rhs.reserve(vec_size);
	auto rhs_inserter = back_inserter(vec_rhs);

	generate_n(lhs_inserter, vec_lhs.capacity(),[&Dis,&MT] {return Dis(MT); });
	generate_n(rhs_inserter, vec_lhs.capacity(),[&Dis, &MT] {return Dis(MT); });

	vector<thread> Threads;
	Threads.reserve(N_Cores); 
	auto TH_Inserter = back_inserter(Threads);

	mutex    Lock;
	atomic<int> Sum = 1;
	bool flag = false;
	auto Now = chrono::system_clock::now();
	for (int32_t i = 0; i < N_Cores; ++i)
	{

		uint32_t start = i * th_calc_size;
		uint32_t last = (i + 1) * th_calc_size;

		if (!flag) {
			Now = chrono::system_clock::now();
			flag = true;
		}
		Threads.emplace_back(atomic_::inner_product,
			ref(vec_lhs), ref(vec_rhs),
			start, last, ref(Sum)/*, ref(Lock)*/);
    };
	
	for_each(begin(Threads), end(Threads), [](auto& Th) {Th.join(); });
	chrono::duration<double> Duration = chrono::system_clock::now() - Now;
	std::cout << "my thread ver inner_product ? : ";
	std::cout << Sum << endl;
	
	std::cout << "my thread ver second : " << Duration.count() << endl;

	std::cout << "standard lib inner_product ? : ";
	Now = chrono::system_clock::now();
	std::cout << inner_product(begin(vec_lhs), end(vec_lhs), begin(vec_rhs), 1) << endl;
	Duration =  chrono::system_clock::now() - Now;
	std::cout << "standard second : " << Duration.count() << endl;

	std::promise<int32_t> my_promise;
	std::future<int32_t> future = my_promise.get_future();
	my_promise.set_value(123);
	std::cout << future.get();

	
}