/*
 * @author Tomasz Piątek
 * @brief Class 7-points Write a class to handle a file with all constructors, destructor, operators... (C++11 recommended)
 */
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
//#include <fcntl.h>

class File {
public:
	//File(){}

	File(std::string filename = "/tmp/aa") : myfile(filename, std::ios_base::app){
		//default ctor
		std::cout << "default ctor" << std::endl;
	};

	File(const File& rhs)/* : myfile(std::copy(rhs))*/ {
		//copy ctor
		std::cout << "cpy ctor" << std::endl;

	}

	File(File&& rhs)/* : myfile(std::move(rhs))*/{
		//mv ctor
		std::cout << "mv ctor" << std::endl;
	}

	File& operator=(const File& rhs){
		//copy assign op
		std::cout << "cpy assign op" << std::endl;
		return *this;
	}

	File& operator=(File&& rhs){
		//mv assign op
		std::cout << "mv assign op" << std::endl;
		return *this;
	}

	~File(){
		//dstr
		myfile.close();
		std::cout << "Dstr: file closed" << std::endl;
	}

private:
	std::ifstream myfile;

};

int main() {
    File f {"/tmp/aa"}; 

    File f2 { f } ; 

    File f3 = f2; 

    File f4; 
	
    f = f3; 
}