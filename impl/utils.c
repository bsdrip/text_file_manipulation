#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "../headers/utils.h"

char * changeWord(const char * str, const char * find, const char * replace)
{
  char* dest = malloc(strlen(str) - strlen(find) + strlen(replace) + 1);
  char* destptr = dest;

  *dest = 0;

  while (*str)
  {
    if (!strncmp(str, find, strlen(find)))
    {
      strcat(destptr, replace);
      str += strlen(find);
      destptr += strlen(replace);
    }
    else
    {
      *destptr = *str;
      destptr++;
      str++;
    }
    *destptr = 0;
  }
  return dest;
}

void passed(const char * file, int ln, int yn)
{
  char tmpf[FILEMAXSIZE] = "tmp.txt";
  FILE *fp1, *fp2;
  char c;
  char str[STRMAXSIZE];
  int counter = 0;
  char* sentence = NULL;
  fp1 = fopen(file, "r");
  fp2 = fopen(tmpf, "w");

  const char pass[STRMAXSIZE] = "Megfelelt";
  const char fail[STRMAXSIZE] = "Megbukott";
  const char none[STRMAXSIZE] = "NUL";
  while (!feof(fp1))
  {
    strcpy(str, "\0");
    fgets(str, STRMAXSIZE, fp1);

    if (!feof(fp1))
    {
      counter++;
      if (counter == ln)
      {
        if (strstr(str, pass))
        {
          if (yn == 1) 
          { 
            sentence = changeWord(str, pass, fail); 
            fprintf(fp2, "%s", sentence);
          }
          else if (yn == 0)
          {
            fprintf(fp2, "%s", str);
          }
        }
        else if (strstr(str, fail))
        {
          if (yn == 0) 
          { 
            sentence = changeWord(str, fail, pass); 
            fprintf(fp2, "%s", sentence);
          }
          else if (yn == 1)
          {
            fprintf(fp2, "%s", str);
          }
        }
        else if (strstr(str, "NULL"))
        {
          if (yn == 1) 
          { 
            sentence = changeWord(str, "NULL", fail); 
            fprintf(fp2, "%s", sentence);
          }
          else if (yn == 0)
          {
            sentence = changeWord(str, "NULL", pass); 
            fprintf(fp2, "%s", sentence);
          }
        }
      }
      else
      {
        fprintf(fp2, "%s", str);
      }
    }
  }

  free(sentence);
  fclose(fp1);
  fclose(fp2);

  remove(file);
  rename(tmpf, file);
}

void checkLine(const char * file, int ln)
{
  int passd;
  int randn;
  int fd1[2];
  int fd2[2];

  pid_t p;

  if (pipe(fd1) == -1)
  {
    fprintf(stderr, "Pipe 1 failed\n");
    exit(1);
  }

  if (pipe(fd2) == -1)
  {
    fprintf(stderr, "Pipe 2 failed\n");
    exit(1);
  }

  p = fork();

  if (p < 0)
  {
    fprintf(stderr, "Fork failed\n");
    exit(1);
  }
  
  if (p > 0)
  {
    close(fd1[0]);
    int n = rand() % ln + 1;
    randn = n;
    write(fd1[1], &n, sizeof(int));
    close(fd1[1]);

    wait(NULL);
    close(fd2[1]);
    int yn;
    read(fd2[0], &yn, sizeof(int));
    passd = yn;
    close(fd2[0]);
  }
  else
  {
    close(fd1[1]);
    int child_n;
    read(fd1[0], &child_n, sizeof(int));
    int ten = rand() % 10 + 1;
    if (ten == 1)
    { 
      int yn = 1;
      write(fd2[1], &yn, sizeof(int));
      close(fd2[1]);
    }
    else
    {
      int yn = 0;
      write(fd2[1], &yn, sizeof(int));
      close(fd2[1]);
    }
    close(fd2[0]);
    close(fd1[0]);
    exit(0);
  } 
  passed(file, randn, passd);
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
  fprintf(fp, "%s ", "NULL");
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
