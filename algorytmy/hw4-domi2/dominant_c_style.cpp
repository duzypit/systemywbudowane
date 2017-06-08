/*
 * @author Tomasz Piątek
 * @brief determining of dominant
 */

/*
gen input
count occurences
print domi
*/

#include <iostream>
#include <array>
#include <iterator>
#include <random>
#include <algorithm>
#include <map>


/*
andom numbers generator
*/
template<class Iter>
void fill_random( Iter start, Iter end, int min, int max)
{
    static std::random_device rd;    // you only need to initialize it once
    static std::mt19937 mte(rd());   // this is a relative big object to create

    std::uniform_int_distribution<int> dist(min, max);

    std::generate(start, end, 
    	[&] () { 
    		return dist(mte); 
    	}
    );
}

/*
overloaded << op for array
*/
template<std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<int, N>&arr){
	os << "[";
	int last = arr.size();
	int pos = 0;
	for(auto r: arr) { 
		pos++;
		os << r;
		if (pos != last) os << ", ";
	}
	os << "]";
	return os;
}

/*
tmplated function printing map -- debug
*/
template<typename Map>
void print_map(Map& m){
	std::cout << '{';
	int last = m.size();
	int pos = 0;	
	for(auto& p: m){
		pos++;
		std::cout<< p.first << ':' << p.second; 
		if (pos != last) std::cout << ", ";
	}
	std::cout << "}\n";
}



int main(){
	//gen input
	std::array<int, 600> input;
	fill_random(input.begin(), input.end(), 0, 256);

	//debug - show values
	std::cout << "Random array values: " << std::endl; 
	std::cout << input << "\n\n";


	//map input by keys
	std::map<int, int> map_values;

	for(auto& v: input){
		if(map_values.find(v) != map_values.end()){
			map_values.at(v) +=1;
		} else{
			map_values[v] = 1;
		}
	}

	//debug show mapped values
	std::cout << "Mapped values: " << std::endl;
	print_map(map_values);

	//cpy values to vector pairs
	std::vector<std::pair<int, int>> v(map_values.begin(), map_values.end());

	//sort vector 
	std::sort(v.begin(), v.end(), 
		[](const std::pair<int, int > &a, const std::pair<int, int > &b) { 
			return b.second < a.second;
		}
	);

	//show domi
	std::pair<int, int> biggest = v.front();
	std::cout << "Dominant: quantity" << std::endl;
	for ( const auto &p : v ) {
		if(biggest.second == p.second){
			std::cout << p.first << " : " << p.second << std::endl;
		}
	}

    std::cout << std::endl;

	return 0;
}