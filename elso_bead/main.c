//
// Szerzo: Szabo Balint
// Feladat: 
// Itt van az ősz .... itt a szüret ideje is. Az "Oprendszer Hegyvidék" bírója (hegybíró) elrendelte, hogy a 
// pontosabb nyilvántartás és a nemkívánatos "csinált bor" háttérbe szorítása miatt minden borászat köteles 
// jelenteni az egyes szüretelt fajták eredményeit. Azaz meg kell adni, hogy melyik borászat, mekkora területről 
// (négyszögölben), milyen típusú szőlőt szüretelt, amiből hány liter, milyen cukorfokú must készült. Például: 
// Öt puttony borászat, 1580 négyszögöl, kékfrankos szőlőből, 2960 liter, 21 cukorfokú mustot készített.
//
// A szüreti eredmény adatokat fájlban tároljuk, az adatfelvételen túl legyen lehetőségünk az adatokon 
// módosítani, törölni vagy  listát készíteni.
//
// Készítsen C nyelvű programot ami  segít a hegybírónak, és ezt a feladatot megoldja, a megoldásnak vagy az
// opsys.inf.elte.hu kiszolgálón, vagy egy hozzá hasonló(linux) rendszeren kell futnia. A megoldást a beadási 
// határidőt követő héten be kell mutatni a gyakorlatvezetőnek.
//



#include <stdio.h>

struct Bor 
{
  char boraszat[1000];
  int terulet;
  char tipus[1000];
  int liter;
  int cukorfok;
};


void read(struct Bor*);
void list(struct Bor*);


int main(void)
{
  
  struct Bor myBor;
  read(&myBor);
  list(&myBor);

  return 0;
}

void read(struct Bor* bor)
{
  printf("Boraszat: "); scanf("%s", bor->boraszat);
  printf("Terulet: "); scanf("%i", &bor->terulet);
  printf("Tipus: "); scanf("%s", bor->tipus);
  printf("Liter: "); scanf("%i", &bor->liter);
  printf("Cukorfok: "); scanf("%i", &bor->cukorfok);
}

void list(struct Bor* bor)
{
  printf("%s %i %s %i %i\n", bor->boraszat, bor->terulet, bor->tipus, bor->liter, bor->cukorfok);
}
