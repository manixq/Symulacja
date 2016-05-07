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
 fprintf(Dane::do_pliku_,"Zdarzenie DostepDoIO... Wykonano!\n");
 fprintf(Dane::do_pliku_, "Wolne urzadzenie o numerze: %d\n",i);
 io_[i]->PrzydzielKolejka();
 Dane::calk_czas_odpowiedzi_ += Dane::czas_symulacji_ - io_[i]->WezProces()->get_czas_czekania();
 Dane::ilosc_odpowiedzi_++;
 int tpo = io_[i]->WezProces()->get_tpo();
 zakonczenie_obslugi_io_->czas_[i] = Dane::czas_symulacji_ + tpo;
 fprintf(Dane::do_pliku_, "Przypisano proces urzadzeniu nr: %d\n",i);
 fprintf(Dane::do_pliku_, "Zaplanowano zdarzenie ZakonczenieObslugiIO o czasie: %f\n\n", zakonczenie_obslugi_io_->czas_[i]);
 
}
