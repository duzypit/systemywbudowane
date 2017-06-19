
//021 - nowa wlasnosc cpp std::asynch - wrapper na watki, ma polaczony ze soba future domyslnie, 
//mozemy zrobic get i czekamy az bedzie wartosc, jest to SZABLON -> LOOK NA VECTOR l21 get, l20 asynch, 
//ladne roziwazanie#include <iostream>
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
	//A future is an object that can retrieve a value from some provider object or function, 
	//properly synchronizing this access if in different threads.

	//Calls fn (with args as arguments) at some point, returning without waiting for the execution of fn to complete.
	//The value returned by fn can be accessed through the future object returned (by calling its member future::get).

	std::future<int> fu = std::async(factorial, 4);	
	result = fu.get();

	std::cout << "result = " << result << std::endl;

	return 0;
}

