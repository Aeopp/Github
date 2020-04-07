#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <utility>
#include <iomanip>
#include "Utility.h"
//
//using std::rel_ops::operator!=;
//using std::rel_ops::operator<=;
//using std::rel_ops::operator>;
//using std::rel_ops::operator>=;

struct User
{
private:	
	enum  class 
	EMumberType : uint8_t 
	{
		EName =0 ,
		EAge,
		EMath,
		EEng,
		EKor,

		ENone=255,
	};

	std::string Name;
	int32_t Age = -1;
	int32_t Math = -1;
	int32_t Eng = -1;
	int32_t Kor = -1;
	float Sum = -1.f;
	float Average = 1.f;

	void RandSet();
	inline void Print()const;
	inline void Calc();

	friend  std::ofstream& operator<<(std::ofstream& FileWrite,const User& Rhs);

	friend  std::ostream& operator<<(std::ostream& ConOut, const User& Rhs);
	friend  std::istream& operator>>(std::istream& Conin, User& Rhs);
public:
	void SetData(const int32_t PAge, std::string&& PName/*R-Value Ref*/,
		const int32_t PMath, const int32_t PEng, const int32_t PKor);

	User(User&& Rhs)noexcept = default;
	/*virtual*/~User() noexcept = default;
	User& operator=(User&& Rhs) noexcept = default;

	User() = default;
	User(const User& Rhs) = default;
	User& operator=(const User& Rhs) = default;
	

	inline std::string getName() const;
	void FileSetUpData(const std::string& Str, 
	const std::string & Sepa =/* 파싱용 구분자 */":");

	void  Write(std::ofstream& FileWrite, const User& Rhs)const;

	inline void SetName(const std::string PName); 
	inline bool operator<(const User& Rhs)const;
	inline bool operator<=(const User& Rhs)const;
	inline bool operator>(const User& Rhs)const;
	inline bool operator>=(const User& Rhs)const;
	inline bool operator==(const User& Rhs)const;
	inline bool operator!=(const User& Rhs)const;
};
inline void User::SetName(const std::string PName)
{
	this->Name = PName;
};

inline  std::ostream& operator<<(std::ostream& ConOut, const User& Rhs)
{
	Rhs.Print();
	return ConOut;
}



inline void User::Print() const
{
	std::cout
		<< "\t" << "이름 : " << Name << "\t나이 : " << Age
		<< "\t수학 : " << Math << "\t영어 : " << Eng
		<< "\t국어 : " << Kor << "\t총점 : " << Sum
		<< "\t평균 : " << Average << std::endl;
};

inline bool User::operator<(const User& Rhs)const
{
	return this->Sum < Rhs.Sum;
};
inline bool User::operator<=(const User& Rhs)const
{
	return this->Sum <= Rhs.Sum;
};

inline bool User::operator>(const User& Rhs)const
{
	return this->Sum  > Rhs.Sum;
};
inline bool User::operator>= (const User& Rhs)const
{
	return this->Sum >= Rhs.Sum;
};
inline bool User::operator==(const User& Rhs)const
{
	return(this->Name == Rhs.Name);
};
inline bool User::operator!=(const User& Rhs)const
{
	return  (! (this->Name == Rhs.Name));
};
inline void User::Calc()
{
	Sum =static_cast<float> (  Math + Eng + Kor);
	Average = static_cast<float>(Sum / 3);
}

inline std::string User::getName() const
{
	return Name;
}
