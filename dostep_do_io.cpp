#include "dostep_do_io.h"
#include "dane.h"
#include "io.h"
#include "random.h"
#include "zakonczenie_obslugi_io.h"

DostepDoIO::DostepDoIO(IO** io, ZakonczenieObslugiIO* zakonczenie_obslugi_io)
 : io_(io),
   zakonczenie_obslugi_io_(zakonczenie_obslugi_io)
{
}

void DostepDoIO::Wypisz(int i){
 char buffer[255];
 Dane::ZapiszDoPliku("Zdarzenie DostepDoIO... Wykonano!\n");
 sprintf(buffer, "Wolne urzadzenie o numerze: %d\n", i);
 Dane::ZapiszDoPliku(buffer);
 sprintf(buffer, "Przypisano proces urzadzeniu nr: %d\n", i);
 Dane::ZapiszDoPliku(buffer);
 sprintf(buffer, "Zaplanowano zdarzenie ZakonczenieObslugiIO o czasie: %f\n\n", zakonczenie_obslugi_io_->czas_[i]);
 Dane::ZapiszDoPliku(buffer);
}

void DostepDoIO::Wykonaj(int i, int iteracje){
 io_[i]->PrzydzielKolejka();
 if (Dane::GetIloscOdpowiedzi() < iteracje)
 {
  Dane::SetCalkCzasOdpowiedz(Dane::GetCalkCzasOdpowiedz() + Dane::GetCzasSymulacji() - io_[i]->WezProces()->get_czas_czekania_io());
  Dane::SetIloscOdpowiedzi(1 + Dane::GetIloscOdpowiedzi());
 }

 int tpo = io_[i]->WezProces()->get_tpo();
 zakonczenie_obslugi_io_->czas_[i] = Dane::GetCzasSymulacji() + tpo;
 Wypisz(i);
}
