#include <iostream>
#include <thread>
#include <future>

int factorial(int N)
{
	std::cout << "factorial" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	int res = 1;
	for(int i = 1 ; i <= N ; i++)
		res *= i;
	
	return res;
}

int main()
{
	//wraps any Callable target (function, lambda expression, bind expression, or another function object)
	//so that it can be invoked asynchronously.
	//Its return value or exception thrown is stored in a shared state which can be accessed through std::future objects.
	std::packaged_task<int(int)> pk(factorial);

	std::this_thread::sleep_for(std::chrono::seconds(5));
	pk(6); // can be executed later on, not during creation
	
	int result = pk.get_future().get();
	std::cout << "Main thread: result = " << result << std::endl;

	return 0;
}

//check if new thread is created
//while true ; do ps -eLf | grep a.out; sleep 1; clear; done

