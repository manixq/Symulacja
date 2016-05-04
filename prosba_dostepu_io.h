#ifndef  SYMULACJA_PROSBA_DOSTEPU_IO_H
#define SYMULACJA_PROSBA_DOSTEPU_IO_H


class IO;
class Procesor;

//Zdarzenie generowane przez czas TPIO 
//zwalnia procesor oraz dodaje jego proces do kolejki io
//gdy TPIO == 0 to nie prosimy o dostep do urzadzenia io
//w konstruktorze podajemy wskaznik do tablicy procesorw i urzadzen I/O
class ProsbaDostepuIO
{
public:
 ProsbaDostepuIO(Procesor** procesory,IO** ios);

 //Wybiera losowo urzadzenie
 //zwalnia procesor
 //umieszcza proces w kolejce urzadzenia
 //jako argument num podajemy numer procesora 
 void Wykonaj(int num);
 double czas_[2];
private:
 Procesor** procesory_;
 IO** ios_;
};

#endif
