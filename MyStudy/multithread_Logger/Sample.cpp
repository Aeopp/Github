#include <atomic>
#include <iostream>
#include <string>
#include <mutex>
#include <queue> 
#include <fstream>
#include <sstream>
#include <iterator>
#include <functional>
using namespace std; 
class Logger
{
public:
	virtual ~Logger(); 
	Logger();
	constexpr Logger(const Logger& src) = delete;
	constexpr Logger& operator=(const Logger& rhs) = delete; 
	constexpr Logger(Logger&&) noexcept = delete;
	constexpr Logger& operator=(Logger&&) noexcept= delete;
	
	 void log(const string& entry)&;
private:
	// 백그라운드 스레드에서 실행될 함수
	 void processEntries(); 
	// 큐 접근 보호하기 위한 뮤텍스와 조건변수
	mutex mMutex;
	condition_variable mCondVar;
	queue<string> mQueue; 
	thread mThread; 
	atomic<bool> mExit; 
};

Logger::~Logger()
{
	{
  		unique_lock<mutex> lock(mMutex);
		mExit = true; 
		mCondVar.notify_all(); 
	}
	mThread.join();
}

Logger::Logger() : mExit(false )
{
	mThread = thread{ &Logger::processEntries,this }; 
}

void Logger::log(const string& entry)&
{
	// 뮤텍스 락 걸고 항목을 큐에추가
	unique_lock<mutex> lock(mMutex);
	mQueue.push(entry);
	// 스레드를 깨우기 위해 조건 변숭 ㅏㄹ림
	mCondVar.notify_all(); 
}

void Logger::processEntries()
{
	ofstream ofs("log.txt");
	if (ofs.fail()) {
		cerr << "로그파일 오픈 실패 " << endl;
		return;
	}
	unique_lock<mutex> lock(mMutex);
	while (true) {
		while (!mExit) {
			this_thread::sleep_for(chrono::milliseconds(1000));
			mCondVar.wait(lock);
		}
		//알림 대기   
		mCondVar.wait(lock);
		// 조건 변수 알림 수신. 큐에 항목이 들어있을 가능성이 높다.
		lock.unlock();
		while (true) {
			lock.lock();
			if (mQueue.empty()) {
				break;
			}
			else {
				ofs << mQueue.front() << endl;
				mQueue.pop();
			}
			lock.unlock();
		}
	}
};

void logSomeMessages(int id, Logger& logger) {
	for (int32_t i = 0; i < 10; ++i) {
		stringstream ss;
		ss << "로그 엔트리 " << i << "스레드에서 " << id;
		logger.log(ss.str());
	}
};
void foo(int& a) 
{
	a = 127;
};

void print(int& test) {
	std::cout << test << '\n';
	test = 99999999;
};

struct ABC {
	ABC() { std::cout << __FUNCTION__ << endl; };
	ABC(ABC& a)
	{
		std::cout << __FUNCTION__ << endl;
	};
	ABC(ABC&& a)



	{
		std::cout << __FUNCTION__ << endl;
	};
	ABC&operator=(ABC&& a)noexcept(true) 
	{
		std::cout << __FUNCTION__ << endl;
	};
	ABC& operator=(ABC&  a)
	{
		std::cout << __FUNCTION__ << endl;
	};
	void foo() {
		std::cout << __FUNCTION__ << endl; 
	}; 
};
template<typename _Ty> 
class ref_
{
public  : 
	_Ty& _Ty_ref;
	// ref_(_Ty& param) : _Ty_ref(param) {}; 
	void foo() { 
		cout << _Ty_ref;  
	};
};
int main()
{
	ABC ads;

	auto qwe = thread{ &ABC::foo,ABC() };
	qwe.join(); 
	auto zxc = thread{ &ABC::foo,ref(ads)}; 
	zxc.join(); 

	int qweqwe; 
	/*
	int i = 10;

	auto f1 = std::bind(print, i);
	auto f2 = std::bind(print, std::ref(i));

	i = 99999;

	f1();
	f2();
	i = 33;
	f2();
	f1();*/

	//Logger logger;
	//vector<thread> threads;

	//auto makethread = [&logger,i = 0]()mutable{
	//	return thread{ logSomeMessages, ++i, ref(logger) };
	//};
	//  generate_n(inserter(threads, begin(threads)), 10, makethread);
	///*for (int32_t i = 0; i < 10; ++i) {
	//	threads.emplace_back(logSomeMessages, ++i, ref(logger));
	//}*/
	//
	//for_each(begin(threads), end(threads), mem_fn(&thread::join)); 

	/*for (int i = 0; i < 10; ++i) {
		threads.emplace_back(logSomeMessages, i, ref(logger));
	};*/

};
