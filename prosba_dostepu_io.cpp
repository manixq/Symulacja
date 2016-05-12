#include  "prosba_dostepu_io.h"
#include "procesor.h"
#include "dane.h"
#include "random.h"
#include "io.h"

ProsbaDostepuIO::ProsbaDostepuIO(Procesor** procesory, IO** ios)
 : czas_{-1, -1},
   procesory_(procesory),
   ios_(ios){}

void ProsbaDostepuIO::Wykonaj(int num)
{
 czas_[num] = -1;
 int i;
 i = Random::Normal(0, 4);
 Proces* proces = procesory_[num]->Zwolnij();
 Dane::SetCzasPracyProcesora(num, Dane::GetCzasSymulacji() - proces->get_czas_czekania() + Dane::GetCzasPracyProcesora(num));

 int tpo = Random::Normal(1, 10);
 proces->set_tpo(tpo);
 proces->set_priorytet(-tpo);

 //TO jako czas symulacji
 //by wyliczyc czas pobytu w kolejce: czas_symulacji(w momencie opuszczenia kolejki) - TO
 proces->set_czas_czekania(Dane::GetCzasSymulacji());
 ios_[i]->DodajKolejka(proces);

 fprintf(Dane::GetDoPliku(),"Zdarzenie Prosba Dostepu do IO... Wykonano! \n");
 fprintf(Dane::GetDoPliku(), "Zwolniono Procesor nr: %d\n", num);
 fprintf(Dane::GetDoPliku(), "Dodano Proces do Kolejki urzadzenia nr: %d\n\n",i);
}
