#ifndef SYMULACJA_PROCESOR_H_
#define SYMULACJA_PROCESOR_H_
#include "proces.h"


//reprezentuje pojedynczy procesor ktory jest zajmowany przez proces
//uzycie Procesor proc();
//Procesor proc;
//proc.Przydziel(p);
//proc.Zwolnij();
//funkcje nie wymagaja dodatkowego komentarza
class Procesor
{
public:
 Procesor();
 void Przydziel(Proces* x);
 Proces* Zwolnij();
 bool Wolny();
private:
 Proces* obecny_proces_;
};
#endif
