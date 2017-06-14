//011 - smart mutex - smart pointer, RAII (przydzielanie pamieci w konstruktorze lub 
//destruktorze), std::lock_guard znika jak wychodzimy ze scope - linia 18
#include <iostream> //std::cout
#include <thread> //std::thread
#include <vector> //std::vector
#include <mutex> //std::mutex, std::lock_guard

class Wallet {
public:
	Wallet() : m_money(0) {}


//m_myMutex is member of class Wallet, which is what is used to protect m_money. lock(m_myMutex) simply engages 
//the lock and the exit from the block causes its destruction, dis-engaging the lock. guard 
//is just a convenient way to engage and dis-engage the lock.
	void addMoney(int val) {
		std::lock_guard<std::mutex> lock(m_myMutex);
			for(int i = 0 ; i < val; i++)
				m_money++;
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
