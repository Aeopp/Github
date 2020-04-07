#pragma once
#include "StMgr.h"

template<class T , class Arg >
StMgr<T, Arg>* StMgr<T, Arg>::getStMgr()
{
	if (RetVal != nullptr) return RetVal;

	RetVal = new StMgr();

	RetVal->Init([](const Arg& Lhs, const T& Rhs)
	{return Lhs != Rhs.getName();  });

	return RetVal;
};

template<class T, class Arg>
void StMgr<T, Arg>::Delete()
{
	auto Deleter = getStMgr();

	if (Deleter)
	{
		delete getStMgr();
	}
};

template<class T, class Arg>
void StMgr<T, Arg>::Init(FuncType setSortFunc, 
const std::string& setFileName)
{
	FPtr = setSortFunc;
	FileName = setFileName;
}

template<class T, class Arg>
bool StMgr<T, Arg>::Save()
{
	uint32_t IsSave;

	Utility::InputHelper(std::cin,
	"현재 데이터를 세이브 합니다 계속합니까? (1) 세이브 (0) 취소", IsSave);

	if (!(IsSave == 0 || IsSave == 1))
	{
		std::cout << "올바르게 입력해주세요.";
		StMgr::Save();
	};

	std::ofstream FileWrite(FileName);

	const size_t ListSize = StMgr::List.getSize();

	for (int i = 0; i < ListSize; ++i)
	{
		List[i].Write(FileWrite, List[i]);
	};
	return true;
}
template<class T, class Arg>
bool StMgr<T, Arg>::Load()
{
	std::string Buf = Utility::FileRead(FileName);
	std::stringstream SS(Buf);
	std::string Par;

	List.DeleteAll();

	while (std::getline(SS, Par))
	{
		User Temp;
		Temp.FileSetUpData(Par);
		List.SortInsert(Temp);
	};
	return true;
};
template<class T, class Arg>
void StMgr<T, Arg>::AddStu()
{
	uint32_t Flag;
	Utility::InputHelper(std::cin, "어디에 삽입할까요 ? (1) Front (2) Back (3) Search (4) Sort  ", Flag);
	if (!(Flag == 1 || Flag == 2 || Flag == 3 || Flag == 4))
	{
		std::cout << "올바르게 입력해주세요.";
		AddStu();
	}
	std::string SearchName;
	User UserArg;
	User Temp;
	std::cin >> UserArg;
	switch (Flag)
	{
	case 1:
		List.front_Insert(UserArg);
		break;
	case 2:
		List.back_Insert(UserArg);
		break;
	case 3:
		Utility::InputHelper(std::cin, "입력하신 학생위치에 삽입됩니다.", SearchName);
		List.Insert<std::string>(SearchName,FPtr, UserArg);
		break;
	case 4:
		List.SortInsert(UserArg);
		break;
	default:
		break;
	}
	return;
};
template<class T, class Arg>
void StMgr<T,Arg>::Modified()
{
	std::string modiname;

	Utility::InputHelper(std::cin, 
	" 수정을 원하는 학생 이름 입력 : ", modiname);

	User& Ref = List.SearchData(modiname, FPtr);

	std::cin >> Ref;
};
template<class T, class Arg>
void StMgr<T,Arg>::Erase()
{
	std::string Name;
	Utility::InputHelper(std::cin, " 삭제할 학생 이름 : ", Name);

	List.Erase(Name,FPtr);
};
template<class T , class Arg>
uint32_t StMgr<T, Arg>::Menu()
{
	uint32_t Case;
	std::cout << "============================================= 성적 관리 프로그램 =============================================\n\n";
	std::cout << List;
	Utility::InputHelper(std::cin, "(0) 세이브 (1) 로딩 (2) 추가 (3) 수정 (4) 정렬 (5) 삭제 (6) 출력 (7) 파일이름수정 (8) 종료 ", Case);
	return Case;
};