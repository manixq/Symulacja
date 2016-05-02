#include "io.h"
#include "dane.h"

IO::IO()
 : obecny_proces_(nullptr),
   kolejka_priorytetowa_(new KolejkaPrio()){}

void IO::DodajKolejka(Proces* proces)
{
 kolejka_priorytetowa_->DodajProces(proces);
}

void IO::Przydziel(Proces* proces)
{
 obecny_proces_ = proces;
 proces->set_to(0);
}

//przydziela proces urzadzeniu prosto z jego kolejki
void IO::PrzydzielKolejka()
{
 //UaktualnijPriorytet(Dane::czas_symulacji_ - obecny_proces_->get_czas_czekania());
 obecny_proces_ = kolejka_priorytetowa_->Wyrzuc();
}

void IO::UsunProces()
{
 obecny_proces_ = nullptr;
}

void IO::UaktualnijPriorytet(double x)
{
 kolejka_priorytetowa_->Uaktualnij(x);

 KolejkaPrio* kolejka = new KolejkaPrio();
 KolejkaPrio* ptr;
 while(kolejka_priorytetowa_->Wielkosc() != 0)
  kolejka->DodajProces(kolejka_priorytetowa_->Wyrzuc());
 ptr = kolejka_priorytetowa_;
 kolejka_priorytetowa_ = kolejka;
 delete ptr;
}

Proces* IO::WezProces()
{
 return obecny_proces_;
}

int IO::WielkoscKolejki()
{
 return kolejka_priorytetowa_->Wielkosc();
}

bool IO::Wolny()
{
 if (obecny_proces_)
  return false;
 else return true;
}
