#ifndef SYMULACJA_WOLNY_PROCESOR_H_
#define SYMULACJA_WOLNY_PROCESOR_H_

class Procesor;
class SystemKomputerowy;

class WolnyProcesor
{
public:
 WolnyProcesor(SystemKomputerowy* sys, Procesor** p);
 void Wykonaj();
private:
 SystemKomputerowy* sys_;
 Procesor** p_;
};
#endif
