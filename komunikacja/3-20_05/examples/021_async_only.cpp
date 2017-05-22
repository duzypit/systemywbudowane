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
	
	std::future<int> fu = std::async(factorial, 4);	
	result = fu.get();

	std::cout << "result = " << result << std::endl;

	return 0;
}

