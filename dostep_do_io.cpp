#include "dostep_do_io.h"
#include "dane.h"
#include "io.h"
#include "moj_random.h"
#include "zakonczenie_obslugi_io.h"

DostepDoIO::DostepDoIO(IO** io, ZakonczenieObslugiIO* zakonczenie_obslugi_io)
 : io_(io),
   zakonczenie_obslugi_io_(zakonczenie_obslugi_io)
{
}

void DostepDoIO::Wykonaj(int i)
{
 kDoPliku << "Zdarzenie DostepDoIO... Wykonano!\n";
 kDoPliku << "Wolne urzadzenie o numerze: " << i << "\n";
 io_[i]->PrzydzielKolejka();
 Dane::calk_czas_odpowiedzi_ += Dane::czas_symulacji_ - io_[i]->WezProces()->get_czas_czekania();
 int tpo = io_[i]->WezProces()->get_tpo();
 zakonczenie_obslugi_io_->czas_[i] = Dane::czas_symulacji_ + tpo;
 kDoPliku << "Przypisano proces urzadzeniu nr: " << i << "\n";
 kDoPliku << "Zaplanowano zdarzenie ZakonczenieObslugiIO o czasie: "<< zakonczenie_obslugi_io_->czas_[i] << "\n\n";
 
}
