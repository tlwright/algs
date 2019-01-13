/*
  write code to print just unique words...
  given ab cd ef ab cd, just print ab cd and ef
*/
 
#include <stdio.h>
#include <string.h>

int myhash(char * word) {
  int j, val = 0;
  int len = strlen(word);
  
  for (j = 0; j < len; j++) {
    val += word[j];
  }
  
  return val;
}

/* 
   from http://www.isthe.com/chongo/tech/comp/fnv/
    hash = offset_basis
    for each octet_of_data to be hashed
      // swap next two lines for FNV-1a 
      hash = hash * FNV_prime
      hash = hash xor octet_of_data
    return hash

    The FNV_prime is dependent on n, the size of the hash:
      32 bit FNV_prime = 224 + 28 + 0x93 = 16777619
    The offset_basis for FNV-1 is dependent on n, the size of the hash:
      32 bit offset_basis = 2166136261
*/

unsigned long fnv1a(unsigned char *str)
{
  unsigned long hash = 2166136261U;
  while(*str!='\0') {
    hash ^= *str++;
    hash *= 16777619;
  }
  return hash;
}

/* 
   from http://fr.wikipedia.org/wiki/Table_de_hachage#Fonction_de_Hachage
*/

unsigned long hash(unsigned char *str)
{
  unsigned long hash = 5381;
  while(*str!='\0') {
    int c = *str;
    /* hash = hash*33 + c */
    hash = ((hash << 5) + hash) + c;
    str++;
  }
  return hash;
}

/*
  from The Practice of Programming: Kerninghan and Pike
*/

unsigned int kphash(char *str)
{
  unsigned int h = 0;
  unsigned char *p;

  for (p = (unsigned char *) str; *p != '\0'; p++) {
    h = 31 * h + *p;
  }
  return h;
}


int main(int argc, char * argv[]) {
#define SIZE 11  
  int i;
  char * tbl[SIZE] = {'\0','\0','\0','\0','\0', '\0','\0','\0','\0','\0'};

  for (i = 1; i < argc; i++) {
    int val = kphash(argv[i]) % SIZE;
    if (!tbl[val]) {
      printf ("%s\n", argv[i]);
      tbl[val] = argv[i];
    } else if (strcmp(tbl[val], argv[i])) 
      printf ("collision: %s and %s\n", tbl[val], argv[i]);
  }
  return 0;
}
