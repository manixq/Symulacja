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
   io_[i]->WezProces()->set_czas_czekania(Dane::GetCzasSymulacji() - io_[i]->WezProces()->get_czas_czekania());
   sys_->KolejkaK()[1]->DodajProces(io_[i]->WezProces());
   io_[i]->UsunProces();
   fprintf(Dane::GetDoPliku(), "Zdarzenie ZakonczenieObslugiIO... Wykonano! \n");
   fprintf(Dane::GetDoPliku(), "Zwolniono urzadzenie I/O nr: %d\n\n",i);
 
}
