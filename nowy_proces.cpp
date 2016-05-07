#include "nowy_proces.h"
#include "moj_random.h"
#include "dane.h"

NowyProces::NowyProces(SystemKomputerowy* sys)
 :czas_(0.0),
  sys_(sys){}

void NowyProces::Wykonaj()
{
 Proces* proces = new Proces;
 proces->set_wiek(Dane::czas_symulacji_);
 proces->set_czas_czekania(Dane::czas_symulacji_);
 sys_->DodajProces(proces);
 czas_ = Random::Wykladn() + Dane::czas_symulacji_;
 fprintf(Dane::do_pliku_,"Zdarzenie Nowy Proces... Wykonano! \n");
 fprintf(Dane::do_pliku_, "Nastepny proces zaplanowano o czasie: %f\n\n", czas_ + Dane::czas_symulacji_);
}
