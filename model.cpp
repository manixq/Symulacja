#include "model.h"
#include "moj_random.h"
#include "dane.h"

Model::Model(int l_iteracji)
 : czas_(0.0),
   iteracje(l_iteracji)
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


void Model::Wykonaj(bool gui)
{
 bool flaga = true;
 for (;;)
 {
  kDoPliku << "      ---Czas Systemu: " << Dane::czas_symulacji_ << "---\n";
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

  if(gui)
   Dane::GUI(p, io_, moj_system);
  Dane::Parametry(gui);
  kDoPliku << "\n--------------------------------------------------------------------\n";

  if(iteracje)
   iteracje--;
  else{
   kDoPliku << "            ---Koniec---\n";
   fclose(Dane::file);
   break;
  }
  Aktualizuj();
 }
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
