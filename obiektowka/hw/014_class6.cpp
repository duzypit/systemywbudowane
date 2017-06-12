/*
 * @author Tomasz Piątek
** @brief Class 7-points Write a class to handle a file with all constructors, destructor, operators... (C++11 recommended)
 */
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
//#include <fcntl.h>
enum file_flags: int {
	O_RONLY = 1,
	O_WRONLY = 2,
	O_APPEND = 4,
	O_WR_O_APP = 6,
};

class File {
public:
	
	std::ifstream myfile;
	std::string filename;
	file_flags flags;

	File(){}

	File(std::string fname, file_flags flag) /*: myfile(fname, std::ios_base::app)*/{
		//default ctor
		this->filename = fname;
		this->flags = flag;
		std::cout << "Flags: " << flag << std::endl;

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

	int translate_flags(file_flags flag){
		switch(flag) {
			case (O_WRONLY | O_APPEND): return std::ios::app;
			case (O_WRONLY) : return std::ios::out;
			default : return std::ios::in;
		}
	}
	
};


	/*
	overloaded oprerator | for enum file_flags type
	*/
	file_flags operator|(const file_flags& lhs, const file_flags& rhs){
		
		return static_cast<file_flags>(static_cast<char>(lhs) | static_cast<char>(rhs));
	}

int main() {
    File f {"/tmp/aa", O_WRONLY | O_APPEND}; 

    //File f2 { f } ; 

    //File f3 = f2; 

    //File f4; 
	
    //f = f3; 
}