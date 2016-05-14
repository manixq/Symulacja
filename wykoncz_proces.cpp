#include "wykoncz_proces.h"
#include "proces.h"
#include "procesor.h"
#include "dane.h"

WykonczProces::WykonczProces(Procesor** procesor_)
 : czas_{-1, -1},
   p_(procesor_)
{
}

void WykonczProces::Wykonaj(int i, int iteracje, double czas_konca)
{
 czas_[i] = -1;
 Proces* proces = p_[i]->Zwolnij();
 if (czas_konca > Dane::GetCzasSymulacji())
 {
  Dane::SetCzasPracyProcesora(i, Dane::GetCzasSymulacji() - proces->get_czas_dostepu_proc() + Dane::GetCzasPracyProcesora(i));
  Dane::SetCalkCzasPrzetwarzania(Dane::GetCzasSymulacji() - proces->get_wiek() + Dane::GetCalkCzasPrzetwarzania());
 }

 if (Dane::GetCalkLiczbaProcesow() < iteracje)
 {
  Dane::SetCalkLiczbaProcesow(Dane::GetCalkLiczbaProcesow() + 1);
  if (Dane::GetMaxCzasOczek() < proces->get_czas_czekania())
   Dane::SetMaxCzasOczek(proces->get_czas_czekania());
  Dane::SetCalkCzasOczek(proces->get_czas_czekania() + Dane::GetCalkCzasOczek());
 }

 if (Dane::GetStacjonarnosc() < Dane::GetCalkLiczbaProcesow() && Dane::GetCalkLiczbaProcesow() < iteracje)
  fprintf(Dane::GetStats(), "%f ", proces->get_czas_czekania());

 delete proces; 
 fprintf(Dane::GetDoPliku(),"Zdarzenie WykonczProces... Wykonano! \n");
 fprintf(Dane::GetDoPliku(), "Zwolniono Procesor nr: %d\n",i);
 fprintf(Dane::GetDoPliku(), "Permanentnie usunieto Proces z systemu\n\n");
}

