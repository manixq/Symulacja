#ifndef SYMULACJA_DOSTEP_DO_IO_H_
#define SYMULACJA_DOSTEP_DO_IO_H_

class ZakonczenieObslugiIO;
class IO;

//Jesli urzadzenia sa nieobslugiwane, to sprawdzamy czy proces czeka w kolejce na obsluge
//Nastepnie proces opuszcza kolejke urzadzenia i zaczyna jego obsluge na czas TPO <1:10>[ms]
//Procesy sa wybierane w kolejnosci od najwyzszego priorytetu
class DostepDoIO
{
public:
 DostepDoIO(IO** io, ZakonczenieObslugiIO* zakonczenie_obslugi_io);
 void Wykonaj(int i);
private:
 IO** io_;
 ZakonczenieObslugiIO* zakonczenie_obslugi_io_;
};
#endif
