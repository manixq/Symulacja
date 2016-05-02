#include  "prosba_dostepu_io.h"
#include "procesor.h"
#include "dane.h"
#include "moj_random.h"
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
 Dane::czas_pracy_procesora_[num] += Dane::czas_symulacji_ - proces->get_czas_czekania();

 int tpo = Random::Normal(1, 10);
 proces->set_tpo(tpo);
 proces->set_priorytet(-tpo);

 //TO jako czas symulacji
 //by wyliczyc czas pobytu w kolejce: czas_symulacji(w momencie opuszczenia kolejki) - TO
 proces->set_czas_czekania(Dane::czas_symulacji_);
 ios_[i]->DodajKolejka(proces);

 kDoPliku << "Zdarzenie Prosba Dostepu do IO... Wykonano! \n";
 kDoPliku << "Zwolniono Procesor nr: " << num << "\n";
 kDoPliku << "Dodano Proces do Kolejki urzadzenia nr: " << i << "\n\n";
}
