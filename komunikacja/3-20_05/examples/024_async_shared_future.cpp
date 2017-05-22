#include <iostream>
#include <thread>
#include <future>


int factorial(std::shared_future<int> f)
{
	int res = 1;
	
	std::cout << "New thread : waiting for a future to be ready..." << std::endl;	
	int N = f.get();
	std::cout << "New thread : future received" << std::endl; 

	for(int i = 1 ; i <= N ; i++)
		res *= i;
	
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return res;
}

int main()
{
	int result = 0;

	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::shared_future<int> sf = f.share();
	 
	std::cout << "Main thread : before async" << std::endl;
	std::future<int> fu1 = std::async(std::launch::async, factorial, sf); 
	std::future<int> fu2 = std::async(std::launch::async, factorial, sf); 
	std::future<int> fu3 = std::async(std::launch::async, factorial, sf); 

    p.set_value(4);	
	
	result = fu1.get();
	std::cout << "Main thread: result = " << result << std::endl;
	
	result = fu2.get();
	std::cout << "Main thread: result = " << result << std::endl;

	result = fu3.get();
	std::cout << "Main thread: result = " << result << std::endl;

	return 0;
}

