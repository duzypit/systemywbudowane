#include <iostream>
#include <array>

using namespace std;

const double pi = 3.1415;
//różnica mędzy strukturą i klasą jest taka, że w klasie wszystko jest prywatne

/*struct Osoba {
public
    int get_plec() {return plec;}
    int plec;
rivate:
    int wiek;
}
*/
//enkapsulacja zadanie obiektowości nr 1
//obiektowosc to 3 elementy: Paradygmat obiektowy: enkapsulacja, dziedziczenie, polimorfizm 
class Osoba {
    int wiek;
    int plec;
public:
    //konstruktor nazwa jak klasa, nie posiada zwracanej wartosci
//    Osoba() {wiek =0; plec = 0;}
//argumenty domyślne
    Osoba(int w = 0, int p = 0) {wiek = w; plec = p;}
    //inline sugestia w standardzie - jesli niski poziom opytmalizacji jest ustawiony
    //const w ciele tej funkcji juz nie mozna zmienic stanu danego obiektu
    inline int get_plec() const { /*plec = 777;*/ return plec;}
    void set_plec(int i) {plec = i;}
    int get_wiek() {return wiek;}

};
void function_x(Array<string,nn>)


int main(void){
    //struct Osoba s(10,1)   ;
    Osoba s[2];
    Osoba *ptr_s;
    cout << "plec: " <<  "\t" << s[0].get_plec() << " wiek: " <<  "\t" << s[0].get_wiek() <<endl;
    ptr_s = &s[0];
    cout << ptr_s -> get_wiek() << endl;
    std::array<A, 2>
    return 0;
}
