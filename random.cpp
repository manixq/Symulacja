#include "random.h"
#include "math.h"
#include <fstream>
#include "dane.h"

int64_t Random::kernel_[] = { 0, 0, 0, 0, 0, 0, 0 };
int64_t Random::kernel_next_ = 0;
int64_t Random :: m_ = 2147483647;
int64_t Random :: a_ = 16807;
double Random :: L_ = 1;
bool Random::test_ = 1;

double Random :: Normal(int i)
{
 kernel_[i] = (kernel_[i] * a_) % m_;
 return static_cast<double>(kernel_[i])/m_;
}

double Random :: Normal(int min, int max, int i)
{
 return min + (max-min)*Normal(i);
}

double Random :: Wykladn(int i)
{
 return ((-1 / L_) * log(Normal(i)));
}

void Random :: Init(int64_t kernel, double L)
{
 Dane::SetKernel(kernel);
 Dane::SetL(L);
 if(test_)
  Test(kernel);
 kernel_[0] = kernel;
 for (int i = 1; i < 7; i++)
 {
  kernel_[i] = kernel_[i - 1];
  for (int j = 0; j < 200000; j++)
   kernel_[i] = (kernel_[i] * a_) % m_;
 }
 kernel_next_ = kernel_[6];
 L_ = L;

 for (int i = 0; i < 200000; i++)
  kernel_next_ = (kernel_next_ * a_) % m_;

 std::string tryb;
 if (Dane::GetNumerSymulacji())
  tryb = "a";
 else tryb = "w";
 FILE* stats;
 stats = fopen("Statystyki.txt", tryb.c_str());
 Dane::SetStats(stats);
 fprintf(stats, "\nKernel: %d   L: %f \n Sredni czas oczekiwania na procesor w kolejnych iteracjach: ", static_cast<int>(kernel), L);
}

void Random::Test(int64_t kernel)
{
 kernel_[0] = 1117;
 for (int i = 1; i < 7; i++)
 {
  kernel_[i] = kernel_[i - 1];
  for (int j = 0; j < 200000; j++)
   kernel_[i] = (kernel_[i] * a_) % m_;
 }
 L_ = 0.05;
 FILE* normal = fopen("Normal.txt", "w");
 for (int j = 0; j < 7; j++)
 {
  for (int i = 0; i < 10000; i++)
  {
   fprintf(normal, "%f ", Normal(j));
  }
  fprintf(normal, "\n");
 }
 fclose(normal);

 kernel_[0] = 1271;
 L_ = 0.05;
 FILE* wyklad = fopen("Wykladn.txt", "w");
 for (int j = 0; j < 7; j++)
 {
  for (int i = 0; i < 10000; i++)
  {
   fprintf(normal, "%f ", Wykladn(j));
  }
  fprintf(normal, "\n");
 }
 fclose(wyklad);
 test_ = 0;
}

int64_t Random::KernelNext()
{
 return kernel_next_;
}
