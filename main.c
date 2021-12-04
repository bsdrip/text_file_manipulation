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

#define STRMAXSIZE 1000
#define FILEMAXSIZE 12

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
void printToFile(const char*, struct Bor);
void listFile(const char*);
void deleteLine(const char*, int);
void modifyLine(const char*, int, struct Bor);

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



//////////////////////////////// FUNCTIONS ///////////////////////////////////

void modifyLine(const char* file, int modl, struct Bor bor)
{
  char tmpf[FILEMAXSIZE] = "tmp.txt";
  FILE *fp1, *fp2;
  char c;
  char str[STRMAXSIZE];
  int counter = 0;
  fp1 = fopen(file, "r");
  fp2 = fopen(tmpf, "w");
  
  while (!feof(fp1))
  {
    strcpy(str, "\0");
    fgets(str, STRMAXSIZE, fp1);

    if (!feof(fp1))
    {
      counter++;
      if (counter == modl)
      {
        fprintf(fp2, "%s ", bor.boraszat);
        fprintf(fp2, "%i ", bor.terulet);
        fprintf(fp2, "%s ", bor.tipus);
        fprintf(fp2, "%i ", bor.liter);
        fprintf(fp2, "%i ", bor.cukorfok);
        fprintf(fp2, "\n");
      }
      else
      {
        fprintf(fp2, "%s", str);
      }
    }
  }

  fclose(fp1);
  fclose(fp2);

  remove(file);
  rename(tmpf, file);
}


void deleteLine(const char* file, int dell)
{
  char tmpf[FILEMAXSIZE] = "tmp.txt";
  FILE *fp1, *fp2;
  char c;
  char str[STRMAXSIZE];
  int counter = 0;

  fp1 = fopen(file, "r");
  fp2 = fopen(tmpf, "w"); 

  while (!feof(fp1))
  {
    strcpy(str, "\0");
    fgets(str, STRMAXSIZE, fp1);

    if (!feof(fp1))
    {
      counter++;
      if (counter != dell)
      {
        fprintf(fp2, "%s", str);
      }
    }
  }

  fclose(fp1);
  fclose(fp2);

  remove(file);
  rename(tmpf, file);
}


void listFile(const char* file)
{
  FILE *fp;

  char c;

  fp = fopen(file, "r");

  printf("\n");
  c = fgetc(fp);
  while (c != EOF)
  {
    printf("%c", c);
    c = fgetc(fp);
  }

  fclose(fp);
}

void printToFile(const char* file, struct Bor bor)
{
  FILE *fp;

  fp = fopen(file, "a");

  fprintf(fp, "%s ", bor.boraszat);
  fprintf(fp, "%i ", bor.terulet);
  fprintf(fp, "%s ", bor.tipus);
  fprintf(fp, "%i ", bor.liter);
  fprintf(fp, "%i ", bor.cukorfok);
  fprintf(fp, "\n");

  fclose(fp);
}


void readStruct(struct Bor* bor)
{
  printf("  Borászat: "); scanf("%s", bor->boraszat);
  printf("  Terlet: "); scanf("%i", &bor->terulet);
  printf("  Típus: "); scanf("%s", bor->tipus);
  printf("  Liter: "); scanf("%i", &bor->liter);
  printf("  Cukorfok: "); scanf("%i", &bor->cukorfok);
}

void listStruct(struct Bor* bor)
{
  printf("\n%s %i %s %i %i\n", bor->boraszat, bor->terulet, bor->tipus, 
    bor->liter, bor->cukorfok);
}

