#ifndef  SYMULACJA_SYSTEM_KOMPUTEROWY_H_
#define SYMULACJA_SYSTEM_KOMPUTEROWY_H_
#include <vector>
#include "procesor.h"
#include "io.h"
#include "moj_random.h"

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
 //zwraca proces dotyczacy aktualnego zdarzenia
 Proces* ProcesZdarzenia();
 //zwraca tablice w ktorej umieszamy nasze kolejki k1 i k2
 SJF** KolejkaK();
 //zwraca aktualny czas zdarzenia
 double CzasZdarzenia();
 double OutL();
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
 Random* r;
 //liczba zakonczonych procesow
 int proc_killed_;
 //licba zgloszonych do io
 int io_call_;
 //czas dzialania systemu
 double caly_czas_;
 //czas wykorzystywania procesora
 double zuzycie_[2];
 //czas miedzy zgloszeniem procesu do systemu a jego smiercia
 double czas_przetwarzania_;
 //czas miedzy zgloszeniem io a odpowiedzia
 double czas_odpowiedzi_;
 //laczny czas oczekiwania  w kolejce
 double czas_czekania_;
};
#endif
