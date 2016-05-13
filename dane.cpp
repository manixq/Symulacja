
#include  "dane.h"
#include "system_komputerowy.h"
#include "fstream"
#include "stdio.h"

FILE* Dane::do_pliku_ = nullptr;
FILE* Dane::stats_ = nullptr;
double Dane::czas_pomiarow_ = 0.0;
double Dane::czas_symulacji_ = 0.0;
double Dane::czas_pracy_procesora_[] = { 0.0, 0.0 };
double Dane::calk_czas_przetwarzania_ = 0.0;
double Dane::calk_czas_oczek_na_procesor_ = 0.0;
double Dane::max_czas_oczek_ = 0.0;
double Dane::calk_czas_odpowiedzi_ = 0.0;
double Dane::L_ = 0.0;
int Dane::calk_liczba_procesow_ = 0;
int Dane::ilosc_odpowiedzi_ = 0;
int Dane::kernel_ = 0;
int Dane::numer_symulacji_ = 0;
bool Dane::stacjonarnosc_ = true;

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

std::string Dane::ZmienNazwe()
{
 std::string plik = "symulacja_";
 std::string nr_sym = std::to_string(Dane::numer_symulacji_);
  std::string nazwa = plik + nr_sym + ".txt";
  return nazwa;
}


void Dane::Parametry(bool gui)
{
 if (gui)
 {
  printf("Maksymalny czas oczekiwania na procesor: %f\n",max_czas_oczek_);
  printf("Sredni czas oczekiwania na procesor: %f\n", (calk_liczba_procesow_) ? calk_czas_oczek_na_procesor_ / calk_liczba_procesow_ : 0);
  for (int i = 0; i < 2; i++)
   printf("Wykorzystanie procesora nr %d wynosi: %f %%\n", i, czas_symulacji_ ? czas_pracy_procesora_[i] / czas_symulacji_ * 100 : 0);
  printf("Przepustowosc systemu mierzona liczba procesow zakonczonych w jednostce czasu: %f\n",czas_symulacji_ ? calk_liczba_procesow_ / czas_symulacji_ : 0);
  printf("Sredni czas przetwarzania(czas miedzy zgloszeniem procesu do systemu a jego zakonczeniem): %f\n",(calk_liczba_procesow_) ? calk_czas_przetwarzania_ / calk_liczba_procesow_ : 0);
  printf("Sredni czas odpowiedzi(czas miedzy zgloszeniem zadania dostepu do IO, a jego otrzymaniem): %f\n", ilosc_odpowiedzi_ ? calk_czas_odpowiedzi_ / ilosc_odpowiedzi_ : 0);
  printf("\n--------------------------------------------------------------------\n");
 }
  fprintf(do_pliku_, "\n--------------------------------------------------------------------\n");
  fprintf(do_pliku_, "Maksymalny czas oczekiwania na procesor: %f\n", max_czas_oczek_);
  fprintf(do_pliku_,"Sredni czas oczekiwania na procesor: %f\n", (calk_liczba_procesow_) ? calk_czas_oczek_na_procesor_ / calk_liczba_procesow_: 0);
  for (int i = 0; i < 2; i++)
   fprintf(do_pliku_,"Wykorzystanie procesora nr %d wynosi: %f %%\n", i, czas_pomiarow_ ? czas_pracy_procesora_[i] / czas_pomiarow_ * 100 : 0);
  fprintf(do_pliku_,"Przepustowosc systemu mierzona liczba procesow zakonczonych w jednostce czasu: %f\n", czas_pomiarow_ ? calk_liczba_procesow_ / czas_pomiarow_ : 0);
  fprintf(do_pliku_,"Sredni czas przetwarzania(czas miedzy zgloszeniem procesu do systemu a jego zakonczeniem): %f\n", (calk_liczba_procesow_) ? calk_czas_przetwarzania_ / calk_liczba_procesow_ : 0);
  fprintf(do_pliku_,"Sredni czas odpowiedzi(czas miedzy zgloszeniem zadania dostepu do IO, a jego otrzymaniem): %f\n", ilosc_odpowiedzi_ ? calk_czas_odpowiedzi_ / ilosc_odpowiedzi_ : 0);
  
}
 



