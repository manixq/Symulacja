#ifndef SYMULACJA_DANE_H_
#define  SYMULACJA_DANE_H_
#include <fstream>
#include <string>
class Procesor;
class IO;
class SystemKomputerowy;

//Klasa sluzaca do zbierania wynikow i wypisywania niektorych komunikator
//klasa wykonuje niektore obliczenia by ulatwic prezentacje wynikow
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

 //funkcje do zapisu danych dla roznych plikow
 static void ZapiszDoPliku(char buffer[]);

 //zeruje statystyki i rozpoczoczyna ich zbior
 static void Ustawienia();

 //funkcje get||set by zachowac enkapsulacje
 static void SetStacjonarnosc(int stat);
 static void SetCzasPomiarow(double czas);
 static void SetCzasSymulacji(double czas);
 //SetCzasPracyProcesora(numer procesora, czas);
 static void SetCzasPracyProcesora(int i,double czas);
 static void SetCalkLiczbaProcesow(int i);
 static void SetCalkCzasPrzetwarzania(double czas);
 static void SetCalkCzasOczek(double czas);
 static void SetMaxCzasOczek(double czas);
 static void SetKernel(int x);
 static void SetL(double L);
 static void SetCalkCzasOdpowiedz(double czas);
 static void SetIloscOdpowiedzi(int i);
 static void SetNumerSymulacji(int n);

 static void SetDoPliku(FILE* plik);
 static void SetStats(FILE* plik);

 static int GetStacjonarnosc();
 static double GetCzasPomiarow();
 static double GetCzasSymulacji();
 //GetCzasPracyProcesora(numer procesora);
 static double GetCzasPracyProcesora(int i);
 static int GetCalkLiczbaProcesow();
 static double GetCalkCzasPrzetwarzania();
 static double GetCalkCzasOczek();
 static double GetMaxCzasOczek();
 static double GetCalkCzasOdpowiedz();
 static int GetIloscOdpowiedzi();
 static int GetNumerSymulacji();

 static FILE* GetStats();
 static FILE* GetDoPliku();

 static void SetCzasIteracje(double czas, int iteracje);
private:
 static int stacjonarnosc_;

 static double przepustowosc_;
 static double przetwarzanie_;

 //czas trwania pomiaru
 static double czas_pomiarow_;

 //calkowity czas symulacji
 static double czas_symulacji_;

 static bool wyzeruj_wyniki_;

 //czas jaki procesor jest uzywany przez procesy
 static double czas_pracy_procesora_[2];

 //liczba mowiaca ile stworzylismy procesow
 static int calk_liczba_procesow_;

 //suma czasu jaki uplywa miedzy zgloszeniem procesu do systemu,
 //a jego zakonczeniem (czas zycia wszystkich procesow)
 static double calk_czas_przetwarzania_;

 //suma czasu oczekiwania na procesor przez procesy oraz counter
 static double calk_czas_oczek_na_procesor_;
 static double max_czas_oczek_;

 //parametry generatora
 static int kernel_;
 static double L_;

 static int liczba_iteracji_;
 static double czas_konca_;

 //czas miedzy zgloszeniem zadania dostepu do jednego z urzadzen io
 //i jego otrzymaniem (czas spedzony w kolejkach io przez wszystkie procesy)
 //oraz counter
 static double calk_czas_odpowiedzi_;
 static int ilosc_odpowiedzi_;
 
 static int numer_symulacji_;

 //plik do zapisywania danych - step by step
 static FILE* do_pliku_;

 //plik do koncowych statystyk
 static FILE* stats_;
};
#endif
