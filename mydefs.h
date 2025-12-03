#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>


#define BRDSZ 6
#define MAXBRDS 200000
#define MAXSTR (BRDSZ*BRDSZ+BRDSZ+2)

struct board {
   char brd[BRDSZ][BRDSZ];
   char hawkletter;
   int brdcol;
   int brdrow;
   int parent;
};
typedef struct board board;

struct st {
   struct board brd[MAXBRDS];
   int f;
   int e;
};
typedef struct st state;

void space2dash(char* str);
bool spaceafterow(const char* str, int pos);
void removespaces(char* str);


bool brdsize(board* b);
bool brdsizetest(board* b);
bool validhawk(const char *str);
bool validlength(const char *str);
bool validdimensions(const board *b);
bool validletters(const char *str);


bool skipcol(board* b, int col);
bool brdcompleted(board* b);
bool brdcompare(const board* b1, const board* b2);
bool uniquebrd(const state* s, const board* b);
bool hawkpush(state* s, board* b);

void printboard(const board* b);
void findsolutionpath(const state* s, int index);


#include "md.h"
