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
 int get_tpio();
 int get_tpo();
 int get_priorytet();
 bool get_zadanie_dostepu(); 
 void set_tpio(int x);
 void set_tpo(int x);
 void set_tpw(int x);
 void set_priorytet(double x);
 void set_to(int x);
 void set_zadanie_dostepu(bool x);
private:
 //czas dostepu do procesora zadany przez proces
 int tpw_;
 //czas po ktorym proces zada dostepu do I/O
 int tpio_;
 //czas nieprzerwanego dostepu do I/O
 int tpo_;
 //czas oczekiwania w kolejce do I/O
 int to_;
 //zmienna pomocnicza 
 //jesli proces zada dostepu do I/O - true
 bool zadanie_dostepu_;
 int priorytet_;
};
#endif//SYMULACJA_PROCES_H_
