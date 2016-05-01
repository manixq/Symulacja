#include "moj_random.h"
#include "math.h"
#include <fstream>

int64_t Random::kernel_ = 0;
int64_t Random::m_ = 2147483647;
int64_t Random::a_ = 16807;
double Random::L_ = 1;


double Random::Normal()
{
 kernel_ = (kernel_ * a_) % m_;
 return static_cast<double>(kernel_)/m_;
}

double Random::Normal(int min, int max)
{
 return min + (max-min)*Normal();
}

double Random::Wykladn()
{
 return ((-1 / L_) * log(Normal()));
}

void Random::test()
{
 //wygenerowac spora liczbe zm losowych i zapisac do pliku by sprawdzic wykresy
 std::ofstream off;
 off.open("rand.txt");
 int x;
 for (int i = 0; i < 100000; i++) {
  kernel_ = (kernel_ * a_) % m_;
 // double x=  (1/L_)*log(kernel_);
  x = kernel_;
  x = x % 20;
 
  off << x <<" ";
 }
 off.close();
}

void Random::Init(int64_t kernel, double L)
{
 kernel_ = kernel;
 L_ = L;
}
