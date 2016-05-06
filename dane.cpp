#define _CRT_SECURE_NO_WARNINGS
#include  "dane.h"
#include "system_komputerowy.h"

FILE* Dane::file = fopen("Parametry.txt", "w");
std::ofstream kDoPliku;
double Dane::czas_symulacji_ = 0.0;
double Dane::czas_pracy_procesora_[] = { 0.0, 0.0 };
double Dane::calk_czas_przetwarzania_ = 0.0;
double Dane::calk_czas_oczek_na_procesor_ = 0.0;
double Dane::calk_czas_odpowiedzi_ = 0.0;
double Dane::L_ = 0.0;
int Dane::calk_liczba_procesow_ = 0;
int Dane::ilosc_odpowiedzi_ = 0;
int Dane::ilosc_oczek_na_procesor_ = 0;
int Dane::kernel_ = 0;

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

void Dane::Parametry(bool gui)
{
 if (gui)
 {
  printf("\n\nSredni czas oczekiwania na procesor: %f\n",(ilosc_oczek_na_procesor_) ? calk_czas_oczek_na_procesor_ / ilosc_oczek_na_procesor_:0);
  for (int i = 0; i < 2; i++)
   printf("Wykorzystanie procesora nr %d wynosi: %f %%\n", i, czas_symulacji_ ? czas_pracy_procesora_[i] / czas_symulacji_ * 100 : 0);
  printf("Przepustowosc systemu mierzona liczba procesow zakonczonych w jednostce czasu: %f\n",czas_symulacji_ ? calk_liczba_procesow_ / czas_symulacji_ : 0);
  printf("Sredni czas przetwarzania(czas miedzy zgloszeniem procesu do systemu a jego zakonczeniem): %f\n",(calk_liczba_procesow_) ? calk_czas_przetwarzania_ / calk_liczba_procesow_ : 0);
  printf("Sredni czas odpowiedzi(czas miedzy zgloszeniem zadania dostepu do IO, a jego otrzymaniem): %f\n", ilosc_odpowiedzi_ ? calk_czas_odpowiedzi_ / ilosc_odpowiedzi_ : 0);
 }
 
  fprintf(file,"\n\nSredni czas oczekiwania na procesor: %f\n", (ilosc_oczek_na_procesor_) ? calk_czas_oczek_na_procesor_ / ilosc_oczek_na_procesor_ : 0);
  for (int i = 0; i < 2; i++)
   fprintf(file,"Wykorzystanie procesora nr %d wynosi: %f %%\n", i, czas_symulacji_ ? czas_pracy_procesora_[i] / czas_symulacji_ * 100 : 0);
  fprintf(file,"Przepustowosc systemu mierzona liczba procesow zakonczonych w jednostce czasu: %f\n", czas_symulacji_ ? calk_liczba_procesow_ / czas_symulacji_ : 0);
  fprintf(file,"Sredni czas przetwarzania(czas miedzy zgloszeniem procesu do systemu a jego zakonczeniem): %f\n", (calk_liczba_procesow_) ? calk_czas_przetwarzania_ / calk_liczba_procesow_ : 0);
  fprintf(file,"Sredni czas odpowiedzi(czas miedzy zgloszeniem zadania dostepu do IO, a jego otrzymaniem): %f\n", ilosc_odpowiedzi_ ? calk_czas_odpowiedzi_ / ilosc_odpowiedzi_ : 0);
}
 



void Dane::Reset()
{
 czas_symulacji_ = 0.0;
 czas_pracy_procesora_[0] = 0.0;
 czas_pracy_procesora_[1] = 0.0;
 calk_czas_przetwarzania_ = 0.0;
 calk_czas_oczek_na_procesor_ = 0.0;
 calk_czas_odpowiedzi_ = 0.0;
 L_ = 0.0;
 calk_liczba_procesow_ = 0;
 ilosc_odpowiedzi_ = 0;
 ilosc_oczek_na_procesor_ = 0;
 kernel_ = 0;
}
