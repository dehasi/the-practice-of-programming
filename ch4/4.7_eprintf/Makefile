main: eprintf.o
	gcc main.c eprintf.o -o main
	./main

eprintf.o: eprintf.h eprintf.c
	gcc -c eprintf.c -o eprintf.o


.PHONY: clean
clean:
	rm main || true
	rm *.o || true
