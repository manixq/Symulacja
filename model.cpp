#include "model.h"
#include "random.h"
#include "dane.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

Model::Model()
 : czas_(0.0),
   iteracje_(60000),
   czas_konca_(200000),
   k_p_(2),
   k_io_(5),
   k_epsilon_(0.00001),
   gui_(0)
{
 for (int i = 0; i < k_io_; i++)
  io_[i] = new IO();
 moj_system_ = new SystemKomputerowy();
 p_[0] = new Procesor();
 p_[1] = new Procesor();

 nowy_proces_event_ = new NowyProces(moj_system_);
 prosba_dostepu_io_event_ = new ProsbaDostepuIO(p_, io_);
 zakonczenie_obslugi_io_event_ = new ZakonczenieObslugiIO(io_, moj_system_);
 wykoncz_proces_event_ = new WykonczProces(p_);
 wolny_procesor_event_ = new WolnyProcesor(moj_system_, p_, prosba_dostepu_io_event_, wykoncz_proces_event_);
 dostep_do_io_ = new DostepDoIO(io_, zakonczenie_obslugi_io_event_);
}
Model::~Model()
{

 for (int i = 0; i < k_io_; i++)
  delete io_[i];
 
 delete moj_system_;
 delete p_[0];
 delete p_[1];

 delete nowy_proces_event_;
 delete prosba_dostepu_io_event_;
 delete zakonczenie_obslugi_io_event_;
 delete wykoncz_proces_event_;
 delete wolny_procesor_event_;
 delete dostep_do_io_;
}


void Model::Wykonaj()
{
 int ite = 0;
 bool flaga = true;
 for (;;)
 {
  fprintf(Dane::GetDoPliku(),"\n\n      ---Czas Systemu: %f ---\n", Dane::GetCzasSymulacji());
  flaga = true;
  while (flaga)
  {
   flaga = false;

   if (ZdarzenieNowyProces())
    flaga = true;

   if (ZdarzenieProsbaDostepuIO())
    flaga = true;

   if (ZdarzenieZakonczenieObslugiIO())
    flaga = true;

   if (ZdarzenieWykonczProces())
    flaga = true;
   
   if (ZdarzenieWolnyProcesor())
    flaga = true;

   if (ZdarzenieGotoweUrzadzenie())
    flaga = true;
  }

  //tu zmienilem w petli uwaga
  Ustawienia(ite);

  //tu tez zmienialem, dobrze sprwadzic
  if (Koniec(ite))
   break;
  Aktualizuj();
  ite++;
 }
}

void Model::Menu()
{
 int kernel = 1123;
 double L = 0.073;
 int stacjonarnosc;
 std::cout << "\n\nPodaj kernel (np. 1129): ";
 std::cin >> kernel;
 fprintf(Dane::GetDoPliku(), "Kernel: %d\n", kernel);
 std::cout << "Podaj intensywnosc L (np. 0.073): ";
 std::cin >> L;
 fprintf(Dane::GetDoPliku(), "L: %f\n", L);
 std::cout << "Podaj ilosc iteracji dla procesow (np. 50 000): ";
 std::cin >> iteracje_;
 std::cout << "Podaj czas symulacji (np. 200 000): ";
 std::cin >> czas_konca_;

 Dane::SetCzasIteracje(czas_konca_, iteracje_);

 fprintf(Dane::GetDoPliku(), "Liczba iteracji: %d\n",iteracje_);
 std::cout << "\nLiczba zakonczonych procesow wymagana do rozpoczecia rejetrowania wynikow:\n(0 - od poczatku)\nWybierasz: ";
 std::cin >> stacjonarnosc; Dane::SetStacjonarnosc(stacjonarnosc);
 
 
 std::cout << "\nSymulacja Natychmiastowa: Wprowadz '0'\n";
 std::cout << "Symulacja Krok po kroku: Wprowadz '1'\n";
 std::cout << "Wybierasz:  ";
 std::cin >> gui_;
 Random::Init(kernel, L);
}

bool Model::ZdarzenieNowyProces()
{
 if (abs(nowy_proces_event_->czas_ - Dane::GetCzasSymulacji()) <= k_epsilon_)
 {
  nowy_proces_event_->Wykonaj();
  return true;
 }
 return false;
}

