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
   if (nowy_proces_event->czas_ == Dane::czas_symulacji_)
   {
    //w momencie gdy zmienna iteracje jest ujemna,
    //nowe procesy nie wplyna do systemu, a procesy pozostale dokoncza swe dzialanie
    if (iteracje >= 0)
    {
     nowy_proces_event->Wykonaj();
     flaga = true;
    }else  nowy_proces_event->czas_ = -1;
   }

   for (int i = 0; i < 2; i++)
    if (prosba_dostepu_io_event->czas_[i] == Dane::czas_symulacji_)
    {
     prosba_dostepu_io_event->Wykonaj(i);
     flaga = true;
    }

   for (int i = 0; i < 5; i++)
    if (zakonczenie_obslugi_io_event->czas_[i] == Dane::czas_symulacji_)
    {
     zakonczenie_obslugi_io_event->Wykonaj(i);
     flaga = true;
    }

   for (int i = 0; i < 2; i++)
    if (wykoncz_proces_event->czas_[i] == Dane::czas_symulacji_)
    {
     wykoncz_proces_event->Wykonaj(i);
     flaga = true;
    }
   
    for (int i = 0; i < 2; i++)
     if (!moj_system->KolejkaK()[0]->Pusta() || !moj_system->KolejkaK()[1]->Pusta())
     {
      if (p[i]->Wolny())
      {
       wolny_procesor_event->Wykonaj(i);
       flaga = true;
      }
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
  if (!Aktualizuj())
  {
   Dane::Parametry();
   kDoPliku << "            ---Koniec---\n";
   break;
  }
  kDoPliku << "\n--------------------------------------------------------------------\n";
  iteracje--;
 }
}

bool Model::Aktualizuj()
{
 //odstep czasu miedzy zdarzeniami ktorego symulacja nigdy nie przekroczy
 //zapewni nam to poprawne zakonczenie dzialania procesow
 double tmin = Dane::czas_symulacji_ + 100;
 if (nowy_proces_event->czas_ >= 0)
  tmin = nowy_proces_event->czas_;
 for (int i = 0; i < 2; i++)
  if (prosba_dostepu_io_event->czas_[i] >= 0 && prosba_dostepu_io_event->czas_[i] < tmin)
   tmin = prosba_dostepu_io_event->czas_[i];
 for (int i = 0; i < 5; i++)
  if (zakonczenie_obslugi_io_event->czas_[i] >= 0 && zakonczenie_obslugi_io_event->czas_[i] < tmin)
   tmin = zakonczenie_obslugi_io_event->czas_[i];
 for (int i = 0; i < 2; i++)
  if (wykoncz_proces_event->czas_[i] >= 0 && wykoncz_proces_event->czas_[i] < tmin)
   tmin = wykoncz_proces_event->czas_[i];
 if (tmin == Dane::czas_symulacji_ + 100)
  return false;
 tmin = tmin - Dane::czas_symulacji_;
 Dane::czas_symulacji_ += tmin;
 return true;
}
