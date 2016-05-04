#ifndef SYMULACJA_NOWY_PROCES_H_
#define SYMULACJA_NOWY_PROCES_H_

#include "system_komputerowy.h"

//Zdarzenie generowane przez zrodlo TPG
//Umieszcza proces na koncu kolejki K1
//Zaplanowuje nowe zdarzenie NowyProces
//w konstruktorze podajemy wskaznik na system
//w systemie znajduja sie kolejki 
class NowyProces
{
public:
 NowyProces(SystemKomputerowy* sys);

 //tworzy nowy proces id odaje  go do kolejki
 void Wykonaj();
 double czas_;
private:
 SystemKomputerowy* sys_;
};

#endif