bool Model::ZdarzenieProsbaDostepuIO()
{
 bool wykonano = false;
 for (int i = 0; i < k_p_; i++)
  if (abs(prosba_dostepu_io_event_->czas_[i] - Dane::GetCzasSymulacji()) <= k_epsilon_)
  {
   prosba_dostepu_io_event_->Wykonaj(i, czas_konca_);
   wykonano =  true;
  }
 return wykonano;
}

bool Model::ZdarzenieZakonczenieObslugiIO()
{
 bool wykonano = false;
 for (int i = 0; i < k_io_; i++)
  if (abs(zakonczenie_obslugi_io_event_->czas_[i] - Dane::GetCzasSymulacji()) <= k_epsilon_)
  {
   zakonczenie_obslugi_io_event_->Wykonaj(i);
   wykonano = true;
  }
 return wykonano;
}

bool Model::ZdarzenieWykonczProces()
{
 bool wykonano = false;
 for (int i = 0; i < k_p_; i++)
  if (abs(wykoncz_proces_event_->czas_[i] - Dane::GetCzasSymulacji()) <= k_epsilon_)
  {
   wykoncz_proces_event_->Wykonaj(i, iteracje_, czas_konca_);
   wykonano = true;

   
  }
 return wykonano;
}

bool Model::ZdarzenieWolnyProcesor()
{
 bool wykonano = false;
 for (int i = 0; i < k_p_; i++)
  if ((!moj_system_->KolejkaK()[0]->Pusta() || !moj_system_->KolejkaK()[1]->Pusta()) && p_[i]->Wolny())
  {
   wolny_procesor_event_->Wykonaj(i);
   wykonano = true;
  }
 return wykonano;
}

bool Model::ZdarzenieGotoweUrzadzenie()
{
 bool wykonano = false;
 for (int i = 0; i < k_io_; i++)
 {
  if (io_[i]->Wolny() && io_[i]->WielkoscKolejki())
  {
   dostep_do_io_->Wykonaj(i, iteracje_);
   wykonano = true;
  }
 }
 return wykonano;
}

void Model::Ustawienia(int ite)
{
 if (gui_)
  Dane::GUI(p_, io_, moj_system_);
 Dane::Parametry(gui_);

 //ustawienie rejestrowania wynikow
 Dane::Ustawienia();
 
}

bool Model::Powtorzyc()
{
 bool restart = 1;
 std::cout << "\nPonowic Symulacje: '1'\n";
 std::cout << "Wyjdz: '0'\n";
 std::cout << "Wybierasz:  ";
 std::cin >> restart;
 std::cout << "\n--------------------------------------\n";
 return restart;
}

bool Model::Koniec(int ite)
{
 if (Dane::GetCalkLiczbaProcesow() >= iteracje_ && Dane::GetCzasSymulacji() >= czas_konca_) {
  fprintf(Dane::GetDoPliku(), "            ---Koniec---\n");
  return true;
 }
 return false;
}

void Model::Aktualizuj()
{
  double tmin = nowy_proces_event_->czas_;
 for (int i = 0; i < k_p_; i++)
  if (prosba_dostepu_io_event_->czas_[i] >= 0 && prosba_dostepu_io_event_->czas_[i] < tmin)
   tmin = prosba_dostepu_io_event_->czas_[i];
 for (int i = 0; i < k_io_; i++)
  if (zakonczenie_obslugi_io_event_->czas_[i] >= 0 && zakonczenie_obslugi_io_event_->czas_[i] < tmin)
   tmin = zakonczenie_obslugi_io_event_->czas_[i];
 for (int i = 0; i < k_p_; i++)
  if (wykoncz_proces_event_->czas_[i] >= 0 && wykoncz_proces_event_->czas_[i] < tmin)
   tmin = wykoncz_proces_event_->czas_[i];

 tmin = tmin - Dane::GetCzasSymulacji();
 Dane::SetCzasSymulacji(Dane::GetCzasSymulacji() + tmin);
 Dane::SetCzasPomiarow(Dane::GetCzasPomiarow() + tmin);
}
