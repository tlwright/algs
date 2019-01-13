#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int in, diff, lo = 0, hi = 5; /* array max = 5 */
  int x[] = {3, 4, 5, 7, 50, 100}; /* sorted list */ 

  if (argc != 2) {
    printf("%s num\n", argv[0]);
    return 0;
  }
  for (in = 0; in <= hi; in++) printf("%d ", x[in]); /* print array */
  printf("\n");
  in = atoi(argv[1]); /* get sum */
  diff = in - x[lo];
  while (diff < x[hi]) {
    printf("%d + %d = %d\n", x[lo], x[hi], x[lo] + x[hi]);
    hi--;
  }
  while (diff != x[hi] && lo != hi) {
    hi = 5;
    diff = in - x[++lo];
    while (diff < x[hi]) {
      printf("%d + %d = %d\n", x[lo], x[hi], x[lo] + x[hi]);
      hi--;
    }
  }
  if (diff == x[hi]) printf("%d + %d = %d\n", x[lo], x[hi], in);
  else printf("no 2 numbers found whose sum = %d\n", in);
  return 0;
}
