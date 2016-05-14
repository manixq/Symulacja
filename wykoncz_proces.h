#ifndef SYMULACJA_WYKONCZ_PROCES_H_
#define SYMULACJA_WYKONCZ_PROCES_H_

class Procesor;

//Zdarzenie Oznacza bezpowrotne usuniecie procesu
//Wykonuje sie gdy czas TPW procesu wynosi 0
class WykonczProces
{
public:
 WykonczProces(Procesor** p);
 
 //bezpowrotnie zwolni proces z systemu
 //jako argument i podajemy numer procesora
 void Wykonaj(int i, int iteracje, double czas_konca);
 double czas_[2];
private:
 Procesor** p_;
};
#endif
