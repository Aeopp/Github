#pragma once
#include "LinkedList.h"

class StMgr
{
private:
	static inline bool Save();
	static inline bool Load();
	static inline void AddStu();
	static inline void Modified();
	static inline void Erase();
	static uint32_t  Menu();
	static inline LinkedList List;
	static inline std::string FileName = "ScoreBoard.txt";
public:
	static bool Run()
	{
		while (true)
		{
			uint32_t Case = Menu();
			switch (Case)
			{
			case 0:
				Save();
				break;
			case 1:
				Load();
				break;
			case 2:
				AddStu();
				break;
			case 3:
				Modified();
				break;
			case 4:
				List.Sort();
				break;
			case 5:
				Erase();
				break;
			case 6:
				std::cout << List;
				break;
			case 7:
				Utility::InputHelper(std::cin, "���� ������ �����̸� : ", FileName);
				break;
			case 8:
				exit(0);
				break;
			default:
				break;
			}
		};
	};
};

 inline bool StMgr::Save()
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

	const size_t ListSize = List.getSize();

	 for (int i = 0; i < ListSize; ++i)
	 {
		 List[i].Write(FileWrite,List[i]);
	 };
	 return true;
 }
 inline bool StMgr::Load()
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

 inline void StMgr::AddStu()
 {
	 uint32_t Flag;
	 Utility::InputHelper(std::cin, "��� �����ұ�� ? (1) Front (2) Back (3) Search (4) Sort  ", Flag);
	 if (!(Flag == 1 || Flag == 2 || Flag == 3 || Flag == 4))
	 {
		 std::cout << "�ùٸ��� �Է����ּ���.";
		 AddStu(); }

	 std::string SearchName;
	 User Arg;
	 User Temp;
	 std::cin >> Arg;
	 switch (Flag)
	 {
	 case 1:
		 List.front_Insert(Arg);
		 break;
	 case 2:
		 List.back_Insert(Arg);
		 break;
	 case 3:
		 Utility::InputHelper(std::cin, "�Է��Ͻ� �л���ġ�� ���Ե˴ϴ�.", SearchName);
		 Temp.SetName(SearchName);
		 List.Insert(Temp, Arg);
		 break;
	 case 4:
		 List.SortInsert(Arg);
		 break;
	 default:
		 break;
	 }
	 return ; 
 };

 inline void StMgr::Modified()
 {
	 std::string modiname;
	 Utility::InputHelper(std::cin, " ������ ���ϴ� �л� �̸� �Է� : ", modiname);
	 User Temp;
	 Temp.SetName(modiname);
	 User& Ref = List.SearchData(Temp);
	 std::cin >> Ref;
 };

 inline void StMgr::Erase()
 {
	 std::string Name;
	 Utility::InputHelper(std::cin, " ������ �л� �̸� : ", Name);
	 User Target;
	 Target.SetName(Name);
	 List.Erase(Target);
 };

 inline uint32_t StMgr::Menu()
 {
	 uint32_t Case;
	 std::cout << "============================================= ���� ���� ���α׷� =============================================\n\n";
	 std::cout << List;
	 Utility::InputHelper(std::cin,"(0) ���̺� (1) �ε� (2) �߰� (3) ���� (4) ���� (5) ���� (6) ��� (7) �����̸����� (8) ���� ", Case);
	 return Case;
 };