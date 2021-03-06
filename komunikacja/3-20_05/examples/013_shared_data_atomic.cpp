//013 - shared data std::atomic l 26 - zeby dzialal trzeba spelnic warunki jakie sa w 
//komentarzach, klasa nie ma metod, tylko dane (op przypisania i kopiowania) i prymitywy - inty floaty itp.
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>

//c++14 standard:
//Specializations and instantiations of the atomic template shall have a deleted copy constructor, a deleted
//copy assignment operator, and a constexpr value constructor.
//shortly => primities, POD (plain old data)

class Wallet {
public:
	Wallet() : m_money(0) {}
	void addMoney(int val) {
		for(int i = 0 ; i < val; i++)
			m_money++;
	}

	void removeMoney(int val) { 
		m_money -= val; 
	}

	void checkMoney() { std::cout << m_money << std::endl; }

private:
	std::atomic<int> m_money;
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
