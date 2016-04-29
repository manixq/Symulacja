#include "procesor.h"
#include <cstdio>
#include <cstdlib>

Procesor::Procesor(int debug)
 : obecny_proces_(nullptr)
{
 debug_ = debug;
 if(debug_) printf("[SYSTEM]: stworzono Procesor\n");
}

void Procesor::Przydziel(Proces* x)
{

 obecny_proces_ = x;
 if(debug_) printf("[PROCESOR]: przydzielono proces.\n");

}

void Procesor::Zwolnij(Proces* x)
{
 
 if (obecny_proces_ == x)
 {
  obecny_proces_ = nullptr;
  if(debug_) printf("[PROCESOR] - zwolniono proces.\n");
 }
}

bool Procesor::Wolny()
{
 if (obecny_proces_ == nullptr)
  return true;
 else return false;
}
