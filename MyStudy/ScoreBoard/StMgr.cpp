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
	"���� �����͸� ���̺� �մϴ� ����մϱ�? (1) ���̺� (0) ���", IsSave);

	if (!(IsSave == 0 || IsSave == 1))
	{
		std::cout << "�ùٸ��� �Է����ּ���.";
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
	Utility::InputHelper(std::cin, "��� �����ұ�� ? (1) Front (2) Back (3) Search (4) Sort  ", Flag);
	if (!(Flag == 1 || Flag == 2 || Flag == 3 || Flag == 4))
	{
		std::cout << "�ùٸ��� �Է����ּ���.";
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
		Utility::InputHelper(std::cin, "�Է��Ͻ� �л���ġ�� ���Ե˴ϴ�.", SearchName);
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
	" ������ ���ϴ� �л� �̸� �Է� : ", modiname);

	User& Ref = List.SearchData(modiname, FPtr);

	std::cin >> Ref;
};
template<class T, class Arg>
void StMgr<T,Arg>::Erase()
{
	std::string Name;
	Utility::InputHelper(std::cin, " ������ �л� �̸� : ", Name);

	List.Erase(Name,FPtr);
};
template<class T , class Arg>
uint32_t StMgr<T, Arg>::Menu()
{
	uint32_t Case;
	std::cout << "============================================= ���� ���� ���α׷� =============================================\n\n";
	std::cout << List;
	Utility::InputHelper(std::cin, "(0) ���̺� (1) �ε� (2) �߰� (3) ���� (4) ���� (5) ���� (6) ��� (7) �����̸����� (8) ���� ", Case);
	return Case;
};