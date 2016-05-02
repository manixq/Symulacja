#include "model.h"
#include "moj_random.h"
#include "dane.h"
int main()
{
 kDoPliku.open("Dane.txt");

 Random::Init(127, 0.2);
 
 Model model_symulacji(1000);
 model_symulacji.Wykonaj(0);


 kDoPliku.close();
 std::system("Pause");
}
