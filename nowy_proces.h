#ifndef SYMULACJA_NOWY_PROCES_H_
#define SYMULACJA_NOWY_PROCES_H_

#include "system_komputerowy.h"

//Zdarzenie generowane przez zrodlo TPG
//Umieszcza proces na koncu kolejki K1
//Zaplanowuje nowe zdarzenie NowyProces
class NowyProces
{
public:
 NowyProces(SystemKomputerowy* sys);
 void Wykonaj();
 double czas_;
private:
 SystemKomputerowy* sys_;
};

#endif

