#ifndef DOMINANT_CLASS_HPP
#define DOMINANT_CLASS_HPP


class Dominant{
public:
	//ctor
	Dominant(int size = 600, int min = 0, int max = 256) : mt((std::random_device())()) {
		fill_random(size, min, max).map_input().cp_to_vector().sort_vector();


	}
	
	Dominant& print_input(){
		std::cout << "Generated int array: " << std::endl;
		std::cout << "[";

		int last = this->input.size();
		int pos = 0;
		for(auto e: this->input) { 
			pos++;
			std::cout << e;
			if (pos != last) std::cout << ", ";
		}
		std::cout << "]" << std::endl; 
		return *this;
	} 

	Dominant& print_map_values(){
		std::cout << "Generated map array: " << std::endl;
		std::cout << '{';
		int last = this->map_values.size();
		int pos = 0;	
		for(auto& p: this->map_values){
			pos++;
			std::cout<< p.first << ':' << p.second; 
			if (pos != last) std::cout << ", ";
		}
		std::cout << "}" << std::endl;
		return *this;
	} 

	Dominant& print_result(){
		std::pair<int, int> biggest = v.front();
		std::cout << "Dominant: quantity" << std::endl;
		for ( const auto &p : this->v ) {
			if(biggest.second == p.second){
				std::cout << p.first << " : " << p.second << std::endl;
			}
		}

		return *this;
	}

private:
	std::vector<int> input;
	std::mt19937 mt;
	std::map<int, int> map_values;
	std::vector<std::pair<int, int>> v;

	Dominant& fill_random(int size, int min, int max){
		std::uniform_int_distribution<int> dist(min, max);
		for(int i = 0; i < size; i++){
			this->input.push_back(dist(mt));
		}

		return *this;
	}

	Dominant& map_input(){
		for(auto& v: this->input){
			if(this->map_values.find(v) != this->map_values.end()){
				this->map_values.at(v) +=1;
			} else{
				this->map_values[v] = 1;
			}
		}	
		return *this;
	}

	Dominant& cp_to_vector(){
		 copy(this->map_values.begin(), this->map_values.end(), back_inserter(this->v));
		 return *this;
	}

	Dominant& sort_vector(){
		std::sort(this->v.begin(), this->v.end(), 
			[](const std::pair<int, int > &a, const std::pair<int, int > &b) { 
				return b.second < a.second;
			}
		);
		return *this;
	}

};
#endif