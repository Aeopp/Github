#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random> 
#include <numeric>
#include <iterator>
using namespace std;

inline namespace {
    template<typename _Ty>
    void th_inner_product(const vector<_Ty>& lhs,
        const vector<_Ty>& rhs, const uint32_t start,
        const uint32_t end, atomic<_Ty>& sum) {
         _Ty local_sum = 0; 
        for (uint32_t i = 0; i < end; ++i) {
            local_sum  += (lhs[i] * rhs[i]);
        }
        std::cout <<   "local_sum   " << local_sum << endl; 

        sum += local_sum; 
    };
};

int main() {
    using calc_type = int32_t;
    constexpr uint32_t N_Core = 4;
    constexpr uint32_t vec_size = 100'000ul; 
    constexpr uint32_t calc_range = vec_size / N_Core; 
    cout.precision(5);
    cout << fixed; 
    vector<calc_type> lhs, rhs;
    lhs.reserve(vec_size);  rhs.reserve(vec_size);

    random_device Rd;
    mt19937 MT(77); 
    uniform_int_distribution<calc_type> Dis(0, 99);

    generate_n(back_inserter(lhs), vec_size, [&Dis,&MT]()
        {return Dis(MT);  });
    generate_n(back_inserter(rhs), vec_size, [&Dis, &MT]()
        {return Dis(MT);  });

    

    auto NOW = chrono::system_clock::now();

	atomic<calc_type > sum = 0;
   th_inner_product(lhs, rhs, 0, vec_size, sum);
    chrono::duration<float_t> Duration  = 
     chrono::system_clock::now() - NOW;

    cout << sum << endl << " TIME : " << Duration.count() << endl;
   
    vector<thread> Threads;
    Threads.reserve(N_Core);

    sum = 0;
    bool flag = false;
    for (uint32_t i = 0; i < N_Core; ++i) {
        uint32_t start = calc_range * i;
        uint32_t last = calc_range * (i + 1);
        if (flag == false) {
        NOW = chrono::system_clock::now();
        flag = true; 
        }
        Threads.push_back(thread{ th_inner_product<calc_type>,
            cref(lhs), cref(rhs), start, last, ref(sum) }); 
       //  th_inner_product(lhs, rhs,   start, last,sum); 
    };

	for_each(begin(Threads), end(Threads), [](auto& cur_Thread)
		{cur_Thread.join();  });
    Duration = chrono::system_clock::now() - NOW;
   
	
    cout << sum << endl << " TIME : " << Duration.count() << endl;
}
