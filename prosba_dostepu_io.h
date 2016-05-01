#ifndef  SYMULACJA_PROSBA_DOSTEPU_IO_H
#define SYMULACJA_PROSBA_DOSTEPU_IO_H

class IO;
class Procesor;

class ProsbaDostepuIO
{
public:
 ProsbaDostepuIO(Procesor** procesory,IO** ios);
 void Wykonaj();
 int czas_[2];
private:
 Procesor** procesory_;
 IO** ios_;
};

#endif
