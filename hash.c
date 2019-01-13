/*
  write code to print just unique words...
  given ab cd ef ab cd, just print ab cd and ef
*/
 
#include <stdio.h>
#include <string.h>
#define SIZE 11  

int myhash(char * word) {
  int j, val = 0;
  int len = strlen(word);
  
  for (j = 0; j < len; j++) {
    val += word[j];
  }
  
  return val;
}

int main(int argc, char * argv[]) {
  int i;
  char * tbl[SIZE] = {'\0','\0','\0','\0','\0', '\0','\0','\0','\0','\0'};

  for (i = 1; i < argc; i++) {
    int val = myhash(argv[i]) % SIZE;
    if (!tbl[val]) {
      printf ("%s\n", argv[i]);
      tbl[val] = argv[i];
    } else if (strcmp(tbl[val], argv[i])) 
      printf ("collision: %s and %s\n", tbl[val], argv[i]);
  }

  return 0;
}
