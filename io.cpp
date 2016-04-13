#include "io.h"

IO::IO()
 : obecny_proces_(nullptr),
 kolejka_priorytetowa_(new KolejkaPrio())
{
 printf("[SYSTEM]: stworzono Urzadzenie IO\n");
}

void IO::DodajKolejka(Proces* proces)
{
 kolejka_priorytetowa_->DodajProces(proces);
 printf("[IO]: nowy proces w kolejce\n");
}

void IO::Przydziel(Proces* proces)
{
 obecny_proces_ = proces;
 proces->set_to(0);
 printf("[IO]: proces otrzymal nieprzerwany dostep do urzadzenia\n");
}

void IO::PrzydzielKolejka()
{
 obecny_proces_ = kolejka_priorytetowa_->Wyrzuc();
}

void IO::UsunProces()
{
 int x =  obecny_proces_->get_tpw()-obecny_proces_->get_tpio();
 obecny_proces_->set_tpw(x);
 obecny_proces_ = nullptr;
}

void IO::UaktualnijPriorytet(double x)
{
 kolejka_priorytetowa_->Uaktualnij(x);
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
