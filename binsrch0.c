#include <stdio.h>
#include <stdlib.h>

int iterBinSrch( int array[], int size, int target) {
  int lower = 0, upper = size - 1, center, range, i;

  printf("item = %d, array size = %d, array = ", target, size); /* show args */
  for (i = 0; i < size; i++) printf("%d ", array[i]);
  printf("\n");

  while( 1 ){
    if( lower > upper ){ /* sanity check */
      printf("Limits reversed\n");
      return -1;
    }    
    range = upper - lower;
    printf("upper %d, lower %d, range %d, center %d\n", /* DEBUG */
	   upper, lower, range, center);
    if( range == 0 && array[lower] != target ){
      printf("Element not in array\n");
      return -1;
    }
    if( array[lower] > array[upper] ){ /* sanity check */
      printf("Array not sorted\n");
      return -1;
    }
    center = ((range)/2) + lower;
    if( target == array[center] ) return center;
    else if( target < array[center] ) upper = center - 1; /* eliminate upper */
    else lower = center + 1; /* eliminate lower half */
  }
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

  rc = iterBinSrch(intin, argc - 2, item);
  printf("iterBinSrch(intin, item) returned %d\n", rc);
  return 0;
}
