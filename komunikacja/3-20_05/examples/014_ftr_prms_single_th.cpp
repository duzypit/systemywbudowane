#include <iostream>
#include <string>
#include <future>

int main()
{
	//create promise (input) - shared state is alocated
	std::promise<std::string> prms;

	//obtain future from promise (output) - shared state is shared
	std::future<std::string> ftr = prms.get_future();

	//set input (promise)
	prms.set_value("Hello world");

	//get output (future)
	std::string str = ftr.get();

	std::cout << str << std::endl;

	return 0;
}

//g++ <name> -std++=c++11 -pthread
