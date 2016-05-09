#include "model.h"
#include "moj_random.h"
#include "dane.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

Model::Model()
 : czas_(0.0), iteracje(80000),
   gui(0)
{
 for (int i = 0; i < 5; i++)
  io_[i] = new IO();
 moj_system = new SystemKomputerowy();
 p[0] = new Procesor();
 p[1] = new Procesor();

 nowy_proces_event = new NowyProces(moj_system);
 prosba_dostepu_io_event = new ProsbaDostepuIO(p, io_);
 zakonczenie_obslugi_io_event = new ZakonczenieObslugiIO(io_, moj_system);
 wykoncz_proces_event = new WykonczProces(p);
 wolny_procesor_event = new WolnyProcesor(moj_system, p, prosba_dostepu_io_event, wykoncz_proces_event);
 dostep_do_io = new DostepDoIO(io_, zakonczenie_obslugi_io_event);
}
Model::~Model()
{
 for (int i = 0; i < 5; i++)
  delete io_[i];
 delete moj_system;
 delete p[0];
 delete p[1];

 delete nowy_proces_event;
 delete prosba_dostepu_io_event;
 delete zakonczenie_obslugi_io_event;
 delete wykoncz_proces_event;
 delete wolny_procesor_event;
 delete dostep_do_io;
}


void Model::Wykonaj()
{
 bool flaga = true;
 for (;;)
 {
  fprintf(Dane::do_pliku_,"\n\n      ---Czas Systemu: %f ---\n", Dane::czas_symulacji_);
  flaga = true;
  while (flaga)
  {
   flaga = false;
   if (abs(nowy_proces_event->czas_ - Dane::czas_symulacji_) < 0.00001)
   {
     nowy_proces_event->Wykonaj();
     flaga = true;
   }

   for (int i = 0; i < 2; i++)
    if (abs(prosba_dostepu_io_event->czas_[i] - Dane::czas_symulacji_) < 0.00001)
    {
     prosba_dostepu_io_event->Wykonaj(i);
     flaga = true;
    }

   for (int i = 0; i < 5; i++)
    if (abs(zakonczenie_obslugi_io_event->czas_[i] - Dane::czas_symulacji_) < 0.00001)
    {
     zakonczenie_obslugi_io_event->Wykonaj(i);
     flaga = true;
    }

   for (int i = 0; i < 2; i++)
    if (abs(wykoncz_proces_event->czas_[i] - Dane::czas_symulacji_) < 0.00001)
    {
     wykoncz_proces_event->Wykonaj(i);
     flaga = true;
    }
   
    for (int i = 0; i < 2; i++)
     if ((!moj_system->KolejkaK()[0]->Pusta() || !moj_system->KolejkaK()[1]->Pusta()) && p[i]->Wolny())
     {
       wolny_procesor_event->Wykonaj(i);
       flaga = true;
     }

   for (int i = 0; i < 5; i++)
   {
    if (io_[i]->Wolny() && io_[i]->WielkoscKolejki())
    {
     dostep_do_io->Wykonaj(i);
     flaga = true;
    }
   }
  }
  if (gui)
   Dane::GUI(p, io_, moj_system);
  Dane::Parametry(gui);
  if (!iteracje) {
   fprintf(Dane::do_pliku_, "            ---Koniec---\n");
   break;
  }
  Aktualizuj();
  iteracje--;
 }
}

void Model::Menu()
{
 int kernel;
 double L= 0.073;
 std::cout << "\n\nPodaj kernel (np. 1271): ";
 std::cin >> kernel;
 fprintf(Dane::do_pliku_, "Kernel: %d\n", kernel);
 std::cout << "Podaj intensywnosc L (np. 0.072): ";
 std::cin >> L;
 fprintf(Dane::do_pliku_, "L: %f\n", L);
 std::cout << "Podaj ilosc iteracji (np. 1000): ";
 std::cin >> iteracje;
 fprintf(Dane::do_pliku_, "Liczba iteracji: %d\n",iteracje);
 std::cout << "\nSymulacja Natychmiastowa: Wprowadz '0'\n";
 std::cout << "Symulacja Krok po kroku: Wprowadz '1'\n";
 std::cout << "Wybierasz:  ";
 std::cin >> gui;
 Random::Init(kernel, L);

 std::string tryb;
 if (Dane::numer_symulacji_)
   tryb = "a";
 else tryb = "w";
 
  Dane::stats_ = fopen("Statystyki_1.txt", tryb.c_str());
  fprintf(Dane::stats_, "%%Kernel: %d   L: %f \n x%d=[", kernel, L,Dane::numer_symulacji_);
  fclose(Dane::stats_);

  Dane::stats_ = fopen("Statystyki_2.txt", tryb.c_str());
  fprintf(Dane::stats_, "Kernel: %d   L: %f \n", kernel, L);
  fclose(Dane::stats_);
 

}

bool Model::Powtorzyc()
{
 bool restart = 1;
 std::cout << "\nPonowic Symulacje: '1'\n";
 std::cout << "Wyjdz: '0'\n";
 std::cout << "Wybierasz:  ";
 std::cin >> restart;
 return restart;
}


void Model::Aktualizuj()
{
  double tmin = nowy_proces_event->czas_;
 for (int i = 0; i < 2; i++)
  if (prosba_dostepu_io_event->czas_[i] >= 0 && prosba_dostepu_io_event->czas_[i] < tmin)
   tmin = prosba_dostepu_io_event->czas_[i];
 for (int i = 0; i < 5; i++)
  if (zakonczenie_obslugi_io_event->czas_[i] >= 0 && zakonczenie_obslugi_io_event->czas_[i] < tmin)
   tmin = zakonczenie_obslugi_io_event->czas_[i];
 for (int i = 0; i < 2; i++)
  if (wykoncz_proces_event->czas_[i] >= 0 && wykoncz_proces_event->czas_[i] < tmin)
   tmin = wykoncz_proces_event->czas_[i];

 tmin = tmin - Dane::czas_symulacji_;
 Dane::czas_symulacji_ += tmin;
}
