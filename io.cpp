#include "io.h"
#include "dane.h"

IO::IO()
 : obecny_proces_(nullptr),
   kolejka_priorytetowa_(new KolejkaPrio()){}

IO::~IO()
{
 if (obecny_proces_)
  delete obecny_proces_;
 delete kolejka_priorytetowa_;
}

void IO::DodajKolejka(Proces* proces)
{
 kolejka_priorytetowa_->DodajProces(proces);
}



//przydziela proces urzadzeniu prosto z jego kolejki
void IO::PrzydzielKolejka()
{
 UaktualnijPriorytet();
 obecny_proces_ = kolejka_priorytetowa_->Wyrzuc();
}

void IO::UsunProces()
{
 obecny_proces_ = nullptr;
}

void IO::UaktualnijPriorytet()
{
 kolejka_priorytetowa_->Uaktualnij();
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
