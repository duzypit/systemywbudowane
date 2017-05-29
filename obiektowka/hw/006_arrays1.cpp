/*
 * @author Tomasz Piątek
 * @brief Arrays 3-pkt Write a program to concatenate two tables.
 */

#include <iostream>
#include <array>
#include <algorithm>

int main(){
	std::array<int, 3> a1 {1,2,3};
	std::array<int, 3> a2 {4,5,6};
	std::merge(std::begin(a), std::end(a), std::begin(b),std::end(b));

	return 0;
}
