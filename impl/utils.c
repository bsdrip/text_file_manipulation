#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../headers/utils.h"

void checkLine(const char * file)
{
  // implement this
}

void modifyLine(const char * file, int modl, struct Bor bor)
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
        fprintf(fp2, "%s ", bor.megfelelt);
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


void deleteLine(const char * file, int dell)
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


void listFile(const char * file)
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

void printToFile(const char * file, struct Bor bor)
{
  FILE *fp;
  fp = fopen(file, "a");

  fprintf(fp, "%s ", bor.boraszat);
  fprintf(fp, "%i ", bor.terulet);
  fprintf(fp, "%s ", bor.tipus);
  fprintf(fp, "%i ", bor.liter);
  fprintf(fp, "%i ", bor.cukorfok);
  fprintf(fp, "%s ", "Nem ellenorzott");
  fprintf(fp, "\n");

  fclose(fp);
}


void readStruct(struct Bor * bor)
{
  printf("  Borászat: "); scanf("%s", bor->boraszat);
  printf("  Terlet: "); scanf("%i", &bor->terulet);
  printf("  Típus: "); scanf("%s", bor->tipus);
  printf("  Liter: "); scanf("%i", &bor->liter);
  printf("  Cukorfok: "); scanf("%i", &bor->cukorfok);
}

void listStruct(struct Bor * bor)
{
  printf("\n%s %i %s %i %i\n", bor->boraszat, bor->terulet, bor->tipus,
    bor->liter, bor->cukorfok);
}

size_t numberOfLines(const char * file)
{ 
  FILE *fp;
  char c;
  size_t counter = 0;
  fp = fopen(file, "r");
  if (fp != NULL) {
    while ((c = fgetc(fp)) != EOF)
    {
      if (c == '\n')
      {
        counter++;
      }
    }
  }

  fclose(fp);
  if (counter == 0)
  {
    printf("\n  Log fájl nem létezik. Létrehozható adatfelvétellel (f).\n");
  }
  else
  {
    printf("\n  Log fájlban lévő sorok száma: %lu\n", counter);
  }

  return counter;
}
