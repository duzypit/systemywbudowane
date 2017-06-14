//016 - std::ref - oba watki maja dostep, get lockuje l26,
#include <iostream>
#include <string>
#include <future>
#include <thread>

void thFun(std::promise<std::string>& prms)
{
	std::this_thread::sleep_for(std::chrono::seconds(5));

	//set input (promise)
	prms.set_value("Hello world");
}

int main()
{
	//create promise (input) - shared state is alocated
	std::promise<std::string> prms;

	//obtain future from promise (output) - shared state is shared
	std::future<std::string> ftr = prms.get_future();

	//share the input(promise) with new thread
	// You should think of using std::ref when a function takes a template parameter by value, such as std::bind.
	// std::ref is a value type that behaves like a reference.
	std::thread th(&thFun, std::ref(prms));

	//get output (future)
	std::string str = ftr.get();

	std::cout << str << std::endl;
	th.join();
	return 0;
}

//g++ <name> -std++=c++11 -pthread
