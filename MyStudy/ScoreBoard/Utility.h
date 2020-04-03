#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector> 
class Utility
{
public:
	template<typename T>
	static inline void SAFE_DELETE(T*& Param)
	{
		assert(Param && " Param nullptr");
		if (Param != nullptr);
		delete Param;
	};
	template<typename T>
	static inline void Swap(T&& Lhs, T&& Rhs)
	{
		std::remove_reference_t<T> Temp = Lhs;
		Lhs = std::move(Rhs);
		Rhs = std::move(Temp);
	};
	template <>
	static inline void Swap
	(int32_t& Lhs, int32_t& Rhs)
	{
		Lhs = Lhs ^ Rhs;
		Rhs = Lhs ^ Rhs;
		Lhs = Lhs ^ Rhs;
	};
	template<typename T>
	static inline void InputHelper(std::istream& Conin,const std::string& Message, /*Pass To Ref or Ptr */T& Dest)
	{
		std::cout << Message;
		Conin >> Dest;

		if (Conin.fail())
		{
			std::cout << "입력 서식에 맞게 입력하여 주세요." << std::endl;
			Conin.clear();
			Conin.ignore(100,'\n');
			InputHelper(Conin, Message, Dest);
		};
	};
	static inline void FileWrite(const std::string&FileName /*.확장자 붙이기*/,const std::string & Value)
	{
		std::ofstream Out(FileName/*std::ios::app Add Mode*/);
		std::string str;
		
		assert(Out.is_open() && "File Write Fail !!");
		
		Out << Value;
	};
	static inline std::string FileRead(const std::string& FileName)
	{
		std::ifstream In(FileName);
		std::string Str;
		std::string RetBuf;

		RetBuf.reserve(1000);

		if (In.is_open() == false)
		{
			return "File Read Fail!";
		}
		while (In)
		{
			std::getline(In, Str);
			RetBuf += (Str)+"\n"; 
		};
		return RetBuf;
		/*if (In.is_open())
		{
			In >> Str;
			std::cout << Str << std::endl;
		}
		else
			std::cout << "File Read Fail !!";*/
	};
	static inline std::vector<std::string> FileLineRead(const std::string& FileName)
	{
		std::ifstream In(FileName);
		std::string Str;
		
		std::vector<std::string > RetBuf;

		if (In.is_open() == false)
		{
			std::cout << "File Read Fail";
		}
		while (In)
		{
			std::getline(In, Str);
			RetBuf.emplace_back((Str)+"\n"); 
		};
		return RetBuf;
		/*if (In.is_open())
		{
			In >> Str;
			std::cout << Str << std::endl;
		}
		else
			std::cout << "File Read Fail !!";*/
	};
};
