#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
	const std::vector<std::string> args{argv + 1, argv + argc};
	

	
	if(args.front() == "-h"){
		std::cout << "print help" << std::endl;
	}

	if(args.front() == "-v"){
		std::cout << "verbose" << std::endl;
		for(auto a : args){
			std::cout << a << std::endl;
		}
	}
	if(std::size_t found = args.front().find("-f=")){
		//std::string val = args.frong().su
		std::string::size_type p = args.front().find('=');
		std::string::size_type k = args.front().size();
		std::string val = args.front().substr(p, k);
		std::cout << std::pow(std::atoi(val)) << std::endl;
	}
	
	//-h disp help  
	//-v print all args passed
	//-f calc pow
//przepisz z uzyciem biblioteki cxxopts 
	 
	return 0;
}