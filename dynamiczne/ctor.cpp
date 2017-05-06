/*#include <iostream>

using namespace std;

class A{
public:
	A(char x){cout << _x << "()" << endl;};
	~A(){cout <<  _x << "~()" << endl;}
private:
	char _x;
};

int main(void){

	A a('a');
	A b('b');

	{
		A c("c");
	}

	A d("d");	

	return 0;
}*/
/*przykład scope guard*/
class scope_guard{
public:
	scope_guard(mutex_m){
		m.lock();
	}

	~scope_guard(){
		m.unlock();
	}
}

std::shared_ptr //współdzielony (liczy ref); auto sp = std::make_shared (new A); sp2(sp); - wszystkie beda wiedziały ile jest fef, rpzy wyjsciu z zakresu zmiennej zmniejsza sie counter ref jak dojedzie do 0 usuwa
std::unique_ptr //unikalny
std::weak_ptr //zwykły ptrd

#include <vector> // automatycznie się rozszerza
std::vector<int> v;
v[0] = 5;

