#include "nowy_proces.h"
#include "moj_random.h"
NowyProces::NowyProces(SystemKomputerowy* sys)
 :czas_(0.0),
  sys_(sys){}

void NowyProces::Wykonaj()
{
 sys_->DodajProces();
 czas_ = Random::Wykladn();
}
