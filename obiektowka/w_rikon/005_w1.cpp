class Ext
{
  //domyslnie jest private:
  int a, b;
  class Nest1
  {
    public:
      Nest1(int C, int D) : c(C), d(D) {}
      void dis();
    private:
      int c, d;
  };

  public:
    Ext(int A, int B) : a(A), b(B) {}
    Nest1 set_n1() //tworze funkcje na podstawie klasy
    {
      return Nest1(100+a, 200+b); //zwracam klase z parametrami
    }
    void disp_nl()
    {
      set_a1().dis();
    }


}

void P11()
{
  Ext::Nest2 my_n2("atrybut");

class X; //deklaracja zapowiadajaca - kompilator leci linia po linii i w funkcji Y jak znajdzie odwołanie do klasy X nie będzie wiedział o co chodzi. Dzieki tej deklaracji poinformujemy go ze w kodzie wystapi klasa X

class Y
{
  friend void function1(Y &);

  public:
    Y(int A):a(A) {}
    void pokaz(X *pX);
    int get_a()
    {
      return a;
    }

  private:
    int a;
}
void function1(Y &y)
{
  cout << y.a << endl; //w klasie Y uzyty zostal "friend" dlatego moge sie dobrac do zmiennej ktora jest prywatna
}


class X
{
  friend void Y::pokaz(X*);
  // mozna tez zaprzyjaznic cala klase, czyli: friend class Y

  public:
    X(int A):a(A) {}
    int get_a()
    {
      return a;
    }

  private:
    int a;
}
void Y::pokaz(X* pX)
{
  cout << pX->a << "\t" << a << endl; //jest "friend" więc jest dostęp
}


