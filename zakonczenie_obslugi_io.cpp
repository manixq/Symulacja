#include "zakonczenie_obslugi_io.h"
#include "io.h"
#include "dane.h"
#include "system_komputerowy.h"

ZakonczenieObslugiIO::ZakonczenieObslugiIO(IO** io, SystemKomputerowy* sys)
 : czas_{-1, -1, -1, -1, -1},
   io_(io),
   sys_(sys)
{
}

void ZakonczenieObslugiIO::Wykonaj(int i)
{
   czas_[i] = -1;
   io_[i]->WezProces()->set_czas_czekania(Dane::czas_symulacji_);
   sys_->KolejkaK()[1]->DodajProces(io_[i]->WezProces());
   io_[i]->UsunProces();
   kDoPliku << "Zdarzenie ZakonczenieObslugiIO... Wykonano! \n";
   kDoPliku << "Zwolniono urzadzenie I/O nr: " << i << "\n\n";
}
