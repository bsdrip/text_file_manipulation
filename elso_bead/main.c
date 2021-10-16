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
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STRMAXSIZE 1000

struct Bor 
{
  char boraszat[STRMAXSIZE];
  int terulet;
  char tipus[STRMAXSIZE];
  int liter;
  int cukorfok;
};


void readStruct(struct Bor*);
void listStruct(struct Bor*);
void printToFile(char*, struct Bor);
void listFile(char*);

int main(void)
{

  struct Bor temp;
  char file[12] = "log/log.txt";
  
  // menu
  char choice[STRMAXSIZE];
  do 
  {
  printf("\
      \n  Mit szeretnel?\n\
      (l) lista keszitese\n\
      (f) adatok felvetele\n\
      (m) adatok modositasa\n\
      (t) adatok torlese\n\
      (e) log torlese\n\
      (x) kilepes\n\
      l/f/m/t/x: "); scanf("%s", &choice);
  
    switch (choice[0])
    {
    case 'l':
      if (access(file, F_OK))
      {
        printf("Log file is empty.\n");
      }
      else 
      {
        listFile(file);
      }
      break;
      
    case 'f':
      readStruct(&temp);
      printToFile(file, temp);
      listFile(file);
      break;

    case 'e':
      remove(file);
    
//    case 'm':
//      break;
//    
//    case 't':
//      break;
    }
  } while (choice[0] != 'x');


  return 0;
}



//////////////////////////////////////////// FUNCTIONS ///////////////////////////////////////////

void listFile(char filename[100])
{
  FILE *file;

  char c;

  file = fopen(filename, "r");

  if (file == NULL)
  {
    printf("Cannot open file.\n");
    exit (0);
  }

  c = fgetc(file);
  while (c != EOF)
  {
    printf("%c", c);
    c = fgetc(file);
  }

  fclose(file);
}

void printToFile(char filename[100], struct Bor bor)
{
  FILE *outfile;

  outfile = fopen(filename, "a");

  if (outfile == NULL)
  {
    fprintf(stderr, "\nFile cannot be opened\n");
    exit (1);
  }

  //fprintf(outfile, "%u ", SERIAL);
  fprintf(outfile, "%s ", bor.boraszat);
  fprintf(outfile, "%i ", bor.terulet);
  fprintf(outfile, "%s ", bor.tipus);
  fprintf(outfile, "%i ", bor.liter);
  fprintf(outfile, "%i ", bor.cukorfok);
  fprintf(outfile, "\n");

  if (fwrite != 0)
  {
    printf ("Succcess!\n");
  }
  else
  {
    printf("Error.\n");
  }

  fclose(outfile);
}


void readStruct(struct Bor* bor)
{
  printf("Boraszat: "); scanf("%s", bor->boraszat);
  printf("Terulet: "); scanf("%i", &bor->terulet);
  printf("Tipus: "); scanf("%s", bor->tipus);
  printf("Liter: "); scanf("%i", &bor->liter);
  printf("Cukorfok: "); scanf("%i", &bor->cukorfok);
}

void listStruct(struct Bor* bor)
{
  printf("%s %i %s %i %i\n", bor->boraszat, bor->terulet, bor->tipus, bor->liter, bor->cukorfok);
}
