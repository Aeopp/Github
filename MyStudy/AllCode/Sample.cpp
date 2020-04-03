#include <iostream>
#include <regex>
#include <vector>
int main() {
	// 주어진 파일 이름들.
	std::vector<std::string> file_names = { "db-123-log.txt", "db-124-log.txt",
										   "not-db-log.txt", "db-12-log.txt",
										   "db-12-log.jpg" };
	std::regex re("db-\\d*-log\\.txt");
	for (const auto &file_name : file_names) {
		// std::boolalpha 는 bool 을 0 과 1 대신에 false, true 로 표현하게 해줍니다.
		std::cout << file_name << ": " << std::boolalpha
			<< std::regex_match(file_name, re) << '\n';
	};

};