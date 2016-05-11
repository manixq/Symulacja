#include "moj_random.h"
#include "math.h"
#include <fstream>
#include "dane.h"

int64_t Random :: kernel_ = 0;
int64_t Random :: m_ = 2147483647;
int64_t Random :: a_ = 16807;
double Random :: L_ = 1;


double Random :: Normal()
{
 kernel_ = (kernel_ * a_) % m_;
 return static_cast<double>(kernel_)/m_;
}

double Random :: Normal(int min, int max)
{
 return min + (max-min)*Normal();
}

double Random :: Wykladn()
{
 return ((-1 / L_) * log(Normal()));
}

void Random :: Init(int64_t kernel, double L)
{
 Dane::kernel_ = kernel;
 Dane::L_ = L;
 kernel_ = kernel;
 L_ = L;

 std::string tryb;
 if (Dane::numer_symulacji_)
  tryb = "a";
 else tryb = "w";

 Dane::stats_ = fopen("Statystyki.txt", tryb.c_str());
 fprintf(Dane::stats_, "\nKernel: %d   L: %f \n Sredni czas oczekiwania na procesor w kolejnych iteracjach: ", static_cast<int>(kernel), L);

}


void Random::Test()
{
 kernel_ = 1271;
 L_ = 0.05;
 FILE* normal = fopen("Normal.txt","w");
 for (int i = 0; i < 10000; i++)
 {
  fprintf(normal, "%f ", Normal());
 }
 fclose(normal);

 kernel_ = 1271;
 L_ = 0.05;
 FILE* wyklad = fopen("Wykladn.txt", "w");
 for (int i = 0; i < 10000; i++)
 {
  fprintf(normal, "%f ",Wykladn());
 }
 fclose(wyklad);
}
