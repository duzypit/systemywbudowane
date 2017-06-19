//020 - unique lock, bardziej rozbudowany poprzedni przyklad, przekazywanie wyjscia z watku, 
//l26 czekamy, l17 powiadamiamy prosty problem, skomplikowane rozwiazanie 
#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>

std::mutex my_mutex;
// A condition variable is an object able to block the calling thread until notified to resume.
// It uses a unique_lock (over a mutex) to lock the thread when one of its wait functions is called. 
//The thread remains blocked until woken up by another thread that calls a notification function on the 
//same condition_variable object.
// Objects of type condition_variable always use unique_lock<mutex> to wait: for an alternative that 
//works with any kind of lockable type, see condition_variable_any
std::condition_variable my_cond;

void factorial(int N, int& x)
{
	int res = 1;
	for(int i = 1 ; i <= N ; i++)
		res *= i;

	std::unique_lock<std::mutex> lk(my_mutex);
		x = res;
//Unblocks one of the threads currently waiting for this condition.
// If no threads are waiting, the function does nothing.
// If more than one, it is unspecified which of the threads is selected.
		my_cond.notify_one();
}

int main()
{
	int result = 0;
	std::thread th(factorial, 4, std::ref(result));
	
	std::unique_lock<std::mutex> lk(my_mutex);
		while(result == 0) {
//The execution of the current thread (which shall have locked lck's mutex) is blocked until notified.
//At the moment of blocking the thread, the function automatically calls lck.unlock(), allowing other 
//locked threads to continue.			
			my_cond.wait(lk);
		}
	lk.unlock(); //why?
	
	std::cout << "result = " << result << std::endl;
	
	th.join();

	return 0;
}

