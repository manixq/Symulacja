#ifndef SYMULACJA_DANE_H_
#define  SYMULACJA_DANE_H_
#include "fstream"
class Procesor;
class IO;
class SystemKomputerowy;
extern std::ofstream kDoPliku;

class Dane
{
public:
 static void GUI(Procesor** procesory, IO** io, SystemKomputerowy* sys);
 static void Parametry();
 static double czas_symulacji_;
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
};
#endif
