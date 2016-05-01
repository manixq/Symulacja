#include "procesor.h"
#include <cstdio>
#include <cstdlib>

Procesor::Procesor()
 : obecny_proces_(nullptr)
{
 
}

void Procesor::Przydziel(Proces* x)
{

 
}

void Procesor::Zwolnij(Proces* x)
{
 
 if (obecny_proces_ == x)
 {
  obecny_proces_ = nullptr;

 }
}

bool Procesor::Wolny()
{
 if (obecny_proces_ == nullptr)
  return true;
 else return false;
}
