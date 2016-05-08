#define _CRT_SECURE_NO_WARNINGS
#include "model.h"
#include "moj_random.h"
#include "dane.h"
#include <iostream>
#include <string>


int main()
{
 bool restart = true;
 while (restart) {
  std::string nazwa = Dane::ZmienNazwe();
  Dane::do_pliku_ = fopen(nazwa.c_str(), "w");
  nazwa = "stats_" + nazwa;
  Dane::stats_ = fopen(nazwa.c_str(), "w");
  restart = false;
  Model model_symulacji;
  model_symulacji.Menu(); 
  model_symulacji.Wykonaj();
  restart = model_symulacji.Powtorzyc();
  fclose(Dane::stats_);
  fclose(Dane::do_pliku_);
  Dane::Reset();
 }
 Random::Test();
 std::system("Pause");
}
