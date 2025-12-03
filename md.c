#include "mydefs.h"
void space2dash(char* str) { 
int length = strlen(str);
   for (int i = 0; i < length; i++) { 
       if (str[i] == '\n') { 
           str[i] = '-'; 
       }
       
   }
   str[length-1] = '\0'; 
} 

bool spaceafterow(const char* str, int pos) {
   return isupper(str[pos - 1]) && isupper(str[pos + 1]);
}

void removespaces(char* str) {
   int i = 0, j = 0;
   while (str[i] != '\0') {
       if (str[i] != ' ' || spaceafterow(str, i)) {
           str[j++] = str[i];
       }
       i++;
   }
   str[j] = '\0';
}

bool file2str(const char* fname, char* str) {
   FILE* file = fopen(fname, "rt");
   if (file == NULL) {
       return false;
   }

   int i = 0;
   char ch;

   while ((ch = fgetc(file)) != EOF) {
       str[i++] = ch;
   }

   str[i] = '\0';
   fclose(file);
   if(str == NULL){
       return false;
   }
   removespaces(str);
   space2dash(str);
   return true;
}

bool brdsize(board* b) {
   b->brdcol = 0;
   b->brdrow = 0;

   for (int row = 0; row < BRDSZ; row++) {
       int col = 0;
       while (col < BRDSZ && b->brd[row][col] != '\0') {
           col++;
       }
       if (col > 0) {
           b->brdrow++;
       }
       if (col > b->brdcol) {
           b->brdcol = col;
       }
   }
   if(brdsizetest(b)){
       return true;
   } else{
       return false;
   }
}

bool brdsizetest(board* b) {
   if (b->brdrow <= 0 || b->brdrow > BRDSZ) {
       return false;
   }
   if (b->brdcol <= 0 || b->brdcol > BRDSZ) {
       return false;
   }
   return true;
}

bool validhawk(const char *str) {
   if(isupper(str[0]) && str[1] == '-'){
       return true;
   }
   return false;
}


bool validletters(const char *str) {
   int i = 0;
   while (str[i] != '\0') {
       if (!(isupper(str[i]) || str[i] == '-')) {
           return false;
       }
       i++;
   }
   return true; 
}

bool validdimensions(const board *b) {
   int row_count = 0;

   for (int row = 0; row < BRDSZ; row++) {
       int col_count = 0;
       int col = 0;
       while (col < BRDSZ && b->brd[row][col] != '\0') {
           col_count++;
           col++;
       }
       if (col_count > 0) {
           row_count++;
           if (col_count != b->brdcol) {
               return false;
           }
       }
   }
   return row_count == b->brdrow;
}

state* str2state(const char* str) {
   board b = {0};
   state* s = calloc(1, sizeof(state));

   s->f = 0;
   s->e = -1;

   if (str == NULL || s == NULL) {
       return NULL;
   }

   b.hawkletter = str[0];
   if(!validhawk(str) || !validletters(str)){
   free(s);
       return NULL;
   }

   int row = 0, col = 0;
   for (int i = 2; str[i] != '\0'; i++) {
       if (str[i] == '-') {
           row++;
           col = 0;
       } else if (row < BRDSZ && col < BRDSZ) {
           b.brd[row][col++] = str[i];
       }
   }

   brdsize(&b);
   if(!brdsize(&b) || !validdimensions(&b)){
   free(s);
       return NULL;
   }
   s->brd[++s->e] = b;
   return s;
}

bool skipcol(board*b, int col) {
   for (int row = 1; row < b->brdrow; row++) {
       if (b->brd[row][col] != b->brd[0][col]) {
           return false;
       }
   }
   return true;
}

bool brdcompleted(board* b) {
   for (int col = 0; col < b->brdcol; col++) {
       if (!skipcol(b, col)) {
           return false;
       }
   }
   return true;
}

bool brdcompare(const board* b1, const board* b2) {
   if (b1->hawkletter != b2->hawkletter || b1->brdrow != b2->brdrow || b1->brdcol != b2->brdcol) {
       return false;
   }
   for (int row = 0; row < b1->brdrow; row++) {
       for (int col = 0; col < b1->brdcol; col++) {
           if (b1->brd[row][col] != b2->brd[row][col]) {
               return false;
           }
       }
   }
   return true;
}

bool uniquebrd(const state* s, const board* b) {
   for (int i = 0; i <= s->e; i++) {
       if (brdcompare(&s->brd[i], b)) {
           return false;
       }
   }
   return true;
}

