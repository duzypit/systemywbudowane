//015 l23 - przekazujemy promisa do nowego watku - wejscie, condition variable jesli 
//ktos nie zapisze we future wartosci to promise jest blokniety - move przeniesienie 
//wlasnosci, std::move
#include <iostream>
#include <string>
#include <future>
#include <thread>

void thFun(std::promise<std::string>&& prms)
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

	//move the input(promise) to new thread
	std::thread th(&thFun, std::move(prms));

	//get output (future)
	std::string str = ftr.get();

	std::cout << str << std::endl;
	th.join();
	return 0;
}

