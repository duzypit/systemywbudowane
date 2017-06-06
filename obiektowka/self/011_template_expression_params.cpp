#include <iostream>
#include <vector>

/*
template class
*/
template <class T, int SIZE> //size is the expr param
class StaticArray{
private:
	T m_array[SIZE]; //the expr param controls the size of the array
public:
	T* getArray();
	T& operator[](int index){
		return m_array[index];
	}
};

/*
example how a func for a class with an expr param is defined outside of the class
*/
template<class T, int SIZE>
T* StaticArray<T, SIZE>::getArray(){
	return m_array;
}

/*
templated member function
*/
// template<typename T, int SIZE>
// void StaticArray<T, SIZE>::fill(T value){
// 	for(int count = 0; count < SIZE; ++count){
// 		this->m_array[count] = (count + value);
		
// 	}
// }

/*
templated member func
*/
// template<typename T, int SIZE>
// void StaticArray<T, int SIZE>::show(int s){
// 	std::cout << "Array values: " << '\n';
// 	for (int count = size-1; count >= 0; --count) {
// 		std::cout << this->m_array[count] << '\n';
// 	}
// }

/*
main
*/
int main(){
	//template expression parameters
	//doesnt substitute for a type
	//instead is replaced by value
	//it can be:
	//value of integral type or enum
	//ptr or ref to class obj
	//ptr or ref to a function
	//ptr or ref to a class member func
	StaticArray<int, 12> intArray;
	for(int count=0; count <12; ++count){
		intArray[count] = count;
	}

	for(int count=11; count >=0; --count){
		std::cout << intArray[count] << " ";
	}
	std::cout << '\n';

	StaticArray<double, 4> doubleArray;

	for(int count=0; count < 4; ++count){
		doubleArray[count] = 4.4+0.1*count;
	}

	for(int count=3; count >=0; --count){
		std::cout << doubleArray[count] << " ";
	}
	std::cout << '\n';

}

