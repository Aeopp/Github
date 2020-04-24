#include <iostream>
#include <mutex>
#include <list>
#include <vector> 
#include <string>
#include <algorithm>
#include <iterator>
#include <atomic>
#include <chrono>
#include <functional>
#include <utility>
#include <future>
#include <thread>
using namespace std; 
atomic<int32_t> counter(0);

void func(atomic<int32_t>& counter)
{
	int result = 0; 
	for (int32_t i = 0; i < 100; ++i)
	{
		++result; 
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	counter += result; 
}
class request
{
public :
	int32_t mid;
	request(int32_t id) :mid(id) {};
	void process()const& noexcept
	{
		cout << "processing request " << mid << endl;
	};
};
void foo(int a, int b, int c)noexcept
{
	thread_local int32_t n = 0;
	int32_t  k = 0;
	std::cout << ++n << " ";
	std::cout << ++k << " ";
}

void doSomeWork()
{
	for (int32_t i = 0; i < 5; ++i)
		cout << i << endl;
	cout << "Thread throwing a reuntime_error exception..." << endl;
	
	throw runtime_error("Exception from thread");   
}
void threadFunc(exception_ptr& err)
{
	try { doSomeWork();   }
	catch (...)
	{
		cout << "Thread caught exception, " << endl;
		err = current_exception(); 
	}
}
void doWorkInThread()
{
	exception_ptr error;
	thread t{ threadFunc,ref(error) }; 
	
	t.join();

	if (error)
	{
		cout << "메인 스레드 예외를 받아옴";
		rethrow_exception(error);
	}
	else
		cout << "Main thread did not receive any exception." << endl;
}
struct a { void foo() { cout << "wq"; } }; 

// 쓰레드에서 한번만 실행하게 세팅.
once_flag gOnceFlag;
void initializeSharedResources()
{
	cout << "Shared resources initialized." << endl;
}; 
void processingFunction()
{
	call_once(gOnceFlag, initializeSharedResources);
	cout << "Processing" << endl;
}; 
class Counter
{
public:
	Counter(int32_t id, int numIterations)
		: mId(id), mNumIterations(numIterations) {};
	void operator()()const&
	{
		for (int i = 0; i < mNumIterations; ++i)
		{
			unique_lock<timed_mutex> lock(mTimedMutex, 200ms);
			if (lock)
			{
				cout << "카운터 " << mId << "has value "; 
				cout << i << endl; 
			}
			else
			{
				// 200ms 안에 락을 획득하지 못 함
			}
		}
	}
private:
	int mId;
	int mNumIterations;
	static inline timed_mutex mTimedMutex; 
};
namespace
{
	
 }
string operator""king(uint64_t ok)noexcept(true)
{
	return to_string(ok);
};
int sum(const std::vector<int>& v, int start, int end) {
	int total = 0;
	for (int i = start; i < end; ++i) {
		total += v[i];
	}
	return total;
}

int parallel_sum(const std::vector<int>& v) {
	// lower_half_future 는 1 ~ 500 까지 비동기적으로 더함
	// 참고로 람다 함수를 사용하면 좀 더 깔끔하게 표현할 수 도 있다.
	// --> std::async([&v]() { return sum(v, 0, v.size() / 2); });
	std::future<int> lower_half_future =
	std::async(std::launch::async, sum, ref(v), 0, v.size() / 2);

	// upper_half 는 501 부터 1000 까지 더함
	int upper_half = sum(v, v.size() / 2, v.size());

	return lower_half_future.get() + upper_half;
}

int main() {
	std::vector<int> v;
	v.reserve(1000);

	for (int i = 0; i < 1000; ++i) {
		v.push_back(i + 1);
	}

	std::cout << "1 부터 1000 까지의 합 : " << parallel_sum(v) << std::endl;
};

//int some_task(int x) { return 10 + x; }  
//int main()
//{
//	packaged_task<int(int)> task(some_task); 
//	
//
//	auto start = task.get_future(); 
//
//	thread t(move(task), 5);
//
//	cout << start.get() << endl; 
//	t.join(); 
//	/*vector<thread> threads;
//	threads.reserve(3); 
//	auto  _inserter = inserter(threads, begin(threads)); 
//
//	generate_n(_inserter, 3,
//	[](){return move(thread{ processingFunction }); });
//
//	for_each(begin(threads), end(threads), mem_fn(&thread::join));*/
//
//
//
//	/*try {
//		doWorkInThread();
//	}
//	catch (const exception& e)
//	{
//		cout << "메인 함수 캐치: " << e.what() << endl;
//	}*/
//	//atomic<int32_t> counter = 0ul;
//	//vector<thread> threads;
//	//auto th_inserter = inserter(threads, begin(threads));
//
//	////for (int32_t i = 0; i < 10; ++i)
//	////	threads.push_back(thread{ func,ref(counter)});
//	//generate_n(th_inserter, 1000, [&counter]()
//	//	{return thread{ func,ref(counter) }; });
//
//	//for_each(begin(threads), end(threads),mem_fn(&thread::join));
//
//	//cout << "result = " << counter << endl;
//
//	
//
//	/*std::list a{ 1,2,3,4,5,6,7,8,9,10 };
//	std::list<string> b;
//
//	transform(a.begin(), a.end(), back_inserter(b),
//	[](const auto&element )
//		{
//			return " qweqweqwe";
//		});
//	copy(b.begin(), b.end(),
//	std::ostream_iterator<decltype(*b.begin())>(std::cout, " "));*/
//	//request _re(123);
//
//	//thread foothread{ foo,1,2,3 };
//	//thread foothread2{ foo,1,2,3 };
//	//thread foothread3{ foo,1,2,3 };
//	//thread foothread4{ foo,1,2,3 };
//	//thread foothread5{ foo,1,2,3 };
//	//thread foothread6{ foo,1,2,3 };
//
//	//thread request_th{ &request::process,std::cref(_re)};
//
//	//	foothread.join();
//	//	foothread2.join();
//	//	foothread3.join();
//	//	foothread4.join();
//	//	foothread5.join();
//	//	foothread6.join();
//	//request_th.join();
//
//
//
//
//}
//
