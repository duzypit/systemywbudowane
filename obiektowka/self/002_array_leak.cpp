#include <iostream>
#include <vector>

void doSomething(bool earlyExit); //example of memory leak

int main(){

	std::cout << "We have leak over here ;)\n";
	doSomething(1);

}

void doSomething(bool earlyExit){
	int *array = new int[5] {2,3,4,5,6};

	if(earlyExit){
		return;
		//memory leak
	}

	//do stuff here

	delete[] array; //never called
}
