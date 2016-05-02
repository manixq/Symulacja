#ifndef SYMULACJA_WYKONCZ_PROCES_H_
#define SYMULACJA_WYKONCZ_PROCES_H_

class Procesor;
//Zdarzenie Oznacza bezpowrotne usuniecie procesu
//Wykonuje sie gdy czas TPW procesu wynosi 0
class WykonczProces
{
public:
 WykonczProces(Procesor** p);
 void Wykonaj(int i);
 double czas_[2];
private:
 Procesor** p_;
};
#endif
