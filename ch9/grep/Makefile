.PHONY: run
run: grep
	#./grep '^#include' *.c *h blabla.c
	cat test.txt | ./grep 'aa*'

grep: grep.c eprintf.o
	@gcc grep.c eprintf.o -o grep

eprintf.o: eprintf.c
	@gcc -c eprintf.c -o eprintf.o

.PHONY: clean
clean:
	@rm grep *.o || true
