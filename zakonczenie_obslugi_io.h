#ifndef SYMULACJA_ZAKONCZENIE_OBSLUGI_IO_H_
#define SYMULACJA_ZAKONCZENIE_OBSLUGI_IO_H_

class SystemKomputerowy;
class IO;

//Pobudzone przez czas TPO
//Zdarzenie oznacza zakonczenie obslugi urzadzenia I/O
//Zwalnia urzadzenie, a proces kieruje do kolejki SJF
class ZakonczenieObslugiIO
{
public:
 ZakonczenieObslugiIO(IO** io, SystemKomputerowy* sys);
 void Wykonaj(int i);
 double czas_[5];
private:
 IO** io_;
 SystemKomputerowy* sys_;
};
#endif
