/*
 * @author Tomasz Piątek
 * @brief Class 1-point When copy ctor, operator= is called?
 */
#include <iostream>

struct MyType { 
    MyType(const MyType& rhs); 
    MyType& operator=(const MyType& rhs); 
};

int main() { 
    MyType a,b; 
    MyType c = a;
    b = a;
}