#ifndef  SYMULACJA_SYSTEM_KOMPUTEROWY_H_
#define SYMULACJA_SYSTEM_KOMPUTEROWY_H_
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

 //zwalnia i USUWA proces z systemu
 void Zabij(Proces* proces);

 //zwraca tablice w ktorej umieszamy nasze kolejki k1 i k2
 SJF** KolejkaK();


 //zwraca wartosc true jesli procesor jest w tej chwili wolny
 //tzn obecny_proces == nullptr
 bool WolnyProcesor();

private:
 SJF** kolejki_k_;
};
#endif
