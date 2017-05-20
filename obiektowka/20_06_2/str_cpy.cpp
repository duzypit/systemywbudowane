#include <iostream>


using namespace std;

int main(void){

	char* z = new char [20];
	z = "aaaaaaaaaa";
	char* nz = new char [20];

	std::strcpy(z, nz);
	cout << "nz= " << nz << endl;

	string S = "BBBBBBBBBB";
	string cs(s);

	cout << "cs= " << sc << endl;


	return 0;
}