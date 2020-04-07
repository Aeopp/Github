#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector> 
#include <string>
namespace  Utility
{
	template<typename T>
	inline void SAFE_DELETE(T*& Param)
	{
		assert(Param && " Param nullptr");
		if (Param != nullptr);
		delete Param;
	};

	template<typename T>
	inline void Swap(T&& Lhs, T&& Rhs)
	{
		std::remove_reference_t<T> Temp = std::move(Lhs);
		Lhs = std::move(Rhs);
		Rhs = std::move(Temp);
	};

	template <>
	inline void Swap
	(int32_t& Lhs, int32_t& Rhs)
	{
		Lhs = Lhs ^ Rhs;
		Rhs = Lhs ^ Rhs;
		Lhs = Lhs ^ Rhs;
	};

	template<typename T>
	void InputHelper
	(std::istream& Conin, const std::string& Message,/*Pass To Ref or Ptr */T& Dest)
	{
		std::cout << Message;
		Conin >> Dest;

		if (Conin.fail())
		{
			std::cout << "입력 서식에 맞게 입력하여 주세요." << std::endl;
			Conin.clear();
			Conin.ignore(100, '\n');
			InputHelper(Conin, Message, Dest);
		};
	};

	inline void FileWrite
	(const std::string& FileName /*.확장자 붙이기*/, const std::string& Value);
	std::string FileRead(const std::string& FileName);

	std::vector<std::string> FileLineRead
	(const std::string& FileName);
};
