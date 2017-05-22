#include <stdio.h>
#include <thread>
#include <mutex>
#include <vector>
#include <condition_variable>

static const int THREAD_NUM = 5;
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

			if(m_index == m_elem_num)
				m_cv_free_slots.wait(lk);			

			m_buff[m_index++] = val;
			ret =  0;
			
			m_cv_data_ready.notify_one();

		return ret;
	}

	int pop_front() {
		int ret = -1;
		
		std::unique_lock<std::mutex> lk(m_mutex);
			
			if(m_index == 0) {			
				printf("consumer id before wait : %lu m_index = %d\n", std::this_thread::get_id(),  m_index);
				m_cv_data_ready.wait(lk);
				printf("consumer id after : %lu m_index = %d\n", std::this_thread::get_id(),  m_index);
			}
			
			ret = m_buff[--m_index];

			m_cv_free_slots.notify_one();

		return ret;
	}

private:
	int* m_buff;
	int m_elem_num;
	int m_index;
	std::mutex m_mutex;
	std::condition_variable m_cv_free_slots;
	std::condition_variable m_cv_data_ready;
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
		printf("consumer id : %lu | read %d\n", std::this_thread::get_id(), temp);
	}
}

int main() 
{
	Buff myBuff{BUFF_SIZE};
	std::thread th1{producer, std::ref(myBuff)};
	std::vector<std::thread> vec_th;
	for(int i = 0 ; i < THREAD_NUM ; i++)
		vec_th.push_back(std::thread(consumer, std::ref(myBuff)));
		
	th1.join();
	for(std::thread& th : vec_th)
		th.join();

	return 0;
}
