/*
 * @author Tomasz Piątek
 * @brief Class 5-point Write a class containing variables type of an integer, 
 * string and double with all constructors, destructor, operators... (C++11 recommended - move semantic)
 */
#include <iostream>

class MyClass { 
public:
	MyClass(): i(0), s("nothing"), d(0.0) {
		//default ctor
	};

	MyClass(const MyClass& rhs){
		//copy ctor
		SetI(rhs.i);
		SetS(rhs.s);
		SetD(rhs.d);
	};

	MyClass(MyClass&& rhs){
		//mv ctor
		//The move constructor is much faster than a copy constructor because it doesn’t allocate memory nor does it copy memory buffers.
		SetI(rhs.i);
		SetS(rhs.s);
		SetD(rhs.d);
		rhs.i = 0;
		rhs.s = "none";
		rhs.d = 0.0;

	}

	MyClass& operator=(const MyClass& rhs){
		//mv op assign

	}

	~MyClass(){
		//dstr
		//...smt happened here
		std::cout << "Destruction done." << std::endl;
	}

	int GetI (){ return this->i;}
	std::string GetS () {return this->s;}
	double GetD () {return this->d;}

	void SetI(int x){ this->i = x;}
	void SetS(std::string y){ this->s = y;}
	void SetD(double z){ this->d = z;}

	void PrintAll(){
		std::cout << "i: " << this->GetI() << ", s: " << this->GetS() << ", d: " << this->GetD() << std::endl;
	}

private:
	int i;
	std::string s;
	double d;	

};

int main() { 
	MyClass lifko;
	lifko.SetS("skocz po piwko");
	lifko.PrintAll();
}