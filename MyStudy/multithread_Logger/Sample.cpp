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
	// ��׶��� �����忡�� ����� �Լ�
	 void processEntries(); 
	// ť ���� ��ȣ�ϱ� ���� ���ؽ��� ���Ǻ���
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
	// ���ؽ� �� �ɰ� �׸��� ť���߰�
	unique_lock<mutex> lock(mMutex);
	mQueue.push(entry);
	// �����带 ����� ���� ���� ���� ������
	mCondVar.notify_all(); 
}

void Logger::processEntries()
{
	ofstream ofs("log.txt");
	if (ofs.fail()) {
		cerr << "�α����� ���� ���� " << endl;
		return;
	}
	unique_lock<mutex> lock(mMutex);
	while (true) {
		while (!mExit) {
			this_thread::sleep_for(chrono::milliseconds(1000));
			mCondVar.wait(lock);
		}
		//�˸� ��� 
		mCondVar.wait(lock);
		// ���� ���� �˸� ����. ť�� �׸��� ������� ���ɼ��� ����.
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
		ss << "�α� ��Ʈ�� " << i << "�����忡�� " << id;
		logger.log(ss.str());
	}
};
int main()
{
	Logger logger;
	vector<thread> threads;

	auto makethread = [&logger,i = 0]()mutable{
		return thread{ logSomeMessages, ++i, ref(logger) };
	};
	  generate_n(inserter(threads, begin(threads)), 10, makethread);
	/*for (int32_t i = 0; i < 10; ++i) {
		threads.emplace_back(logSomeMessages, ++i, ref(logger));
	}*/
	
	for_each(begin(threads), end(threads), mem_fn(&thread::join)); 

	/*for (int i = 0; i < 10; ++i) {
		threads.emplace_back(logSomeMessages, i, ref(logger));
	};*/

};
