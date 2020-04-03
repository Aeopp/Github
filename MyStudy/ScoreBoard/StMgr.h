#pragma once
#include "LinkedList.h"
using T = User;
class StMgr
{
private:
	using FPtrType = std::function<bool(const std::string& name, const T& User)>;

	static inline bool Save();
	static inline bool Load();
	static inline void AddStu();
	static inline void Modified();
	static inline void Erase();
	static uint32_t  Menu();
	static inline LinkedList List;
	static inline std::string FileName = "ScoreBoard.txt";
	static inline FPtrType FPtr = [](const std::string& name, const T& User)->bool
	{
		return name != User.getName() ; };

	//static FPtrType retFPtr() 
	//{

	//}
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
				Utility::InputHelper(std::cin, "새로 관리할 파일이름 : ", FileName);
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
	"현재 데이터를 세이브 합니다 계속합니까? (1) 세이브 (0) 취소", IsSave);

	 if (!(IsSave == 0 || IsSave == 1))
	 {
		 std::cout << "올바르게 입력해주세요.";
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
	 Utility::InputHelper(std::cin, "어디에 삽입할까요 ? (1) Front (2) Back (3) Search (4) Sort  ", Flag);
	 if (!(Flag == 1 || Flag == 2 || Flag == 3 || Flag == 4))
	 {
		 std::cout << "올바르게 입력해주세요.";
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
		 Utility::InputHelper(std::cin, "입력하신 학생위치에 삽입됩니다.", SearchName);
		 /*Temp.SetName(SearchName);*/
		 List.Insert(SearchName,FPtr, Arg);
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
	 Utility::InputHelper(std::cin, " 수정을 원하는 학생 이름 입력 : ", modiname);
	 /*User Temp;
	 Temp.SetName(modiname);*/

	 User& Ref = List.SearchData(modiname,FPtr);
	 std::cin >> Ref;
 };

 inline void StMgr::Erase()
 {
	 std::string Name;
	 Utility::InputHelper(std::cin, " 삭제할 학생 이름 : ", Name);
	/* User Target;
	 Target.SetName(Name);*/

	 List.Erase(Name,FPtr);
 };

 inline uint32_t StMgr::Menu()
 {
	 uint32_t Case;
	 std::cout << "============================================= 성적 관리 프로그램 =============================================\n\n";
	 std::cout << List;
	 Utility::InputHelper(std::cin,"(0) 세이브 (1) 로딩 (2) 추가 (3) 수정 (4) 정렬 (5) 삭제 (6) 출력 (7) 파일이름수정 (8) 종료 ", Case);
	 return Case;
 };