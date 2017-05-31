/*
 * @author Tomasz Piątek
 * @brief Class 1-point When copy ctor, operator= is called?
 */
#include <iostream>

struct MyType { 
    MyType(const MyType& rhs); 
    MyType& operator=(/*next, copy ctor called*/const MyType& rhs); 
};

int main() { 
    MyType a,b; 
    /*copy ctor called below*/
    MyType c = a;
    /*next, operator= called, copy ctor*/
    b = a;
}