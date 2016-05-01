#include "model.h"
#include "moj_random.h"
#include "komunikaty.h"
int main()
{
 kDoPliku.open("Dane.txt");

 Random::Init(127, 2.2);
 
 Model model_symulacji(1000);
 model_symulacji.Wykonaj();


 kDoPliku.close();
 std::system("Pause");
}
