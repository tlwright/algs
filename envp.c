#include <stdio.h>
int main (int argc, char *argv[], char *envp[]) {
  int idx = 0;

  for (idx = 0; envp[idx]; idx++) 
    printf("envp[%d] = %s\n", idx, envp[idx]);
 
  return 0;
}
