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

void SystemKomputerowy::DodajProces(Proces* proces)
{
 kolejki_k_[0]->DodajProces(proces);
}

SJF** SystemKomputerowy::KolejkaK()
{
 return kolejki_k_;
}


