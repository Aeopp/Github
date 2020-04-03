//#include <iostream>
//#include <fstream>
//#include <string>
//
//int main()
//{
//	std::ofstream f;
//
//	/*f.open("D:\MyStudy\StudyStream\TestText.txt");*/
//	f.open("Test.txt");
//	f << "OK Test !!  " << 1234 <<std:: endl;
//	f.close(); 
//
//	//std::ifstream f;
//	//std::string str;
//	//int i;
//	//f.open("Test.txt");
//	//f >> str >> i;
//	//std::cout << str << i << std::endl;
//	//f.close(); 
//};

 
#include <fstream>
#include <iostream>
#include <string>

int main() {
	std::ifstream in("test.txt");
	char buf[100];

	if (!in.is_open())
	{
		std::cout << "파일을 찾을 수 없습니다!" << std::endl;
		return 0; 
	};
	while (in)
	{
		in.getline(buf, 100);
		std::cout << buf << std::endl;
	};

		return 0; 
}