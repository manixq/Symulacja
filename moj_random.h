#ifndef SYMULACJA_MOJ_RANDOM_H_
#define SYMULACJA_MOJ_RANDOM_H_
#include <cstdint>

class Random
{
public:
 Random(int64_t kernel);//TODO kernel 127 
 int64_t Normal();
 int64_t Wykladn();
 
 void test();//funkcja do testow - koniecznie skasowac <-------------------------------------------

private:
 //jadro generatora, seed
 int64_t X0_;
 int64_t m_;
 int64_t a_; 
 //L_ musi byc takie by rozklad wykladniczy nie generowal procesow czesciej niz co 50ms
 int64_t L_;
};
#endif

