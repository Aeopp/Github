#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <iomanip>
#include "Utility.h"

struct User
{
private:	
	enum  EMumberType : uint8_t
	{
		EName = 0,
		EAge,
		EMath,
		EEng,
		EKor,

		ENone=255,
	};

	std::string Name;
	int32_t Age;
	int32_t Math;
	int32_t Eng;
	int32_t Kor;
	float Sum;
	float Average;

	void RandSet();
	inline void Print()const;
	inline void Calc();

	friend inline std::ofstream& operator<<(std::ofstream& FileWrite,const User& Rhs);
	friend inline std::ostream& operator<<(std::ostream& ConOut, const User& Rhs);
	friend inline std::istream& operator>>(std::istream& Conin, User& Rhs);
public:
	User();
	const inline  std::string getName() const;
	void FileSetUpData(const std::string& Str, const std::string & Sepa = ":");
	void inline Write(std::ofstream& FileWrite, const User& Rhs);
	inline void SetData(const int32_t PAge, std::string&& PName,
	const int32_t PMath, const int32_t PEng, const int32_t PKor);
	inline void SetName(const std::string PName); 
	
	inline bool operator<=(const User& Rhs)const;
	inline bool operator>=(const User& Rhs)const;
	inline bool operator!=(const User&Rhs)const;
};
inline void User::SetName(const std::string PName)
{
	this->Name = PName;
};
inline std::ofstream& operator<<(std::ofstream& FileWrite, const User& Rhs)
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
inline  std::ostream& operator<<(std::ostream& ConOut, const User& Rhs)
{
	Rhs.Print();
	return ConOut;
}
inline std::istream & operator>>(std::istream & Conin,User& Rhs)
{
	Utility::InputHelper(Conin, "�̸� : ", Rhs.Name)			;
	Utility::InputHelper(Conin, "���� : ", Rhs.Age)	  ;
	Utility::InputHelper(Conin, "���� : ", Rhs.Math)	  ;
	Utility::InputHelper(Conin, "���� : ", Rhs.Eng);
	Utility::InputHelper(Conin, "���� : ", Rhs.Kor);
	//Conin.ignore(INT_MAX, '\n');

	Rhs.Calc(); 
	return Conin;
};
inline void User::RandSet()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_int_distribution<int32_t> dis(0, 100);

	Age = std::clamp((dis(gen) % 21), 14, 20);
	Math = dis(gen);
	Eng = dis(gen);
	Kor = dis(gen);
	Calc();
}

inline void User::Print() const
{
	std::cout 
	<< "\t" << "�̸� : " << Name  << "\t���� : " << Age
	<< "\t���� : " << Math << "\t���� : " << Eng 
	<< "\t���� : " << Kor << "\t���� : " << Sum
	<< "\t��� : " << Average << std::endl;
}
 
inline bool User::operator<=(const User& Rhs)const
{
	return this->Sum <= Rhs.Sum;
};
inline bool User::operator>=(const User& Rhs)const 
{  
	return(!(*this <= Rhs));
};
inline bool User::operator!=(const User&Rhs)const 
{
	return( this->Name != Rhs.Name);
};
inline void User::Calc()
{
	Sum = Math + Eng + Kor;
	Average = static_cast<float>(Sum / 3);
}
inline void User::Write(std::ofstream & FileWrite, const User & Rhs)
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

inline User::User(){}

inline const std::string User::getName() const
{
	return Name;
}

 inline void User::SetData(const int32_t PAge, 
	 std::string && PName, const int32_t PMath, 
	 const int32_t PEng, const int32_t PKor)
{
	 Age = PAge;
	 Name = std::move(PName);
	 Math = PMath;
	 Eng = PEng;
	 Kor = PKor;
	 Calc();
 };
