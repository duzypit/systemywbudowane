#include <iostream>
#include <vector>
#include <array>

//http://www.learncpp.com/cpp-tutorial/132-function-template-instances/

//C++ does not compile the template func dicrectly, instead at compile time, it replaces the template function & the template type parameters with actual types.
//its called a function template instance.
//all operators or function calls that you use must be defined in class, template, etc..

/*
	template function
*/
template <typename T>
const T& max(T& x, T& y){
	return (x > y)? x : y;
}

/*
	class used with templated func
*/
class Cents{
private:
	int m_cents;
public:
	Cents(int cents) : m_cents(cents) {}

	/* 
		comment this op & try to compile 
	*/
	friend bool operator>(const Cents& c1, const Cents& c2){
		return (c1.m_cents > c2.m_cents);
	}

	friend std::ostream& operator<< (std::ostream& stream, const Cents& cents){
		stream << cents.m_cents << " cents ";
		return stream;
	}

	Cents& operator+=(const Cents& cents){
		this -> m_cents += cents.m_cents;
		return *this;
	}

	Cents& operator/=(const int& value){
		this -> m_cents /= value;
		return *this;
	}

	void show_cents(){
		std::cout << "Bigger cents: " << m_cents << std::endl;
	}
};

template <typename T, std::size_t SIZE>
T average(std::array<T, SIZE> arr){
	T sum = 0;
	for(auto e: arr){
		sum += e;
	}

	sum /= arr.size();
	return sum;
}

int main(){
	//function templates -operators, function calls, function templates
	std::cout << "Comment operator> inside Cents class first & see what you get ;)" << std::endl;
	Cents nickle(5);
	Cents dime(10);

	Cents bigger = max(nickle, dime);
	bigger.show_cents();

	std::array<int, 5> a = {5,3,2,1,4};
	std::cout << "array average: " << average(a) << std::endl;

	std::array<Cents, 3> c {Cents(5), Cents(10), Cents(15)};
	std::cout << "Cents array average: " << average(c) << std::endl;

	return 0;
}

