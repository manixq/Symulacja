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
 Dane::czas_pracy_procesora_[i] += Dane::czas_symulacji_ - proces->get_czas_czekania();
 Dane::calk_czas_przetwarzania_ += Dane::czas_symulacji_ - proces->get_wiek();
 Dane::calk_liczba_procesow_++;
 delete proces; 
 kDoPliku << "Zdarzenie WykonczProces... Wykonano! \n";
 kDoPliku << "Zwolniono Procesor nr: " << i << "\n";
 kDoPliku << "Permanentnie usunieto Proces z systemu\n\n";
}
