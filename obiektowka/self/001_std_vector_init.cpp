#include <iostream>
#include <vector>


int main(){
	std::vector<int> array; //no need to specify length
	std::vector<int> array2 = {9,3,5,6,7}; //use initilaizer list to init
	std::vector<int> array3 {0,3,4,5,7,8,9,3,4}; //use uniform init to init array (c++11 onward)

	array[6] = 2; //no bounds chcecking, acces via [] operator
	array.at(7) = 3; //bounds chcecking
	//in either case, if you request an element that is off the end of the array, the vector will not auto resize

//c++11  assign values using initializer list
	array = {0,1,2,3,4}; //ok, array length is now 5
	array = {9,8,7}; // ok, array length is now 3



}