void Dane::Reset()
{
 
 fprintf(stats_, "\nMaksymalny czas oczekiwania na procesor: %f\n", max_czas_oczek_);
 fprintf(stats_, "Sredni czas oczekiwania na procesor: %f\n", (calk_liczba_procesow_) ? calk_czas_oczek_na_procesor_ / calk_liczba_procesow_ : 0);
 for (int i = 0; i < 2; i++)
  fprintf(stats_, "Wykorzystanie procesora nr %d wynosi: %f %%\n", i, czas_pomiarow_ ? czas_pracy_procesora_[i] / czas_pomiarow_ * 100 : 0);
 fprintf(stats_, "Przepustowosc systemu mierzona liczba procesow zakonczonych w jednostce czasu: %f\n", czas_pomiarow_ ? calk_liczba_procesow_ / czas_pomiarow_ : 0);
 fprintf(stats_, "Sredni czas przetwarzania(czas miedzy zgloszeniem procesu do systemu a jego zakonczeniem): %f\n", (calk_liczba_procesow_) ? calk_czas_przetwarzania_ / calk_liczba_procesow_ : 0);
 fprintf(stats_, "Sredni czas odpowiedzi(czas miedzy zgloszeniem zadania dostepu do IO, a jego otrzymaniem): %f\n", ilosc_odpowiedzi_ ? calk_czas_odpowiedzi_ / ilosc_odpowiedzi_ : 0);
 fprintf(stats_, "\n-------------------------------------\n");
 fclose(stats_);
 max_czas_oczek_ = 0.0;
 czas_pomiarow_ = 0.0;
 czas_symulacji_ = 0.0;
 czas_pracy_procesora_[0] = 0.0;
 czas_pracy_procesora_[1] = 0.0;
 calk_czas_przetwarzania_ = 0.0;
 calk_czas_oczek_na_procesor_ = 0.0;
 calk_czas_odpowiedzi_ = 0.0;
 L_ = 0.0;
 calk_liczba_procesow_ = 0;
 ilosc_odpowiedzi_ = 0;
 kernel_ = 0;
 numer_symulacji_++;
}

void Dane::ZapiszDoPliku(char buffer[])
{
 fprintf(do_pliku_, buffer);
}
void Dane::ZapiszDoStatystyk(char buffer[])
{
 fprintf(stats_, buffer);
}

void Dane::Ustawienia()
{
  stacjonarnosc_ = 1;
  czas_pomiarow_ = 0.0;
  max_czas_oczek_ = 0.0;
  czas_pracy_procesora_[0] = 0.0;
  czas_pracy_procesora_[1] = 0.0;
  calk_czas_przetwarzania_ = 0.0;
  calk_czas_oczek_na_procesor_ = 0.0;
  calk_czas_odpowiedzi_ = 0.0;
 // calk_liczba_procesow_ = 0;
  ilosc_odpowiedzi_ = 0;
}

void Dane::SetStacjonarnosc(bool stat)
{
 stacjonarnosc_ = stat;
}

void Dane::SetCzasPomiarow(double czas)
{
 czas_pomiarow_ = czas;
}

void Dane::SetCzasSymulacji(double czas)
{
 czas_symulacji_ = czas;
}

void Dane::SetCzasPracyProcesora(int i, double czas)
{
 czas_pracy_procesora_[i] = czas;
}

void Dane::SetCalkLiczbaProcesow(int i)
{
 calk_liczba_procesow_ = i;
}

void Dane::SetCalkCzasPrzetwarzania(double czas)
{
 calk_czas_przetwarzania_ = czas;
}

void Dane::SetCalkCzasOczek(double czas)
{
 calk_czas_oczek_na_procesor_ = czas;
}


void Dane::SetMaxCzasOczek(double czas)
{
 max_czas_oczek_ = czas;
}

void Dane::SetKernel(int x)
{
 kernel_ = x;
}

void Dane::SetL(double L)
{
 L_ = L;
}

void Dane::SetCalkCzasOdpowiedz(double czas)
{
 calk_czas_odpowiedzi_ = czas;
}

void Dane::SetIloscOdpowiedzi(int i)
{
 ilosc_odpowiedzi_ = i;
}

void Dane::SetNumerSymulacji(int n)
{
 numer_symulacji_ = n;
}

void Dane::SetDoPliku(FILE* plik)
{
 do_pliku_ = plik;
}

void Dane::SetStats(FILE* plik)
{
 stats_ = plik;
}

bool Dane::GetStacjonarnosc()
{
 return stacjonarnosc_;
}

double Dane::GetCzasPomiarow()
{
 return czas_pomiarow_;
}

double Dane::GetCzasSymulacji()
{
 return czas_symulacji_;
}

double Dane::GetCzasPracyProcesora(int i)
{
 return czas_pracy_procesora_[i];
}

int Dane::GetCalkLiczbaProcesow()
{
 return calk_liczba_procesow_;
}

double Dane::GetCalkCzasPrzetwarzania()
{
 return calk_czas_przetwarzania_;
}

double Dane::GetCalkCzasOczek()
{
 return calk_czas_oczek_na_procesor_;
}


double Dane::GetMaxCzasOczek()
{
 return max_czas_oczek_;
}


double Dane::GetCalkCzasOdpowiedz()
{
 return calk_czas_odpowiedzi_;
}

int Dane::GetIloscOdpowiedzi()
{
 return ilosc_odpowiedzi_;
}

int Dane::GetNumerSymulacji()
{
 return numer_symulacji_;
}

FILE* Dane::GetStats()
{
 return stats_;
}

FILE* Dane::GetDoPliku()
{
 return do_pliku_;
}
