#ifndef SYMULACJA_PROCES_H_
#define SYMULACJA_PROCES_H_

//reprezentuje procesy ktore pojawiaja sie w losowych chwilach
//przyklad stworzenia procesu: Proces p();
class Proces
{
public:
 Proces();
 //funkcje sluza do zwracania i przypisywania zmiennych w obiekcie
 int get_tpw();
 int get_tpo();
 int get_priorytet();
 double get_wiek();
 double get_czas_zgloszen();
 double get_czas_czekania();
 void set_tpo(int x);
 void set_tpw(int x);
 void set_priorytet(double x);
 void set_wiek(double x);
 void set_czas_zgloszen(double x);
 void set_czas_czekania(double x);
private:
 //czas dostepu do procesora zadany przez proces
 int tpw_;

 //czas nieprzerwanego dostepu do I/O
 int tpo_;

 int priorytet_;

 //czas stworzenia procesu
 double wiek_;

 //czas zgloszenia zadania dostepu
 double czas_zgloszen_;

 //czas czekania w kolejce,
 // uzywane takze jako czas uzyskania dostepu do procesora
 double czas_czekania_;
};
#endif//SYMULACJA_PROCES_H_
