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
 Model(int l_iteracji);
 ~Model();

 //rozpoczynamy symulacje
 //gui oznacza tryb krokowy
 void Wykonaj(bool gui);

 //aktualizujemy czasy i priorytety
 //w razie niepowodzenia zwracamy false i konczymy symulacje
 void Aktualizuj();
private:
 double czas_;
 int iteracje;

 IO* io_[5];
 SystemKomputerowy* moj_system;
 Procesor* p[2];

 NowyProces* nowy_proces_event;
 ProsbaDostepuIO* prosba_dostepu_io_event;
 ZakonczenieObslugiIO* zakonczenie_obslugi_io_event;
 WykonczProces* wykoncz_proces_event;
 WolnyProcesor* wolny_procesor_event;
 DostepDoIO* dostep_do_io;
};
#endif
