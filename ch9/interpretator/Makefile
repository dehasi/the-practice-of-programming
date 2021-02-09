.PHONY: run
run: evaluate evaluate3
	./evaluate
	./evaluate3

evaluate3: evaluate3.c eprintf.o
	@gcc evaluate3.c eprintf.o -o evaluate3

evaluate: evaluate.c eprintf.o
	@gcc evaluate.c eprintf.o -o evaluate

eprintf.o: eprintf.c
	@gcc -c eprintf.c -o eprintf.o

.PHONY: clean
clean:
	@rm evaluate3 evaluate *.o || true
