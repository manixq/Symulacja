#ifndef SYMULACJA_NOWY_PROCES_H_
#define SYMULACJA_NOWY_PROCES_H_

#include "system_komputerowy.h"

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

