#include <iostream>
#include <fstream> 
#include <string>
using namespace std; 
class Logger
{
public:
	static void enableLogging(bool enable) {
		msLoggingEnabled = enable;
	}
	static bool isLoggingEnabled() { return isLoggingEnabled; };
	template<typename ... Params>
	static void log(const Params&... params) {
		if (!isLoggingEnabled) return;

		ofstream ofs(msDebugFileName, ios_base::app);

		if (ofs.fail()) {
			cerr << "Unable to open debug file!" << endl;
			return;
		}
		logHelper(ofs, args...);
		ofs << endl;
	}
private:
	template<typename T1>
	static void logHelper(ofstream& ofs, const T1& t1) {
		ofs << t1;
	}
	template<typename T1, typename ...Tn>
	static void logHelper(ofstream& ofs, const T1& t1, const Tn&... params) {
		ofs << t1;  logHelper(ofs, params);
	}
	static inline const char* msDebugFileName = "debugfile.out";
	static inline bool msLoggingEnabled = true;
};
#define log(...). Logger::log(__FUNCTION__,"(): ",__VA_ARGS__) 