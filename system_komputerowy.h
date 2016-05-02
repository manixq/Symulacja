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
 void DodajProces(Proces* proces);

 //zwraca tablice w ktorej umieszamy nasze kolejki k1 i k2
 SJF** KolejkaK();

private:
 SJF** kolejki_k_;
};
#endif
