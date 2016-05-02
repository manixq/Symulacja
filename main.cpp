#include "model.h"
#include "moj_random.h"
#include "dane.h"
#include <iostream>


int main()
{
 int64_t kernel;
 double L;
 int iter;

 kDoPliku.open("Dane.txt");
 std::cout << "Podaj kernel (np. 127): ";
 std::cin >> kernel;
 std::cout << "/nPodaj intensywnosc L (np. 0.1): ";
 std::cin >> L;
 std::cout << "/nPodaj ilosc iteracji (np. 1000): ";
 std::cin >> iter;

 system("cls");

 int x;
 std::cout << "Symulacja Natychmiastowa: WprowadŸ '0'\n";
 std::cout << "Symulacja Krok po kroku: WprowadŸ '1'\n";
 std::cout << "Wybierasz:  ";
 std::cin >> x;
 
 system("cls");

 Random::Init(kernel, L);
 Model model_symulacji(iter);
 model_symulacji.Wykonaj(x);

 kDoPliku.close();
 std::system("Pause");
}
