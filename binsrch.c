#include <stdio.h>
#include <stdlib.h>

int iterBinSrch( int array[], int size, int target) {
  int lower = 0, upper = size - 1, center;

  while( lower <= upper ) { /* DEBUG */
    center = (lower + upper)/2;

    printf("lower %d, center %d, upper %d, lower %d, center %d, upper %d\n", 
	   lower, center, upper, array[lower], array[center], array[upper]);
    if( array[lower] > array[upper] ){ /* sanity check */
      printf("Array not sorted\n");
      return -1;
    }

    if( target == array[center] ) return center;
    else if( target < array[center] ) upper = center - 1; /* eliminate upper */
    else lower = center + 1; /* eliminate lower half */
  }
  printf("Element not in array\n");
  return -1;
}

int main (int argc, char *argv[]) {
  int *intin, i, item, rc;

  if (argc < 3) {
    printf("%s item num-1 ... num-n\n", argv[0]);
    return -1;
  }

  /* create array of ints from argv */
  item = atoi(argv[1]);
  intin = calloc(argc - 2, sizeof(int));
  for (i = 0; i < argc - 2; i++) intin[i] = atoi(argv[i+2]);

  printf("item = %d, array size = %d, array = ", item, argc-2); /* show args */
  for (i = 0; i < argc - 2; i++) printf("%d ", intin[i]);
  printf("\n");

  rc = iterBinSrch(intin, argc - 2, item);
  printf("iterBinSrch(%p, %d, %d) returned %d\n", intin, argc - 2, item, rc);
  return 0;
}
