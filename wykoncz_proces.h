#ifndef SYMULACJA_WYKONCZ_PROCES_H_
#define SYMULACJA_WYKONCZ_PROCES_H_

class Procesor;

class WykonczProces
{
public:
 WykonczProces(Procesor** p);
 void Wykonaj();
 int czas_[2];
private:
 Procesor** p_;
};
#endif
