#include <stdio.h>
#include <thread>
#include <mutex>
#include <condition_variable>

static const int BUFF_SIZE  = 10;

class Buff
{
public:
	Buff(int elem) : m_index(0), m_elem_num(elem) {
		m_buff = new int[elem];
	}

	~Buff(){ delete [] m_buff; }

	int push_front(int val) {
		int ret =-1;

		std::unique_lock<std::mutex> lk(m_mutex);
			if(m_index < m_elem_num) {
				m_buff[m_index++] = val;
				ret =  0;
			}

			m_cond_var.notify_one();

		return ret;
	}

	int pop_front() {
		int ret = -1;
		
		std::unique_lock<std::mutex> lk(m_mutex);
			if(m_index == 0) {			
				printf("pop_front() before wait...\n");
				m_cond_var.wait(lk);
				printf("pop_front() after wait...\n");
			}
			ret = m_buff[--m_index];

		return ret;
	}

private:
	int* m_buff;
	int m_elem_num;
	int m_index;
	std::mutex m_mutex;
	std::condition_variable m_cond_var;
};

void producer(Buff& buf)
{
	int result;
	while(1) {
		std::this_thread::sleep_for(std::chrono::seconds(5));
		for(int i = 10 ; i < 10 + BUFF_SIZE ; i++) {
				result = buf.push_front(i);
				printf("producer : %d result %d\n", i, result);
		}
	}
}

void consumer(Buff& buf)
{
	int temp;
	while(1) {
		temp = buf.pop_front();
		//if(temp != -1)
			printf("consumer : %d\n", temp);
		//no busy wait!!!!
	}
	
}

int main() 
{
	Buff myBuff{BUFF_SIZE};
	std::thread th1{producer, std::ref(myBuff)};
	std::thread th2{consumer, std::ref(myBuff)};

	th1.join();
	th2.join();

	return 0;
}
