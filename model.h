#ifndef SYMULACJA_MODEL_H_
#define SYMULACJA_MODEL_H_
#include "io.h"
#include "system_komputerowy.h"
#include "dostep_do_io.h"
#include "wolny_procesor.h"
#include "wykoncz_proces.h"
#include "zakonczenie_obslugi_io.h"
#include "nowy_proces.h"
#include "prosba_dostepu_io.h"
#include <fstream>

class Model
{
public:
 //jako argument Modelu podajemy liczbe iteracji
 //gdy model wykona okreslona liczbe iteracji, konczy prace
 Model();
 ~Model();

 //rozpoczynamy symulacje
 void Wykonaj();
 void Menu();

 bool ZdarzenieNowyProces();
 bool ZdarzenieProsbaDostepuIO();
 bool ZdarzenieZakonczenieObslugiIO();
 bool ZdarzenieWykonczProces();
 bool ZdarzenieWolnyProcesor();
 bool ZdarzenieGotoweUrzadzenie();

 //decyduje ot rybie graficznym
 //decyduje o momencie rozpoczecia liczenia statystyk
 void Ustawienia(int ite);
 bool Powtorzyc();
 bool Koniec(int ite);

 //aktualizujemy czasy i priorytety
 //w razie niepowodzenia zwracamy false i konczymy symulacje
 void Aktualizuj();
private:
 double czas_;
 int iteracje_;
 double czas_konca_;

 //liczba procesorow
 const int k_p_;

 //liczba io
 const int k_io_;

 const int k_epsilon_;

 //gui oznacza tryb krokowy
 int gui_;

 IO* io_[5];
 SystemKomputerowy* moj_system_;
 Procesor* p_[2];

 NowyProces* nowy_proces_event_;
 ProsbaDostepuIO* prosba_dostepu_io_event_;
 ZakonczenieObslugiIO* zakonczenie_obslugi_io_event_;
 WykonczProces* wykoncz_proces_event_;
 WolnyProcesor* wolny_procesor_event_;
 DostepDoIO* dostep_do_io_;
};
#endif
