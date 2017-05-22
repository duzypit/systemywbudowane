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
	std::packaged_task<int(int)> pk(factorial);
	std::future<int> ft = pk.get_future();

	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "Main thread: create new thread" << std::endl; 
	std::thread th(std::move(pk), 6);	
	
	std::cout << "Main thread: get from future" << std::endl; 
	int result = ft.get();
	std::cout << "Main thread: result = " << result << std::endl;

	th.join();
	return 0;
}

//check if new thread is created
//while true ; do ps -eLf | grep a.out; sleep 1; clear; done

