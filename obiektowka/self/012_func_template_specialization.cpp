#include <iostream>

/*
templated class
*/
template <class T>
class Storage {
private:
	T m_value;
public:
	Storage(T value){
		m_value = value;
	}
	~Storage(){}
	void print(){
		std::cout << m_value << '\n';
	}
};
/*
function template spec
called full or explict function template spec
*/
template<>
void Storage<double>::print(){
	std::cout << std::scientific << m_value << '\n';
}

/*
func template spec for std::string
*/
template<>
Storage<char*>::Storage(char* value){
	m_value = std::string(value);
}

int main(){
	//define same storage units
	Storage<int> nValue(5);
	Storage<double> dValue(6.7);

	nValue.print();
	dValue.print();

	char *string =new char[40];
	std::cout << "enter a string: ";
	std::cin >> string;

	Storage<char*> value(string);

	value.print();

}

