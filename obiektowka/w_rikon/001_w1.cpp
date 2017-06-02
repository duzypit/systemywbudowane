#include <iostream>

using namespace std;
//using std:cout;

int foo_1(int); //nastepuje skopiowanie wartosci - wymaga duzo pracy
void foo_2(int *); //nastepuje skopiowanie adresu - wymaga mazo pracy
void foo_2a(int *&); //nastepuje referencja adresu - czyli nie kopiuj na stosie
void foo_3(int &); //nastepuje referencja - czyli nie kopiuj na stosie
void foo_3a(const int &);

struct Osoba
{
    int wiek;
    int plec;
};

int main(int arqc, char *argv[])
{
    //Prata - szkoła programowania c++
    //Symfonia C++
    //schilbt - Programowanie C++
    //Thinking in C++
	cout << "C++ jest wydajny" << endl;
	int b=1;
	cout << "Ustawiam b: " << b << endl;
	b=foo_1(b);
	cout << "Ustawiam b przez wskaznik: " << b << endl;
	foo_2(&b);
	cout << "Ustawiam b przez referencje: " << b << endl;
	foo_3(b);

	Osoba os={50,1};
//	os.wiek=50;
//	os.plec=1;
	cout << "Wiek: " << os.wiek << endl;

	Osoba tab_os[2] {{50,1},{14,2}};
	cout << "Wiek drugiej osoby: " << tab_os[1].wiek << endl;

}

int foo_1(int g)
{
	cout << g << endl;
	g=13;
    return g;
}
void foo_2(int *g)
{
	cout << *g << endl;
    *g=40;
}
void foo_3(int &g)
{
	cout << "Reference type: " << g << endl;
	g=77;
}
void Foo(const Osoba *s)
{
    cout << s[1]->wiek << endl;
}

