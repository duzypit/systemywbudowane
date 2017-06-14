/*
 * @author Tomasz Piątek, @rikon
** @brief Class 7-points Write a class to handle a file with all constructors, destructor, operators... (C++11 recommended)
 */
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

/*
enum flags @rikon
*/
enum flags : int {
	O_RONLY = 1 << 1,
	O_WRONLY = 1 << 2,
	O_APPEND = 1 << 4,
	O_WRONLY_APPEND = 1 << 6
};

/*
overloaded oprerator | for enum flags type @rikon
*/
flags operator|(flags lhs, flags rhs){
	
	return static_cast<flags>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

/*
File class
*/
class File {
private:
	
	std::ifstream my_file;
	std::string path;
	flags file_flags;

public:
	File(){}

	File(std::string fname, flags flag) /*: my_file(path, translate_flags(flag))*/{
		//default ctor
		this->path = fname;
		this->file_flags = flag;
		open_file();
	};

	File(const File& rhs)/* : my_file(std::copy(rhs))*/ {
		//copy ctor
		std::cout << "cpy ctor" << std::endl;
		this->path = rhs.path;
		this->file_flags = rhs.file_flags;
		open_file();
	}

	File operator=(const File& rhs){
		//copy assign op @rikon
		if(this != &rhs){
			File tmp  {rhs.path, rhs.file_flags};
			return tmp;
		} else {
			return *this;
		}
	}

	~File(){
		//dstr
		my_file.close();
		std::cout << "Dstr: file closed" << std::endl;
	}

	void open_file(){
		my_file.close();
		my_file.open(this->path, translate_flags(this->file_flags));
	}

	std::ios_base::openmode translate_flags(flags flag){
		switch(flag) {
			case (O_WRONLY_APPEND): return std::ios::app;
			case (O_WRONLY) : return std::ios::out;
			default : return std::ios::in;
		}
	}
	
};


int main() {
    File f {"/tmp/aa", O_WRONLY | O_APPEND}; 

    File f2 { f } ; 

    File f3 = f2; 

    File f4; 
	
    f = f3; 
}