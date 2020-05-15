#pragma once
#include <string>activecf.h


namespace Debug {
	// string �� ��� ����
	static auto LogImplementation(const char* __Func, long  __LINE, std::string Message)
	{
		std::string Log = " Function ";
		return (Log + __Func + " Line :  " + std::to_string(__LINE) + " \n " + Message).c_str();
	};
#define Log(Target) LogImplementation(__FUNCTION__,__LINE__,Target)
};