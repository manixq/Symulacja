#include "proces.h"
#include <cstdio>

Proces::Proces():
 tpw_(0),
 tpo_(0),
 priorytet_(0),
 wiek_(0.0),
 czas_zgloszen_(0.0),
 czas_czekania_(0.0)
{
 ////printf("[SYSTEM]: stworzono Proces\n");
}

int Proces::get_tpw()
{
 return tpw_;
}

int Proces::get_tpo()
{
 return tpo_;
}

int Proces::get_priorytet()
{
 return priorytet_;
}

double Proces::get_wiek()
{
 return wiek_;
}

double Proces::get_czas_zgloszen()
{
 return czas_zgloszen_;
}

double Proces::get_czas_czekania()
{
 return czas_czekania_;
}
void Proces::set_tpo(int x)
{
 tpo_ = x;
}

void Proces::set_tpw(int x)
{
 tpw_ = x;
}

void Proces::set_priorytet(double x)
{
 priorytet_ = x;
}

void Proces::set_wiek(double x)
{
 wiek_ = x;
}

void Proces::set_czas_czekania(double x)
{
 czas_czekania_ = x;
}

void Proces::set_czas_zgloszen(double x)
{
 czas_zgloszen_ = x;
}
