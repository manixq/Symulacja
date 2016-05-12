#include "wykoncz_proces.h"
#include "proces.h"
#include "procesor.h"
#include "dane.h"

WykonczProces::WykonczProces(Procesor** procesor_)
 : czas_{-1, -1},
   p_(procesor_)
{
}

void WykonczProces::Wykonaj(int i)
{
 czas_[i] = -1;
 Proces* proces = p_[i]->Zwolnij();
 Dane::SetCzasPracyProcesora(i, Dane::GetCzasSymulacji() - proces->get_czas_czekania() + Dane::GetCzasPracyProcesora(i));
 Dane::SetCalkCzasPrzetwarzania(Dane::GetCzasSymulacji() - proces->get_wiek() + Dane::GetCalkCzasPrzetwarzania());
 Dane::SetCalkLiczbaProcesow(Dane::GetCalkLiczbaProcesow() + 1);
 delete proces; 
 fprintf(Dane::GetDoPliku(),"Zdarzenie WykonczProces... Wykonano! \n");
 fprintf(Dane::GetDoPliku(), "Zwolniono Procesor nr: %d\n",i);
 fprintf(Dane::GetDoPliku(), "Permanentnie usunieto Proces z systemu\n\n");

}
