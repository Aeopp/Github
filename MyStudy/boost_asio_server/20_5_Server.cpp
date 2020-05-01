#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

int main()
{
	//setlocale(LC_ALL, "");
	
	try {
		boost::asio::io_service io_service;
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 13);

		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint);

		std::wcout << L"서버 시작" << std::endl;
		while (true)
		{
			const std::string message_to_send = "Server Hello";

			boost::asio::ip::tcp::iostream stream;

			std::wcout << "check 1" << std::endl;

			boost::system::error_code error_code;
			acceptor.accept(*stream.rdbuf(), error_code);

			if(!error_code) // TODO how to take care of multiple clients?? 
				{
				std::string line;
				std::getline(stream, line);
				std::cout << line << std::endl;

				stream << message_to_send;
				stream << std::endl; 
			}
		}
	}
	catch (std::exception& exception){
		std::wcout << exception.what(); 
	}
}