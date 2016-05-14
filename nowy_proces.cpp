#include "nowy_proces.h"
#include "random.h"
#include "dane.h"

NowyProces::NowyProces(SystemKomputerowy* sys)
 :czas_(0.0),
  sys_(sys){}

void NowyProces::Wykonaj()
{
 Proces* proces = new Proces;
 proces->set_wiek(Dane::GetCzasSymulacji());
 proces->set_czas_czekania(Dane::GetCzasSymulacji());
 sys_->DodajProces(proces);
 czas_ = Random::Wykladn(4) + Dane::GetCzasSymulacji();
 fprintf(Dane::GetDoPliku(),"Zdarzenie Nowy Proces... Wykonano! \n");
 fprintf(Dane::GetDoPliku(), "Nastepny proces zaplanowano o czasie: %f\n\n", czas_);
}
