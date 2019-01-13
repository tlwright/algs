#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *xstrtok_r(char *s, const char *delim, char **ptrptr) {
  /*
    1st call has s pointing to string,
    subsequent calls have s = null so ptrptr is used

    If s, set sp1 to s else set sp1 to *ptrptr.
    Find any char in delim in sp1, change it to NULL,
    set *ptrptr to char after delim(s) (or NULL), return *ptrptr.

    ret = strtok_r(s, delim, ptrptr) where s = ",,,abc,,,def,,,ghi,,,", 
    delim = ",":
    *ret = 'abc',  **ptrptr = ',,def,,,ghi,,,' 
    *ret = 'def',  **ptrptr = ',,ghi,,,'
    *ret = 'ghi',  **ptrptr = ',,'
    *ret = (null), **ptrptr = ',,' 
  */

  int dcnt = 0, tcnt = 0; /* delim cntr, token cntr */
  char *sp1 = s ? s : *ptrptr;
  char *sp2, *dp;

  /* look for: delimiter (skip them), non-delimiter/token, delimiter */
  for(dp = (char *) delim, sp2 = sp1; *sp2; dp = (char *) delim, sp2++) {
    for( ; *dp; dp++) { /* test each char in delim */
      if(*dp == *sp2) break; /* found a delimiter */
    }  /* end for(*dp) */ 

    if (*dp) { /* found a delimiter */
      if (tcnt) { /* delimiter after a token */
	*sp2 = 0; /* set delim to null */
	*ptrptr = sp2 + 1; /* next token */
	return sp1; /* token */
      }
      dcnt++;
    } else { /* found non-delimiter/token */
      if (!tcnt && dcnt) { /* first token after delimiter */
	sp1 = sp2; /* save ptr */
      }
      tcnt++;
    }
  } /* end for(*sp2) */
  if (tcnt) *ptrptr = sp2; /* *ptrptr = tcnt ? sp2 : *ptrptr; next token */
  return (*sp1 && tcnt) ? sp1: NULL; /* next token or null if no more tokens */
}

int main(int argc, char *argv[]) {
  char **ptrptr, *ptr, *ptr2;

  if (argc != 3) {
    printf("%s delim(s)-in-quotes phrase-in-quotes\n", argv[0]);
    return 0;
  }

  ptr2 = malloc(strlen(argv[2]) + 1);

  strcpy(ptr2, argv[2]);
  for (ptr = strtok_r(ptr2, argv[1], ptrptr); ptr; 
       ptr = strtok_r(NULL, argv[1], ptrptr)) {
    printf("ptr %p *ptr '%s', *ptrptr %p **ptrptr '%s'\n", 
	   ptr, ptr, *ptrptr, *ptrptr);
  }
  printf("ptr %p *ptr '%s', *ptrptr %p **ptrptr '%s'\n\n", 
	 ptr, ptr, *ptrptr, *ptrptr);

  strcpy(ptr2, argv[2]);
  for (ptr = xstrtok_r(ptr2, argv[1], ptrptr); ptr; 
       ptr = xstrtok_r(NULL, argv[1], ptrptr)) {
    printf("ptr %p *ptr '%s', *ptrptr %p **ptrptr '%s'\n", 
	   ptr, ptr, *ptrptr, *ptrptr);
  }
  printf("ptr %p *ptr '%s', *ptrptr %p **ptrptr '%s'\n", 
	 ptr, ptr, *ptrptr, *ptrptr);
  
  free(ptr2);
  return 0;
}
