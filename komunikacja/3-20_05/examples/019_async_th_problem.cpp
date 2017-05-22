#include <iostream>
#include <thread>

void factorial(int N, int& x)
{
	int res = 1;
	for(int i = 1 ; i <= N ; i++)
		res *= i;

	x = res;
}

int main()
{
	int result;
	std::thread th(factorial, 4, std::ref(result));
	
	std::cout << "result = " << result << std::endl;
	
	th.join();

	return 0;
}

