#include  "prosba_dostepu_io.h"
#include "procesor.h"
#include "dane.h"
#include "random.h"
#include "io.h"

ProsbaDostepuIO::ProsbaDostepuIO(Procesor** procesory, IO** ios)
 : czas_{-1, -1},
   procesory_(procesory),
   ios_(ios){}

void ProsbaDostepuIO::Wykonaj(int num, int czas_konca)
{
 czas_[num] = -1;

 Proces* proces = procesory_[num]->Zwolnij();
 if (czas_konca > Dane::GetCzasSymulacji())
 {
  Dane::SetCzasPracyProcesora(num, Dane::GetCzasSymulacji() - proces->get_czas_dostepu_proc() + Dane::GetCzasPracyProcesora(num));
 }
 int tpo = Random::Normal(1, 10, 2);
 proces->set_tpo(tpo);
 proces->set_priorytet(-tpo);

 //by wyliczyc czas pobytu w kolejce: czas_symulacji(w momencie opuszczenia kolejki) - TO
 proces->set_czas_czekania_io(Dane::GetCzasSymulacji());
 int i;
 i = Random::Normal(0, 4, 1);
 ios_[i]->DodajKolejka(proces);

 fprintf(Dane::GetDoPliku(),"Zdarzenie Prosba Dostepu do IO... Wykonano! \n");
 fprintf(Dane::GetDoPliku(), "Zwolniono Procesor nr: %d\n", num);
 fprintf(Dane::GetDoPliku(), "Dodano Proces do Kolejki urzadzenia nr: %d\n\n",i);
}
