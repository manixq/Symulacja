#include  "dane.h"
#include "system_komputerowy.h"


std::ofstream kDoPliku;
double Dane::czas_symulacji_ = 0.0;
double Dane::czas_pracy_procesora_[] = { 0.0, 0.0 };
int Dane::calk_liczba_procesow_ = 0;
double Dane::calk_czas_przetwarzania_ = 0.0;
double Dane::calk_czas_oczek_na_procesor_ = 0.0;
double Dane::calk_czas_odpowiedzi_ = 0.0;
void Dane::GUI(Procesor** procesory, IO** io, SystemKomputerowy* sys)
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
 printf(">\n\n\n");

 std::system("Pause");
}