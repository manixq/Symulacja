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

//kolejka dla procesow zadajacych dostepu do urzadzenia I/O
//uzycie: KolejkaPrio kolejka;
class KolejkaPrio
{
public:
 KolejkaPrio();
 virtual ~KolejkaPrio();
 virtual void DodajProces(Proces* proces);
 void Uaktualnij(double x);
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
};

enum Rodzaj_Zdarzenia
{
 BRAK = 0,
 NOWY_PROCES,
 PROSBA_DOSTEPU_IO,
 ZAKONCZENIE_OBSLUGI_IO,
 WYKONCZ_PROCES
};

//atrybut listy jednokierunkowej uzywanej do obslugi zdarzen
class Zdarzenie
{
public:
 Zdarzenie();
 Zdarzenie(Rodzaj_Zdarzenia rodzaj_zdarzenia, double czas, Proces* proces);
 Zdarzenie(Rodzaj_Zdarzenia rodzaj_zdarzenia, double czas, Proces* proces, Zdarzenie* nastepne_zdarzenie);
private:
 double czas_;
 Proces *proces_;
 Zdarzenie *nastepny_;
 Rodzaj_Zdarzenia rodzaj_zdarzenia_;
 friend class KolejkaZdarzen;
};

//lista jednokierunkowa w ktorej przechowujemy zdarzenia
//zwracane zmienne jako najwczesniejsze rozumiemy obecne
class KolejkaZdarzen
{
public:
 KolejkaZdarzen();
 ~KolejkaZdarzen();
 //zwraca czas wystapienia zdarzenia
 double WezCzas();
 //zwraca rodzaj najwczesniejszego(obecnego) zdarzenia
 Rodzaj_Zdarzenia WezRodzaj();
 bool Pusta();
 //zwraca proces najwczesniejszego zdarzenia
 Proces* WezProces();
 //wypisuje wszystkie zdarzenia
 //potrzebne wylacznie w celut testownia za pomoca GUI
 void Wypisz();
 void DodajZdarzenie(Rodzaj_Zdarzenia rodzaj_zdarzenia, double czas, Proces* proces);
 void UsunZdarzenie();
 //Modyfikuje||uaktualnie czas wszystkich zdarzen
 void UaktualnijCzas();
private:
 Zdarzenie* head_zdarzenie_;
};

#endif
