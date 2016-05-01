#ifndef SYMULACJA_IO_H_
#define SYMULACJA_IO_H_
#include "kolejka.h"

//reprezentuje urzadzenia I/O ktore sa zajmowane przez procesy
//uzycie: IO io();
class IO
{
public:
 IO();
 void DodajKolejka(Proces* proces);
 //przydziela proces do urzadzenia
 void Przydziel(Proces* proces);
 //przydziela proces do kolejki urzadzenia
 void PrzydzielKolejka();
 //zwalnia urzadzenie
 void UsunProces();
 void UaktualnijPriorytet(double x);
 //zwraca proces obslugujacy I/O
 Proces* WezProces();
 int WielkoscKolejki();
 bool Wolny();
private:
 int debug_;
 Proces* obecny_proces_;
 KolejkaPrio* kolejka_priorytetowa_;
};

#endif

