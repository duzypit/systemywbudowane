#include <iostream>
#include <thread>
#include <vector>

class Wallet {
public:
	Wallet() : m_money(0) {}
	void addMoney(int val) {
		for(int i = 0 ; i < val; i++)
			m_money++;
	}

	void removeMoney(int val) { m_money -= val; };
	int checkMoney() { std::cout << m_money << std::endl; }

private:
	int m_money;
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
