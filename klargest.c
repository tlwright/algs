/* find k largest ints in array */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free, qsort */

int cmp(const void *x, const void *y) {
  const int *xx = x, *yy = y;

  return *yy - *xx; /* reverse args for descending order */
}

int main(int argc, char *argv[]) {
  int k, i, *intin;

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
  qsort(intin, argc-2, sizeof(int), cmp); /* qsort(*base, nmemb, size, cmp); */
  for (i = 0; i < argc - 2; i++) printf("%d ", intin[i] ); putchar('\n');
  for (i = 0; i < k; i++) printf("%d ", intin[i] ); putchar('\n');
  return 0;
}
