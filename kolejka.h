#ifndef SYMULACJA_KOLEJKA_H_
#define SYMULACJA_KOLEJKA_H_
#include "proces.h"
#include <queue>

//Atrybut kolejki priorytetowej
class Pole
{
public: 
 Pole();
 Pole(Proces* proces);
private:
 Proces* proces_;
 Pole* nastepne_;
 friend class KolejkaPrio;
 friend class SJF;
};

//Kolejka do kt�rej trafiaj� procesy zwolnione 
//przez procesor z powodu ��dania dost�pu do 
//urz�dze� wej - wyj.Procesy s� w niej pouk�adane
//w zale�no�ci od ich priorytetu.
//uzycie:
//KolejkaPrio kolejka;
//kolejka.DodajProces(p);
class KolejkaPrio
{
public:
 KolejkaPrio();
 virtual ~KolejkaPrio();
 virtual void DodajProces(Proces* proces);

 //uaktualnia priorytety kolejki
 void Uaktualnij();

 //Wyrzuca proces z listy
 //proces NIE JEST trwale usuniety z systemu
 //zwraca wyrzucony proces
 Proces* Wyrzuc();
 //zwraca liczebnosc listy
 virtual int Wielkosc();
protected:
 //liczba procesow w liscie
 int i;
 Pole* lista_;
};

//Kolejka przechowuja procesy zwolnione z urzadzen I/O
//Procesy pouk�adane s� zgodnie z metod� SJF 
//-najpierw najkr�tszy pozosta�y czas.
class SJF:public KolejkaPrio
{
public:
 SJF();
 virtual void DodajProces(Proces* proces);
 virtual ~SJF();
 virtual int Wielkosc();
 virtual Proces* WezProces(int x);
 virtual void UsunProces(int x);
 virtual bool Pusta();
 int i;
};

//kolejka do ktorej trafiaja procesy ktore dopiero
//pojawily sie w systemie i nie mialy jeszcze
//przydzielonego procesora.
//przyklad uzycia K kolejka;
class Kolejka : public SJF
{
public:
 void DodajProces(Proces* proces);
 int Wielkosc();
 Proces* WezProces(int x);
 void UsunProces(int x);
 bool Pusta();
private:
 std::deque<Proces*> lista_;
 int i;
};


#endif
