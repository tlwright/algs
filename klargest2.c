/* find k largest ints in array */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free, qsort */

// Finds k largest positive, non-zero integers. Assumes list length >= k.
int *findMaxK(int list[], int len, int k) {
  // Sorted (ascending) list of results.
  int i, j, t, *r = calloc(k, sizeof(int));

  for(i = 0; i < len; i++) {
    if(list[i] > r[0]) {
      // Current number is bigger than the smallest of the preliminary results,
      // insert this new number into the list, keeping it sorted.
      r[0] = list[i];
      for(j = 1; j < k && r[j-1] > r[j]; j++) {
	// Swap r[j-1] with r[j]
	t = r[j]; r[j] = r[j-1]; r[j-1] = t;
      }
    }
  }
  return r;
}

int main(int argc, char *argv[]) {
  int k, i, *intin, *maxk;

  if (argc < 3) {
    printf("%s k n1 n2 ...", argv[0]);
    return -1;
  }
  k = atoi(argv[1]);
  if (k > (argc - 2)) {
    printf("%s k n1 n2 ...", argv[0]);
    printf("k=%d, argc - 2 = %d\n", k, argc - 2);
    return -1;
  }
  /* create array of ints from argv */
  intin = calloc(argc - 2, sizeof(int));
  for (i = 0; i < argc - 2; i++) intin[i] = atoi(argv[i+2]);
  maxk = findMaxK(intin, argc - 2, k);
  for (i = 0; i < k; i++) printf("%d ", maxk[i] ); putchar('\n');
  return 0;
}
