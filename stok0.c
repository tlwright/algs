#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *xstrtok_r(char *s, const char *delim, char **ptrptr) {
  /*
    If s, set tmp to s else set tmp to *ptrptr.
    Find any char in delim in tmp, change it to NULL,
    set *ptrptr to char after delim(s) (or NULL), return *ptrptr.

    ret = strtok_r(s, delim, ptrptr) where s = ",,,abc,,,def,,,ghi,,,", 
    delim = ",":
    *ret = 'abc',  **ptrptr = ',,def,,,ghi,,,' 
    *ret = 'def',  **ptrptr = ',,ghi,,,'
    *ret = 'ghi',  **ptrptr = ',,'
    *ret = (null), **ptrptr = ',,' 
  */

  int dcnt = 0, tcnt = 0;
  char *sp1 = s ? s : *ptrptr;
  char *sp2 = sp1;
  char *dp = (char *) delim;

  /* look for: delimiter (skip them), non-delimiter/token, delimiter */
  while(*sp2) {
    while(*dp) { 
      if(*dp == *sp2) break;
      dp++;
    }  /* end while(*dp) */ 

    if (*dp) { /* found a delimiter */
      if (tcnt) { /* delimiter after a token */
	*sp2 = 0;
	*ptrptr = sp2 + 1;
	return sp1;
      }
      dcnt++;
    } else { /* found non-delimiter */
      if (!tcnt && dcnt) { /* first token after delimiter */
	sp1 = sp2; 
      }
      tcnt++;
    }
    dp = (char *) delim;
    sp2++;
  } /* end while(*sp2) */
  *ptrptr = tcnt ? sp2 : *ptrptr;;
  return (*sp1 && tcnt) ? sp1: NULL;
}

int main(int argc, char *argv[]) {
  char **ptrptr, *ptr, *ptr2;

  if (argc != 3) {
    printf("%s delim(s)-in-quotes phrase-in-quotes\n", argv[0]);
    return 0;
  }

  ptr2 = malloc(strlen(argv[2]) + 1);

  strcpy(ptr2, argv[2]);
  ptr = strtok_r(ptr2, argv[1], ptrptr);
  while (ptr) {
    printf("ptr %p *ptr '%s', *ptrptr %p **ptrptr '%s'\n", 
	   ptr, ptr, *ptrptr, *ptrptr);
    ptr = strtok_r(NULL, argv[1], ptrptr);
  }
  printf("ptr %p *ptr '%s', *ptrptr %p **ptrptr '%s'\n\n", 
	 ptr, ptr, *ptrptr, *ptrptr);

  strcpy(ptr2, argv[2]);
  ptr = xstrtok_r(ptr2, argv[1], ptrptr);
  while (ptr) {
    printf("ptr %p *ptr '%s', *ptrptr %p **ptrptr '%s'\n", 
	   ptr, ptr, *ptrptr, *ptrptr);
    ptr = xstrtok_r(NULL, argv[1], ptrptr);
  }
  printf("ptr %p *ptr '%s', *ptrptr %p **ptrptr '%s'\n", 
	 ptr, ptr, *ptrptr, *ptrptr);
  
  free(ptr2);
  return 0;
}
