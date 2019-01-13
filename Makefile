CC       = gcc
CPP	 = g++
CFLAGS   = -Wall -g
INC_DIR  = -I.
EXEC     = hash hash1 crc crct crcr hsort ll hamming bst qsort isort recurprt \
	   stok stok0 prodcon rwords xorxchg llsort dlsort cisco cisco1 \
	   envp animal treelist fact fib twonums twonumsdiff twonumshash \
	   remchar q bstq stk bststk hsearch hsearchr bst0 bst0a bst0b bst1 \
	   bst2 bst2a bst2b qcpp stkcpp bstcpp sudoku llt stkt llcyclic \
	   llmtolast fact2 fib1 fib2 fib3 binsrch endian klargest klargest2 \
	   mymalloc ciscoiter hash2 remchar2 twonumshash2 cisco2
% : %.c
	$(CC) $(CFLAGS) $(INC_DIR) -o $@ $<
% : %.cc
	$(CPP) $(CFLAGS) $(INC_DIR) -o $@ $<

all:    $(EXEC)

prodcon: prodcon.c
	$(CC) $(CFLAGS) $(INC_DIR) -pthread -o $@ $<

clean:
	rm -f *.core *~ *.o $(EXEC)
