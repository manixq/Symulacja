#include "procesor.h"
#include <cstdio>
#include <cstdlib>

Procesor::Procesor()
 : obecny_proces_(nullptr)
{
 printf("[SYSTEM]: stworzono Procesor\n");
}

void Procesor::Przydziel(Proces* x)
{

 obecny_proces_ = x;
 printf("[PROCESOR]: przydzielono proces.\n");

}

void Procesor::Zwolnij(Proces* x)
{
 
 if (obecny_proces_ == x)
 {
  obecny_proces_ = nullptr;
  printf("[PROCESOR] - zwolniono proces.\n");
 }
}

bool Procesor::Wolny()
{
 if (obecny_proces_ == nullptr)
  return true;
 else return false;
}
