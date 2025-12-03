#include "mydefs.h"

#define MAXSTR (BRDSZ*BRDSZ+BRDSZ+2)

int main(void)
{

char str[MAXSTR];
  state* s;

  strcpy(str, "");
  s = str2state(str);
  assert(s == NULL);
  free(s);

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

   //additional tests
   
   strcpy(str, "A-ABC-ABC-ABC-CBA");
   s = str2state(str);
   assert(s);
   assert(solve(s, true)==2);
   free(s);

   assert(file2str("tests/0moves.brd", str));
   assert(strcmp("A-B", str)==0);
   s = str2state(str);
   assert(s);
   assert(solve(s, false)==0);
   free(s);

   assert(file2str("tests/4moves.txt", str));
   assert(strcmp("O-COMS-COMS-COMS-CMMS-CSSO", str)==0);
   s = str2state(str);
   assert(s);
   assert(solve(s, false)==4);
   free(s);

   assert(file2str("tests/imposs.brd", str));
   assert(strcmp("A-BC-DE", str)==0);
   s = str2state(str);
   assert(solve(s, false)==-1);
   free(s);

   assert(file2str("tests/10moves.brd", str));
   s = str2state(str);
   assert(solve(s, false)==10);
   free(s);

   assert(file2str("tests/9moves.brd", str));
   s = str2state(str);
   assert(solve(s, false)==9);
   free(s);

   assert(file2str("tests/11moves.brd", str));
   s = str2state(str);
   assert(solve(s, false)==11);
   free(s);

   return EXIT_SUCCESS;
}
