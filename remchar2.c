#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen, strcpy */

/* 
   given two char strings src and rem, remove chars in rem from src. 
   given "hello there" "eo", result is "hll thr".
*/

int main (int argc, char *argv[]) {
  int idx1, idx2;
  char a[256] = {0};
  char *sp;

  if (argc != 3) {
    printf("%s src-string rem-string\n", argv[0]);
    return 1;
  }

  /* enter string char counts into an array indexed by the char */
  for (idx1 = 0; argv[2][idx1]; idx1++) {
    a[ (int) argv[2][idx1] ]++;
  }

  /* copy argv[1] so we can change it */
  sp = strdup(argv[1]);
  if (!sp) {
    printf("strdup failed\n");
    exit (1);
  }

  /* copy chars with a count of 0 */
  for (idx1 = 0, idx2 = 0; sp[idx1]; idx1++) {
    if (a[ (int) sp[idx1] ] == 0) {
      sp[idx2++] = sp[idx1];
    }
  }
  sp[idx2] = 0;

  printf("original string is '%s', remove-chars is '%s'\n", argv[1], argv[2]);
  printf("updated string is '%s'\n", sp);
  return 0;
}
