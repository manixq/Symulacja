#include <cstdio>
#include "system_komputerowy.h"

SystemKomputerowy::SystemKomputerowy()
 : kLiczbaProcesorow_(2),
   kLiczbaIO_(5),
   kolejka_k1_(new Kolejka),
   kolejka_zdarzen_(new KolejkaZdarzen()),
   kolejka_k2_(new SJF())
{
 kolejki_k_ = new SJF*[2];
 kolejki_k_[0] = kolejka_k1_;
 kolejki_k_[1] = kolejka_k2_;
 //nie wiedzialem jaki zakres, narazie tak jest
 double  TPG = static_cast<double>(30 - 1) * (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) + 1;
 kolejka_zdarzen_->DodajZdarzenie(NOWY_PROCES, TPG, nullptr);
 for(int i = 0; i < kLiczbaProcesorow_; i++)
  procesory_.push_back(new Procesor());
 for (int i = 0; i < kLiczbaIO_; i++)
  io_.push_back(new IO());
 printf("[SYSTEM]: stworzono System komputerowy\n");
 printf("[SYSTEM]: nowe zdarzenie - czas: %f, %s\n", TPG, "NOWY_PROCES");
}

SystemKomputerowy::~SystemKomputerowy()
{
 for (int i = 0; i < kLiczbaProcesorow_; i++)
  delete procesory_[i];
 procesory_.clear();
 for (int i = 0; i < kLiczbaIO_; i++)
  delete io_[i];
 io_.clear();
 delete kolejka_zdarzen_;

}

double SystemKomputerowy::CzasZdarzenia()
{
 if(!kolejka_zdarzen_->Pusta())
  return kolejka_zdarzen_->WezCzas();
 else return -1;
}

Rodzaj_Zdarzenia SystemKomputerowy::RodzajZdarzenia()
{
 if (!kolejka_zdarzen_->Pusta())
  return kolejka_zdarzen_->WezRodzaj();
 else return BRAK;
}

bool SystemKomputerowy::WolnyProcesor()
{
 for (int i = 0; i < kLiczbaProcesorow_; i++)
  if (procesory_[i]->Wolny())
   return true;
 return false;
}

void SystemKomputerowy::DodajProces()
{
 Proces* ptr_proces = new Proces();
 double  TPG = static_cast<double>(30 - 1) * (static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) + 1;//rand() % 20 + 1;
 kolejka_k1_->DodajProces(ptr_proces);
 kolejka_zdarzen_->DodajZdarzenie(NOWY_PROCES, TPG, nullptr);
 printf("[SYSTEM]: nowe zdarzenie - czas: %f, %s\n", TPG, "NOWY_PROCES");
}


void SystemKomputerowy::PrzydzielProcesor(int x)
{
 Proces* ptr;
 int czas;
 bool flag = true;
 int k = 0;
 flag = true;
 k = 0;
 int i = rand() % KolejkaK()[x]->Wielkosc();
 ptr = KolejkaK()[x]->WezProces(i);
 KolejkaK()[x]->UsunProces(i);
 while (k < kLiczbaProcesorow_)
 {
  if (procesory_[k]->Wolny())
  {
   procesory_[k]->Przydziel(ptr);
   flag = false;
   czas = rand() % ptr->get_tpw();
   ptr->set_tpio(czas);
   if (czas != 0)
   {
    ptr->set_tpo(rand() % 10 + 1);
    ptr->set_zadanie_dostepu(true);
    kolejka_zdarzen_->DodajZdarzenie(PROSBA_DOSTEPU_IO, czas, ptr);
    printf("[SYSTEM]: nowe zdarzenie - czas: %d, %s\n", czas, "PROSBA_DOSTEPU_IO");
   }
   else
   {
    ptr->set_zadanie_dostepu(false);
    ptr->set_tpo(0);
    kolejka_zdarzen_->DodajZdarzenie(WYKONCZ_PROCES, ptr->get_tpw(), ptr);
    printf("[SYSTEM]: nowe zdarzenie - czas: %d, %s\n", ptr->get_tpw(), "WYKONCZ_PROCES");
   }
   break;
  }
  else
   k++;
 }
}

void SystemKomputerowy::Uaktualnij()
{
 double x = kolejka_zdarzen_->WezCzas();
 for (int i = 0; i < kLiczbaIO_; i++)
  io_[i]->UaktualnijPriorytet(x);
 kolejka_zdarzen_->UaktualnijCzas();
}

