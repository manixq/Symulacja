#ifndef SYMULACJA_KOMUNIKATY_H_
#define SYMULACJA_KOMUNIKATY_H_
#include "procesor.h"
#include "io.h"
#include "system_komputerowy.h"
#include "fstream"
extern std::ofstream kDoPliku;

class Komunikaty
{
public:
 static void WypiszDowolne(char* a);
 static void WypiszStanKolejek(Procesor** procesory, IO** io, SystemKomputerowy* sys);
 static void WypiszParametry();
};

#endif
