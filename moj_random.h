#ifndef SYMULACJA_MOJ_RANDOM_H_
#define SYMULACJA_MOJ_RANDOM_H_
#include <cstdint>

class Random
{
public:
 //generuje liczbe losowa <0:1>
 //o rozkladzie rownomiernym
 static double Normal();

 //generuje liczbe losowa <min:max>
 //o rozkladzie rownomiernym
 static double Normal(int min, int max);

 //generuje liczbe losowa 
 //o rozkladzie wykladniczym
 static double Wykladn();

 //tutaj inicjalizuje seed oraz intensywnosc L
 static void Init(int64_t kernel, double L);

 //testowanie generatorów
 static void Test();

 //jadro generatora, seed
 static int64_t kernel_;
 static int64_t m_;
 static int64_t a_; 

 //L_ musi byc tak dobrane by procesy nie czekaly dluzej niz 50ms
 static double L_;
};
#endif

