#include "komunikaty.h"


void Komunikaty::WypiszStanKolejek(Procesor** procesory, IO** io, SystemKomputerowy* sys)
{
 printf("\n\nProcesory:\n   ");
 for (int i = 0; i < 2; i++)
  if (procesory[i]->Wolny())
   printf(" [ ]");
  else
   printf(" [X]");
 printf("\n\nUrzadzenia wejscia wyjscia:  ");
 for (int i = 0; i < 5; i++)
 {
  printf("\n   io[%d]", i + 1);
  if (io[i]->Wolny())
   printf(" [ ]   kolejka urzadzenia: <->");
  else
  {
   printf(" [X]   kolejka urzadzenia: <-");
   for (int j = 0; j < io[i]->WielkoscKolejki(); j++)
    printf("x-");
   printf(">");
  }
 }
 printf("\n\nKolejka SJF:  ");
 printf("<-");
 for (int j = 0; j < sys->KolejkaK()[1]->Wielkosc(); j++)
  printf("x-");
 printf(">");
 printf("\n\nKolejka dla Nowych:  ");
 printf("<-");
 for (int j = 0; j < sys->KolejkaK()[0]->Wielkosc(); j++)
  printf("x-");
 printf(">");
}

void Komunikaty::WypiszParametry()
{
}
