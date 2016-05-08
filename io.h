#ifndef SYMULACJA_IO_H_
#define SYMULACJA_IO_H_
#include "kolejka.h"

//reprezentuje urzadzenia I/O ktore sa zajmowane przez procesy
//uzycie: IO io();
//io.DodajKolejka(p);
//io.UaktualnijPriorytet();
//io.PrzydzielKolejka();
//io.UsunProces();
class IO
{
public:
 IO();
 ~IO();
 //dodaje proces do kolejki priorytetowej
 void DodajKolejka(Proces* proces);

 //przydziela proces z kolejki urzadzenia
 void PrzydzielKolejka();

 //zwalnia urzadzenie
 void UsunProces();

 //uaktualnia priorytety procesow  w kolejkach do urzadzen
 void UaktualnijPriorytet();

 //zwraca proces obslugujacy I/O
 Proces* WezProces();
 int WielkoscKolejki();
 bool Wolny();
private:
 Proces* obecny_proces_;
 KolejkaPrio* kolejka_priorytetowa_;
};

#endif

