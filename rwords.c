#include <stdio.h>
#include <string.h>

void rstr(char str[], int st, int end) {
  /*  char tmp; */
  while(end > st) {
    str[st] ^= str[end];
    str[end] ^= str[st];
    str[st++] ^= str[end--];
    /* tmp = str[st];
    str[st++] = str[end];
    str[end--] = tmp; */
  }
}

void rwords(char str[]) {
  int st = 0, end = 0, len = strlen(str);

  rstr(str, st, len - 1); /* the whole thing */
  while (end < len) {
    if (str[end] != ' ') {
      st = end; /* move to next word */
      while (end < len && str[end] != ' ') /* find end of word */
	end++;
      end--;
      rstr(str, st, end); /* each word */
    }
    end++;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("%s phrase in quotes\n", argv[0]);
    return 0;
  }
  rwords(argv[1]);   /* reverse the 1st arg: phrase in quotes*/
  printf(argv[1]);
  return 0;
}
