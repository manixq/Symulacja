#include "procesor.h"
#include <cstdio>
#include <cstdlib>

Procesor::Procesor()
 : obecny_proces_(nullptr)
{
 
}

Procesor::~Procesor()
{
 if (obecny_proces_)
  delete obecny_proces_;
}


void Procesor::Przydziel(Proces* x)
{
 obecny_proces_ = x; 
}

Proces* Procesor::Zwolnij()
{
 Proces* p = obecny_proces_;
  obecny_proces_ = nullptr;
  return p;
}

bool Procesor::Wolny()
{
 if (obecny_proces_ == nullptr)
  return true;
 else return false;
}
