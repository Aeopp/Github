#pragma once
#include "Utility.h"
#include <algorithm>

void Utility::FileWrite(const std::string& FileName, const std::string& Value)
{
	{
		std::ofstream Out(FileName/*std::ios::app Add Mode*/);
		std::string str;

		assert(Out.is_open() && "File Write Fail !!");

		Out << Value;
	};
}

std::string Utility::FileRead(const std::string& FileName)
{
	std::ifstream In(FileName);
	std::string Str;
	std::string RetBuf;

	if (In.is_open() == false)
	{
		return "File Read Fail!";
	}
	while (In)
	{
		std::getline(In, Str);
		/*	RetBuf += (Str)+"\n"; */
		RetBuf += std::move((Str)+"\n");
	};
	RetBuf.erase(std::end(RetBuf) - 4, std::end(RetBuf));
	In.close();
	return RetBuf;
}

std::vector<std::string> Utility::FileLineRead(const std::string& FileName)
{
	std::ifstream In(FileName);
	std::string Str;

	std::vector<std::string> RetBuf;

	if (In.is_open() == false)
	{
		std::cout << "File Read Fail";
	}
	while (In)
	{
		std::getline(In, Str);

		RetBuf.emplace_back(std::move((Str)+"\n"));
	};
	return RetBuf;
}
