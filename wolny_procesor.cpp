#include "wolny_procesor.h"
#include "system_komputerowy.h"
#include "dane.h"
#include "moj_random.h"
#include "prosba_dostepu_io.h"
#include "wykoncz_proces.h"

WolnyProcesor::WolnyProcesor(SystemKomputerowy* sys, Procesor** p, ProsbaDostepuIO* prosba_dostepu_io, WykonczProces* wykoncz_proces)
 : sys_(sys),
   p_(p),
   prosba_dostepu_io_(prosba_dostepu_io),
   wykoncz_proces_(wykoncz_proces)
{
}

void WolnyProcesor::Wykonaj(int i)
{
 kDoPliku << "Zdarzenie WolnyProcesor... Wykonano!\n";
 kDoPliku << "Wolny Procesor o numerze: " << i << "\n";
 int x = 0;
 int num = 0;
 Proces* proces;

 //Od kolejki zalezy wybor algorytmu za pomoca ktorego przydziele proces
  if (!sys_->KolejkaK()[0]->Pusta() && !sys_->KolejkaK()[1]->Pusta())
  {
   num = Random::Normal(0, 1);
   x = sys_->KolejkaK()[num]->Wielkosc();
   x = Random::Normal(0, x - 1);
   proces = sys_->KolejkaK()[num]->WezProces(x);
   sys_->KolejkaK()[num]->UsunProces(x);
   p_[i]->Przydziel(proces);
  } 
  else if(!sys_->KolejkaK()[0]->Pusta())
  {
   x = sys_->KolejkaK()[0]->Wielkosc();
   x = Random::Normal(0, x - 1);
   proces = sys_->KolejkaK()[0]->WezProces(x);
   sys_->KolejkaK()[0]->UsunProces(x);
   p_[i]->Przydziel(proces);
  }
  else 
  {
   proces = sys_->KolejkaK()[1]->WezProces(0);
   sys_->KolejkaK()[1]->UsunProces(0);
   p_[i]->Przydziel(proces);
  }

  kDoPliku << "Przydzielono proces do procesora nr: " << i << "\n";
  int tpw = proces->get_tpw();
  if (tpw == 0)
   tpw = Random::Normal(1, 50);
  proces->set_tpw(tpw);
  int tpio = Random::Normal(0, tpw - 1);
  if (tpio != 0)
  {
   proces->set_tpw(tpw - tpio);
   prosba_dostepu_io_->czas_[i] = Dane::czas_symulacji_ + tpio;   
   kDoPliku << "Zaplanowano zdarzenie ProsbaDostepuIO o czasie: " << prosba_dostepu_io_->czas_[i] << "\n\n";
  }
  else
  {
   wykoncz_proces_->czas_[i] = Dane::czas_symulacji_ + tpw;
   kDoPliku << "Zaplanowano zdarzenie WykonczProces o czasie: " << wykoncz_proces_->czas_[i] << "\n\n";
  }
  Dane::calk_czas_oczek_na_procesor_ += Dane::czas_symulacji_ - proces->get_czas_czekania();
  Dane::ilosc_oczek_na_procesor_++;
  proces->set_czas_czekania(Dane::czas_symulacji_);
}
