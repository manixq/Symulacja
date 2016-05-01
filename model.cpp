#include "model.h"
#include "moj_random.h"
#include "komunikaty.h"

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
 zakonczenie_obslugi_io_event = new ZakonczenieObslugiIO(io_);
 wykoncz_proces_event = new WykonczProces(p);
 wolny_procesor_event = new WolnyProcesor(moj_system, p);
 dostep_do_io = new DostepDoIO(io_);
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
 

 while (iteracje >= 0)
 {

  if (nowy_proces_event->czas_ == 0.0) nowy_proces_event->Wykonaj();

  for (int i = 0; i < 2; i++)
   if (prosba_dostepu_io_event->czas_[i] == 0) prosba_dostepu_io_event->Wykonaj();

  for (int i = 0; i < 5; i++)
   if (zakonczenie_obslugi_io_event->czas_[i]) zakonczenie_obslugi_io_event->Wykonaj();

  for (int i = 0; i < 2; i++)
   if (wykoncz_proces_event->czas_[i]) wykoncz_proces_event->Wykonaj();

  for (int i = 0; i < 2; i++)
   if (p[i]->Wolny()) wolny_procesor_event->Wykonaj();

  for (int i = 0; i < 5; i++)
   if (io_[i]->Wolny())dostep_do_io->Wykonaj();

  iteracje--;
 }
}