bool hawkpush(state* s, board* b) {
   for (int col = 0; col < b->brdcol; col++) {
       if (!skipcol(b, col)) {
           board newboard = *b;
           char newhawkletter = newboard.brd[newboard.brdrow - 1][col];

           for (int row = newboard.brdrow - 1; row > 0; row--) {
               newboard.brd[row][col] = newboard.brd[row - 1][col];
           }

           newboard.brd[0][col] = newboard.hawkletter;
           newboard.hawkletter = newhawkletter;
           newboard.parent = s->f;

           if (s->e + 1 < MAXBRDS && uniquebrd(s, &newboard)) { 
               s->e++;
               s->brd[s->e] = newboard;
           }
       }
   }
   return true;
   if(s == NULL){
       return false;
   }
}

int cntletters(const board* b) {
   int cnt = 0;
   for (int row = 0; row < b->brdrow; row++) {
       for (int col = 0; col < b->brdcol; col++) {
           if (b->brd[row][col] != '\0') {
               cnt++;
           }
       }
   }
   return cnt;
}

bool hawkpushtest(state *s, board* b) {
   board originalbrd = *b;
   int originallettercnt = cntletters(b);
   bool result = hawkpush(s, b);
   if (!result) {
       return false;
   }
   board* newbrd = &s->brd[s->e];
   if (newbrd->brdrow != originalbrd.brdrow || newbrd->brdcol != originalbrd.brdcol) {
       return false;
   }
   int newlettercnt = cntletters(newbrd);
   if (originallettercnt != newlettercnt) {
       return false;
   }
   for (int col = 0; col < b->brdcol; col++) {
       if (!skipcol(&originalbrd, col)) {
           if (newbrd->brd[0][col] != originalbrd.hawkletter) {
               return false;
           }
           if (newbrd->hawkletter != originalbrd.brd[originalbrd.brdrow - 1][col]) {
               return false;
           }
           for (int row = 1; row < originalbrd.brdrow; row++) {
               if (newbrd->brd[row][col] != originalbrd.brd[row - 1][col]) {
                   return false;
               }
           }
       }
   }
   return true;
}


int movescalc(const state* s, int index) {
   int moves = 0;

   while (index != 0) {
       index = s->brd[index].parent;
       moves++;
   }
   return moves;
}

void printboard(const board* b) {
   for (int row = 0; row < b->brdrow; row++) {
       for (int col = 0; col < b->brdcol; col++) {
           putchar(b->brd[row][col]);
       }
       putchar('\n');
   }
}

void findsolutionpath(const state* s, int index) {
   int path[MAXBRDS];
   int path_len = 0;

   while (index != 0) {
       path[path_len++] = index;
       index = s->brd[index].parent;
   }
   path[path_len++] = 0;

   for (int i = path_len - 1; i >= 0; i--) {
       printboard(&s->brd[path[i]]);
       printf("\n");
   }
}

int solve(state* s, bool verbose) { 
   if(s == NULL)
   if (brdcompleted(&s->brd[0])) {
       if (verbose) {
           printboard(&s->brd[0]);
       }
       return 0;
   }

   while (s->f <= s->e) {
       board* current_board = &s->brd[s->f];
       if (brdcompleted(current_board)) {
           int moves = movescalc(s, s->f);

           if (verbose) {
               findsolutionpath(s, s->f);
           }
           return moves;
       }
       hawkpush(s, current_board);
       s->f++;
   }
   return -1;
}

void test(void){
  char str[MAXSTR];
  state* s;

   //String Testing
  //NULL file
  strcpy(str, "");
  s = str2state(str);
  assert(s == NULL);
  free(s);

  //Space in File After New line and in middle of board was tested in given files

  //Board Testing
  //Same Letter
  strcpy(str, "A-AAA-AAA-AAA-AAA");
  s = str2state(str);
  assert(s);
  assert(solve(s, false)==0);
  free(s);

  //Edge Case Match
  strcpy(str, "A-BAD-BAD-BCD");
  s = str2state(str);
  assert(s);
  assert(solve(s, false)==1);
  free(s);

  //Valid Board Size and Hawk
  strcpy(str, "B-AB-AC");
  s = str2state(str);
  assert(s);
  assert(solve(s, false)==1);
  free(s);

  //Checkered Board
  strcpy(str, "X-XOX-OXO-XOX");
  s = str2state(str);
  assert(s);
  assert(solve(s, false)==6);
  free(s);

  //Single Letter Occurence
  strcpy(str, "A-BAB-BDB-BAB");
  s = str2state(str);
  assert(s);
  assert(solve(s, false)==2);
  free(s);

  //Returns NULL from invalid dimensions
  strcpy(str, "A-ABC-BC-ABC-CBA");
  s = str2state(str);
  assert((s) == NULL);
  free(s);

  //Returns NULL from Invalid Hawk
  strcpy(str, "ABC-ABC-ABC-CBA");
  str2state(str);
  assert((s) == NULL);
  free(s);

  strcpy(str, "AB-ABC-ABC-ABC-CBA");
  str2state(str);
  assert((s) == NULL);
  free(s);

  //Returns NULL from no board
  strcpy(str, "A-");
  str2state(str);
  assert((s) == NULL);
  free(s);
}


