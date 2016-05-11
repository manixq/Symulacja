#include "model.h"
#include "moj_random.h"
#include "dane.h"
#include <iostream>
#include <stdio.h>
#include <fstream>

Model::Model()
 : czas_(0.0),
   iteracje_(60000),
   k_p_(2),
   k_io_(5),
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
  fprintf(Dane::do_pliku_,"\n\n      ---Czas Systemu: %f ---\n", Dane::czas_symulacji_);
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
  Ustawienia(ite);
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
 std::cout << "\n\nPodaj kernel (np. 1129): ";
 std::cin >> kernel;
 fprintf(Dane::do_pliku_, "Kernel: %d\n", kernel);
 std::cout << "Podaj intensywnosc L (np. 0.073): ";
 std::cin >> L;
 fprintf(Dane::do_pliku_, "L: %f\n", L);
 std::cout << "Podaj ilosc iteracji (np. 50 000): ";
 std::cin >> iteracje_;
 fprintf(Dane::do_pliku_, "Liczba iteracji: %d\n",iteracje_);
 std::cout << "\nPominac faze przejsciowa:\n tak - 0\n nie - 1\nWybierasz: ";
 std::cin >> Dane::stacjonarnosc_;
 
 std::cout << "\nSymulacja Natychmiastowa: Wprowadz '0'\n";
 std::cout << "Symulacja Krok po kroku: Wprowadz '1'\n";
 std::cout << "Wybierasz:  ";
 std::cin >> gui_;
 Random::Init(kernel, L);
}

bool Model::ZdarzenieNowyProces()
{
 if (abs(nowy_proces_event_->czas_ - Dane::czas_symulacji_) < 0.00001)
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
  if (abs(prosba_dostepu_io_event_->czas_[i] - Dane::czas_symulacji_) < 0.00001)
  {
   prosba_dostepu_io_event_->Wykonaj(i);
   wykonano =  true;
  }
 return wykonano;
}

bool Model::ZdarzenieZakonczenieObslugiIO()
{
 bool wykonano = false;
 for (int i = 0; i < k_io_; i++)
  if (abs(zakonczenie_obslugi_io_event_->czas_[i] - Dane::czas_symulacji_) < 0.00001)
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
  if (abs(wykoncz_proces_event_->czas_[i] - Dane::czas_symulacji_) < 0.00001)
  {
   wykoncz_proces_event_->Wykonaj(i);
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
   dostep_do_io_->Wykonaj(i);
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
 if (ite >= 10000 && !(Dane::stacjonarnosc_))
 {
  Dane::stacjonarnosc_ = 1;
  Dane::czas_pomiarow_ = 0.0;
  Dane::max_czas_oczek_ = 0.0;
  Dane::czas_pracy_procesora_[0] = 0.0;
  Dane::czas_pracy_procesora_[1] = 0.0;
  Dane::calk_czas_przetwarzania_ = 0.0;
  Dane::calk_czas_oczek_na_procesor_ = 0.0;
  Dane::calk_czas_odpowiedzi_ = 0.0;
  Dane::calk_liczba_procesow_ = 0;
  Dane::ilosc_odpowiedzi_ = 0;
  Dane::ilosc_oczek_na_procesor_ = 0;
 }
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

bool Model::Koniec(int ite)
{
 if (ite >= iteracje_) {
  fprintf(Dane::do_pliku_, "            ---Koniec---\n");
  return true;
 }
 return false;
}

void Model::Aktualizuj()
{
  double tmin = nowy_proces_event_->czas_;
 for (int i = 0; i < 2; i++)
  if (prosba_dostepu_io_event_->czas_[i] >= 0 && prosba_dostepu_io_event_->czas_[i] < tmin)
   tmin = prosba_dostepu_io_event_->czas_[i];
 for (int i = 0; i < 5; i++)
  if (zakonczenie_obslugi_io_event_->czas_[i] >= 0 && zakonczenie_obslugi_io_event_->czas_[i] < tmin)
   tmin = zakonczenie_obslugi_io_event_->czas_[i];
 for (int i = 0; i < 2; i++)
  if (wykoncz_proces_event_->czas_[i] >= 0 && wykoncz_proces_event_->czas_[i] < tmin)
   tmin = wykoncz_proces_event_->czas_[i];

 tmin = tmin - Dane::czas_symulacji_;
 Dane::czas_symulacji_ += tmin;
 Dane::czas_pomiarow_ += tmin;
}
