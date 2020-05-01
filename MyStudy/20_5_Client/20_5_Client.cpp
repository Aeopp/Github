#include <iostream>
#include <string>
#include <boost/asio.hpp>
int main(int argc,char* argv[])
{
	try
	{
		if(argc!=2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;  
		}
		boost::asio::ip::tcp::iostream stream(argv[1], std::to_string(int32_t(13)));
		if(!stream)
		{
			std::cout << "Unable to connect: " << stream.error().message() << std::endl;
			return 1; 
		}

		stream << "Hello from client";
		stream << std::endl;

		std::string line;
		std::getline(stream, line);
		std::cout << line << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Exception : " << e.what() << std::endl; 
	}

	return  0; 
}