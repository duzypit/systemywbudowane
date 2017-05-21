#include <iostream>
#include <array>
#include <iterator>
#include <random>
#include <algorithm>

template< class Iter >


void fill_with_random_int_values( Iter start, Iter end, int min, int max)
{
    static std::random_device rd;    // you only need to initialize it once
    static std::mt19937 mte(rd());   // this is a relative big object to create

    std::uniform_int_distribution<int> dist(min, max);

    std::generate(start, end, [&] () { return dist(mte); });
}

std:: ostream& operator<<(std::ostream& os, const std::array<int, 10>&arr){
	os << "[";
	for(auto r: arr) os << r << ",";
	os << "]";
	return os;
}

int main()
{
    std::array<int, 10> a;

    fill_with_random_int_values(a.begin(), a.end(), 0, 1000);

    for ( int i : a ) std::cout << i << ' ';
    std::cout << '\n';
	
	int max = 0;
	for (int i: a ){
		if(i > max) {
			max = i;
		}
	}

	std::cout << "max " << max << std::endl;
	std::cout << a << std::endl;
}