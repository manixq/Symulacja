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
  Dane::do_pliku_ = fopen(Dane::ZmienNazwe().c_str(), "w");
  restart = false;
  Model model_symulacji;
  model_symulacji.Menu(); 
  model_symulacji.Wykonaj();
  restart = model_symulacji.Powtorzyc();
  fclose(Dane::do_pliku_);
  Dane::Reset();
 }
 std::system("Pause");
}
