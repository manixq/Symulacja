#ifndef SYMULACJA_DANE_H_
#define  SYMULACJA_DANE_H_
#include <fstream>
#include <string>
class Procesor;
class IO;
class SystemKomputerowy;

class Dane
{
public:

 //wypisuje w konsoli stan systemu krok po kroku
 static void GUI(Procesor** procesory, IO** io, SystemKomputerowy* sys);

 //generuje nowa nazwe pliku do ktorego zapisujemy wyniki
 static std::string ZmienNazwe();

 //wypisuje w konsoli i do pliku "Parametry.txt"
 //obliczenia symulacyjne
 static void Parametry(bool gui);
 static void Reset();

 //calkowity czas symulacji
 static double czas_symulacji_;

 //czas jaki procesor jest uzywany przez procesy
 static double czas_pracy_procesora_[2];

 //liczba mowiaca ile stworzylismy procesow
 static int calk_liczba_procesow_;

 //suma czasu jaki uplywa miedzy zgloszeniem procesu do systemu,
 //a jego zakonczeniem (czas zycia wszystkich procesow)
 static double calk_czas_przetwarzania_;

 //suma czasu oczekiwania na procesor przez procesy oraz counter
 static double calk_czas_oczek_na_procesor_;
 static int ilosc_oczek_na_procesor_;


 //parametry generatora
 static int kernel_;
 static double L_;

 //czas miedzy zgloszeniem zadania dostepu do jednego z urzadzen io
 //i jego otrzymaniem (czas spedzony w kolejkach io przez wszystkie procesy)
 //oraz counter
 static double calk_czas_odpowiedzi_;
 static int ilosc_odpowiedzi_;

 static int numer_symulacji_;
 static FILE* do_pliku_;
};
#endif
