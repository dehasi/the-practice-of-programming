main: main.cpp csv.o
	g++ main.cpp csv.o -o main
	./main < ../quotes.csv

csv.o: csv.cpp csv.h
	g++ -c csv.cpp -o csv.o

.PHONY: clean
clean:
	rm main || true
	rm *.o || true
