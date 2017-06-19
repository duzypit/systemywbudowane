//022 - asynch policy AUTO - deukcja typow, polityka obslugi asynch, obsluga funkcji w nowym watku 
//std::launch::async, std::launch::defered - ten sam watek i polityka domyslna,ktora wybieze system 
//async swietnie dziala z future i promise
#include <iostream>
#include <thread>
#include <future>


int factorial(int N)
{
	int res = 1;
	for(int i = 1 ; i <= N ; i++)
		res *= i;
	
	//std::this_thread::sleep_for(std::chrono::seconds(5));
	return res;
}

int main()
{
	int result = 0;

	std::future<int> fu = std::async(factorial, 4); //may create new thread	
	//std::future<int> fu = std::async(std::launch::deferred, factorial, 4); //does not create new thread	
	//std::future<int> fu = std::async(std::launch::async, factorial, 4); //creates new thread	
	//std::future<int> fu = std::async(std::launch::deferred | std::launch::async, factorial, 4); //may create new thread	

	result = fu.get();

	std::cout << "result = " << result << std::endl;

	return 0;
}

