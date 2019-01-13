#define _POSIX_MAPPED_FILES
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

void * mymalloc (size_t size) {
  void * p;

  p = mmap(0, size, PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
  return ((int) p == -1) ? NULL : p; 
}

void myfree (void * addr, size_t size) {
  int p;

  p = munmap(addr, size);
  if (p == -1) printf("myfree failed\n");
}

int main() {
  void *p;

  p = mymalloc(1024);
  if (!p) printf("mymalloc failed\n");
  else myfree(p, 1024);
  return 0;
}
