#pragma once

#define STRMAXSIZE 1000
#define FILEMAXSIZE 12

struct Bor
{
  char boraszat[STRMAXSIZE];
  int terulet;
  char tipus[STRMAXSIZE];
  int liter;
  int cukorfok;
  char megfelelt[STRMAXSIZE];
};

size_t numberOfLines(const char*);
void readStruct(struct Bor*);
void listStruct(struct Bor*);
void printToFile(const char*, struct Bor);
void listFile(const char*);
void deleteLine(const char*, int);
void modifyLine(const char*, int, struct Bor);
void checkLine(const char*);
