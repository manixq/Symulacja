#ifndef SYMULACJA_WOLNY_PROCESOR_H_
#define SYMULACJA_WOLNY_PROCESOR_H_

class WykonczProces;
class ProsbaDostepuIO;
class Procesor;
class SystemKomputerowy;
//Gdy mamy wolny procesor to przydzielamy mu proces
//z jednej z kolejek(o ile nie sa puste).
//Proces przydzielany jest na czas TPK <1:50>[ms]
//Ustawiamy czas TPIO <0,TPK0>[ms] dla zdarzenia ProsbaDostepuIO
//jesli TPIO == 0, to nie inicjujemy zdarzenia ProsbaDostepuIO
class WolnyProcesor
{
public:
 WolnyProcesor(SystemKomputerowy* sys, Procesor** p, ProsbaDostepuIO* prosba_dostepu_io, WykonczProces* wykoncz_proces);
 void Wykonaj(int i);
private:
 SystemKomputerowy* sys_;
 Procesor** p_;
 ProsbaDostepuIO* prosba_dostepu_io_;
 WykonczProces* wykoncz_proces_;
};
#endif
