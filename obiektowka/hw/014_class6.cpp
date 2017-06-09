/*
 * @author Tomasz Piątek
** @brief Class 7-points Write a class to handle a file with all constructors, destructor, operators... (C++11 recommended)
 */
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
//#include <fcntl.h>

class File {
public:
	//File(){}

	File(std::string fname = "/tmp/aa") : myfile(fname, std::ios_base::app){
		//default ctor
		this->filename = fname;
		std::cout << "default ctor" << std::endl;
	};

	File(const File& rhs)/* : myfile(std::copy(rhs))*/ {
		//copy ctor
		std::cout << "cpy ctor" << std::endl;

	}

	File& operator=(const File& rhs){
		//copy assign op
		std::cout << "cpy assign op" << std::endl;
		if(this != &rhs){

		}
		return *this;
	}

	~File(){
		//dstr
		myfile.close();
		std::cout << "Dstr: file closed" << std::endl;
	}

	std::ifstream myfile;
	std::string filename;

};

int main() {
    File f {"/tmp/aa"}; 

    //File f2 { f } ; 

    //File f3 = f2; 

    File f4; 
	
    //f = f3; 
}