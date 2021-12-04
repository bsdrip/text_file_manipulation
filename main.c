//
// Szerzo: Szabo Balint
// Feladat: 
// Itt van az ősz .... itt a szüret ideje is. Az "Oprendszer Hegyvidék" bírója 
// (hegybíró) elrendelte, hogy a pontosabb nyilvántartás és a nemkívánatos 
// "csinált bor" háttérbe szorítása miatt minden borászat köteles jelenteni az 
// egyes szüretelt fajták eredményeit. Azaz meg kell adni, hogy melyik 
// borászat, mekkora területről (négyszögölben), milyen típusú szőlőt 
// szüretelt, amiből hány liter, milyen cukorfokú must készült. Például: 
// Öt puttony borászat, 1580 négyszögöl, kékfrankos szőlőből, 2960 liter, 21 
// cukorfokú mustot készített.
//
// A szüreti eredmény adatokat fájlban tároljuk, az adatfelvételen túl legyen 
// lehetőségünk az adatokon módosítani, törölni vagy  listát készíteni.
//
// Készítsen C nyelvű programot ami  segít a hegybírónak, és ezt a feladatot 
// megoldja, a megoldásnak vagy az opsys.inf.elte.hu kiszolgálón, vagy egy 
// hozzá hasonló(linux) rendszeren kell futnia. A megoldást a beadási határidőt 
// követő héten be kell mutatni a gyakorlatvezetőnek.
//


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "headers/utils.h"

int main(void)
{
  struct Bor temp;
  const char file[FILEMAXSIZE] = "log.txt";
  
  char choice[STRMAXSIZE];
  do 
  {
  printf("\n################################################\
      \n  Mit szeretnél?\n\
      (l) lista keszítése\n\
      (f) adatok felvétele\n\
      (m) adatok modosítasa\n\
      (t) adatok törlése\n\
      (e) log törlése\n\
      (x) kilépés\n\
      l/f/m/t/x: "); scanf("%s", choice);
  
  int n; 
    switch (choice[0])
    {
    case 'l':
      if (access(file, F_OK))
      {
        printf("\n  Log fájl nem létezik. Létrehozható adatfelvétellel (f).\n");
      }
      else 
      {
        printf("\n  Log fájl tartalma:\n");
        listFile(file);
      }
      break;
      
    case 'f':
      readStruct(&temp);
      printToFile(file, temp);
      listStruct(&temp);
      break;

    case 'm':
      if (access(file, F_OK))
      {
        printf("\n  Log fájl nem létezik. Létrehozható adatfelvétellel (f).\n");
      }
      else 
      {
        listFile(file);
        printf("\n  Melyik sort szeretnéd módosítani?\n");
        scanf("%i", &n);
        printf("\n  Add meg az új paramétereket a sornak:\n");
        readStruct(&temp);
        listStruct(&temp);
        modifyLine(file, n, temp);
      }
      break;
    
    case 't':
      if (access(file, F_OK))
      {
        printf("\n  Log fájl nem létezik. Létrehozható adatfelvétellel (f).\n");
      }
      else 
      {
        listFile(file);
        printf("\n  Melyik sort szeretnéd törölni?\n");
        scanf("%i", &n);
        deleteLine(file, n);
      }
      break;

    case 'e':
      if (access(file, F_OK))
      {
        printf("\n  Log fájl nem létezik. Létrehozható adatfelvétellel (f).\n");
      }
      else 
      {
        printf("\n  Log fájl törölve.\n");
        remove(file);
      }
      break;
    }
  } while (choice[0] != 'x');


  return 0;
}
