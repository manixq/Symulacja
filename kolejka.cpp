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
 ++i;
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
 ++i;
}

SJF::~SJF(){}

int SJF::Wielkosc()
{
 return i;
}

Proces* SJF::WezProces(int x)
{
 return lista_->nastepne_->proces_;
}

void SJF::UsunProces(int x)
{
 lista_->nastepne_ = lista_->nastepne_->nastepne_;
 --i;
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
  i = ptr->nastepne_->proces_->get_tpo();
  ptr->nastepne_->proces_->set_priorytet(x - i);
  ptr = ptr->nastepne_;
 }
}

//usuwa proces z kolejki
//przydziela usuniety proces urzadzeniu
Proces* KolejkaPrio::Wyrzuc()
{
 Proces* ptr = lista_->nastepne_->proces_; 
 lista_->nastepne_ = lista_->nastepne_->nastepne_;
 --i;
 return ptr;
}

int KolejkaPrio::Wielkosc()
{
 return i;
}

