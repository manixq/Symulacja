#ifndef SYMULACJA_RANDOM_H_
#define SYMULACJA_RANDOM_H_
#include <cstdint>

class Random
{
public:
 //generuje liczbe losowa <0:1>
 //o rozkladzie rownomiernym
 //argument numerem generatora
 static double Normal(int i);

 //generuje liczbe losowa <min:max>
 //o rozkladzie rownomiernym
 //argument numerem generatora
 static double Normal(int min, int max, int i);

 //generuje liczbe losowa 
 //o rozkladzie wykladniczym
 //argument numerem generatora
 static double Wykladn(int i);

 //tutaj inicjalizuje seed oraz intensywnosc L
 static void Init(int64_t kernel, double L);

 //testowanie generatorów
 static void Test(int64_t kernel);


private:
 //jadro generatora, seed
 //6 - TPW
 //5 - losowanie z kolejki do procesora
 //4 - TPG
 //3 - wybor kolejki do procesorow
 //2 - TPO
 //1 - numer urzadzenia
 //0 - SJF
 static int64_t kernel_[7];

 static int64_t kernel_next_;
 static int64_t m_;
 static int64_t a_; 

 //L_ musi byc tak dobrane by procesy nie czekaly dluzej niz 50ms
 static double L_;
 static bool test_;
};
#endif

