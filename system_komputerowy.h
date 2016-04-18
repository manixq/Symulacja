#ifndef  SYMULACJA_SYSTEM_KOMPUTEROWY_H_
#define SYMULACJA_SYSTEM_KOMPUTEROWY_H_
#include <vector>
#include "procesor.h"
#include "io.h"


//gromadzi wszystkie pozostale elementy systemu
//Przyklad uzycia: SystemKomputerowy sys();
class SystemKomputerowy
{
public:
 SystemKomputerowy();
 ~SystemKomputerowy();
 //wprowadza nowy proces do systemu
 //zaplanuj nowy proces TPG (1:30) <-tu nie wiedzialem jaki przedzial, 
 //ale przy doborze jak wyzej mozna zaobserwowac zapelnianie kolejek - po dluzszym czasie
 void DodajProces();
 //przydziela procesowi pierwszy wolny procesor 
 void PrzydzielProcesor(int x);
 //wybiera urzadzenie i przydziela mu proces
 // w przypadku zajetego urzadzenia, proces trafia do kolejki
 void PrydzielIO(Proces* proces);
 //uaktualniamy czas systemu/zdarzen, priorytet
 void Uaktualnij();
 //zwalniamy urzadzenie i/o
 //w przypadku niepustej kolejki i/o przydzielamy nowy
 void ZwolnijIO(Proces* proces);
 void ZwolnijProcesor(Proces* x);
 //interfejs graficzny sluzacy do testowania symulacji
 void GUI();
 //usuwa aktualne zdarzenie
 void UsunZdarzenie();
 //zwalnia i USUWA proces z systemu
 void Zabij(Proces* proces);
 //Generator Multiplikatywny
 int64_t new_rand();
 //zwraca proces dotyczacy aktualnego zdarzenia
 Proces* ProcesZdarzenia();
 //zwraca tablice w ktorej umieszamy nasze kolejki k1 i k2
 SJF** KolejkaK();
 //zwraca aktualny czas zdarzenia
 double CzasZdarzenia();
 //zwraca rodzaj aktualnego zdarzenia
 Rodzaj_Zdarzenia RodzajZdarzenia();
 //zwraca wartosc true jesli procesor jest w tej chwili wolny
 //tzn obecny_proces == nullptr
 bool WolnyProcesor();
private:
 const int kLiczbaProcesorow_;
 const int kLiczbaIO_;
 std::vector<Procesor*> procesory_;
 std::vector<IO*> io_;
 Kolejka* kolejka_k1_;
 SJF** kolejki_k_;
 KolejkaZdarzen* kolejka_zdarzen_;
 SJF* kolejka_k2_;
 //jadro generatora, seed
 int64_t X0;
 int64_t m;
 int64_t a;
};
#endif
