#include "system_komputerowy.h"
#include <ctime>
#include "moj_random.h"
#include <fstream>

int main()
{
 Random r(77);
 //r.test();
 Proces* ptr_proces;
 double TPG = r.Wykladn();
 bool flaga=false;
 int tick = 10000;
 SystemKomputerowy moj_system;
 printf("\n*******************************************************************\n");
 std::ofstream of;
 of.open("plik.txt");
 do
 { 
  printf("\nKomunikaty:\n");
  flaga = false;
  moj_system.Uaktualnij();
 
   //pojawienie sie procesu
   if (moj_system.RodzajZdarzenia() == NOWY_PROCES && moj_system.CzasZdarzenia() == 0)
   {
    moj_system.UsunZdarzenie();
    if(tick >=0)
    moj_system.DodajProces();
    flaga = true;
   }

   //zakonczenie obslugi urzadzenia i/o
   if (moj_system.RodzajZdarzenia() == ZAKONCZENIE_OBSLUGI_IO && moj_system.CzasZdarzenia() == 0)
   {
    ptr_proces = moj_system.ProcesZdarzenia();
    moj_system.UsunZdarzenie();
    moj_system.ZwolnijIO(ptr_proces);
    flaga = true;
   }

   //zadanie dostepu do urzarzenia i/o
   if (moj_system.RodzajZdarzenia() == PROSBA_DOSTEPU_IO && moj_system.CzasZdarzenia() == 0)
   {
    ptr_proces = moj_system.ProcesZdarzenia();
    moj_system.UsunZdarzenie();  
    moj_system.ZwolnijProcesor(ptr_proces);  
    if(ptr_proces->get_zadanie_dostepu())
     //przydzielenie do io
     moj_system.PrydzielIO(ptr_proces);
    flaga = true;
   }

   //Jakis proces otrzymal czas TPIO==0 i dlatego trzeba go teraz zabic
   if (moj_system.RodzajZdarzenia() == WYKONCZ_PROCES && moj_system.CzasZdarzenia() == 0)
   {
    moj_system.Zabij(moj_system.ProcesZdarzenia());
    moj_system.UsunZdarzenie();
    flaga = true;
   }

   //przydzielenie procesora
   if (moj_system.WolnyProcesor())
   {
    if (!moj_system.KolejkaK()[0]->Pusta() && !moj_system.KolejkaK()[1]->Pusta()) {
     int x = r.Normal() % 2;
     moj_system.PrzydzielProcesor(x);
     flaga = true;
    }
    else if (!moj_system.KolejkaK()[0]->Pusta())
    {
     moj_system.PrzydzielProcesor(0);
     flaga = true;
    }
    else if (!moj_system.KolejkaK()[1]->Pusta())
    {
     moj_system.PrzydzielProcesor(1);
     flaga = true;
    }
   }

   tick--;
   if(tick>=0)
   of << moj_system.OutL() << " ";
 

 //tryb graficzy - step by step
  moj_system.GUI();
 // std::system("Pause");
 } while (flaga);
 of.close();
 std::system("Pause");
}
