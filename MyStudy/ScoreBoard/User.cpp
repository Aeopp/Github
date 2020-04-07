#pragma once
#include "User.h"

void User::Write(std::ofstream& FileWrite, const User& Rhs)const
{

	std::string Buf;

	Buf += " �̸� : " + Rhs.Name +

		" ���� : " + std::to_string(Rhs.Age) +
		" ���� : " + std::to_string(Rhs.Math) +
		" ���� : " + std::to_string(Rhs.Eng) +
		" ���� : " + std::to_string(Rhs.Kor) +
		" ���� : " + std::to_string(Rhs.Sum) +
		" ��� : " + std::to_string(Rhs.Average) +

		"\n";

	FileWrite << Buf;
};
void User::RandSet()
{
	static std::random_device RandomDevice;
	static std::mt19937 Generate(RandomDevice());
	static std::uniform_int_distribution<int32_t> Distribution(0, 100);

	Age = std::clamp((Distribution(Generate)), 14, 20);
	Math = Distribution(Generate);
	Eng = Distribution(Generate);
	Kor = Distribution(Generate);
	Calc();
}

void User::SetData(const int32_t PAge,
	std::string&& PName, const int32_t PMath,
	const int32_t PEng, const int32_t PKor)
{
	Age = PAge;
	Name = std::move(PName);
	Math = PMath;
	Eng = PEng;
	Kor = PKor;
	Calc();
};

void User::FileSetUpData(const std::string & Str,const std::string& Sepa)
{
	std::stringstream SS(Str);
	std::string Buf;

	EMumberType AssignType  = EMumberType::EName;

	while (SS >> Buf)
	{
		if(Buf == Sepa)
		{
			switch (AssignType)
			{
			case EMumberType::EName:
				SS >> Name;
				AssignType = EMumberType::EAge;
				break;
			case EMumberType::EAge:
				SS >> Age;
				AssignType = EMumberType::EMath;
				break;
			case EMumberType::EMath:
				SS >> Math;
				AssignType = EMumberType::EEng;
				break;
			case EMumberType::EEng:
				SS >> Eng;
				AssignType = EMumberType::EKor;
				break;
			case EMumberType::EKor:
				SS >> Kor;
				AssignType = EMumberType::ENone;
				break;
			default:
				break;
			}
		};
	};
	Calc();
}
std::ofstream& operator<<(std::ofstream& FileWrite, const User& Rhs)
{
	std::string Buf;

	Buf += " �̸� : " + Rhs.Name +

		" ���� : " + std::to_string(Rhs.Age) +
		" ���� : " + std::to_string(Rhs.Math) +
		" ���� : " + std::to_string(Rhs.Eng) +
		" ���� : " + std::to_string(Rhs.Kor) +
		" ���� : " + std::to_string(Rhs.Sum) +
		" ��� : " + std::to_string(Rhs.Average) +

		"\n";

	FileWrite << Buf;
	return FileWrite;
};

std::istream& operator>>(std::istream& Conin, User& Rhs)
{
	Utility::InputHelper(Conin, "�̸� : ", Rhs.Name);
	Utility::InputHelper(Conin, "���� : ", Rhs.Age);
	Utility::InputHelper(Conin, "���� : ", Rhs.Math);
	Utility::InputHelper(Conin, "���� : ", Rhs.Eng);
	Utility::InputHelper(Conin, "���� : ", Rhs.Kor);
	//Conin.ignore(INT_MAX, '\n');

	Rhs.Calc();
	return Conin;
};