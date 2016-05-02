#ifndef SYMULACJA_KOMUNIKATY_H_
#define SYMULACJA_KOMUNIKATY_H_
#include "procesor.h"
#include "io.h"
#include "system_komputerowy.h"


class Komunikaty
{
public:
 static void WypiszStanKolejek(Procesor** procesory, IO** io, SystemKomputerowy* sys);
 static void WypiszParametry();
 static bool komunikaty_;
};

#endif
