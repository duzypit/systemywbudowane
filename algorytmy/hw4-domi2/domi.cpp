/*
 * @author Tomasz Piątek
 * @brief determining of dominant
 */

/*
	load input
	count occurences
	print dominant
 */
#include <iostream>
#include <array>
#include <iterator>
#include <random>
#include <algorithm>
#include <map>
/*
fill array with random numbers
*/
template<class Iter>
void fill_random( Iter start, Iter end, int min, int max)
{
    static std::random_device rd;    // you only need to initialize it once
    static std::mt19937 mte(rd());   // this is a relative big object to create

    std::uniform_int_distribution<int> dist(min, max);

    std::generate(start, end, [&] () { return dist(mte); });
}

/*
overloaded << op for array
*/
template<std::size_t N>
std:: ostream& operator<<(std::ostream& os, const std::array<int, N>&arr){
	os << "[";
	for(auto r: arr) { 
		os << r << " ";

	}
	os << "]";
	return os;
}

template<typename Map>
void print_map(Map& m){
	std::cout << '{';
	for(auto& p: m){
		std::cout<< p.first << ':' << p.second << ' ';
	}
	std::cout << "}\n";
}

int main(){

	std::array<int, 300> input_array;
	fill_random(input_array.begin(), input_array.end(), 0, 256);

	std::cout << "Random array values: " << input_array << std::endl;

	std::cout << "Mapped values: " << std::endl;
	std::map<int, int> map_values;

	for(auto& v: input_array){
		if(map_values.find(v) != map_values.end()){
			map_values.at(v) +=1;
		} else{
			map_values[v] = 1;
		}
	}

	print_map(map_values);

//'dump' the map to a vector: vector<pair<K,V>> v(m.begin(), m.end());



// std::sort(object.begin(), object.end(), pred());

// where, pred() is a function object defining the order on objects of myclass. Alternatively, you can define myclass::operator<.

// For example, you can pass a lambda:

// std::sort(object.begin(), object.end(),
//           [] (myclass const& a, myclass const& b) { return a.v < b.v; });

// Or if you're stuck with C++03, the function object approach (v is the member on which you want to sort):

// struct pred {
//     bool operator()(myclass const & a, myclass const & b) const {
//         return a.v < b.v;
//     }
// };



	return 0;
}