#include <iostream>
#include <vector>

// int max(int x, int y){
// 	return (x > y)? x : y;
// }

//template <typename T, typename T1>
//for class type beter idea is to pass const reference not by value
template <typename T>
T max(T x, T y){
	return (x > y)? x : y;
}
int main(){
	//function templates
	std::cout << "max(3,5): " << max(3,5) << std::endl;
	std::cout << "max(3.0,5.0): " << max(3.0,5.0) << std::endl;

}

