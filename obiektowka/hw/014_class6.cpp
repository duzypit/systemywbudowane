/*
 * @author Tomasz Piątek
 * @brief Class 7-points Write a class to handle a file with all constructors, destructor, operators... (C++11 recommended)
 */
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <fcntl.h>

class File {
public:
	File(std::string filename) : myfile(filename){
		//default ctor
		if()
	};

	// File(const File& rhs){
	// 	//copy ctor
	// }

	// File(File&& rhs) : myfile(std::move(rhs)){
	// 	//mv ctor

	// }

	// File& operator=(const File& rhs){
	// 	//copy assign op
	// }

	// File& operator=(File&& rhs){
	// 	//mv assign op

	// }

	~File(){
		//dstr
		myfile.close();
		std::cout << "Dstr: file closed" << std::endl;
	}

private:
	std::ifstream myfile;

};

int main() {
    File f {"/tmp/aa", O_WRONLY | O_APPEND}; 

    //File f2 { f } ; 

    //File f3 = f2; 

    //File f4; 

    //f = f3; 
}