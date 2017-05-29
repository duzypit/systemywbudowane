/*
 * @author Tomasz Piątek
 * @brief Class 1-point Why it doesn't compile. Fix it....
 */
#include <iostream>

struct MyType {
    MyType(const MyType& t); 
};

int main() {
    MyType a;
}