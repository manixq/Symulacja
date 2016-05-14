#include "model.h"
#include "random.h"
#include "dane.h"
#include <iostream>
#include <string>
#include <fstream>

int main()
{
 bool restart = true;
 while (restart) {
  FILE* do_pliku;
  do_pliku = fopen(Dane::ZmienNazwe().c_str(), "w");
  Dane::SetDoPliku(do_pliku);
  restart = false;
  Model* model_symulacji = new Model();
  model_symulacji->Menu();
  model_symulacji->Wykonaj();
  restart = model_symulacji->Powtorzyc();
  Dane::Reset();
  delete model_symulacji;
  fclose(do_pliku);
  fclose(Dane::GetStats());
 }
 std::system("Pause");
}
