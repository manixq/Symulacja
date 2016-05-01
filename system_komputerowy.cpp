#include <cstdio>
#include "system_komputerowy.h"

SystemKomputerowy::SystemKomputerowy()
{
 kolejki_k_ = new SJF*[2];
 kolejki_k_[0] = new Kolejka();
 kolejki_k_[1] = new SJF();
}

SystemKomputerowy::~SystemKomputerowy()
{
 delete kolejki_k_[0];
 delete kolejki_k_[1];
 delete[] kolejki_k_;
}


bool SystemKomputerowy::WolnyProcesor()
{

}



void SystemKomputerowy::DodajProces()
{
 kolejki_k_[0]->DodajProces(new Proces());
}


void SystemKomputerowy::PrzydzielProcesor(int x)
{

}

void SystemKomputerowy::Uaktualnij()
{
 
}

void SystemKomputerowy::ZwolnijIO(Proces* proces)
{
 
}

void SystemKomputerowy::ZwolnijProcesor(Proces* x)
{

}

void SystemKomputerowy::PrydzielIO(Proces* proces)
{

}

void SystemKomputerowy::Zabij(Proces* proces)
{

}

SJF** SystemKomputerowy::KolejkaK()
{
 return kolejki_k_;
}


