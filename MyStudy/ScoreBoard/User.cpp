#include "User.h"

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
			case 0:
				SS >> Name;
				AssignType = EMumberType::EAge;
				break;
			case 1:
				SS >> Age;
				AssignType = EMumberType::EMath;
				break;
			case 2:
				SS >> Math;
				AssignType = EMumberType::EEng;
				break;
			case 3:
				SS >> Eng;
				AssignType = EMumberType::EKor;
				break;
			case 4:
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