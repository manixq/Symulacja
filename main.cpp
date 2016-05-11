#include "model.h"
#include "moj_random.h"
#include "dane.h"
#include <iostream>
#include <string>
#include <fstream>

int main()
{
 bool restart = true;
 while (restart) {
  Dane::do_pliku_ = fopen(Dane::ZmienNazwe().c_str(), "w");
  restart = false;
  Model* model_symulacji = new Model();
  model_symulacji->Menu();
  model_symulacji->Wykonaj();
  restart = model_symulacji->Powtorzyc();
  Dane::Reset();
  delete model_symulacji;
  fclose(Dane::do_pliku_);
  fclose(Dane::stats_);
 }
 Random::Test();
 std::system("Pause");
}
