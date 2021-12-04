//
// Szerzo: Szabo Balint
// Feladat: lásd: README.md
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
  size_t line_num;

  line_num = numberOfLines(file);

  do 
  {
  printf("\n################################################\
      \n  Mit szeretnél?\n\
      (l) lista keszítése\n\
      (f) adatok felvétele\n\
      (m) adatok módosítasa\n\
      (t) adatok törlése\n\
      (e) log törlése\n\
      (c) ellenőrzés\n\
      (x) kilépés\n\
      l/f/m/t/c/x: "); scanf("%s", choice);
  
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
        printf("\n  Módosítani kívánt sor sorszáma: ");
        scanf("%i", &n);
        while (n >= line_num || n < 1) {
          printf("  Csak 0-nál nagyobb, illetve a sorok számánál nem nagyobb számot adhatsz meg: ");
          scanf("%i", &n);
        }
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
        printf("\n  Törölni kívánt sor sorszáma: ");
        scanf("%i", &n);
        while (n >= line_num || n < 1) {
          printf("  Csak 0-nál nagyobb, illetve a sorok számánál nem nagyobb számot adhatsz meg: ");
          scanf("%i", &n);
        }
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
    case 'c':
      if (access(file, F_OK))
      {
        printf("\n  Log fájl nem létezik. Létrehozható adatfelvétellel (f).\n");
      }
      else 
      {
        listFile(file);
        printf("\n  A számadó útnak indult.\n");
        checkLine(file);
        listFile(file);
      }
    break;
    }
  } while (choice[0] != 'x');


  return 0;
}
