#include <cstdio>
#include "system_komputerowy.h"

SystemKomputerowy::SystemKomputerowy()
 : kLiczbaProcesorow_(2),
   kLiczbaIO_(5),
   kolejka_k1_(new Kolejka),
   kolejka_zdarzen_(new KolejkaZdarzen()),
   kolejka_k2_(new SJF()),
   zuzycie_{0.0, 0.0},
   czas_przetwarzania_(0.0),
   caly_czas_(0.0),
   proc_killed_(0),
   io_call_(0),
   czas_odpowiedzi_(0.0), 
   czas_czekania_(0.0)
{
 
 kolejki_k_ = new SJF*[2];
 kolejki_k_[0] = kolejka_k1_;
 kolejki_k_[1] = kolejka_k2_;
 r = new Random(127);
 double  TPG = r->Wykladn();
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
 delete kolejki_k_[0];
 delete kolejki_k_[1];
 delete[] kolejki_k_;
 delete r;

}

double SystemKomputerowy::CzasZdarzenia()
{
 if(!kolejka_zdarzen_->Pusta())
  return kolejka_zdarzen_->WezCzas();
 else return -1;
}

double SystemKomputerowy::OutL()
{
 return czas_czekania_ / proc_killed_;
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
 proc_killed_++;
 Proces* ptr_proces = new Proces();
 ptr_proces->set_tpw(r->Normal() % 50 + 1);
 double  TPG = r->Wykladn();
 ptr_proces->set_wiek(caly_czas_);
 ptr_proces->set_czas_czekania(caly_czas_);
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
 int i = r->Normal() % KolejkaK()[x]->Wielkosc();
 ptr = KolejkaK()[x]->WezProces(i);
 KolejkaK()[x]->UsunProces(i);
 if(!x)
  czas_czekania_ += (caly_czas_ - ptr->get_czas_czekania());
 while (k < kLiczbaProcesorow_)
 {
  if (procesory_[k]->Wolny())
  {
   
   procesory_[k]->Przydziel(ptr);
   flag = false;
   czas = r->Normal() % ptr->get_tpw();
   ptr->set_tpio(czas);
   if (czas != 0)
   {
    zuzycie_[k] += czas;
    ptr->set_tpo(r->Normal() % 10 + 1);
    ptr->set_zadanie_dostepu(true);
    kolejka_zdarzen_->DodajZdarzenie(PROSBA_DOSTEPU_IO, czas, ptr);
    printf("[SYSTEM]: nowe zdarzenie - czas: %d, %s\n", czas, "PROSBA_DOSTEPU_IO");
   }
   else
   {
    ptr->set_zadanie_dostepu(false);
    ptr->set_tpo(0);
    zuzycie_[k] += ptr->get_tpw();
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
 caly_czas_ += x;
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
    czas_odpowiedzi_ += caly_czas_ - io_[i]->WezProces()->get_czas_zgloszen();
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
 int x = r->Normal() % kLiczbaIO_;
 int y =r->Normal() % 10 + 1;
 proces->set_tpo(y);
 proces->set_priorytet(-y);
 proces->set_czas_zgloszen(caly_czas_);
 io_call_++;
 if (io_[x]->Wolny())
 {
  io_[x]->Przydziel(proces);
  kolejka_zdarzen_->DodajZdarzenie(ZAKONCZENIE_OBSLUGI_IO, y, proces);
  printf("[SYSTEM]: nowe zdarzenie - czas: %d, %s\n", y, "ZAKONCZENIE_OBSLUGI_IO");
  printf("[SYSTEM]: Przydzielilem proces do urzadzenia nr %d\n", x + 1);
 }
 else
 {
  //proces->set_czas_zgloszen
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
 printf("\nzuzycie procesora nr1:%f%%\n",zuzycie_[0]/caly_czas_*100);
 printf("zuzycie procesora nr2: %f%%\n", zuzycie_[1] / caly_czas_ * 100);
 printf("przepustowosc systemu: %f\n",proc_killed_/caly_czas_);
 printf("sredni czas przetwarzania %f\n", czas_przetwarzania_/proc_killed_);
 printf("sredni czas odpowiedzi: %f\n", czas_odpowiedzi_/io_call_);
 printf("sredni czas oczekiwania na procesor: %f\n\n", czas_czekania_ / proc_killed_);



 printf("\n*******************************************************************\n");
}

void SystemKomputerowy::Zabij(Proces* proces)
{
 czas_przetwarzania_ += caly_czas_ - proces->get_wiek();
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


