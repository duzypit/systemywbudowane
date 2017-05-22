#include <iostream>
#include <thread>

class Buff
{
public:
	Buff(int elem) : m_index(0), m_elem_num(elem) {
		m_buff = new int[elem];
	}

	~Buff(){ delete [] m_buff; }

	int push_front(int val) {
		int ret =-1;

		if(m_index < m_elem_num) {
			m_buff[m_index++] = val;
			ret =  0;
		}

		return ret;
	}

	int pop_front() {
		int ret = -1;
		
		if(m_index > 0)
			ret = m_buff[--m_index];

		return ret;
	}

private:
	int* m_buff;
	int m_elem_num;
	int m_index;
};

void producer(Buff& buf)
{
	int result;
	while(1) {
		for(int i = 0 ; i < 20 ; i++) {
				result = buf.push_front(i);
				std::cout << "producer : " << i << " result = " << result << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void consumer(Buff& buf)
{
	int temp;
	while(1) {
		temp = buf.pop_front();
		if(temp != -1)
			std::cout << "consumer : " << temp << std::endl;
	}
}

int main() 
{
	Buff myBuff{10};
	std::thread th1{producer, std::ref(myBuff)};
	std::thread th2{consumer, std::ref(myBuff)};

	th1.join();
	th2.join();

	return 0;
}
