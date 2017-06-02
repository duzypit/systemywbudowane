#include <array>

using namespace std;

void functionEx_r(array<string, NN> &a);

struct A {
  int i;
  A(int i,int 5); //???

  private:
    int k;
}

class C {

    C& setC(int,int,int);
    C& setGodzina(int);
    C& setMinuta(int);
    C& setSekunda(int);

    int getGodzina() const;
    int getMinuta() const;
    int getSekunda() const;

    void wyswietl();

  private:
    int godzina;
    int minuta;
    int sekunda;
}

int main()
{
  array<A,NN> tabl; //A-typ (np. string, int); NN-ilosc obiektow

  C* c; //inicjalizacja klasy C
  c=new int; //inicjalizacja pamieci
  c.godzina=10;
  c.getGodzina();

  C* t;
  t=new int[10]; //inicjalizacja klasy C - 10 sztuk.
  cout << t[5].getGodzina() << endl; //wyswietlenie godziny z 5 elementu

  //deklaracja tablicy wskaznikow (czyli [*adres tablicy]->[*adres obiektu]->[C obiekt])
  C** c;

  //iteracja przez tablice
  for(int i=0;i<tabl.size(); i++)
  {
    cout << tabl[i].get_f() << "\t";
  }

  //nowy styl iteracji
  for(auto t: tabl) //kompilator sam znajdzie typ dla zmiennej t
  {
    cout << t.get_f() << "\t";
  }
}
