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
  Model model_symulacji;
  model_symulacji.Menu(); 
  Dane::stats_ = fopen("Statystyki_1.txt", "a");
  model_symulacji.Wykonaj();
  restart = model_symulacji.Powtorzyc();
  fclose(Dane::do_pliku_);
  Dane::Reset();

  fclose(Dane::stats_);
 }
 Random::Test();
 std::system("Pause");
}
