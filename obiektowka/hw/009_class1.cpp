/*
 * @author Tomasz Piątek
 * @brief Class 1-point Why it doesn't compile. Fix it....
 */
#include <iostream>

struct MyType {
	MyType() = default;
	//cpy ctor
    MyType(const MyType&) = default;
};

int main() {
    MyType a;
}