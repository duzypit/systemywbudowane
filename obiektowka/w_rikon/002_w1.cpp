#include <iostream>
#include <array>

using namespace std;

const double pi = 3.1415;

struct Osoba
{
    public:
        int get_plec() { return plec; }
    private:
        int wiek;
        int plec;
};

class Osoba {
    int wiek;
    int plec;
public:
    Osoba() {} //konstruktor
    int get_plec() { return plec; }
    int get_wiek() { return wiek; }
};

