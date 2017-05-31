/*
 * @author Tomasz Piątek
 * @brief Class 1-point Why it doesn't compile. Fix it....
 */
#include <iostream>

struct MyType {
	MyType() {};
    MyType(const MyType& rhs) {}; 
    MyType(MyType& rhs) {};
};

MyType getType() { return MyType{};}

int main() {
    MyType b; 
    MyType a {b};
    MyType c {getType()};
    std::cout << "compiled ;)" << std::endl;
}