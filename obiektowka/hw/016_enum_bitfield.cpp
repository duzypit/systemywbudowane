/*
 * @author Tomasz Piątek
 * @brief C++11 Enum Class as Bitfield
 */
#include <iostream>
#include <bitset>

enum flags : int {
	O_RONLY = 1 << 1,
	O_WRONLY = 1 << 2,
	O_APPEND = 1 << 4,
	O_WRONLY_APPEND = 1 << 6

};

/*
overloaded oprerator | for enum flags type
*/

flags operator |(flags lhs, flags rhs){
	
	return static_cast<flags>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

flags& operator |= (flags& lhs, flags rhs) { 
	return (flags &)(((int &)lhs) |= ((int)rhs)); 
}

flags& operator &= (flags &a, flags b) { 
	return (flags &)(((int &)a) &= ((int)b)); 
} 

flags operator ~ (flags a) { 
	return flags(~((int)a)); 
} 

//inline flags operator | (flags a, flags b) { return flags(((int)a) | ((int)b)); } 
//inline flags &operator |= (flags &a, flags b) { return (flags &)(((int &)a) |= ((int)b)); }
// inline flags operator & (flags a, flags b) { return flags(((int)a) & ((int)b)); } 
// inline flags &operator &= (flags &a, flags b) { return (flags &)(((int &)a) &= ((int)b)); } 
// inline flags operator ~ (flags a) { return flags(~((int)a)); } 
// inline flags operator ^ (flags a, flags b) { return flags(((int)a) ^ ((int)b)); } 
// inline flags &operator ^= (flags &a, flags b) { return (flags &)(((int &)a) ^= ((int)b)); } 

int main(){

	//int i = 0;
	//std::cout<<std::bitset<8>(i)<<std::endl;
	//flags flag = O_WRONLY;
	//flag |= O_APPEND;
	flags flag = O_WRONLY | O_APPEND;
	//flag |= flags::O_APPEND;
	// std::cout<<std::bitset<8>(flag)<<std::endl;


	//clear the ONE flag 
    //mask &= ~Test::One;
	flag &= ~O_APPEND;
    //check the THREE flag 
    //bool threeIsSet = (mask & Test::Three) > 0;

	std::cout<<std::bitset<8>(flag)<<std::endl;

	return 0;
}
