main: csv.h csv.o
	gcc main.c csv.o -o main
	./main < ../quotes.csv

csv.o: csv.h csv.c
	gcc -c csv.c -o csv.o

.PHONY: csvtest
csvtest: csvtest.c
	rm csvtest || true
	gcc csvtest.c -o csvtest
	./csvtest < ../quotes.csv
	rm csvtest

.PHONY: clean
clean:
	rm csvtest || true
	rm main || true
	rm *.o || true
