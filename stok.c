#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *xstrtok_r(char *s, const char *delim, char **ptrptr) {
  /*
    1st call has s pointing to string,
    subsequent calls have s = null so ptrptr is used

    If s, set sp1 to s else set sp1 to *ptrptr.
    Find any char in delim in sp1, change it to NULL,
    set *ptrptr to char after delim(s) (next token or NULL)
    return ptr to current token.

    ret = strtok_r(s, delim, ptrptr) where s = ",,,abc,,,def,,,ghi,,,", 
    delim = ",":
    *ret = 'abc',  **ptrptr = ',,def,,,ghi,,,' 
    *ret = 'def',  **ptrptr = ',,ghi,,,'
    *ret = 'ghi',  **ptrptr = ',,'
    *ret = (null), **ptrptr = ',,' 
  */

  /* NOTE: consider storing delim in char array for easier detection:
     see remchar2.c */

  int dcnt = 0, tcnt = 0; /* init delim cntr, token cntr */
  char *sp1 = s ? s : *ptrptr; /* set string ptr based on s */
  char *sp2, *dp; /* next token ptr, delim ptr */

  /* look for: any delimiter (skip them), non-delimiter/token, delimiter */
  for(dp = (char *) delim, sp2 = sp1; /* init dp and sp2 */
      *sp2; /* while sp2 not null */
      dp = (char *) delim, sp2++) { /* reset delim ptr, inc sp2 */
    for( ; *dp; dp++) { /* test current char for each char in delim */
      if(*dp == *sp2) break; /* found a delimiter */
    }  /* end for(*dp) */ 

    /* Each char is either a delim or a token (non-delim). Count: dcnt, tcnt.
       If delim and !tcnt, do nothing.
       If delim and tcnt, set delim to null (end of current token), break.
       If token and !tcnt (1st) and dcnt (after delim), save token ptr in sp1.
       If token and tcnt (not 1st) or !dcnt (not after delim), do nothing. */

    if (*dp) { /* found a delimiter */
      if (tcnt) { /* delimiter after a token */
	*sp2++ = 0; /* set delim to null, bump ptr to next char */
	break; /* *ptrptr set below to NEXT token */
      }
      dcnt++;
    } else { /* found non-delimiter/token */
      if (!tcnt && dcnt) { /* first token after delimiter */
	sp1 = sp2; /* save ptr to be returned */
      }
      tcnt++;
    }

  } /* end for(*sp2) */

  if (tcnt) *ptrptr = sp2; /* NEXT token */
  return (*sp1 && tcnt) ? sp1: NULL; /* CURRENT token or null if no more */
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
