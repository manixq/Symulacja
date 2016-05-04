#include "model.h"
#include "moj_random.h"
#include "dane.h"
#include <iostream>


int main()
{
 int64_t kernel;
 double L;
 int iter;
 bool restart = true;
 while (restart) {
  restart = false;
  kDoPliku.open("Dane.txt");
  std::cout << "\n\nPodaj kernel (np. 127): ";
  std::cin >> kernel;
  std::cout << "Podaj intensywnosc L (np. 0.1): ";
  std::cin >> L;
  std::cout << "Podaj ilosc iteracji (np. 1000): ";
  std::cin >> iter;

  int x;
  std::cout << "\nSymulacja Natychmiastowa: Wprowadz '0'\n";
  std::cout << "Symulacja Krok po kroku: Wprowadz '1'\n";
  std::cout << "Wybierasz:  ";
  std::cin >> x;

  Random::Init(kernel, L);
  Model model_symulacji(iter);
  model_symulacji.Wykonaj(x);

  std::cout << "\nPonowic Symulacje: '1'\n";
  std::cout << "Wyjdz: '0'\n";
  std::cout << "Wybierasz:  ";
  std::cin >> restart;

  kDoPliku.close();
  Dane::Reset();
 }
 std::system("Pause");
}
