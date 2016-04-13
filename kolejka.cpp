#include "kolejka.h"

void Kolejka::DodajProces(Proces* proces)
{
 lista_.insert(lista_.begin(),proces);
}

int Kolejka::Wielkosc()
{
 return lista_.size();
}

Proces* Kolejka::WezProces(int x)
{
 return lista_[x];
}

void Kolejka::UsunProces(int x)
{
 lista_.erase(lista_.begin()+x);
}

bool Kolejka::Pusta()
{
 return lista_.empty();
}

Pole::Pole():proces_(nullptr), nastepne_(nullptr){}

Pole::Pole(Proces* proces): proces_(proces), nastepne_(nullptr) {}

KolejkaPrio::KolejkaPrio():lista_(new Pole()),i(0){}

KolejkaPrio::~KolejkaPrio()
{
 Pole* ptr = lista_;
 while(ptr)
 {
  ptr = ptr->nastepne_;
  delete lista_;
  lista_ = ptr;
 }
}

void KolejkaPrio::DodajProces(Proces* proces)
{
 Pole* ptr = lista_;
 Pole* nowy = new Pole(proces);
 while (ptr->nastepne_)
 {
  if (proces->get_priorytet() > lista_->nastepne_->proces_->get_priorytet())
   break;
  ptr = ptr->nastepne_;
 }
 nowy->nastepne_ = ptr->nastepne_;
 ptr->nastepne_ = nowy;
 ++this->i;
}

SJF::SJF() :KolejkaPrio(){}

void SJF::DodajProces(Proces* proces)
{
 Pole* ptr = lista_;
 Pole* nowy = new Pole(proces);
 while (ptr->nastepne_)
 {
  if (proces->get_tpw() < lista_->nastepne_->proces_->get_tpw())
   break;
  ptr = ptr->nastepne_;
 }
 nowy->nastepne_ = ptr->nastepne_;
 ptr->nastepne_ = nowy;
 ++this->i;
}

SJF::~SJF(){}

int SJF::Wielkosc()
{
 return KolejkaPrio::Wielkosc();
}

Proces* SJF::WezProces(int x)
{
 return lista_->nastepne_->proces_;
}

void SJF::UsunProces(int x)
{
 lista_->nastepne_ = lista_->nastepne_->nastepne_;
 --this->i;
}

bool SJF::Pusta()
{
 if (lista_->nastepne_ == nullptr)return true; 
 else return false;
}

void KolejkaPrio::Uaktualnij(double x)
{
 Pole* ptr = lista_;
 double i;
 while(ptr->nastepne_)
 {
  i = ptr->nastepne_->proces_->get_priorytet();
  ptr->nastepne_->proces_->set_priorytet(x + i);
  ptr = ptr->nastepne_;
 }
}

Proces* KolejkaPrio::Wyrzuc()
{
 Proces* ptr = lista_->nastepne_->proces_; 
 lista_->nastepne_ = lista_->nastepne_->nastepne_;
 --this->i;
 return ptr;
}

int KolejkaPrio::Wielkosc()
{
 return this->i;
}

Zdarzenie::Zdarzenie():
 czas_(-1),
 proces_(nullptr),
 nastepny_(nullptr),
 rodzaj_zdarzenia_(BRAK){}
Zdarzenie:: Zdarzenie(Rodzaj_Zdarzenia rodzaj_zdarzenia, double czas, Proces* proces):
 czas_(czas),
 proces_(proces),
 nastepny_(nullptr),
 rodzaj_zdarzenia_(rodzaj_zdarzenia){}
Zdarzenie::Zdarzenie(Rodzaj_Zdarzenia rodzaj_zdarzenia, double czas, Proces* proces,Zdarzenie* nastepne_zdarzenie):
 rodzaj_zdarzenia_(rodzaj_zdarzenia),
 czas_(czas),
 proces_(proces),
 nastepny_(nastepne_zdarzenie){}


KolejkaZdarzen::KolejkaZdarzen():head_zdarzenie_(new Zdarzenie()){}
KolejkaZdarzen::~KolejkaZdarzen()
{
 Zdarzenie* ptr = head_zdarzenie_->nastepny_;
 while(ptr)
 {
  ptr = ptr->nastepny_;
  delete head_zdarzenie_;
  head_zdarzenie_ = ptr;
 }
}

double KolejkaZdarzen::WezCzas()
{
 return head_zdarzenie_->nastepny_->czas_;
}

Rodzaj_Zdarzenia KolejkaZdarzen::WezRodzaj()
{
 return head_zdarzenie_->nastepny_->rodzaj_zdarzenia_;
}

bool KolejkaZdarzen::Pusta()
{
 if (head_zdarzenie_->nastepny_ == nullptr)
  return true;
 else
  return false;
}

Proces* KolejkaZdarzen::WezProces()
{
 return head_zdarzenie_->nastepny_->proces_;
}

void KolejkaZdarzen::Wypisz()
{
 int i;
 char* x[]= 
 { "BRAK",
  "NOWY_PROCES",
  "PROSBA_DOSTEPU_IO",
  "ZAKONCZENIE_OBSLUGI_IO",
  "WYKONCZ_PROCES" };
 Zdarzenie* ptr = head_zdarzenie_->nastepny_;
 while(ptr)
 {
  i = ptr->rodzaj_zdarzenia_;
  printf("\n   Czas: %f   Rodzaj: %s ",ptr->czas_,x[i]);
  ptr = ptr->nastepny_;
 }
}

//tu naprawic
void KolejkaZdarzen::DodajZdarzenie(Rodzaj_Zdarzenia rodzaj_zdarzenia, double czas, Proces* proces)
{
  Zdarzenie* ptr_zdarzenie = head_zdarzenie_;
  Zdarzenie* nowe_zdarzenie;
  while(ptr_zdarzenie->nastepny_)
  {   
   if (ptr_zdarzenie->nastepny_->czas_ > czas)
    break;
   ptr_zdarzenie = ptr_zdarzenie->nastepny_;
  }
  nowe_zdarzenie = new Zdarzenie(rodzaj_zdarzenia, czas, proces, ptr_zdarzenie->nastepny_);
  ptr_zdarzenie->nastepny_ = nowe_zdarzenie;
}

void KolejkaZdarzen::UsunZdarzenie()
{
 Zdarzenie* ptr_zdarzenie;
 ptr_zdarzenie = head_zdarzenie_->nastepny_;
 if(head_zdarzenie_->nastepny_)
 {
  head_zdarzenie_ ->nastepny_ = head_zdarzenie_->nastepny_->nastepny_;
  delete ptr_zdarzenie;
 }
}

void KolejkaZdarzen::UaktualnijCzas()
{
 Zdarzenie* ptr = head_zdarzenie_->nastepny_;
 if (ptr) {
  double x = ptr->czas_;
  while (ptr != nullptr)
  {
   ptr->czas_ = ptr->czas_ - x;
   ptr = ptr->nastepny_;
  }
 }
}
