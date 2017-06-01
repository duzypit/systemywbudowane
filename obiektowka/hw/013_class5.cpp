/*
 * @author Tomasz Piątek
 * @brief Class 5-point Write a class containing variables type of an integer, 
 * string and double with all constructors, destructor, operators... (C++11 recommended - move semantic)
 */
#include <iostream>

class MyClass { 
public:
	MyClass(): i(0), s("nothing"), d(0.0) {
		//default ctor + init list
		//init list run before object exists
		std::cout << "default ctor - init list" << std::endl;
	};

	MyClass(int i1, std::string s1, double d1) {
		//default ctor
		SetI(i1);
		SetS(s1);
		SetD(d1);	
		std::cout << "default ctor" << std::endl;	
	};

	MyClass(const MyClass& rhs){
		//copy ctor
		SetI(rhs.i);
		SetS(rhs.s);
		SetD(rhs.d);
		std::cout << "copy ctor" << std::endl;
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
		std::cout << "mv ctor" << std::endl;

	}

	MyClass& operator=(const MyClass& rhs){
		//copy
		i = rhs.i;
		s = rhs.s;
		d = rhs.d;
		std::cout << "copy assigned" << std::endl;	
		return *this;
	}

	MyClass& operator=(MyClass&& rhs){
		//move
		i = std::move(rhs.i);
		s = std::move(rhs.s);
		d = std::move(rhs.d);
		std::cout << "move assigned" << std::endl;	
		return *this;

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
	lifko.SetS("jump for a beer");
	std::cout << "lifko: " << std::endl;
	lifko.PrintAll();

	MyClass mark(lifko);
	mark.SetI(22);
	mark.SetD(3.145);
	std::cout << "mark: " << std::endl;
	mark.PrintAll();

	MyClass tom = mark;
	std::cout << "mark: " << std::endl;
	tom.PrintAll();

	MyClass jake(11,"test",9.9);
	std::cout << "jake: " << std::endl;
	jake.PrintAll();

}