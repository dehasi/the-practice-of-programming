strings: strings.c strings.h eprintf.o
	gcc strings.c eprintf.o -o strings
	./strings eprintf.o blabla

eprintf.o: ../ch4/4.7_eprintf/eprintf.h ../ch4/4.7_eprintf/eprintf.c
	gcc -c ../ch4/4.7_eprintf/eprintf.c -o eprintf.o

.PHONY: clean
clean:
	rm strings || true
	rm *.o || true
