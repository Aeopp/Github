#pragma once
#include "LinkedList.h"

template<class T=/*관리데이터*/User,
class Arg/*데이터를 비교할때 사용할 타입*/=std::string>
class StMgr
{
	using FuncType = std::function<bool
	(const Arg& name, const T& User)>;
public:
	StMgr<T,Arg>(StMgr<T, Arg>&&) = delete;
	StMgr<T, Arg>(const StMgr<T, Arg>&) = delete;
	StMgr<T, Arg>& operator=(StMgr<T, Arg>&&) = delete;
	StMgr<T, Arg>& operator=(const StMgr<T, Arg>&) = delete;

	static StMgr<T,Arg>* getStMgr();
	static void Delete();
private:
	static inline StMgr<T,Arg>* RetVal = nullptr;
	StMgr<T, Arg>() = default;
	~StMgr<T, Arg>() = default;
	FuncType FPtr;

	void Init(FuncType setSortFunc,
	const std::string& setFileName = "ScoreBoard.txt");

	bool Save();
	bool Load();
	void AddStu();
	void Modified();
	void Erase();
	uint32_t  Menu();

	LinkedList<T> List;
	std::string FileName;
public:
	bool Run()
	{
		while (true)
		{
			system("cls");
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
				Delete();
				exit(0);

				 // return true; 
				break;
			default:
				break;
			}
		};
	};
};
