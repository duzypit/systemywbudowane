//012 - unique lock, jak lock_guard, ale mozna go samodzielnie unlockowac, 
//ten smart mutex moze dzialac ze zmienna warunkowa
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class Wallet {
public:
	Wallet() : m_money(0) {}
	void addMoney(int val) {
		std::unique_lock<std::mutex> lk(m_myMutex);
			for(int i = 0 ; i < val; i++)
				m_money++;
		//lk.unlock(); //mozna zrobic
	}

	void checkMoney() { std::cout << m_money << std::endl; }

private:
	int m_money;
	std::mutex m_myMutex;
};

void checkThreads() 
{
	Wallet myWallet;
	std::vector<std::thread> thVec;
	for(int i = 0 ; i < 5 ; i++) {
		thVec.push_back(std::thread(&Wallet::addMoney, &myWallet, 10000));
	}

	for(std::thread& th : thVec) {
		th.join();
	}
	
	myWallet.checkMoney();
}

int main()
{
	for(int i = 0 ; i < 10 ; i++)	
		checkThreads();
	
	return 0;
}
