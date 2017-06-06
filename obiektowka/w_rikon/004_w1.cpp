
C& C::setSekunda(int s)
{
  sekunda = (s>=0&&s<60)?s:0;
  return *this;
}
inline int C::getGodzina() const { return godzina; }
inline int C::getMinuta() const { return minuta; }
inline int c::getSekunda() const { return sekunda; }

void C::wyswietl()
{
  cout << ((godzina==0 || godzina==12)? 12:godzina
    minuta << ";" << (sekunda<10 ? "0" : "") <<
}

void P8()
{
  C o, *c1, *c2, **c3;
  cout << "!. obiekt" << endl;
  c.setGodzina(18).setMinuta(30).setSekunda(22);
  c.wyswietl();
  c.setC(20,20,20).wyswietl();
  cout << "2. wskaznik" << endl;
  c1 = new C(5);
  c1->wyswietl();
  cout << "#. tablica dynamiczna obiektow" << endl;
  c2 = new C[10];
  for(int i=0;i<10;i++)
  {
    c2[i].setGodzina(2*i);
  }
  for(int i=0;i<10;i++)
  {
    c2[i].wyswietl();
  }
  cout << "4. tablica dynamiczna wskaznikow na wskaznik" << endl;
  c3 = new C*[10];
  for(int i=0;i<10;i++)
  {
    c3[i]=new C;
  }
  for(int i=0;i<10;i++)
  {
    c3[i]->setGodzina(i); //strzalki "->" uzywamy dla obiektu typu wskaznikowego
  }
  for(int i=0;i<10;i++)
  {
    c3[9]->wyswietl();
  }
  for(int i=0;i<10;i++)
  {
    delete c3[i];
  }
  delete [] c3;
  delete [] c2;
  delete c1;
}
