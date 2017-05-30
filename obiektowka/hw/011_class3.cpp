/*
 * @author Tomasz Piątek
 * @brief Class 1-point Add operatro= to the class
 */
#include <iostream>

struct MyType {
    MyType( const MyType& rhs);
};

MyType getType() { return MyType{};}

int main() {
    MyType b; 
    MyType a {b};
    MyType c { getType(); }
};