void SystemKomputerowy::ZwolnijIO(Proces* proces)
{
 for (int i = 0; i < kLiczbaIO_; i++)
 {
  if(io_[i]->WezProces() == proces)
  {
   io_[i]->UsunProces();
   kolejka_k2_->DodajProces(proces);
   printf("[SYSTEM]: Przydzielilem proces do kolejki SJF\n");
   if (io_[i]->WielkoscKolejki()>0)
   {
    io_[i]->PrzydzielKolejka();
    kolejka_zdarzen_->DodajZdarzenie(ZAKONCZENIE_OBSLUGI_IO, io_[i]->WezProces()->get_tpo(), io_[i]->WezProces());
    printf("[SYSTEM]: nowe zdarzenie - czas: %d, %s\n", io_[i]->WezProces()->get_tpo(), "ZAKONCZENIE_OBSLUGI_IO");
    printf("[SYSTEM]: Przydzielilem proces do urzadzenia nr %d\n", i + 1);
   }
   break;
  }
 }
}

void SystemKomputerowy::UsunZdarzenie()
{
 printf("[SYSTEM]: Usuwam obecne zdarzenie\n");
 kolejka_zdarzen_->UsunZdarzenie();
}

void SystemKomputerowy::ZwolnijProcesor(Proces* x)
{
 for (int i = 0; i < kLiczbaProcesorow_; i++)
  procesory_[i]->Zwolnij(x);
}

void SystemKomputerowy::PrydzielIO(Proces* proces)
{
 int x = rand() % kLiczbaIO_;
 int y = rand() % 10 + 1;
 proces->set_tpo(y);
 proces->set_priorytet(-y);
 if (io_[x]->Wolny())
 {
  io_[x]->Przydziel(proces);
  kolejka_zdarzen_->DodajZdarzenie(ZAKONCZENIE_OBSLUGI_IO, y, proces);
  printf("[SYSTEM]: nowe zdarzenie - czas: %d, %s\n", y, "ZAKONCZENIE_OBSLUGI_IO");
  printf("[SYSTEM]: Przydzielilem proces do urzadzenia nr %d\n", x + 1);
 }
 else
 {
  io_[x]->DodajKolejka(proces);
  printf("[SYSTEM]: Przydzielilem proces do KOLEJKI urzadzenia nr %d\n", x + 1);
 }
}

void SystemKomputerowy::GUI()
{
 printf("\nLista Zdarzen:");
 kolejka_zdarzen_->Wypisz();
 printf("\n\nProcesory:\n   ");
 for (int i = 0; i < kLiczbaProcesorow_; i++)
  if(procesory_[i]->Wolny())
   printf(" [ ]");
  else
   printf(" [X]");
 printf("\n\nUrzadzenia wejscia wyjscia:  ");
 for (int i = 0; i < kLiczbaIO_; i++)
 {
  printf("\n   io[%d]",i+1);
  if (io_[i]->Wolny())
   printf(" [ ]   kolejka urzadzenia: <->");
  else
  {
   printf(" [X]   kolejka urzadzenia: <-"); 
   for (int j = 0; j < io_[i]->WielkoscKolejki(); j++)
    printf("x-");
   printf(">");
  }
 }
 printf("\n\nKolejka SJF:  ");
 printf("<-");
  for (int j = 0; j < kolejka_k2_->Wielkosc(); j++)
   printf("x-");
 printf(">");
 printf("\n\nKolejka dla Nowych:  ");
 printf("<-");
 for (int j = 0; j < kolejka_k1_->Wielkosc(); j++)
  printf("x-");
 printf(">");
 printf("\n*******************************************************************\n");
}

void SystemKomputerowy::Zabij(Proces* proces)
{
 for (int i = 0; i < kLiczbaProcesorow_; i++)
 {
  procesory_[i]->Zwolnij(proces);
 }
 delete proces;
 printf("[SYSTEM]: Proces zostal usuniety z systemu\n");
}

Proces* SystemKomputerowy::ProcesZdarzenia()
{
 return kolejka_zdarzen_->WezProces();
}

SJF** SystemKomputerowy::KolejkaK()
{
 return kolejki_k_;
}


