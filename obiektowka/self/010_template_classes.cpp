#include <iostream>


/* 
templated array class
*/
template <class T>
class Array {
private:
	int m_length;
	T *m_data;
public:
	Array() {
		m_length = 0;
		m_data = nullptr;
	}

	Array(int length){
		m_data = new T[length];
		m_length = length;
	}

	~Array(){
		delete[] m_data;
	}

	void Erase(){
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
	}

	T& operator[](int index){
		return m_data[index];
	}

	int getLength();
	void fill(T value);
	void show();

};

/*
templated member function
*/
template<typename T>
int Array<T>::getLength() {return m_length;}

/*
templated member function
*/
template<typename T>
void Array<T>::fill(T value){
	for(int count = 0; count < this->getLength(); ++count){
		this->m_data[count] = (count + value);
		
	}
}

/*
templated member func
*/
template<typename T>
void Array<T>::show(){
	std::cout << "Array values: " << '\n';
	for (int count = this->getLength()-1; count >= 0; --count) {
		std::cout << this->m_data[count] << '\n';
	}
}

/*
main
*/
int main(){
	Array<int> intArray(12);
	Array<double> doubleArray(12);

	intArray.fill(1);
	doubleArray.fill(1.5);

	intArray.show();
	doubleArray.show();
}

