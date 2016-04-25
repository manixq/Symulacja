#include "moj_random.h"
#include "math.h"

Random::Random(int64_t kernel):X0_(kernel), m_(2147483647), a_(16807), L_(60)
{
 //Generator Multiplikatywny
}

int64_t Random::Normal()
{
 X0_ = (X0_ * a_) % m_;
 return X0_;
}

int64_t Random::Wykladn()
{
 X0_ = (X0_ * a_) % m_;
 return ((-1 / L_) * log(X0_));
}

void Random::test()
{
 //wygenerowac spora liczbe zm losowych i zapisac do pliku by sprawdzic wykresy
}
