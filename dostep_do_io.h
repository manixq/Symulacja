#ifndef SYMULACJA_DOSTEP_DO_IO_H_
#define SYMULACJA_DOSTEP_DO_IO_H_

class IO;

class DostepDoIO
{
public:
 DostepDoIO(IO** io);
 void Wykonaj();
private:
 IO** io_;
};
#endif
