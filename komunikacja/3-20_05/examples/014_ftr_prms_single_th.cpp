//014 - future i promise - std::promise na typ jest to szablon, a tak naprawde pod 
//spodem jest tworzony tzw. shared state - promise to wejscie do shared state 
//wspoldzielony miedzy watkami i mozemy do niego cos zapisywac l 8, promise jest 
//kojarzony z future - otwieramy drzwi jest to wyjscie l11 stworzylismy kanal komunikacji. 
//l14 ustawiamy wartosc, l17 pobieramy, get jest wywołaniem lockujacym, watek bedzie 
//zablokowany do momentu pojawienia sie danych.
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
