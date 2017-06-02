int *p = new int;


------

#include <new>

char buffer[300];
int *p = new (buffer) int;
char *buffer = new char[300]

------

class B2
{
  public:
    B2() = default;
}

------

volatype - co to było?

------

class A {}
A a;
A a1=a; //Konstruktor kopiujacy

------

B2 b;
b=3.14;

a jak użyję w funkcji explicit to nie będzie działało przypisanie b=3.14

------

namespace NS1
{
  int a=13;
  int b;
  void f() {}
}
namespace NS1
{
  int c=1;
  struct S { int c; };
}

std::cout << NS1::a << endl;
std::cout << NS1::b << endl;
std::cout << NS1::c << endl;

namespace sie lacza - jezeli mam 2 namespace o takiej samej nazwie, to one sie lacza automatycznie

------

namespace NS2
{
  int a=2;
  namespace NS3
  {
    int a=3;
  }
}

std::cout << NS2::NS3::a << endl;

namespace nie tworzy obiektu

------

Aliasy dla namespace

namespace Na234 = NS2::NS3::NS4;

------

namespace dostepny tylko w funkcji

void P18()
{
  using namespace std;
  using std::string; //a to co???

  cout << A2::get_i() << endl;
}

------

Typy statyczne

int licznik=0;
class A
{
  A() { +++licznik; }

  static int licznik; //lepiej uzywac zmiennej static, zamiast tworzyc zmienna globalna przed klasa, bo teraz zmienna licznik nalezy do klasy A
}

------

funkcje statyczne


