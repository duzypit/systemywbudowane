/*
 * @author Tomasz Piątek
 * @brief Class 1-point Add operator= to the class
 */
#include <iostream>
#include <algorithm>
#include <utility>


struct MyType {
	MyType() {};
    MyType(const MyType& rhs) {};
    MyType(MyType& rhs) {};

	MyType& operator=(MyType rhs) {
		if (this != &rhs) {
			//swap(rhs);
			std::cout << "operator= called" << std::endl;
		}

		return *this;
	}    
};



MyType getType() { return MyType{};}

int main() {
    MyType b; 
    MyType a {b};
    MyType c {getType()};
    MyType d;
    d = c;
};