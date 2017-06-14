//010 - std::mutex
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

class Wallet {
public:
	Wallet() : m_money(0) {}
	void addMoney(int val) {
		m_myMutex.lock();
			for(int i = 0 ; i < val; i++)
				m_money++;
		m_myMutex.unlock();
	}

	void removeMoney(int val) { 
		m_myMutex.lock();
			m_money -= val; 
		m_myMutex.unlock();
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
		//std::thread(funkcja, obiekt, arg funkcji)
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
